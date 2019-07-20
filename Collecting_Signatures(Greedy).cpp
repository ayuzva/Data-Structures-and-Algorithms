#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;
using std::max;

struct Segment {//Segment on the numberline
	int start, end;
};


bool sort_comp(Segment& a, Segment& b) {//sorting function

	return(a.end < b.end);
}

vector<int> optimal_points(vector<Segment>& segments) {
	vector<int> points;
	sort(segments.begin(),segments.end(),sort_comp);//Sort by starting point of segments 

	points.push_back(segments[0].end);

	for (int i = 0; i < segments.size(); ++i) {
		
		if (segments[i].start <= points.back()) {
			continue;
		}

		points.push_back(segments[i].end);

	}

	return points;
}

int main() {
	int n;
	std::cin >> n;
	vector<Segment> segments(n);

	for (size_t i = 0; i < segments.size(); ++i) {//Segment coordinates
		std::cin >> segments[i].start >> segments[i].end;
	}

	vector<int> points = optimal_points(segments);

	std::cout << points.size() << "\n";//How many points

	for (size_t i = 0; i < points.size(); ++i) {//coordinate
		std::cout << points[i] << " ";
	}
}
