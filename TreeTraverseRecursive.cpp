int currHeight = 0;
int maxHeight = 0;
maxHeight = tree_traverse(&nodes[root], maxHeight, currHeight);


int tree_traverse(Node* CurrNode, int &maxHeight, int &currHeight){
	currHeight++;
	maxHeight = std::max(maxHeight, currHeight);

	if (CurrNode->children.empty() == true) {
		currHeight--;
		return 0;
	}
	
	for (int leaf_index = 0; leaf_index < CurrNode->children.size(); leaf_index++) {
		tree_traverse(CurrNode->children[leaf_index], maxHeight, currHeight);
	}

	return maxHeight;
}