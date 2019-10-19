#include <iostream>
#include <vector>

using std::vector;

int partition3(vector<int>& A) {
	int sum3way=0;
	vector<vector<int>> lookup;

	for (int i = 0; i < A.size(); i++) {
		sum3way += A[i];
	}

	if (sum3way % 3 != 0)
		return 0;

	sum3way/=3;

	for (int i=0; i <= sum3way; i++) {
		vector<int> fill;
		for (int j=0; j <= A.size(); j++) {
			fill.push_back(0);
			if (i == 0) {
				fill[0] = 1;
			}
		}
		lookup.push_back(fill);
	}

	for (int i=1; i <= sum3way; i++) {
		for (int j=1; j <= A.size(); j++) {
			if ((i - A[j - 1]) < 0) {
				if(lookup[i][j - 1] == 1)
					lookup[i][j] = 1;
			}
			else if (lookup[i][j-1] == 1 || lookup[i-A[j-1]][j - 1] == 1) {
				lookup[i][j] = 1;
			}
			else{
				lookup[i][j] = 0;
			}
		}
	}

	return lookup.back().back();
}

int main() {
	int n;
	std::cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < A.size(); ++i) {
		std::cin >> A[i];
	}
	std::cout << partition3(A) << '\n';
}
