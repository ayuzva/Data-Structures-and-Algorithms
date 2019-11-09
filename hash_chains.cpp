#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::string;
using std::vector;
using std::cin;
using std::list;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count; //the m value staright from input
    // store all strings in one vector
    vector<list<string>> hash_table;
	list<string>::iterator to_delete;

    size_t hash_func(const string& s) const {//hash function will not modify the object because static
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;//returns iterator
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
		this->hash_table.resize(bucket_count);
	} //sets bucket count

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

	void check(const Query& query) {
		// use reverse order, because we append strings to the end
		if (hash_table[query.ind].size() > 0) {
			list<string>::iterator i;
			for (i=hash_table[query.ind].begin(); i != hash_table[query.ind].end(); i++) {//Reversed
				std::cout << *i << " ";
			}
		}
		else {
			//just output a blank line, might have to be adjusted after
		}
	}

	bool find(const Query& query) {
		list<string>::iterator i;
		if (hash_table[hash_func(query.s)].empty() == false) {
			for (i = hash_table[hash_func(query.s)].begin(); i != hash_table[hash_func(query.s)].end(); ++i) {
				if (*i == query.s) {
					this->to_delete = i;
					return true;
				}
				else if (std::next(i) == hash_table[hash_func(query.s)].end()) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}

	void add(const Query& query) {
		if (find(query) == false) {
			hash_table[hash_func(query.s)].push_front(query.s);
		}
	}
	void del(const Query& query) {
		if (find(query) == true) {
			hash_table[hash_func(query.s)].erase(this->to_delete);
		}
	}

    void processQuery(const Query& query) {//Called for every query
		if (query.type == "check") {//Check if content of ith list in the table, if yes print
			check(query);
			std::cout << "\n";
        }else if (query.type == "find") {
			std::cout << (find(query) ? "yes" : "no");
			std::cout << "\n";
		}else if (query.type == "add") {//Adds string into the table, if exists ignore
			add(query);
        }else if (query.type == "del") {
			del(query);
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();//This is where the magic happens
    return 0;
}
