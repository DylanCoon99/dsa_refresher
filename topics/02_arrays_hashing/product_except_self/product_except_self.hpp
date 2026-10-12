#pragma once
#include <vector>

// answer[i] = product of all nums[j], j != i. No division. Prefix/suffix products fit in int.
inline std::vector<int> productExceptSelf(const std::vector<int>& nums) {
	// TODO: implement

	// maps index to the product for that index
	std::vector<int> answer;

	// split each product into left and right products

	// computes the left side products for each index
	int product = 1;
	for (int i = 0; i < nums.size(); ++i) {
		answer.push_back(product);
		product *= nums[i];
	}

	// computes the right side product for each index
	product = 1;
	for (int i = nums.size() - 1; i >= 0; --i) {
		answer[i] *= product;
		product *= nums[i];
	}

	return answer;
}
