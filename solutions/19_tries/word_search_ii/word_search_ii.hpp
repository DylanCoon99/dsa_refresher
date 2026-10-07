#pragma once
#include <array>
#include <string>
#include <vector>

// Approach: put all words in a trie, then DFS from every cell while descending the trie in step;
//           stop when the path is not a prefix of any word, and prune a trie branch once its words are found.
// Key insight: one board DFS guided by a trie tests all words at once and prunes dead prefixes early.
// Time: O(cells * 4 * 3^(L-1)) worst case, in practice only trie-prefix paths  Space: O(total word characters)
// Brute force: run a separate word-search DFS from every cell for every word.
inline std::vector<std::string> findWords(std::vector<std::vector<char>> board,
                                          const std::vector<std::string>& words) {
    struct Node {
        std::array<int, 26> next{};  // 0 = none (node 0 is the root and never a child)
        int word = -1;               // index of the word ending here, or -1
    };
    std::vector<Node> trie(1);
    for (int i = 0; i < static_cast<int>(words.size()); ++i) {
        int cur = 0;
        for (char ch : words[i]) {
            int& nx = trie[cur].next[ch - 'a'];
            if (nx == 0) {
                nx = static_cast<int>(trie.size());
                trie.emplace_back();  // may reallocate: do not keep `nx` across this line
            }
            cur = trie[cur].next[ch - 'a'];
        }
        trie[cur].word = i;
    }

    std::vector<std::string> out;
    const int R = static_cast<int>(board.size()), C = static_cast<int>(board[0].size());
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};

    auto dead = [&](int n) {
        if (trie[n].word >= 0) return false;
        for (int c : trie[n].next)
            if (c) return false;
        return true;
    };
    // Returns after exploring; prunes `node`'s children that became dead.
    auto dfs = [&](auto&& self, int node, int r, int c) -> void {
        char ch = board[r][c];
        board[r][c] = '#';  // visited
        if (trie[node].word >= 0) {
            out.push_back(words[trie[node].word]);
            trie[node].word = -1;  // report once, even if the list repeats it
        }
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nc < 0 || nr >= R || nc >= C || board[nr][nc] == '#') continue;
            int child = trie[node].next[board[nr][nc] - 'a'];
            if (!child) continue;
            self(self, child, nr, nc);
            if (dead(child)) trie[node].next[board[nr][nc] - 'a'] = 0;
        }
        board[r][c] = ch;
    };
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c) {
            int child = trie[0].next[board[r][c] - 'a'];
            if (!child) continue;
            dfs(dfs, child, r, c);
            if (dead(child)) trie[0].next[board[r][c] - 'a'] = 0;
        }
    return out;
}
