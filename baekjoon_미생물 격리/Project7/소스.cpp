#include <stdio.h>
#include <string.h>
#include <deque>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct info {
	int x;
	int y;
	int dir;
	int cnt;
};

vector <info> map[101][101];
deque <info> ll;
int ans = 0;
int N, K, M;

int turndir(int dir)
{
	if (dir == 1)
	{
		dir = 2;
	}
	else if (dir == 2)
	{
		dir = 1;
	}
	else if (dir == 3)
	{
		dir = 4;
	}
	else if (dir == 4)
	{
		dir = 3;
	}
	return dir;
}

bool compare(info a, info b)
{
	return a.cnt > b.cnt;
}

void sum()
{
	ans = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j].size() > 1)
			{
				sort(map[i][j].begin(), map[i][j].end(), compare);
				int dir = map[i][j].front().dir;
				int temp = 0;

				for (int ii = 0; ii < map[i][j].size(); ii++)
				{
					temp += map[i][j][ii].cnt;
				}
				ll.push_back({j,i,dir,temp });
				ans += temp;
			}
			else if(map[i][j].size() == 1)
			{
				ans += map[i][j].front().cnt;
				ll.push_back(map[i][j].front());
			}

			map[i][j].clear();
		}
	}
}

void move()
{
	int dx[5] = {0,0,0,-1,1};
	int dy[5] = { 0,-1,1,0,0 };

	deque <info> t;

	for (int i = 0; i < ll.size(); i++)
	{
		int x = ll[i].x;
		int y = ll[i].y;
		int dir = ll[i].dir;
		int cnt = ll[i].cnt;

		int tx = x + dx[dir];
		int ty = y + dy[dir];

		if (tx >= 0 && tx < N && ty >= 0 && ty < N)
		{
			if (tx == 0 || tx == N - 1 || ty == 0 || ty == N - 1)
			{
				dir = turndir(dir);
				map[ty][tx].push_back({ tx,ty,dir,cnt/2 });
			}
			else
			{
				map[ty][tx].push_back({ tx,ty,dir,cnt });
			}
		}
	}
	ll.clear();
	sum();


}

int main()
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		ans = 0;
		ll.clear();

		cin >> N >> K >> M;

		for (int i = 0; i < M; i++)
		{
				info ii;
				cin >> ii.y >> ii.x >> ii.cnt >> ii.dir;
				//map[ii.y][ii.x].push_back(ii);
				ll.push_back(ii);
		}
		
		for (int ii = 0; ii < K; ii++)
		{
			move();
		}

		printf("#%d %d\n", t, ans);
	}

}