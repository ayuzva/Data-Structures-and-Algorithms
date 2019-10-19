#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int>& a, int left, int right) {
	if (left == right) return -1; //terminating empty array call
	if (left + 1 == right) return a[left]; //terminating 1 element array call

	int m = (right + left) / 2;//floor of division

	int elem_left_sub = get_majority_element(a, left, m);
	int elem_right_sub = get_majority_element(a, m, right);//right so far, yes m is right

	if (elem_left_sub == elem_right_sub) {
		return elem_right_sub;
	}
	
	int count_left = 0, count_right = 0;

	for (left; left < right; left++) {
		if (a[left] == elem_left_sub) {
			count_left++;
		}
		if (a[left] == elem_right_sub) {
			count_right++;
		}
	}

	if (count_left > count_right) {
		return elem_left_sub;
	}
	else if (count_right > count_left){
		return elem_right_sub;
	}
	else {//if counts equal
		return -1;
	}
}

int main() {
	int n;
	int count = 0;
	std::cin >> n;
	vector<int> a(n);

	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	n = get_majority_element(a, 0, a.size());

	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] == n) {
			count++;
		}
	}

	std::cout << (count > a.size()/2) << '\n'; //If return is -1 its 0 if its not -1 its 1
	
	return 0;
}
