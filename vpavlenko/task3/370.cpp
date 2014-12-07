#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int n, m, k;
vector<vector<int>> f;

int F(int x, int y)
{
    if (f[x][y] >= 0)
        return f[x][y];
    if ((x == 1 && y <= k) || (y == 1 && x <= k))
        return f[x][y] = 1; 

    unordered_set<int> used;
    for (int i = 1; i < x; ++i)
        used.insert(F(i, y) ^ F(x - i, y));
    for (int i = 1; i < y; ++i)
        used.insert(F(x, i) ^ F(x, y - i));

    for (int i = 0;; ++i)
    if (!used.count(i))
        return f[x][y] = i;
}

int main()
{
    cin >> n >> m >> k;
    f.resize(n + 1, vector<int>(m + 1, -1));
    cout << (F(n, m) ? 1 : 2);
}