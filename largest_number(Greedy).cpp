#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::sort;

bool Comp(string i,string j) {
	return (i+j)>(j+i);
}

string largest_number(vector<string> a) {
	sort(a.begin(),a.end(),Comp);

	//This creates the output
	std::stringstream ret;
	for (size_t i = 0; i < a.size(); i++) {
		ret << a[i];
	}
	string result;
	ret >> result;
	return result;
}

int main() {
	int n;
	std::cin >> n;
	vector<string> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	std::cout << largest_number(a);
}
