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

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

	int LeftChild(int i){
		return 2*i+1;
	}
	
	int RightChild(int i){
		return 2*i+2;
	}

	void SiftDown(int i){
		int minIndex	= i;
		int size		 	=	data_.size();
		
		int leftchild	=	LeftChild(i);
		
		if(leftchild < size && data_[leftchild] < data_[minIndex])
			minIndex = leftchild;

		int rightchild	=	RightChild(i);

		if(rightchild < size && data_[rightchild] < data_[minIndex])
			minIndex = rightchild;

		if(i != minIndex){	
			swap(data_[i],data_[minIndex]);
			swaps_.push_back(make_pair(i,minIndex));
			SiftDown(minIndex);
		}
	}
		

  void GenerateSwaps() {
    swaps_.clear();
		//The approach is the following:
		//Considering that all the leaf nodes are already in accordance 
		//with BinHeap properties (as they don't have any further nodes),
		//we start looking at nodes one level above the leaf nodes.
		//We repair each node in a recursive manner such that they 
		//adhere to the property of BinMinHeap
    for (int i = data_.size()/2; i >= 0; i--){
			SiftDown(i);
		}
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
