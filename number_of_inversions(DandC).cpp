#include <iostream>
#include <vector>

using std::vector;

int merge(vector<int>& a, vector<int>& b, size_t left, size_t ave, size_t right) {//Merge
	int inversions = 0;
	int i = 0, j = left, k = ave;

	while (j < ave && k < right) {
		if (a[j] <= a[k]) {
			b[i] = a[j];
			j++;
			i++;
		}
		else {
			b[i] = a[k];
			k++;
			i++;
			inversions=inversions+(ave-j);
		}
	}

	while (j < ave) {//copy rest of the batch
		b[i] = a[j];
		j++;
		i++;
	}
	while (k < right) {//copy rest of the batch
		b[i] = a[k];
		k++;
		i++;
	}

	for (size_t z = 0; z < i; z++) {//copy sorted elemnts to a[]
		a[left + z] = b[z];
	}

	return inversions;
}

long long get_number_of_inversions(vector<int>& a, vector<int>& b, size_t left, size_t right) {//MergeSort
	long long number_of_inversions = 0;
	if (right <= left + 1) return number_of_inversions;//on the last level,
	size_t ave = left + (right - left) / 2;

	number_of_inversions += get_number_of_inversions(a, b, left, ave);//Got to return sorted array, and number of inversions
	number_of_inversions += get_number_of_inversions(a, b, ave, right);
	number_of_inversions += merge(a, b, left, ave, right);

	return number_of_inversions;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	vector<int> b(a.size());
	std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
