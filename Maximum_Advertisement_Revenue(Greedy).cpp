#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b) {
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());

	long long result = 0;

	for (size_t i = 0; i < a.size(); i++) {
		result += ((long long)a[i]) * b[i];
	}
	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n), b(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];//Profit Per Click
	}
	for (size_t i = 0; i < n; i++) {
		std::cin >> b[i];//Average Number of Clicks
	}
	std::cout << max_dot_product(a, b) << std::endl;
}
