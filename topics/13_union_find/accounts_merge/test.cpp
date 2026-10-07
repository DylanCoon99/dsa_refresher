#include <accounts_merge.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

namespace {
using Accounts = std::vector<std::vector<std::string>>;

// Rows may come back in any order; compare after sorting the rows.
Accounts sorted(Accounts rows) {
    std::sort(rows.begin(), rows.end());
    return rows;
}

// Brute force: keep merging any two groups that share an email until no pair does.
Accounts brute(const Accounts& accounts) {
    struct Group {
        std::string name;
        std::set<std::string> emails;
    };
    std::vector<Group> groups;
    for (const auto& a : accounts) groups.push_back({a[0], std::set<std::string>(a.begin() + 1, a.end())});
    bool changed = true;
    while (changed) {
        changed = false;
        for (std::size_t i = 0; i < groups.size() && !changed; ++i)
            for (std::size_t j = i + 1; j < groups.size() && !changed; ++j) {
                bool share = false;
                for (const auto& e : groups[i].emails) share = share || groups[j].emails.count(e) > 0;
                if (share) {
                    groups[i].emails.insert(groups[j].emails.begin(), groups[j].emails.end());
                    groups.erase(groups.begin() + static_cast<long>(j));
                    changed = true;
                }
            }
    }
    Accounts rows;
    for (const auto& g : groups) {
        std::vector<std::string> row{g.name};
        row.insert(row.end(), g.emails.begin(), g.emails.end());  // std::set iterates in ascending order
        rows.push_back(row);
    }
    return sorted(rows);
}
}  // namespace

TEST_CASE("examples") {
    CHECK(sorted(accountsMerge({{"A", "a@x", "b@x"}, {"B", "c@x"}, {"A", "b@x", "d@x"}})) ==
          sorted({{"A", "a@x", "b@x", "d@x"}, {"B", "c@x"}}));
    CHECK(sorted(accountsMerge({{"A", "a@x"}, {"A", "b@x"}})) == sorted({{"A", "a@x"}, {"A", "b@x"}}));
    CHECK(sorted(accountsMerge({{"A", "a@x", "a@x", "b@x"}})) == sorted({{"A", "a@x", "b@x"}}));
}

TEST_CASE("edge cases") {
    SUBCASE("two people with the same name stay separate") {
        CHECK(sorted(accountsMerge({{"John", "j1@m", "j2@m"}, {"John", "j3@m"}, {"Mary", "m@m"}})) ==
              sorted({{"John", "j1@m", "j2@m"}, {"John", "j3@m"}, {"Mary", "m@m"}}));
    }
    SUBCASE("transitive merge A-B shares one email, B-C shares another") {
        CHECK(sorted(accountsMerge({{"Ann", "a@m", "b@m"}, {"Ann", "c@m", "d@m"}, {"Ann", "b@m", "c@m"}})) ==
              sorted({{"Ann", "a@m", "b@m", "c@m", "d@m"}}));
    }
    SUBCASE("transitive merge where the middle account comes last") {
        CHECK(sorted(accountsMerge({{"Ann", "a@m", "b@m"}, {"Ann", "c@m", "d@m"}, {"Bob", "z@m"}, {"Ann", "b@m", "c@m"}})) ==
              sorted({{"Ann", "a@m", "b@m", "c@m", "d@m"}, {"Bob", "z@m"}}));
    }
    SUBCASE("a single account with duplicate emails") {
        CHECK(sorted(accountsMerge({{"Zed", "b@m", "a@m", "b@m", "a@m"}})) == sorted({{"Zed", "a@m", "b@m"}}));
    }
    SUBCASE("emails come back sorted") {
        CHECK(sorted(accountsMerge({{"Q", "c@m", "a@m"}, {"Q", "b@m", "c@m"}})) == sorted({{"Q", "a@m", "b@m", "c@m"}}));
    }
    SUBCASE("a chain merges only through shared emails") {
        CHECK(sorted(accountsMerge({{"K", "1@m"}, {"K", "1@m", "2@m"}, {"K", "2@m", "3@m"}, {"K", "9@m"}})) ==
              sorted({{"K", "1@m", "2@m", "3@m"}, {"K", "9@m"}}));
    }
    SUBCASE("a single account with a single email") {
        CHECK(sorted(accountsMerge({{"Solo", "s@m"}})) == sorted({{"Solo", "s@m"}}));
    }
}

TEST_CASE("randomized vs repeated merging") {
    const std::vector<std::string> names{"A", "B", "C"};
    for (int trial = 0; trial < 300; ++trial) {
        // Email i belongs to name i % 3, so no email is ever listed under two names.
        int pool = rand_int(3, 12);
        int count = rand_int(1, 8);
        Accounts accounts;
        for (int i = 0; i < count; ++i) {
            int who = rand_int(0, 2);
            std::vector<std::string> row{names[who]};
            int k = rand_int(1, 4);
            for (int j = 0; j < k; ++j) {
                int e = rand_int(0, pool - 1);
                e = e - e % 3 + who;  // an email index owned by this name
                if (e >= pool) e = who;  // who < 3 <= pool, so this stays in range
                row.push_back("e" + std::string(e < 10 ? "0" : "") + std::to_string(e) + "@m");
            }
            accounts.push_back(row);
        }
        CHECK(sorted(accountsMerge(accounts)) == brute(accounts));
    }
}
