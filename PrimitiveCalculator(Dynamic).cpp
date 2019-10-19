#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> dp_table(int n) {
	int result;
	int number;

	int prevsteps;

	vector<int> table;

	table.push_back(-1);
	table.push_back(0);

	for(int i = 2; i < n+1; i++) {
		//vector<int> help;//not used anywhere
		result = i - 1;
		prevsteps = table[result];

		if (i % 2 == 0 && table[i / 2] < prevsteps){
			result = i / 2;
			prevsteps = table[result];
		}
		if (i % 3 == 0 && table[i / 3] < prevsteps) {
			result = i / 3;
			prevsteps = table[result];
		}
		number = prevsteps + 1; //calc number of operations from 1

		table.push_back(number);
	}
	return table;
}

int dynamic_optimal_sequence(int n, vector<int> &lookup_table, vector<int> &sequence) {
	int minimal_candidate;
	int steps;
	
	steps = lookup_table[n - 1];
	minimal_candidate = n-1;
	
	if (n % 2 == 0 && lookup_table[n / 2] < steps) {
		steps = lookup_table[n / 2];
		minimal_candidate = n/2;
	}
	if (n % 3 == 0 && lookup_table[n / 3] < steps) {
		steps = lookup_table[n / 3];
		minimal_candidate = n/3;
	}
	if(minimal_candidate != 1)
		sequence.push_back(dynamic_optimal_sequence(minimal_candidate, lookup_table, sequence));

	return minimal_candidate;
}

/*vector<int> optimal_sequence(int n) {
	std::vector<int> sequence;
	
	while (n >= 1) {
		sequence.push_back(n);
		if (n % 3 == 0) {
			n /= 3;
		}
		else if (n % 2 == 0) {
			n /= 2;
		}
		else {
			n = n - 1;
		}
	}
	
	reverse(sequence.begin(), sequence.end());
	
	return sequence;
}*/

int main() {
	int n;
	std::cin >> n;

	vector<int>table = dp_table(n);
	vector<int> sequence;

	if (n == 1) {
		std::cout << "0" << std::endl;
		std::cout << "1";
		return 0;
	}

	sequence.push_back(dynamic_optimal_sequence(n,table,sequence));
	sequence.push_back(n);
	std::cout << sequence.size()-1 << std::endl;
	
	for (size_t i = 0; i < sequence.size(); ++i) {
		std::cout <<  sequence[i]<< " ";
	}
	return 0;
}
