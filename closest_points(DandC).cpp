#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::min;
using std::hypot;

double get_dist(pair<int,int>& point_a, pair<int,int>& point_b) {//returns distance between two points
	return hypot((point_a.first - point_b.first), (point_a.second - point_b.second));
}

void merge(vector<pair<int,int>>& arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	vector<pair<int,int>> L(n1), R(n2);

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(vector<pair<int,int>>& arr) {//MergeSort
	int n = arr.size();
	for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			int mid = min(left_start + curr_size - 1, n - 1);

			int right_end = min(left_start + 2 * curr_size - 1, n - 1);

			merge(arr, left_start, mid, right_end);
		}
	}
}

double minimal_distance(vector<pair<int,int>>& x, vector<pair<int, int>>& y, int left, int right) {
	if (right <= left + 2) return get_dist(x[left],x[left+1]); //stop on three points remaining, return their distance
	
	double d = 0, d1, d2;
	int ave = (left+right)/2;
	
	d1 = minimal_distance(x, y, left, ave);
	d2 = minimal_distance(x, y, ave, right);

	d = min(d1,d2);//Minimum from two halves (recursion)
	
	vector<pair<int, int>> filtered;//Should contain filtered and sorted (by y) points 

	for (int i = 0; i < y.size(); i++) {
		if (abs(x[ave].first - y[i].second) < d) {//all points within the middle region
			filtered.push_back(y[i]);//Filling out filtered point vector
		}
	}

	for (int j = 0; j < filtered.size();j++) {//attempts distance calculation in the envelope
		for (int k = 1; k < 7; k++) {
			if (get_dist(y[j], y[j + k]) > d || k+1 >= filtered.size()) {
				break;
			}
			d = min(d, get_dist(y[j],y[j+k]));
		}
	}

	return d;//Minimum from two halves and across them
}

int main() {
	int n;
	std::cin >> n;
	//n = 11;
	vector<pair<int, int>> x(n), y(n);

	//int temp[11][2] = { {4,4}, {-2,-2}, {-3,-4}, {-1,3}, {2,3}, {-4,0}, {1,1}, {-1,-1}, {3,-1}, {-4,2}, {-2,4} }; //hardcoded one of the input samples for easier debugging

	for (int i = 0; i < n; i++) {
		std::cin >> x[i].first >> y[i].first;
		//Pointers to each other
		//x[i].first = temp[i][0];
		//y[i].first = temp[i][1];
		x[i].second = y[i].first;
		y[i].second = x[i].first;
	}

	merge_sort(x);//presort by x
	merge_sort(y);//presort by y

	std::cout << std::fixed;
	std::cout << std::setprecision(9) << minimal_distance(x,y, 0, x.size()) << "\n";
}