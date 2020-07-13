#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <utility>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::pair;

#define NUM_LENGTH 7

typedef pair<string,string> array_type;

struct Query {
    string type, name;
    int number;
};

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries() {
    int n;
		static array_type contacts[10000000];
		array_type init ;
		init.first = "NULL";
		init.second = "NULL";
		//std::memset(contacts,"",sizeof(contacts));
    vector<string> result;
    cin >> n;
		string type, name;
		int number;
    for (int i = 0; i < n; ++i) {
        cin >> type;
        if (type == "add"){
            cin >> number >> name;
						contacts[number] = make_pair(type,name);
        } else if(type == "del"){
            cin >> number;
						contacts[number].first = "";
						contacts[number].second = "";
				} else{
						string response = "not found";
            cin >> number;
						//cout << "\n" << contacts[number].first << "\n";
						if(contacts[number].first != ""){
							response = contacts[number].second;
						}
						result.push_back(response);
				}
    }

   return result;
}

int main() {
    write_responses(process_queries());
    return 0;
}
