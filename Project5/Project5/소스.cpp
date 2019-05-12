#include <deque>
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int map[20][20];
int T;
int N;
vector <int> share;
int ans = 999999;

void calc()
{
	deque <int> a;
	deque <int> b;

	do {
		int suma = 0;
		int sumb = 0;
		a.clear();
		b.clear();

		for (int i = 0; i < N; i++)
		{
			if (share[i] == 0)
			{
				a.push_back(i);
			}
			else
			{
				b.push_back(i);
			}
		}


		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0;j < N / 2; j++)
			{
				if (i != j)
				{
					suma += map[a[i]][a[j]];
				}
			}
		}

		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				if (i != j)
				{
					sumb += map[b[i]][b[j]];
				}
			}
		}

		ans = min(ans, abs(suma - sumb));

	} while (next_permutation(share.begin(), share.end()));


}

int main()
{
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		cin >> N;
		ans = 999999;
		share.clear();
		memset(map, 0, sizeof(map));

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < N / 2; i++)
		{
			share.push_back(0);
			share.push_back(1);
		}

		sort(share.begin(), share.end());

		calc();

		printf("#%d %d\n", t, ans);
	}
	
}