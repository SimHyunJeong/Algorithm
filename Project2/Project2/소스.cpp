#include "iostream"
#include "stdio.h"
#include "string.h"
#include "vector"
#include "queue"
#include "deque"

using namespace std;

int N, M;
int map[501][501];
deque <int> dq;
int ans = 0;
int tempans = 0;

bool check(int x, int y, int block)
{
	int tx;
	int ty;

	if (block == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int td1[4] = { 1,1,1,1 };
			int td2[4] = { -1,-1,-1 ,-1 };

			tx = x;
			ty = y;

			//ºÏ
			if (i == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					ty += td1[i];

					if (ty >= 0 && ty < N)
					{
						tempans += map[ty][tx];
					}
					else
					{
						tempans = -1;
						break;
					}
				}
			}
			//¼­
			else if (i == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					tx += td2[i];

					if (tx >= 0 && tx < M)
					{
						tempans += map[ty][tx];
					}
					else
					{
						dq.clear();
						break;
					}
				}
			}
			//³²
			else if (i == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					ty += td2[i];

					if (ty >= 0 && ty < N)
					{
						tempans += map[ty][tx];
					}
					else
					{
						tempans = -1;
						break;
					}
				}
			}
			//µ¿
			else if (i == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					tx += td1[i];

					if (tx >= 0 && tx < M)
					{
						tempans += map[ty][tx];
					}
					else
					{
						tempans = -1;
						break;
					}
				}
			}

		}
	}
	else if (block == 1)
	{
		int td1[4] = { 0,1,0,1 };
		int td2[4] = { 0,0 ,1,1 };

		for (int i = 0; i < 4; i++)
		{
			tx = x + td1[i];
			ty = y + td2[i];

			if (tx >= 0 && tx < M && ty >= 0 && ty < N)
			{
				tempans += map[ty][tx];
			}
		}

	}
	else if (block == 2)
	{
		int td1[4] = { 0,0,1,1 };
		int td2[4] = {};
	}
	else if (block == 3)
	{

	}
	else if (block == 4)
	{

	}
}

void DFS(int x, int y, int block)
{
	for (int j = y; j < N; j++)
	{
		for (int i = x; i < M; i++)
		{
			check(i, j, block);

			if (tempans != -1)
			{
				ans = max(ans, tempans);
			}
			tempans = 0;
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
		}
	}

	DFS(0, 0, 0);

}