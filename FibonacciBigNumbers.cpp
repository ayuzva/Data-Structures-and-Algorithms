#include <iostream>
#include <vector>

/*
For any integer 𝑚 ≥ 2, the sequence 𝐹𝑛 mod 𝑚 is periodic. The period always
starts with 01 and is known as Pisano period.
*/

long long get_pisano_period(long long m) {
	long long a = 0, b = 1;
	long long c = a + b;

	for (int i = 0; i < m*m; i++) {
		c = (a + b) % m;
		a = b;
		b = c;
		if (a == 0 && b == 1)
			return i+1;
	}	
}

//Constraints dictate 1<n<10^8 input for Fib and <10^3 for mod so long is enough 
long long get_fibonacci_huge_fast(long long n, long long m) {
	//Using Pisano period
	long long remainder = (n % get_pisano_period(m)); //This gets us a smaller Fibonacci to calculate faster

	std::vector<long long> FibList(remainder + 1);

	FibList[0] = 0;
	if (remainder > 0)
		FibList[1] = 1;

	for (int i = 2; i <= remainder; ++i) {
		FibList[i] = (FibList[i - 1] + FibList[i - 2]) % m;
	}

	return FibList[remainder];
}

//Naive algorithm fails with big numbers, can't use for stress test
long long get_fibonacci_huge_naive(long long n, long long m) {
	if (n <= 1)
		return n;

	long long previous = 0;
	long long current = 1;

	for (long long i = 0; i < n - 1; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % m;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	//std::cout << get_fibonacci_huge_naive(n, m) << '\n';
	std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
