#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif //Resource managment on unix, ignore for my application

class Node;

class Node {
public:
	int key;
	Node* parent;
	std::vector<Node*> children;

	Node() {
		this->parent = NULL;
	}

	void setParent(Node* theParent) {
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

	int root = 0;

	for (int child_index = 0; child_index < n; child_index++) {
		int parent_index;
		std::cin >> parent_index;
		if (parent_index >= 0)
			nodes[child_index].setParent(&nodes[parent_index]);
		if (parent_index == -1)
			root = child_index;
		nodes[child_index].key = child_index;
	}

	std::stack<Node*> dfs;
	dfs.push(&nodes[root]);//root on the stack

	int height = 0;
	int maxHeight = 0;
	Node* currNode;

	while (dfs.empty() == false) {
		currNode = dfs.top();
		dfs.pop();
		
		height++;
		maxHeight = std::max(maxHeight,height);

		if (currNode->children.empty() == true) {
			height--;
		}
		for (int i = currNode->children.size()-1; i >= 0 ; i--) {
			dfs.push(currNode->children[i]);
		}
	}

	/*Slow tree height finding
	int maxHeight = 0;
	for (int leaf_index = 0; leaf_index < n; leaf_index++) {
		int height = 0;
		for (Node* v = &nodes[leaf_index]; v != NULL; v = v->parent)
			height++;
		maxHeight = std::max(maxHeight, height);
	}*/

	std::cout << maxHeight << std::endl;
	return 0;
}

int main(int argc, char** argv)
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

#endif //Resource managment on unix, ignore for my application

	return main_with_large_stack_space();
}