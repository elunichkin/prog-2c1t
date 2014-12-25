#include "SuffixTree.h"

int SuffixTree::toCode(char symbol) {
    if (symbol >= 'a' && symbol <= 'z')
        return symbol - 'a';
    if (symbol >= 'A' && symbol <= 'Z')
        return SuffixTree::alphabetSize / 2 + symbol - 'A';
    if (symbol == SuffixTree::terminationSymbol)
        return SuffixTree::alphabetSize - 1;
}

SuffixTree::InlineNode::InlineNode(int _parent = 0)
: parent(_parent), length(0), next(SuffixTree::alphabetSize, -1), start(SuffixTree::alphabetSize), end(SuffixTree::alphabetSize)
{}

void SuffixTree::InlineNode::setForSymbol(char symbol, int newNext, int newStart, int newEnd) {
    int code = SuffixTree::toCode(symbol);
    next[code] = newNext;
    start[code] = newStart;
    end[code] = newEnd;
}

int SuffixTree::InlineNode::lengthForSymbol(int code) {
    return end[code] - start[code];
}

void SuffixTree::addNode(int _parent) {
    tree.push_back(InlineNode(_parent));
    links.push_back(-1);
}

void SuffixTree::addLeaf(int node, int symbol, int start) {
    addNode(node);
    tree[node].setForSymbol(symbol, tree.size() - 1, start, s.length());
    tree.back().length = s.length() - start - 1 + tree[node].length;
}

void SuffixTree::next(int& node, int& length, int& code, int start, int end) {
    length = end - start - tree[node].length;
    while (tree[node].next[code] != -1 && length >= tree[node].lengthForSymbol(code)) {
        int newLength = tree[node].lengthForSymbol(code);
        node = tree[node].next[code];
        length -= newLength;
        code = SuffixTree::toCode(s[tree[node].length + start]);
    }
}

bool SuffixTree::trySymbol(int node, int length, int start, int code) {
    if (!length)
        return tree[node].next[code] != -1;
    return SuffixTree::toCode(s[tree[node].start[start] + length]) == code;
}
int SuffixTree::split(int node, int length, int code) {
    if (!length)
        return node;
    if (length == tree[node].lengthForSymbol(code))
        return tree[node].next[code];
    addNode(node);
    char symbol = s[tree[node].start[code] + length];
    tree.back().setForSymbol(symbol, tree[node].next[code], tree[node].start[code] + length, tree[node].end[code]);
    tree[node].end[code] = tree[node].start[code] + length;
    tree[node].next[code] = tree.size() - 1;
    tree[tree.back().next[SuffixTree::toCode(symbol)]].parent = tree.size() - 1;
    tree.back().length = tree[node].length + 1;
    return tree.size() - 1;
}

SuffixTree::SuffixTree(std::string text) {
    s = text + SuffixTree::terminationSymbol;
    int start = 0,
        end = 0;
    tree.push_back(InlineNode());
    links.push_back(0);
    int node = 0,
        length = 0,
        startSymbol = 0,
        alone = -1;
    while (std::max(start, end) < s.length()) {
        int code = SuffixTree::toCode(s[end]);
        while (start <= end && !trySymbol(node, length, startSymbol, code)) {
            int mid = split(node, length, startSymbol);
            if (alone != -1) {
                links[alone] = mid;
                alone = -1;
            }
            if (links[mid] == -1)
                alone = mid;
            addLeaf(mid, code, end);
            ++start;
            node = links[node];
            startSymbol = SuffixTree::toCode(s[start + tree[node].length]);
            if (start <= end)
                next(node, length, startSymbol, start, end);
        }
        if (alone > -1) {
            links[alone] = node;
            alone = -1;
        }
        ++end;
        if (start != end)
            next(node, length, startSymbol, start, end);
    }
}

SuffixTree::Node SuffixTree::getRoot() const {
    return Node(const_cast<SuffixTree&>(*this), 0);
}

int SuffixTree::getLength() const {
    return s.length();
}

SuffixTree::Node::Node(SuffixTree &_suffixTree, int _node)
: suffixTree(_suffixTree), node(_node)
{}

void SuffixTree::Node::operator= (const SuffixTree::Node & other) {
    this->suffixTree = other.suffixTree;
    this->node = other.node;
}

std::vector<SuffixTree::Edge> SuffixTree::Node::getOutgoingEdges() {
    std::vector<Edge> listEdges;
    for (int i = 0; i < SuffixTree::alphabetSize; ++i) {
        if (suffixTree.tree[node].next[i] != -1) {
            listEdges.push_back(Edge(suffixTree, node, i));
        }
    }
    return listEdges;
}

SuffixTree::Edge SuffixTree::Node::getBySymbol(char symbol) {
    return Edge(suffixTree, node, SuffixTree::toCode(symbol));
}

bool SuffixTree::Node::hasEdge(char symbol) {
    return suffixTree.tree[node].next[SuffixTree::toCode(symbol)] != -1;
}

SuffixTree::Edge::Edge(SuffixTree &_suffixTree, int _node, int _symbol)
: suffixTree(_suffixTree), node(_node), symbol(_symbol)
{}

char SuffixTree::Edge::getCharAt(int index) {
    return suffixTree.s[suffixTree.tree[node].start[symbol] + index];
}

SuffixTree::Node SuffixTree::Edge::getNode() {
    return Node(suffixTree, suffixTree.tree[node].next[symbol]);
}

int SuffixTree::Edge::getLen() {
    return suffixTree.tree[node].lengthForSymbol(symbol);
}

void DFS(SuffixTree::Node node, int depth, std::vector<int> &occurences) {
    std::vector<SuffixTree::Edge> edges = node.getOutgoingEdges();
    if (edges.empty())
        occurences.push_back(depth);
    for (int i = 0; i < edges.size(); ++i) {
        DFS(edges[i].getNode(), depth + edges[i].getLen(), occurences);
    }
}

std::vector<int> findAllOccurences(const SuffixTree& suffixTree, std::string pattern) {
    std::vector<int> occurences;
    SuffixTree::Node currentNode = suffixTree.getRoot();
    int currentLength = 0;
    while (currentLength < pattern.size()) {
        if (!currentNode.hasEdge(pattern[currentLength]))
            return occurences;
        SuffixTree::Edge currentEdge = currentNode.getBySymbol(pattern[currentLength]);
        for (int i = 0; i < std::min(currentEdge.getLen(), (int)(pattern.length() - currentLength)); ++i) {
            if (currentEdge.getCharAt(i) != pattern[currentLength + i])
                return occurences;
        }
        currentLength += currentEdge.getLen();
        currentNode = currentEdge.getNode();
    }
    DFS(currentNode, 0, occurences);
    for (int i = 0; i < occurences.size(); ++i)
        occurences[i] = suffixTree.getLength() - currentLength - occurences[i];
    return occurences;
}