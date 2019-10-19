#include <iostream>
#include <vector>

using std::vector;

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int minimum(int a, int b, int c) {
	int y;
	//takes 0 members out of consideration
	if (a == 0)
		a = max(b,c);
	if (b == 0)
		b = max(a,c);
	if (c == 0)
		c = max(a,b);
	

	// minimum is found between the rest
	if (a >= b)
		y = b;
	else
		y = a;

	if (y >= c)
		y = c;

	return y;
}

int get_change(int m, vector<vector<int>> &dictionary) {//for denominations 1, 3, 4
	if (m < 0) 
		return -1;
	if (m == 0)
		return 0;

	for (int i = 0; i < dictionary.size(); i++) {
		if (m == dictionary[i][0]) {
			return dictionary[i][1];
		}
	}
	
	vector<int> new_pair = {m,minimum(get_change(m - 1,dictionary)+1, get_change(m - 3,dictionary)+1, get_change(m - 4,dictionary)+1)};
	
	dictionary.push_back(new_pair);
	
	return new_pair[1];
}

int main() {
	int m;
	std::cin >> m;

	vector<vector<int>> dictionary;

	std::cout << get_change(m,dictionary) << '\n';
}
