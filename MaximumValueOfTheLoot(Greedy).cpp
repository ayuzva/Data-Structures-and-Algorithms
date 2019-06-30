#include <iostream>
#include <vector>
#include <algorithm>//sorting and min/max


using std::vector;
using std::pair;

bool sort_comp(pair<double,int> &a, pair<double, int> &b) {
	
	return (a.first > b.first);
}

double get_optimal_value(int capacity, vector<int> &weights, vector<int> &values) {
	double value = 0.0;
	double a = 0.0;
	
	vector<pair<double,int>> data;//Will contain densities & weight info

	//Calculting all densities and filling out data map
	for (int i = 0; i < weights.size(); i++) {
		data.push_back(pair<double,int>(((double)values[i] / weights[i]),weights[i]));
	}

	//Sorting all densites
	sort(data.begin(),data.end(),sort_comp);

	for (int i = 0; i < data.size(); i++) {
		if (capacity == 0) {//if backpck already full
			return value;
		}
		
		a = std::min(data[i].second, capacity);//Either take full capacity possible or all loot, which ever one is smallest
		value = value + a * data[i].first;//Update current value in bakcpack
		data[i].second -= a;//Reduce quantity of the loot
		capacity = capacity - a;//Reduce capacity of backpack
	}
	return value;
}

int main() {
	int n;
	int capacity;
	std::cin >> n >> capacity;

	vector<int> values(n);
	vector<int> weights(n);

	for (int i = 0; i < n; i++) {
		std::cin >> values[i] >> weights[i];
	}

	double optimal_value = get_optimal_value(capacity, weights, values);

	std::cout.precision(10);
	std::cout << optimal_value << std::endl;
	
	return 0;
}
