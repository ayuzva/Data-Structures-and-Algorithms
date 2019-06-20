#include <iostream>
#include <random>

int get_change_iterative(int m) {//Input value to be changed into coins of 1 5 and 10 
	int Coins[3] = {10,5,1};//Coin Denominations
	int i = 0;
	int n = 0;

	while (m > 0) {//Redo subproblem until solution
		while (m > 0 && Coins[i] <= m) {
			m = m - Coins[i];
			n++;
		}
		i++;//Move on to next largest denomination
	}

	return n;
}

int get_change_alternative(int m) {//Right output, technically wrong method
	//Input value to be changed into coins of 1 5 and 10 
	int n = 0;//Number of coins
	
	n = m / 10;//Greedy but "not" safe move - may not coincide with optimal solution
	m = (m % 10);
	
	n = n + m / 5;
	m = (m % 5);
	
	n = n + m / 1;
	m = (m % 1);

	return n;
}

int main() {
	while(1){//Stress testing
		int m;
		m = rand() % 100;
		//std::cin >> m;

		//std::cout << m << std::endl;

		std::cout << get_change_iterative(m) << " : " << get_change_alternative(m) << '\n';
		
		if (get_change_iterative(m) != get_change_alternative(m)) {
			std::cout << "Failed" << std::endl;
		}
	}
}
