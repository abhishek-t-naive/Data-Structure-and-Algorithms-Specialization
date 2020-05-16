#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
		
		/*The auxiliary_stack is filled with only new maximums. Each time
			a new value comes in, a check is made to find out if it is more
			than the previous value or not.*/
    vector<int> auxiliary_stack;

		int curr_max = 0;

  public:

    void Push(int value) {
        stack.push_back(value);
				if(value >= curr_max){
					auxiliary_stack.push_back(value);
					curr_max = value;
				}
    }

		/*Each time a pop operation is called, we make sure that if it was the
			maximum values among a small grouo of values, we remove the maximum
			from the auxiliary_stack as well.*/
    void Pop() {
        assert(stack.size());
				if(stack.back() == auxiliary_stack.back()){
        	assert(auxiliary_stack.size());
					auxiliary_stack.pop_back();
				}
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        assert(auxiliary_stack.size());

        return auxiliary_stack.back();
    }
};

int main() {
    vector<int> max_out;
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            //cout << stack.Max() << "\n";
						max_out.push_back(stack.Max());
        }
        else {
            assert(0);
        }
    }
		
		for(int i = 0; i < max_out.size(); i++)
			cout << max_out[i] << "\n";

    return 0;
}
