#include "SuffixTree.h"
#include <iostream>
using namespace std;

void main() {
    SuffixTree st("abacaba");
    vector<int> occurences = findAllOccurences(st, "ab");
    cout << occurences.size() << endl;
    for (int i = 0; i < occurences.size(); ++i)
        cout << occurences[i] << " ";
}