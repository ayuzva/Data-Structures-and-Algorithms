#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::min;

class JobQueue {
private:
	int num_workers_;//Number of threads
	vector<int> jobs_;//Vector of jobs with their processing times

	vector<int> assigned_workers_; //Vector of asigned workers to task
	vector<long long> start_times_; //Vector or start times for tasks
	vector < pair<long long, long long>> thread_tree; //Vectore of threads .first is ID .second is Utilization

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}
	void ReadData() {
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	int parent(int c) {
		return (c - 1) / 2;
	}

	int lchild(int a) {
		return (2 * a) + 1;
	}

	int rchild(int b) {
		return (2 * b) + 2;
	}

	void SiftDown(int k) {
		int min_index = k;
		int l = lchild(k);

		if (l < thread_tree.size() && thread_tree[l].second <= thread_tree[min_index].second){
			if (thread_tree[l].second == thread_tree[min_index].second) {
				if (thread_tree[l].first < thread_tree[min_index].first)
					min_index = l;
			}else{ 
				min_index = l; 
			}
		}
			
		int r = rchild(k);
		if (r < thread_tree.size() && thread_tree[r].second <= thread_tree[min_index].second) {
			if (thread_tree[r].second == thread_tree[min_index].second) {
				if (thread_tree[r].first < thread_tree[min_index].first)
					min_index = r;
			}else{
				min_index = r;
			}
		}
		
		if (k != min_index) {
			std::swap(thread_tree[k], thread_tree[min_index]);
			SiftDown(min_index);
		}
	}

	void AssignJobsFast() {
		int l, r, next_worker;
		assigned_workers_.resize(jobs_.size()); //Cuts down the output vectors
		start_times_.resize(jobs_.size());

		thread_tree.resize(num_workers_);

		for (int j = 0; j < thread_tree.size(); j++) {
			thread_tree[j].first = j;//Thread ID
			thread_tree[j].second = (long long)0;//Next free time
		}//Now we have a heap with all nodes equal priority

		for (int i = 0; i < jobs_.size(); i++) {
			long long duration = jobs_[i];
			//l = 1;
			//r = 2;

			/*if (r < thread_tree.size() && thread_tree[0].second == thread_tree[r].second) {
				if (thread_tree[r].first < thread_tree[0].first) {//Case where r is equal to parent
					next_worker = r;
				}else {
					next_worker = 0;
				}
			}else if (l < thread_tree.size() && thread_tree[0].second == thread_tree[l].second) {
				if (thread_tree[l].first < thread_tree[0].first) {//Case where l is equal to parent
					next_worker = l;
				}
				else {
					next_worker = 0;
				}
			}else{*/
				next_worker = 0;
			//}

			assigned_workers_[i] = thread_tree[next_worker].first;
			start_times_[i] = thread_tree[next_worker].second;
			thread_tree[next_worker].second += duration;
			SiftDown(0);
	  }
  }

  void AssignJobsNaive() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobsFast();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}