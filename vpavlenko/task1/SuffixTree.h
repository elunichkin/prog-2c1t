#ifndef SUFFIXTREE
#define SUFFIXTREE

#include <string>
#include <vector>
#include <algorithm>

class SuffixTree {
    const static int alphabetSize = 53;
    const static char terminationSymbol = '$';

    static int toCode(char);

    struct Node;
    struct Edge;

    struct InlineNode {
        InlineNode(int _parent);

        std::vector<int> next, start, end;
        int parent, length;

        void setForSymbol(char, int, int, int);
        int lengthForSymbol(int);
    };

    std::string s;
    std::vector<int> links;
    std::vector<InlineNode> tree;

    void addNode(int);
    void addLeaf(int, int, int);
    void next(int&, int&, int&, int, int);
    bool trySymbol(int, int, int, int);
    int split(int, int, int);

public:
    SuffixTree(std::string text);

    Node getRoot() const;

    struct Node {
        SuffixTree &suffixTree;
        int node;

        Node(SuffixTree &_suffixTree, int _node);
        Node(Node &other);

        std::vector<Edge> getOutgoingEdges();
        Edge getBySymbol(char);
        bool hasEdge(char);

        void operator= (Node &other);
    };

    struct Edge {
        SuffixTree &suffixTree;
        int node, symbol;

        Edge(SuffixTree &_suffixTree, int _node, int _symbol);

        char getCharAt(int);
        Node getNode();
        int getLen();
    };
};

std::vector<int> findAllOccurences(const SuffixTree&, std::string);

#endif