#ifndef _SUFFIXTREE_H
#define _SUFFIXTREE_H

#include <string>
#include <vector>
#include <map>

class SuffixTree {
	std::string string;
	int length;

	struct Node {
		int start_index, end_index, parent, link;
		std::map<char, int> out_edges;

		Node(int _start_index, int _end_index, int _parent);
		int NodeLength();
		int &GetNext(char symbol);

	};

	std::vector<Node> tree;
	int treeSize;

	struct State {
		int vertex, position;

		State(int _vertex, int _position);
	};

	State pointer;

	State MoveTo(State state, int _start_index, int _end_index);
	int Split(State state);
	int GetLink(int vertex);
	void ExtendTree(int position);
	void BuildTree();
};



#endif