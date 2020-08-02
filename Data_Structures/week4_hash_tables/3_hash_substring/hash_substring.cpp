#include <iostream>
#include <string>
#include <vector>

/*NOTE: The trick here is to make sure the value of x is not too large or too small. Moreover, 
	it is important to account for the case where calculated hash value goes negative, by using (a%p + p)%p*/

using std::string;
typedef unsigned long long ull;

//#define IF_DEBUG

struct Data {
    string pattern, text;
};

string fin_str;

/*Finding the substring without using substr method*/
string subString(const string& s, int start, int end)
{
	if(start<=end){
		char obj = s[start];
		fin_str.push_back(obj);
    //std::cout<<fin_str<<"\n";
    subString(s, start+1, end); 
	}
	return fin_str;
}

/*PolyHash function*/
long long polyHash(const string& s, int prime, int x) {
	unsigned long long hash = 0;
	for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i]) % prime;
	return hash;
}

std::vector<long long> preComputeHashes(string text, int pLength, int p, int x) {
	int tLength = text.size();
	std::vector<long long> H(tLength - pLength + 1);
	string s = text.substr(tLength - pLength, pLength);
	H[tLength - pLength] = polyHash(s, p, x);
	long long y = 1;
	for (int i = 1; i <= pLength; ++i)
		y = y * x % p;
	for (int i = tLength - pLength - 1; i >= 0; --i) {
		long long preHash = x * H[i + 1] + text[i] - y * text[i + pLength];
		while (preHash < 0) {
			preHash += p;
		}
		H[i] = preHash % p;
	}
	return H;
}

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

bool areEqual(const string& s1, const string& s2){
	if(s1.size() != s2.size()){
		#ifdef IF_DEBUG
			std::cout<<"The first string is "<<s1<<"\n";
			std::cout<<"The second string is "<<s2<<"\n";
			std::cout<<"The string lengths are not equal\n";
		#endif
		return false;
	}
	else{
		for(int i=0; i<s1.size(); i++){
			if(s1[i] != s2[i])
				return false;
			else
				return true;
		}
	}
}

std::vector<int> get_occurrences(const Data& input) {

    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
		
		int len = t.size() - s.size() + 1;
		int p = 1000000007;
		int x = rand() % (p-1) + 1;
	
		unsigned long long pHash;
		pHash = polyHash(s, p, x);
		#ifdef IF_DEBUG
			std::cout<<"The value of pHash, "<<s<<", is "<<pHash<<"\n";
		#endif

		std::vector<long long> preCompHash;	
		preCompHash.resize(len);
		//std::vector<long long> preCompHash = preComputeHashes(t, s.size(), p, x);	
		preCompHash = preComputeHashes(t, s.size(), p, x);//preComputeHashes(t,s.size(), p, x);

    for (size_t i = 0; i + s.size() <= t.size(); ++i){
			#ifdef IF_DEBUG
				fin_str = "";
				//std::cout<<"The current substring is "<<subString(t,i,i+s.size() - 1)<<"\n";
				std::cout<<"The current substring is "<<t.substr(i,s.size())<<"\n";
				std::cout<<"The hash value of current substring is "<<preCompHash[i]<<"\n";
			#endif
			fin_str = "";
			#ifdef IF_DEBUG
			std::cout<<"The value of i is "<<i<<" and size of s is "<<s.size()<<"\n";
			//std::cout<<"The first string is "<<subString(t,i,s.size() - 1)<<"\n";
			std::cout<<"The first string is "<<t.substr(i,s.size())<<"\n";
			std::cout<<"The second string is "<<s<<"\n";
			fin_str = "";
			//std::cout<<"Are the strings equal: "<<areEqual(subString(t,i,s.size() - 1),s)<<"\n";
			std::cout<<"Are the strings equal: "<<areEqual(t.substr(i,s.size()),s)<<"\n";
			#endif
			if(pHash != preCompHash[i]){
				#ifdef IF_DEBUG
					std::cout<<"The hash values are not equal\n";
				#endif
				continue;
			}
			if(areEqual(t.substr(i,s.size()),s)){
				#ifdef IF_DEBUG
					std::cout<<"Pushing the current string index into queue.\n";
				#endif
				ans.push_back(i);
			}
		}
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
