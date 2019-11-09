#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {//Output
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {//Input
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int parent(int c) {
	  return (c-1)/ 2;
  }

  int lchild(int a) {
	  return (2*a)+1;
  }

  int rchild(int b) {
	  return (2*b)+2;
  }

  void SiftDown(int k,int n) {
	int min_index = k;
	int l = lchild(k);
	if (l < n && data_[l] < data_[min_index])
		min_index = l;
	int r = rchild(k);
	if (r < n && data_[r] < data_[min_index])
		min_index = r;
	if (k != min_index) {
		swap(data_[k], data_[min_index]);
		pair<int, int> p;
		p.first = k;
		p.second = min_index;
		swaps_.push_back(p);
		SiftDown(min_index, n);
	}
  }

  void GenerateSwapsFast() {
	int n = data_.size();
	for (int j = ((n) / 2)-1; j >= 0; j--) {
		SiftDown(j,n);	
	} 
  }

  void GenerateSwapsNaive() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

 public:
  void Solve() {
    ReadData();
    //GenerateSwapsNaive();
	GenerateSwapsFast();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();

  return 0;
}
