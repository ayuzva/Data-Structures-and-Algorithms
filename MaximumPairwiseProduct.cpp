/*
Find the maximum product of two distinct numbers in a sequence of non-negative integers
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

//Pass by reference for faster response
int maxPairwiseProduct(const vector<int>& numbers) {
	int product = 0;
	int n = numbers.size();//length of the vector
	
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			product = max(product, numbers[i] * numbers[j]);
		}
	}

	return product;
}

int fastMaxPairwise(const vector<int>& numbers) {
	int a = 0;
	int b = 0;
	int indexFirstMax;
	int n = numbers.size();//length of the vector

	for (int i = 0; i < n; ++i) {
		if (numbers[i] > a) {
			a = numbers[i];
			indexFirstMax=i;
		}
	}

	for (int j = 0; j < n; ++j) {
		if (numbers[j] > b && j != indexFirstMax) {
			b = numbers[j];
		}
	}

	return a * b;
}

int evenFasterPairwise(const vector<int>& numbers) {
	int n = numbers.size();//length of the vector
	int a=0;
	int b=0;

	for (int i = 0; i < n; ++i) {
		if (numbers[i] > a) {
			b = a;
			a = numbers[i];
		}
	}

	return a * b;
}


int main() {
	//Stress testing two algorithms, a slower and faster
	while (1) {
		int n; //= 5;
		n = rand() % 50 + 1;
		//cin >> n;
		vector<int> numbers(n);

		cout << "Data Set : ";
		for (int i = 0; i < n; ++i) {
			numbers[i] = rand();
			//cin >> numbers[i];
			cout << numbers[i]<<" ";
		}
		cout << endl;

		//Stress Failure condition
		if (maxPairwiseProduct(numbers) != fastMaxPairwise(numbers)) {
			cout << "Failed with: " << maxPairwiseProduct(numbers)<<"      "<< evenFasterPairwise(numbers) << endl;
			return 0;
		}
	}
}
