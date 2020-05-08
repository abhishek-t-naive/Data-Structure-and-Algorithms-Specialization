#include <iostream>
#include <stack>
#include <string>

typedef std::uint16_t Index;

//#define IF_DEBUG

int main(){
	
	std::string text;
	getline(std::cin,text);
	std::stack <int> char_stack;
	int unmatched_pos = 0;
	int top_val;

	for(int pos = 0; pos < text.length(); ++pos){
		char next = text[pos];
	
		#ifdef IF_DEBUG	
			std::cout << "Next char in string is: " << next << "\n";
		#endif

		if(next == '(' || next == '[' || next == '{') {
				if(pos == text.length() - 1){
					unmatched_pos = pos+1;
					std::cout <<unmatched_pos<<"\n"; 
				}
				else{
					char_stack.push(pos);
					#ifdef IF_DEBUG
						std::cout<< "Data pushed is at pos "	<<pos<<"\n";
					#endif
			}
		}
		else{
			if(!char_stack.empty()){
				top_val = char_stack.top();
			}
			else{
				#ifdef IF_DEBUG
					std::cout << "Empty\n";
				#endif
				top_val = -1;
			}

			#ifdef IF_DEBUG
				std::cout << "Current top val in the stack is "<<top_val
				<<"\n";
				std::cout << "Current char is "<<text[top_val] << "\n";
			#endif
			
			if((next == ')' || next == ']' || next == '}') && top_val >= 0){
				if(next == ')' && text[top_val] == '('){
					char_stack.pop();
					if(pos == text.length() - 1){
						if(char_stack.empty()){
							std::cout <<"Success\n";
						#ifdef IF_DEBUG
							std::cout << "Round brackets match found\n";
						#endif
						}
						else{		
							unmatched_pos = char_stack.top() + 1;
							std::cout << unmatched_pos << "\n";
						}
					}
				}
				else if (next == ']' && text[top_val] == '['){
					char_stack.pop();
					if(pos == text.length() - 1){
						if(char_stack.empty()){
							std::cout <<"Success\n";
						#ifdef IF_DEBUG
							std::cout << "Square brackets match found\n";
						#endif
						}
						else{		
							unmatched_pos = char_stack.top() + 1;
							std::cout << unmatched_pos << "\n";
						}
					}
				}
				else if (next == '}' && text[top_val] == '{'){
					char_stack.pop();
					if(pos == text.length() - 1){
						if(char_stack.empty()){
							std::cout <<"Success\n";
						#ifdef IF_DEBUG
							std::cout << "Curly brackets match found\n";
						#endif
						}
						else{		
							unmatched_pos = char_stack.top() + 1;
							std::cout << unmatched_pos << "\n";
						}
					}
				}
				else{
					unmatched_pos = pos + 1;
					#ifdef IF_DEBUG
						std::cout << "No brackets match found\n";
					#endif
					std::cout <<unmatched_pos<<"\n"; 
					exit(0);
				}
			}
			else{
				if(next == '(' || next == ')' ||  next == '[' || next == ']'|| next == '}' || next == '{'){
					unmatched_pos = pos + 1;
					std::cout <<unmatched_pos<<"\n" ; 
					exit(0);
					#ifdef IF_DEBUG
						std::cout << "A single unmatched bracket found\n";
					#endif
				}
				else
					#ifdef IF_DEBUG
						std::cout << "Char found!\n" ;
					#endif
					if(pos == text.length() - 1)
						std::cout << "Success\n";
					continue;
			}
		}
	}
}
