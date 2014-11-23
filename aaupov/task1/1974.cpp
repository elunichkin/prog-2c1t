#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<string, int> sound;

inline string my_tostring(int x)
{
	return to_string(_ULonglong(x));
}

void set_sounds()
{
	for (int i = 0; i < 8; ++i)
	{
		sound[my_tostring(i + 1) + "C"] = i * 12;
		sound[my_tostring(i + 1) + "C+"] = sound[my_tostring(i + 1) + "D-"] = i * 12 + 1;
		sound[my_tostring(i + 1) + "D"] = i * 12 + 2;
		sound[my_tostring(i + 1) + "D+"] = sound[my_tostring(i + 1) + "E-"] = i * 12 + 3;
		sound[my_tostring(i + 1) + "E"] = sound[my_tostring(i + 1) + "F-"] = i * 12 + 4;
		sound[my_tostring(i + 1) + "F"] = sound[my_tostring(i + 1) + "E+"] = i * 12 + 5;
		sound[my_tostring(i + 1) + "F+"] = sound[my_tostring(i + 1) + "G-"] = i * 12 + 6;
		sound[my_tostring(i + 1) + "G"] = i * 12 + 7;
		sound[my_tostring(i + 1) + "G+"] = sound[my_tostring(i + 1) + "A-"] = i * 12 + 8;
		sound[my_tostring(i + 1) + "A"] = i * 12 + 9;
		sound[my_tostring(i + 1) + "A+"] = sound[my_tostring(i + 1) + "B-"] = i * 12 + 10;
		sound[my_tostring(i + 1) + "B"] = i * 12 + 11;
	}
	for (int i = 1; i < 8; ++i)
		sound[my_tostring(i + 1) + "C-"] = sound[my_tostring(i) + "B"];
	for (int i = 0; i < 7; ++i)
		sound[my_tostring(i + 1) + "B+"] = sound[my_tostring(i + 2) + "C"];
}

double I(vector<int> &x, vector<int> &y)
{
	int n = x.size(),
		m = y.size();
	vector<int> lcs(n + m + 1);
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	if (x[i] == y[j])
		++lcs[i - j + m];
	int ans = 0;
	for (int c = 0; c <= n + m; ++c)
		ans = max(ans, lcs[c]);
	return double(ans) / m;
}

void main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	cout.precision(8);
	set_sounds();

	int n;
	cin >> n;
	vector<int> melody(n);
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		melody[i] = sound[s];
	}

	int m;
	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		int k;
		cin >> k;
		vector<int> cur(k);
		for (int j = 0; j < k; ++j)
		{
			string s;
			cin >> s;
			cur[j] = sound[s];
		}
		cout << I(melody, cur) << endl;
	}
}