#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

const long long P = 29, Q = 31;

inline short code(char c) {
    return c - 'a' + 1;
}

int n, m;
vector< vector<char> > a;
vector<long long> p, q;
vector< vector<long long> > front_hash, back_hash;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m;
    p.reserve(n);
    p.push_back(1);
    for (int i = 1; i < n; ++i)
        p.push_back(p[i - 1] * P);
    q.reserve(m);
    q.push_back(1);
    for (int j = 1; j < m; ++j)
        q.push_back(q[j - 1] * Q);

    a.resize(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        cin >> a[i][j];

    front_hash.resize(n, vector<long long>(m));
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
        front_hash[i][j] = code(a[i][j]) * p[i] * q[j];
        if (i > 0)
            front_hash[i][j] += front_hash[i - 1][j];
        if (j > 0)
            front_hash[i][j] += front_hash[i][j - 1];
        if (i > 0 && j > 0)
            front_hash[i][j] -= front_hash[i - 1][j - 1];
    }

    back_hash.resize(n, vector<long long>(m));
    for (int i = n - 1; i >= 0; --i)
    for (int j = m - 1; j >= 0; --j) {
        back_hash[i][j] = code(a[i][j]) * p[n - i - 1] * q[m - j - 1];
        if (i < n - 1)
            back_hash[i][j] += back_hash[i + 1][j];
        if (j < m - 1)
            back_hash[i][j] += back_hash[i][j + 1];
        if (i < n - 1 && j < m - 1)
            back_hash[i][j] -= back_hash[i + 1][j + 1];
    }

    int good_rectangles = 0;
    for (int i_fr = 0; i_fr < n; ++i_fr)
    for (int j_fr = 0; j_fr < m; ++j_fr)
    for (int i_ba = i_fr; i_ba < n; ++i_ba)
    for (int j_ba = j_fr; j_ba < m; ++j_ba) {
        long long front = front_hash[i_ba][j_ba];
        if (i_fr > 0)
            front -= front_hash[i_fr - 1][j_ba];
        if (j_fr > 0)
            front -= front_hash[i_ba][j_fr - 1];
        if (i_fr > 0 && j_fr > 0)
            front += front_hash[i_fr - 1][j_fr - 1];
        front *= p[n - i_fr - 1] * q[m - j_fr - 1];

        long long back = back_hash[i_fr][j_fr];
        if (i_ba < n - 1)
            back -= back_hash[i_ba + 1][j_fr];
        if (j_ba < m - 1)
            back -= back_hash[i_fr][j_ba + 1];
        if (i_ba < n - 1 && j_ba < m - 1)
            back += back_hash[i_ba + 1][j_ba + 1];
        back *= p[i_ba] * q[j_ba];
        good_rectangles += (front == back);

    }

    cout << good_rectangles << endl;
}