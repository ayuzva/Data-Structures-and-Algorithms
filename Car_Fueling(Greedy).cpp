#include <iostream>
#include <vector>
#include <algorithm>//used for max

using std::cin;
using std::cout;
using std::vector;
using std::max;

//-1 is impossible to reach condition
int compute_min_refills(int dist, int tank, vector<int>& stops) {
	int NumStop = 0;//Begining and End positions are not part of the vector
	int refills = 0;
	int CurrentPos = 0;

	while (CurrentPos < dist) {//We are still moving
		while (NumStop < stops.size() && (stops[NumStop] - CurrentPos) <= tank) {
			NumStop++;//Look at the next one
		}

		if (CurrentPos == stops[NumStop - 1]) {
			return - 1; //impossible
		}

		if (NumStop == stops.size() && (dist - CurrentPos) < tank) {
			CurrentPos = dist; //Arived
			return refills;
		}

		//Refueled and updated current position to last available gas station
		CurrentPos = stops[NumStop-1];
		refills++;
	}
	return refills;
}


int main() {
	int d = 0;//destintion in miles
	cin >> d;
	int m = 0;//miles on full tank
	cin >> m;
	int n = 0;//number of gas stations 0<1..<n<d
	cin >> n;

	vector<int> stops(n);//gas station distances
	for (size_t i = 0; i < n; ++i)
		cin >> stops.at(i);

	cout << compute_min_refills(d, m, stops) << "\n";

	return 0;
}
