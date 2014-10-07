#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void p_func(string s, vector<int> &p)
{
	int n = s.length();
	p.assign(n, 0);
	for (int i = 1; i < n; ++i)
	{
		int j = p[i - 1];
		while (j > 0 && s[i] != s[j])
			j = p[j - 1];
		if (s[i] == s[j])
			++j;
		p[i] = j;
	}
}

void main() 
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	string word, jack, concat;
	cin >> word >> jack;
	concat = word + '#' + jack;
	
	vector<int> p;
	p_func(concat, p);
	for (int i = word.length() + 1; i < concat.length(); ++i)
	if (!p[i])
	{
		cout << "Yes" << endl;
		return;
	}
	
	vector<string> ans;
	int cur_pos = concat.length() - 1,
		count = 0;
	while (cur_pos > word.length())
	{
		ans.push_back(concat.substr(cur_pos - p[cur_pos] + 1, p[cur_pos]));
		cur_pos -= p[cur_pos];
		++count;
	}
	cout << "No" << endl;
	for (int i = ans.size() - 1; i >= 0; --i)
		cout << ans[i] << " ";
}