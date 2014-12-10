#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v;

    Edge(int _u, int _v)
        : u(_u), v(_v)
    {
        if (u > v)
            swap(u, v);
    }

    Edge()
        : Edge(0, 0)
    {}

    bool operator== (const Edge &other) {
        return (u == other.u && v == other.v);
    }
};

int n, root, ans;

vector< vector<int> > g;
vector< Edge> e;
vector< int > gr;

int getAns(int u, int p) {
    int ans = 0;
    for (int v : g[u]) {
        if (v == p)
            continue;
        ans ^= getAns(v, u) + 1;
    }
    return gr[u] = ans;
}

void getFirst(int u, int p, int m) {
    for (int v : g[u]) {
        if (v == p)
            continue;
        int cur = ((gr[u] ^ (gr[v] + 1)) ^ m) - 1;
        if (cur < 0) {
            for (int i = 0; i < n - 1; ++i)
            if (e[i] == Edge(u, v)) {
                ans = i + 1;
                return;
            }
        }
        if (cur >= gr[v])
            continue;
        getFirst(v, u, cur);
        if (cur)
            return;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> root;
    --root;
    g.resize(n);
    gr.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
        e.push_back(Edge(u, v));
    }

    if (getAns(root, -1) > 0) {
        getFirst(root, -1, 0);
        cout << 1 << endl << ans;
    }
    else
        cout << 2 << endl;
}