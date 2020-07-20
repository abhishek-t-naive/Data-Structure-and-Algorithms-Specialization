#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

//#define IF_DEBUG

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::list;

struct Query {
    string type, s;
    size_t ind;
};

// store all strings in one vector
vector<list<string> > elems;

class QueryProcessor {
    int bucket_count;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;	
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
				#ifdef IF_DEBUG
					cout<<"String is "<<query.type<<".\n";
				#endif
        if (query.type != "check"){
            cin >> query.s;
        }else{
            cin >> query.ind;
				}
				#ifdef IF_DEBUG
					std::cout<<"The value of ind is "<<query.ind<<" and string is '"<<query.s<<"' .\n";
				#endif
        return query;
    }

    //void writeSearchResult(bool was_found) const {
    //    std::cout << (was_found ? "yes\n" : "no\n");
    //}

    void processQuery(const Query& query) {
			int hash_val;
			elems.resize(bucket_count);	
			bool match_found = false;
			list <string> :: iterator it;
			
			/*Add query implementation*/
    	if (query.type == "add") {
				hash_val = hash_func(query.s);
				
				#ifdef IF_DEBUG
					cout << "Hash value is " << hash_val <<"\n";
				#endif
				
				for(it = elems[hash_val].begin(); it != elems[hash_val].end();++it){
					if(*it == query.s)
						match_found = true;
				}
				
				if(!match_found){
					elems[hash_val].push_front(query.s);	
					#ifdef IF_DEBUG
						cout <<"String being pushed is "<<query.s<<".\n";
						cout << "Size is " << elems[hash_val].size() <<"\n";
					#endif	
				}
				} else if(query.type == "del"){
					hash_val = hash_func(query.s);
					//elems[hash_val].remove(query.s);	
					
					for(it = elems[hash_val].begin(); it != elems[hash_val].end();++it){
						if(*it == query.s){	
							#ifdef IF_DEBUG
								cout << "Element to be deleted found!\n";
							#endif
							it = elems[hash_val].erase(it);
						}
					}
					#ifdef IF_DEBUG
						for(it = elems[hash_val].begin(); it != elems[hash_val].end();++it){
							cout << *it <<" ";
							cout << "\n";
						}
					#endif
				} else if(query.type == "find"){
					hash_val 		= hash_func(query.s);
					#ifdef IF_DEBUG
						cout << "Hash value is " << hash_val <<"\n";
						cout << "Size is " << elems[hash_val].size() <<"\n";
					#endif
					for(it = elems[hash_val].begin(); it != elems[hash_val].end();++it){
						#ifdef IF_DEBUG
						cout <<"Entered find!\n";	
						cout << *it <<" ";
						cout << "\n";
						#endif
						if(*it == query.s){
							#ifdef IF_DEBUG
								cout << "Element found!\n";
							#endif
							match_found = true;
						}
					}
				
					if(match_found)
						cout<<"yes\n";
					else
						cout<<"no\n";
	
				}else{
					hash_val 		= query.ind;
					#ifdef IF_DEBUG
						cout << "Hash value is " << hash_val <<"\n";
						cout << "Size is " << elems[hash_val].size() <<"\n";
					#endif
					for(it = elems[hash_val].begin(); it != elems[hash_val].end();++it){
						cout << *it <<" ";
					}
					cout << "\n";
				}
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i){
            processQuery(readQuery());
            //readQuery();
				}
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
