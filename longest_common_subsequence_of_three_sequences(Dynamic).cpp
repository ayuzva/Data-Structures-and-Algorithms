#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;

int lcs3(vector<int>& a, vector<int>& b, vector<int>& c) {
	vector<vector<vector<int>>> common;
	int maximum;
	
	for (int k = 0; k < a.size() + 1; k++) {//3 dimensional monstrosity
		vector<vector<int>> help1;
		for (int n = 0; n < b.size() + 1; n++) {
			vector<int> help2;
			for (int m = 0; m < c.size() + 1; m++) {
				help2.push_back(0);
			}
			help1.push_back(help2);
		}
		common.push_back(help1);
	}

	for (int l = 1; l < a.size() + 1; l++) {
		for (int i = 1; i < b.size() + 1; i++) {
			for (int j = 1; j < c.size() + 1; j++) {
				if (a[l-1] == b[i-1] && b[i-1]== c[j-1]) {
					maximum = max(max(max(max(max(max(common[l][i][j-1]-1, common[l][i-1][j]-1), common[l][i-1][j-1]-1), common[l-1][i][j]-1), common[l-1][i][j-1]-1), common[l-1][i-1][j]-1), common[l - 1][i - 1][j - 1]) + 1;
					if (maximum < 0) {
						common[l][i][j] = 0;
					}
					else {
						common[l][i][j] = maximum;
					}
				}
				else {
					maximum = max(max(max(max(max(max(common[l][i][j-1], common[l][i-1][j]), common[l][i-1][j-1]), common[l-1][i][j]), common[l-1][i][j-1]), common[l-1][i-1][j]), common[l-1][i-1][j-1]);
					if (maximum < 0) {
						common[l][i][j] = 0;
					}
					else {
						common[l][i][j] = maximum;
					}

				}

			}
		}
	}
	return common[a.size()][b.size()][c.size()];
}

int main() {
	size_t an;
	std::cin >> an;
	vector<int> a(an);
	for (size_t i = 0; i < an; i++) {
		std::cin >> a[i];
	}
	size_t bn;
	std::cin >> bn;
	vector<int> b(bn);
	for (size_t i = 0; i < bn; i++) {
		std::cin >> b[i];
	}
	size_t cn;
	std::cin >> cn;
	vector<int> c(cn);
	for (size_t i = 0; i < cn; i++) {
		std::cin >> c[i];
	}
	std::cout << lcs3(a, b, c) << std::endl;
}
