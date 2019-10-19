#include <iostream>
#include <vector>
#include <algorithm>

using std::max;
using std::vector;

int optimal_weight(int W, const vector<int>& w) {
	vector<vector<int>> lookup;
	
	for (int i = 0; i < W+1; i++) {
		vector<int> fill;
		for (int j = 0; j < w.size()+1; j++) {
			fill.push_back(0);
		}
		lookup.push_back(fill);
	}

	for (int i = 1; i < W+1; i++) {
		for (int j = 1; j < w.size()+1; j++) {
			if ((i - w[j-1]) >= 0) {
				lookup[i][j] = max(lookup[i - w[j - 1]][j-1] + w[j-1], lookup[i][j - 1]);
			}
			else {
				lookup[i][j] = lookup[i][j - 1];
			}
		}
	}

	return lookup[W][w.size()];

	/*
	int current_weight = 0;
	for (size_t i = 0; i < w.size(); ++i) {
		if (current_weight + w[i] <= W) {
			current_weight += w[i];
		}
	}
	return current_weight;*/
}

int main() {
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
