#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::stoi;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a * b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	else {
		assert(0);
	}
}


long long get_maximum_value(const string& exp) {
	long long maximum;
	long long minimum;
	vector<long long> values;
	vector<char> signs;
	vector<vector<long long>> lookupMAX;
	vector<vector<long long>> lookupMIN;

	for (int i = 0; i < exp.size(); i+=2) {
		values.push_back((int)exp[i]-48);
	}

	for (int i = 1; i < exp.size(); i += 2) {
		signs.push_back(exp[i]);
	}

	for (int i = 0; i < values.size(); i++) {
		vector<long long> fill;
		for (int j = 0; j < values.size(); j++) {
			fill.push_back(0);
			if (i == j) {
				fill[i] = values[i];
			}
		}
		lookupMAX.push_back(fill);
		lookupMIN.push_back(fill);
	}//fills both matrix diagonals 

	for (int s = 1; s < values.size(); s++) {
		for (int i = 0; i < values.size()-s; i++) {
			int j = i + s;
			for (int k = i; k < j; k++) {
				maximum = max(max(eval(lookupMAX[i][k], lookupMAX[k+1][j], signs[k]), eval(lookupMIN[i][k], lookupMAX[k+1][j], signs[k])), max(eval(lookupMAX[i][k], lookupMIN[k+1][j], signs[k]), eval(lookupMIN[i][k], lookupMIN[k+1][j], signs[k])));
				minimum = min(min(eval(lookupMAX[i][k], lookupMAX[k+1][j], signs[k]), eval(lookupMIN[i][k], lookupMAX[k+1][j], signs[k])), min(eval(lookupMAX[i][k], lookupMIN[k+1][j], signs[k]), eval(lookupMIN[i][k], lookupMIN[k+1][j], signs[k])));
				
				if (k == i) {
					lookupMAX[i][j] = maximum;
					lookupMIN[i][j] = minimum;
				}
				else {
					lookupMAX[i][j] = max(maximum, lookupMAX[i][j]);
					lookupMIN[i][j] = min(minimum, lookupMIN[i][j]);
				}	
			}
		}
	}
	return lookupMAX[0][values.size()-1];
}

int main() {
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
}
