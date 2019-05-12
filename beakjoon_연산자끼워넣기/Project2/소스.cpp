#include <stdio.h>
#include <iostream>
#include <queue>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

int LOOP;
int N;
int map[21][21];
int tempmap[21][21];

vector <pair<int, int>> v;
int alreadycore=0;
int core = 0;
int ans = 99999;
int templine = 0;

void init()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tempmap[i][j] = map[i][j];
		}
	}
}

bool solve(int Coreindex,int dir, int val1, int val2)
{
	templine = 0;

	//init();

	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	int y = v[Coreindex].first;
	int x = v[Coreindex].second;

	while (x != -1 && x != N && y != -1 && y != N)
	{
		y += dx[dir];
		x += dy[dir];

		if (map[y][x] == val2)
		{
			map[y][x] = val1;

			if (val1 == 2)
			{
				templine++;
			}
		}
		else
		{
			break;
		}

		if (x == 0 || x == N-1 || y == 0 || y == N-1)
		{
			return true;
		}
	}
	templine = 0;
	return false;
}

void DFS(int Coreindex, int CoreCount, int lineCount)
{

	//count가 3 보다 크면
	if (v.size() == Coreindex)
	{
		if (core == CoreCount)
		{
			ans = min(ans, lineCount);
		}
		else if (core < CoreCount)
		{
			core = CoreCount;
			ans = lineCount;
		}

		return;
	}

	int x = v[Coreindex].first;
	int y = v[Coreindex].second;

	for (int i = 0; i < 4; i++)
	{
		if (solve(Coreindex, i, 0,0))
		{
			solve(Coreindex, i, 2,0);
			DFS(Coreindex+1, CoreCount+1, lineCount+templine);
			solve(Coreindex, i, 0,2);
		}
	}
	
	DFS(Coreindex + 1, CoreCount , lineCount);
}

int main()
{
	cin >> LOOP;

	for (int ii = 1; ii <= LOOP; ii++)
	{
		alreadycore = 0;
		ans = 99999;
		core = 0;
		memset(map, 0, sizeof(map));
		v.clear();
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];

				if (map[i][j] == 1)
				{
					if (i != 0 && i != N - 1 && j != 0 && j != N - 1)
					{
						v.push_back(make_pair(i, j));
					}
					else if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
					{
						alreadycore++;
					}
				}
			}
		}

		DFS(0, 0, 0);

		printf("#%d %d\n", ii, ans);
	}
	
}

