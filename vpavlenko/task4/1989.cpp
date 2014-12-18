#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const long long P = 31;

vector<long long> p;

class Fenwick {
    int size;
    vector<char> s;
    vector<long long> tree;

    void modify(int ind, long long diff) {
        for (; ind < size; ind = (ind | (ind + 1)))
            tree[ind] += diff;
    }

    long long sum(int r) {
        long long result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            result += tree[r];
        return result;
    }

public:
    void modify(int ind, char symbol) {
        modify(ind, (symbol - s[ind]) * p[ind]);
        s[ind] = symbol;
    }

    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    Fenwick(string _s) {
        size = _s.length();
        s.assign(size, 0);
        tree.assign(size, 0);
        for (int i = 0; i < size; ++i)
            modify(i, _s[i]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    string normal, reversed;
    cin >> normal;
    reversed = normal;
    reverse(reversed.begin(), reversed.end());
    int n = normal.length();

    p.reserve(n);
    p.push_back(1);
    for (int i = 1; i < n; ++i)
        p.push_back(p[i - 1] * P);
    
    Fenwick front(normal), back(reversed);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string task;
        cin >> task;
        if (task == "change") {
            int ind;
            char symbol;
            cin >> ind >> symbol;
            --ind;
            front.modify(ind, symbol);
            back.modify(n - ind - 1, symbol);
        }
        if (task == "palindrome?") {
            int l, r;
            cin >> l >> r;
            --l; --r;
            long long front_sum = front.sum(l, r),
                back_sum = back.sum(n - r - 1, n - l - 1);
            if (l < n - r - 1)
                front_sum *= p[n - l - r - 1];
            else if (l > n - r - 1)
                back_sum *= p[l + r - n + 1];
            cout << (front_sum == back_sum ? "Yes" : "No") << endl;
        }
    }
}
