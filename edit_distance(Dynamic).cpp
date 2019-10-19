#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int minimum(int a, int b, int c) {
	int min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return min;
}


int edit_distance(const string& str1, const string& str2) {
	vector<vector<int>> distance;
	int insertion;
	int deletion;
	int match;
	int mismatch;

	for (int n = 0; n < str1.length()+1; n++) {
		vector<int> help;
		help.push_back(n);
		distance.push_back(help);
		for (int m = 1; m < str2.length()+1; m++) {
			if (n == 0) {
				distance[n].push_back(m);
			}
			else {
				distance[n].push_back(0);
			}
		}
	}
	
		for (int i = 1; i < str1.length()+1; i++) {
			for (int j = 1; j < str2.length() + 1; j++) {

			insertion = distance[i][j-1]+1;
			deletion = distance[i-1][j]+1;
			match = distance[i-1][j-1];
			mismatch = distance[i-1][j-1]+1;

			if (str1[i-1] == str2[j-1]) {
				distance[i][j] = minimum(insertion, deletion, match);
			}else{
				distance[i][j] = minimum(insertion, deletion, mismatch);
			}
		}
	}
	
	return distance[str1.length()][str2.length()];
}

int main() {
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}
