#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void z_func(string s, vector<int> &z)
{
	int n = s.length();
	z.assign(n, 0);
	for (int i = 1, l = 0, r = 0; i < n; ++i)
	{
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i,
			r = i + z[i] - 1;
	}
}

void main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	string normal, reversed, concat;
	cin >> normal;
	reversed = normal;
	reverse(reversed.begin(), reversed.end());
	concat = reversed + '#' + normal;
	vector<int> z;
	z_func(concat, z);
	int pal_length = 0;
	for (int i = normal.size() + 2; i < concat.size(); ++i)
	if (i + z[i] == concat.size())
	{
		pal_length = concat.size() - i;
		break;
	}
	cout << normal << reversed.substr(pal_length);
}