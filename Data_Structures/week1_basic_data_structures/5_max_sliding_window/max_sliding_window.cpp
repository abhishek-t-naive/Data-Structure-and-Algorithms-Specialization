#include <iostream>
#include <vector>
//#include "StackWithMax.h"
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::max_element;

//#define IF_DEBUG

/*Returns the maximum of a stack in constant time*/
class StackWithMax {
    vector<int> stack;
		
		/*The auxiliary_stack is filled with only new maximums. Each time
			a new value comes in, a check is made to find out if it is more
			than the previous value or not.*/
    vector<int> auxiliary_stack;

		int curr_max = 0;

  public:

		void reset_curr_max(){
			curr_max = 0;
		}

		int curr_max_val(){
			return curr_max;
		}

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
    int Pop() {
        assert(stack.size());
				if(stack.back() == auxiliary_stack.back()){
        	assert(auxiliary_stack.size());
					auxiliary_stack.pop_back();
				}
       stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        //assert(auxiliary_stack.size());

        return auxiliary_stack.back();
    }
		
		int Size(){
			return stack.size();
		}

		int Front(){
			return stack.front();
		}
		
		int Back(){
			return stack.back();
		}
};

void max_sliding_window_naive(vector<int> const & A, int w) {
	
	StackWithMax	stack_left;
	StackWithMax	stack_right;

	if(w == 1){
		for(int i = 0; i < A.size(); i++){
			stack_right.Push(A[i]);
			cout << stack_right.Max()<< "\n";
			stack_right.Pop();
			stack_right.reset_curr_max();
		}
	}
	else{
	/*First Case: If both stack empty, we are just starting searching.
		We fill the first window in the two stacks such that the last value
		is at the top of one of the stacks (in this case, right stack). We 
		return the maximum of maximum of both the stacks*/
		if((stack_left.Size() == 0) && (stack_right.Size() == 0)){
			for(int i = 0; i < w; i++){
				if(i == 0){
					stack_right.Push(A[i]);
					#ifdef IF_DEBUG
						cout << "Value pushed into the right stack is " << A[i] << "\n";
					#endif
				}
				else{
					#ifdef IF_DEBUG
						cout << "Value pushed into the left stack is " << A[i] << "\n";
					#endif
					stack_left.Push(A[i]);
				}
			}
			#ifdef IF_DEBUG
				cout << "First window being prepared!\n";
			#endif
			cout << max(stack_right.Max(),stack_left.Max()) << "\n";
		}
			
		#ifdef IF_DEBUG
			cout << "Entering the real part of the problem!\n";
		#endif
		
		/*We use 'right' to indicate which stack has to be copied into another stack.
			This is basically an indication of changing window and happens when we move
			to a completely new window.*/
		bool right = 1;
		
		for(int j = w; j < A.size(); j++){
			#ifdef IF_DEBUG
				cout << "Value of right is :"<<right<<"\n";
			#endif
			if(right){
				#ifdef IF_DEBUG
					cout << "Entering the part where right stack has 1 element!\n";
				#endif
				stack_right.Pop();
				if(stack_right.Size() == 0)
					stack_right.reset_curr_max();
				stack_right.Push(A[j]);
				while(stack_left.Size() != 0){
					#ifdef IF_DEBUG
						cout << "Top element in stack_left is: " << stack_left.Back() << "\n";
						cout << "Top element of the right stack is " << stack_right.Back() <<"\n";
					#endif
					int val = stack_left.Back();
					stack_right.Push(val);
					stack_left.Pop();
					#ifdef IF_DEBUG
						cout << "Size of the right stack is " << stack_right.Size() <<"\n";
						cout << "Size of the left stack is " << stack_left.Size() <<"\n";
					#endif
				}
				#ifdef IF_DEBUG
					cout << "Left stack is emptied!\n";
					cout << "curr_max in right stack is " << stack_right.curr_max_val() << "\n";
				#endif
				right = false;
				cout << stack_right.Max() << "\n";
				stack_left.reset_curr_max();
			}
			else{
				if(stack_right.Size() != 1){
					stack_right.Pop();
					stack_left.Push(A[j]);	
					#ifdef IF_DEBUG
						cout << "Value pushed into stack_left is: " << A[j] << "\n";
						cout << "Top element in stack_left is: " << stack_left.Back() << "\n";
						cout << "Size of the right stack is " << stack_right.Size() <<"\n";
						cout << "Size of the left stack is " << stack_left.Size() <<"\n";
						cout << "Max of the right stack is " << stack_right.Max() <<"\n";
						cout << "Max of the left stack is " << stack_left.Max() <<"\n";
					#endif
					cout << max(stack_right.Max(),stack_left.Max()) << "\n";
					if(stack_right.Size() == 1){
						right = 1;
						stack_right.reset_curr_max();
					}
				}
			}
		}
	}
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
