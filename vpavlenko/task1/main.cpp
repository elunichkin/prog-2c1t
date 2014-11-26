#include "SuffixTree.h"
#include <iostream>
using namespace std;

void main() {
    vector<int> occurences = findAllOccurences(SuffixTree("ababa"), "ab");
    for (int i = 0; i < occurences.size(); ++i)
        cout << occurences[i] << endl;
}