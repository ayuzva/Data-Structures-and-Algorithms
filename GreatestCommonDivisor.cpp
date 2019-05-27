#include <iostream>
#include <cstdlib>

int gcd_naive(int a, int b) {
	int current_gcd = 1;
	for (int d = 2; d <= a && d <= b; d++) {
		if (a % d == 0 && b % d == 0) {
			if (d > current_gcd) {
				current_gcd = d;
			}
		}
	}
	return current_gcd;
}

int gcd_fast(int a, int b) {

	if(b == 0)
		return a;

	a = a % b;

	return gcd_fast(b, a);
}

int main() {
	while (1) { //stress test for good mesure
		int a, b;
		//std::cin >> a >> b;
		a = rand();
		b = rand();
		
		std::cout << gcd_naive(a, b) << std::endl;
		std::cout << gcd_fast(a, b) << std::endl;

		if (gcd_naive(a, b) != gcd_fast(a, b)) {
			std::cout << "Failed" << std::endl;
			return 0;
		}
	}
}
