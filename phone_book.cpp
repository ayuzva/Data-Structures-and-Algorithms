#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {//The structure per number that contains all info
    string type, name;
	int number;
};

struct Contact {
	string name;
	int number;
};

//Makes an array of instructions and names (and numbers)
vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}	
//Just writes out responses passed to it
void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;

    // Keep list of all existing (i.e. not deleted yet) contacts.
    //vector<Query> contacts(10000000);//Will use direct addressing scheme on this
	vector<Contact> contacts(10000000);

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
			contacts[queries[i].number].name = queries[i].name;
			contacts[queries[i].number].number = queries[i].number;

			//bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            
			/*for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }*/

            // otherwise, just add it
            /*if (!was_founded)
                contacts.push_back(queries[i]);*/

        } else if (queries[i].type == "del") {
			contacts[queries[i].number].number = -1;
			/*for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }*/
        } else {//this implements find command
			if (contacts[queries[i].number].number == -1 || contacts[queries[i].number].name.empty()) {
				result.push_back("not found");
			}
			else {
				result.push_back(contacts[queries[i].number].name);
			}
			/*string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);*/
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
