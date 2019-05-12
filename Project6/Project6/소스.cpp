#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

struct info {
	int x;
	int y;
	int time;
};

int TC, N, M, R, C, T;
int map[51][51];
queue <info> q;
deque <int> d;
int ans = 1;

void dir(int dir)
{
	if (dir == 1)
	{
		d.push_back(0);
		d.push_back(1);
		d.push_back(2);
		d.push_back(3);
	}
	else if (dir == 2)
	{
		d.push_back(2);
		d.push_back(3);
	}
	else if (dir == 3)
	{
		d.push_back(0);
		d.push_back(1);
	}
	// ¿À ¿Þ ¾Æ·¡ À§
	else if (dir == 4)
	{
		d.push_back(3);
		d.push_back(0);
	}
	else if (dir == 5)
	{
		d.push_back(0);
		d.push_back(2);
	}
	else if (dir == 6)
	{
		d.push_back(1);
		d.push_back(2);
	}
	else if (dir == 7)
	{
		d.push_back(1);
		d.push_back(3);
	}
}

bool turnok(int nextdir, int curdir, int dirindex)
{
	// ¿À ¿Þ ¾Æ·¡ À§

	if (curdir == 1)
	{
		if (dirindex == 0)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 6 || nextdir == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 1)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 4 || nextdir == 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex ==2)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 4 || nextdir == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 3)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 5 || nextdir == 6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	// ¿À ¿Þ ¾Æ·¡ À§

	else if (curdir == 2)
	{
		if (dirindex == 3)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 5 || nextdir == 6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 2)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 4 || nextdir == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	// ¿À ¿Þ ¾Æ·¡ À§

	else if (curdir == 3)
	{
		if (dirindex == 0)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 7 || nextdir == 6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 1)
		{
			if (nextdir == 1 || nextdir == 3 ||  nextdir == 4 || nextdir == 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	// ¿À ¿Þ ¾Æ·¡ À§

	else if (curdir == 4)
	{
		if (dirindex == 3)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir ==5 || nextdir == 6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 0)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 6 || nextdir == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}	// ¿À ¿Þ ¾Æ·¡ À§
	else if (curdir == 5)
	{
		if (dirindex == 0)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 7 || nextdir == 6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 2)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 4 || nextdir == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}	// ¿À ¿Þ ¾Æ·¡ À§
	else if (curdir == 6)
	{
		if (dirindex == 1)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 4 || nextdir == 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 2)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 4 || nextdir == 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}	// ¿À ¿Þ ¾Æ·¡ À§
	else if (curdir == 7)
	{
		if (dirindex == 1)
		{
			if (nextdir == 1 || nextdir == 3 || nextdir == 4 || nextdir == 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (dirindex == 3)
		{
			if (nextdir == 1 || nextdir == 2 || nextdir == 5 || nextdir == 6)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

}

void find()
{
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	bool check[51][51] = { false, };
	check[q.front().y][q.front().x] = true;

	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int t = q.front().time;
		q.pop();


		dir(map[y][x]);

		for (int i = 0; i < d.size(); i++)
		{
			int tx = x + dx[d[i]];
			int ty = y + dy[d[i]];

			if (tx >= 0 && tx < M && ty >= 0 && ty < N)
			{
				if (check[ty][tx] == false && map[ty][tx]!=0 && t < T)
				{
					if (turnok(map[ty][tx], map[y][x], d[i]))
					{
						check[ty][tx] = true;
						q.push({ tx,ty,t + 1 });
						ans++;
					}
				}
			}
		}

		d.clear();

	}

}

int main()
{

	cin >> TC;

	for (int t = 1; t <= TC; t++)
	{
		memset(map, 0, sizeof(map));
		ans = 1;

		cin >> N >> M >> R >> C >> T;

		for(int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> map[i][j];
			}
		}

		q.push({ C,R,1 });
		find();

		printf("#%d %d\n", t, ans);
	}
	
	
}