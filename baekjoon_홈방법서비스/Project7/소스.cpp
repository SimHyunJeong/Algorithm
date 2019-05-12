#include <string.h>
#include <stdio.h>
#include <deque>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int map[21][21];
bool check[21][21];
int N, M;
int maxIndex;
int house[50] = { 0, };
int ans = 0;

struct info
{
	int x;
	int y;
	int index;

};

void calc()
{
	int cnthouse = 0;

	for (int i = 1; i <= (2 * N )-1; i++)
	{
		cnthouse += house[i];

		if((cnthouse * M) - ((i*i) + ((i-1) *(i-1))) > 0)
		{
			ans = max(ans, cnthouse);
		}
	}
}


void find(int x, int y)
{
	queue <info> q;

	q.push({ x,y,1 });
	check[y][x] = true;

	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };


	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int index = q.front().index;
		q.pop();

 		for (int i = 0; i < 4; i++)
		{
			int tx = x + dx[i];
			int ty = y + dy[i];

			if (tx >= 0 && tx < N && ty >= 0 && ty < N)
			{
				if (check[ty][tx] == false)
				{
					if (map[ty][tx] != 0)
					{
						house[index + 1]++;
					}
					q.push({ tx,ty,index + 1 });
					check[ty][tx] = true;
				}
			}
		}
	}

	calc();
}

int main()
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		memset(map, 0, sizeof(map));
		ans = 0;

		cin >> N >> M;
		maxIndex = 2 * N - 1;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >>map[i][j];
			}
		}


		for (int i = 0; i < N; i++)
		{
			for (int j =0; j < N; j++)
			{
				memset(house, 0, sizeof(house));
				memset(check, false, sizeof(check));

				if (map[i][j] != 0)
				{
					house[1] = 1;
				}

				find(j,i);
			}
		}

		printf("#%d %d\n", t, ans);
	}

}