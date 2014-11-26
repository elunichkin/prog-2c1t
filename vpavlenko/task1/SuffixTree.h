#ifndef _SUFFIXTREE_H
#define _SUFFIXTREE_H

#include <string>
#include <vector>
#include <map>
#include <stack>

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
        State();
    };

    State pointer;

    State MoveTo(State state, int _start_index, int _end_index);
    int Split(State state);
    int GetLink(int vertex);
    void ExtendTree(int position);
    void BuildTree();
    std::vector<Node> GetTree() const;

public:
    SuffixTree(std::string text);

    template<class Visitor>
    void FindOccurences(Visitor *visitor) const;
};

struct SuffixTreeVisitor {
    std::string pattern;
    std::vector<int> occurences;

    SuffixTreeVisitor(std::string _pattern);

    void AddOccurence(int occurence);
    std::vector<int> GetOccurences();
};

std::vector<int> findAllOccurences(const SuffixTree& suffixTree, std::string pattern);

#endif