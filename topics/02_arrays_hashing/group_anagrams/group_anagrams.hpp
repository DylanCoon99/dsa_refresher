#pragma once
#include <array>
#include <string>
#include <vector>
#include <iostream>
//#include <cctype>
#include <unordered_map>

// Partition strs into groups of mutual anagrams. Group order and order within a group are free.
inline std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
	// TODO: implement

	std::unordered_map<std::string, std::vector<std::string>> map;

	for (auto word : strs) {
		// for each word -> build an array that 
		std::array<int, 26> word_array{}; // sets all elements to zero by default
		for (auto chr : word) {
			word_array[chr - 'a'] += 1;
		}
		// once the array is built -> create a string key with separator
		std::string key;

		key += word_array[0];

		for (int i = 1; i < static_cast<int>(word_array.size()); ++i) {
			key += ('#' + static_cast<char>(word_array[i]));
		}

		map[key].push_back(word);
	}

	// format the result
	std::vector<std::vector<std::string>> result;

	for (auto& [arr, words] : map) {
		result.push_back(words);
		std::cout << "\n";
	}
	

	return result;
}
