#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int N, M;
int map[9][9];
int tempmap[9][9];
queue <pair<int, int>> qq;
queue <pair<int, int>> q;
vector <pair<int, int>>v;
int ans = 0;


void copy(int a[9][9], int b[9][9])
{
	int temp = 0;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			a[j][i] = b[j][i];
		}
	}

}

int calc(int a[9][9])
{
	int temp = 0;

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			if (a[j][i] == 0)
			{
				temp++;
			}
		}
	}
	return temp;
}

void spread()
{
	bool check[9][9] = { false, };
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int tx = x  + dx[i];
			int ty = y + dy[i];

			if (tx >= 0 && tx < M && ty >= 0 && ty < N)
			{
				if (check[ty][tx] == false )
				{
					if (tempmap[ty][tx] == 0)
					{
						tempmap[ty][tx] = 2;
						q.push(make_pair(tx, ty));
					}

					check[ty][tx] = true;
				}
			}
		}

	}

}

void DFS(int wall)
{
	if (wall == 3)
	{
		copy(tempmap,map);

		//for (int i = 0; i < v.size(); i++)
		//{
			//q.push(make_pair(v[i].first, v[i].second));
		q = qq;
		spread();
		//}
		//calc();
		int temp = calc(tempmap);
		memset(tempmap, 0, sizeof(tempmap));
		ans = max(ans, temp);

		return;
	}

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			if (map[j][i] == 0)
			{
				map[j][i] = 1;
				DFS(wall + 1);
				map[j][i] = 0;
			}
		}
	}

}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 2)
			{
				qq.push(make_pair(j, i));
				//v.push_back(make_pair(j, i));
			}
		}
	}

	DFS(0);

	cout << ans;
}