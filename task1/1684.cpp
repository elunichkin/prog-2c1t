#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const long maxlen = 150005;

string first, second, s;
long f[maxlen];
string answer[maxlen];
long cht;

void prefix_function()
{
	long k = 0;
	f[1] = 0;
	for (long it = 2; it <= s.length() - 1; it++)
	{
		while ((k>0) && (s[k + 1] != s[it]))
			k = f[k];
		if (s[k + 1] == s[it])
			k++;
		f[it] = k;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	long q;
	cin >> first >> second;
	s = '$' + first + '$' + second;
	prefix_function();

	bool fail = false;
	for (q = first.length() + 2; q <= s.length() - 1; q++)
	if (f[q] == 0)
	{
		fail = true;
		break;
	}
	if (fail)
	{
		printf("Yes");
		return 0;
	}
	long now = s.length() - 1;
	cht = 0;
	while (now >= first.length() + 2)
	{
		cht++;
		answer[cht] = s.substr(now - f[now] + 1, f[now]);
		now -= f[now];
	}

	printf("No\n");
	for (q = cht; q >= 1; q--)
	{
		cout << answer[q] << " ";
	}
}