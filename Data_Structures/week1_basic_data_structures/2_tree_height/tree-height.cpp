#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

//#define IF_DEBUG

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);

	int root_index;

	//Forming the tree
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
		
		#ifdef IF_DEBUG
			std::cout <<"Child index is: "<< child_index << "\n";
		#endif

    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
		else
			root_index = child_index;
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
	// Algorithm: Breadth-First-Search
	// 1. Identify the parent node and enqueue it in the queue
	// 2. Go to all the children of the parent node and enqueue them in the queue
	// 3. Keep track of how many nodes are there in the next level, as this will help you
	// 		in determining when to increment the height 
  // 4. Dequeue the parent node so that you are left with nodes at the same level in the queue
	// 5. Once you are finished at level (when curr_lvl_leaves == 0), move to the next level
	// 6. Repeat it till you reach leaf nodes 
	
	std::queue<Node *> node_queue;
	int lastParent = -1;
	node_queue.push(&nodes[root_index]);

	int curr_lvl_leaves = 1;												//keeps track of nodes left in the current level	
	int next_lvl_leaves;														//keeps track of nodes in the next level
  int maxHeight = 0;
	
	while(!node_queue.empty()){
		#ifdef IF_DEBUG	
			std::cout<<"Size of the children vector is: "<<node_queue.front()->children.size()<<"\n";
		#endif
		
		for(int i = 0; i < node_queue.front()->children.size() ; i++)
			node_queue.push(node_queue.front()->children[i]);	
	
		next_lvl_leaves = next_lvl_leaves + node_queue.front()->children.size();	
		node_queue.pop();
		curr_lvl_leaves--;

		if(curr_lvl_leaves == 0){
			curr_lvl_leaves = next_lvl_leaves;
			next_lvl_leaves = 0;
			maxHeight++;
		}
		else
			curr_lvl_leaves = curr_lvl_leaves;

		//NOTE: I tried to figure out how to identify if nodes are at the same level or not. I tried to determine 
		//whether they have the same parent or not, which didn't work obviously, as there are possibilities where
		//multiple child nodes can be at the same level but originate from different parents.
	}

	#ifdef IF_DEBUG	
		std::cout<<"Size of the queue after pushing children is: "<<node_queue.size()<<"\n";
	#endif

  std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
