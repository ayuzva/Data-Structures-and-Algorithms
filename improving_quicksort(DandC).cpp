#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm> //for stress testing

using namespace std;
using std::vector;
using std::swap;

struct ThreeWayPartitions {//Can be done via pair or tuple, I wanted to do struct
	int m_start;
	int m_finish;
};

ThreeWayPartitions partition3(vector<int>& a, int l, int r){
	int x = a[l], m1 = l, m2 = l+1;//Should point to ends of the equal region. m1-1 is for last "less". m2+1 is for first "more element.
	ThreeWayPartitions output;

	if (l + 1 == r) { //To handle two element cases
		if (a[l] > a[r]) {
			swap(a[l], a[r]);
		}
		output.m_start = r;
		output.m_finish = r;
		return output;
	}

	for (int i = l + 1; i <= r; i++) {
		if (a[i] < x) {
			m1++;
			swap(a[m1], a[i]);
			if (m1 != m2)
				swap(a[i], a[m2]);
			m2++;
		}
		else if (a[i] == x) {
			swap(a[i], a[m2]);
			m2++;
		}
	}

	swap(a[l], a[m1]);

	output.m_start = m1+1;
	
	output.m_finish = m2-1;

	return output;
}

int partition2(vector<int>& a, int l, int r) {
	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	return j;
}

void randomized_quick_sort(vector<int>& a, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);//Random pivot
	swap(a[l], a[k]);//Move pivot to beggining of the region
	//int m = partition2(a, l, r);//Partition 2 way
	ThreeWayPartitions out = partition3(a, l, r);

	randomized_quick_sort(a, l, out.m_start-1);
	randomized_quick_sort(a, out.m_finish+1, r);
}

int main() {
	int n;
	std::cin >> n;

	vector<int> a(n);

	for (size_t i = 0; i < a.size(); ++i) {//Input
		std::cin >> a[i];
	}

	randomized_quick_sort(a, 0, a.size() - 1);//Call sorting

	for (size_t i = 0; i < a.size(); ++i) {//Output
		std::cout << a[i] << ' ';
	}
}
