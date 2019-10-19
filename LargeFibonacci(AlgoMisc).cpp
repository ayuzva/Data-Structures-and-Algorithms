#include <iostream>
#include <vector>

using namespace std;

int get_fibonacci_last_digit_naive(int n) {
	if (n <= 1)
		return n;

	int previous = 0;
	int current = 1;

	for (int i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
	vector<int> FibList(n + 1);

	FibList[0] = 0;
	if (n > 0)
		FibList[1] = 1;

	for (int i = 2; i <= n; ++i) {
		FibList[i] = (FibList[i - 1] + FibList[i - 2])%10;
	}

	return FibList[n];
}


int main() {
	int n;
	cin >> n;
	//int c = get_fibonacci_last_digit_naive(n);
	//Native algorithm does not actually work for big numbers, while fast does
	//cout << c << '\n';
	cout << get_fibonacci_last_digit_fast(n) << endl;
}
