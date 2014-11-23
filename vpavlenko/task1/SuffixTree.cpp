#include "SuffixTree.h"

SuffixTree::Node::Node(int _start_index = 0, int _end_index = 0, int _parent = -1) 
: start_index(start_index), end_index(end_index), parent(parent), link(-1)
{}

int SuffixTree::Node::NodeLength() {
	return end_index - start_index;
}

int &SuffixTree::Node::GetNext(char symbol) {
	if (!out_edges.count(symbol)) {
		out_edges[symbol] = -1;
	}
	return out_edges[symbol];
}

SuffixTree::State::State(int _vertex, int _position)
: vertex(_vertex), position(_position)
{}

SuffixTree::State SuffixTree::MoveTo(State state, int _start_index, int _end_index) {
	while (_start_index < _end_index) {
		if (state.position == tree[state.vertex].NodeLength()) {
			state = State(tree[state.vertex].GetNext(string[_start_index]), 0);
			if (state.vertex == -1) {
				return state;
			}
		}
		else {
			if (string[tree[state.vertex].start_index + state.position] != string[_start_index]) {
				return State(-1, -1);
			}
			if (_end_index - _start_index < tree[state.vertex].NodeLength() - state.position) {
				return State(state.vertex, state.position + _end_index - _start_index);
			}
			_start_index += tree[state.vertex].NodeLength() - state.position;
			state.position = tree[state.vertex].NodeLength();
		}
	}
	return state;
}

int SuffixTree::Split(SuffixTree::State state) {
	if (state.position == tree[state.vertex].NodeLength()) {
		return state.vertex;
	}
	if (state.position == 0) {
		tree[state.vertex].parent;
	}
	Node currentVertex = tree[state.vertex];
	int currentIndex = treeSize++;
	tree[currentIndex] = Node(currentVertex.start_index, currentVertex.start_index + state.position, currentVertex.parent);
	tree[currentVertex.parent].GetNext(string[currentVertex.start_index]) = currentIndex;
	tree[currentIndex].GetNext(string[currentVertex.start_index + state.position]) = state.vertex;
	tree[state.vertex].parent = currentIndex;
	tree[state.vertex].start_index += state.position;
	return currentIndex;
}

int SuffixTree::GetLink(int vertex) {
	if (tree[vertex].link == -1) {
		return tree[vertex].link;
	}
	if (tree[vertex].parent == -1) {
		return 0;
	}
	int resultPosition = GetLink(tree[vertex].parent);
	tree[vertex].link = Split(MoveTo(SuffixTree::State(resultPosition, tree[resultPosition].NodeLength()), tree[vertex].start_index + (tree[vertex].parent == 0), tree[vertex].end_index));
	return tree[vertex].link;
}

void SuffixTree::ExtendTree(int position) {
	while (true) {
		State newPointer = MoveTo(pointer, position, position + 1);
		if (newPointer.vertex != -1) {
			pointer = newPointer;
			return;
		}
		int middle = Split(pointer);
		int leaf = treeSize++;
		tree[leaf] = Node(position, length, middle);
		tree[middle].GetNext(string[position]) = leaf;
		pointer.vertex = GetLink(middle);
		pointer.position = tree[pointer.vertex].NodeLength();
		if (!middle) {
			break;
		}
	}
}

void SuffixTree::BuildTree() {
	pointer = State(0, 0);
	treeSize = 1;
	for (int i = 0; i < length; ++i)
		ExtendTree(i);
}