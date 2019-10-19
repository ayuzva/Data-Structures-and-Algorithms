#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;
using std::max;

int lcs2(vector<int>& a, vector<int>& b) {
	vector<vector<int>> common;
	int maximum;

	for (int n = 0; n < a.size() + 1; n++) {
		vector<int> help;
		for (int m = 0; m < b.size() + 1; m++) {
				help.push_back(0);
			help.push_back(0);
		}
		common.push_back(help);
	}


	for (int i = 1; i < a.size() + 1; i++) 
		for (int j = 1; j < b.size() + 1; j++) {
			if (a[i-1] == b[j-1]) {
				maximum=max(max(common[i-1][j]-1, common[i][j-1]-1), common[i-1][j-1])+1;
				if (maximum < 0) {
					common[i][j] = 0;
				}
				else {
					common[i][j] = maximum;
				}
			}
			else {
				maximum=max(max(common[i-1][j], common[i][j-1]), common[i-1][j-1]);
				if (maximum < 0) {
					common[i][j] = 0;
				}else {
					common[i][j] = maximum;
				}
			}
		}

	return common[a.size()][b.size()];
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n);

	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	size_t m;
	std::cin >> m;
	vector<int> b(m);

	for (size_t i = 0; i < m; i++) {

		std::cin >> b[i];
	}

	std::cout << lcs2(a, b) << std::endl;
	
	return 0;
}
