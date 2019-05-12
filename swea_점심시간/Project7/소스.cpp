#include <stdio.h>
#include <string.h>
#include <queue>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct info
{
	int x;
	int y;
	int index;
	int time;
	int arrivetime;
};

info s1[2];
deque <info> p;
deque <info> stair[2];
deque <info> tstair[2];
int N;
int map[15][15];
int ans = 99999;
int ii = 0;


void calc()
{
	int time = 0;

	while (!(tstair[0].empty() && tstair[1].empty()))
	{
		time++;

		deque <info> temp[2];

		// 1번계단
		if (!tstair[0].empty())
		{
			temp[0] = tstair[0];
			tstair[0].clear();

			int s1Size = temp[0].size();
			int stairMax = 1;

			for (int i = 0; i < s1Size; i++)
			{

				if (temp[0][i].arrivetime < time)
				{
					if (temp[0][i].time != 0)
					{
						if (stairMax <= 3)
						{
							temp[0][i].time--;
							stairMax++;
						}
					}
					else
					{
						continue;
					}
				}
			
				tstair[0].push_back(temp[0][i]);

			}
		}


		// 2번계단
		if (!tstair[1].empty())
		{
			temp[1] = tstair[1];
			tstair[1].clear();

			int s2Size = temp[1].size();
			int stairMax = 1;

			for (int i = 0; i < s2Size; i++)
			{

				if (temp[1][i].arrivetime < time)
				{
					if (temp[1][i].time != 0)
					{
						if (stairMax <= 3)
						{
							temp[1][i].time--;
							stairMax++;
						}

					}
					else
					{
						continue;
					}
				}

				tstair[1].push_back(temp[1][i]);
			}
		}
	}
	ans = min(time, ans);

}

bool compare(info a, info b)
{
	if (a.arrivetime == b.arrivetime)
	{
		return a.index < b.index;
	}
	else
		return a.arrivetime < b.arrivetime;

}

void DFS(int pindex)
{
	if (pindex == ii)
	{
		tstair[0].clear();
		tstair[1].clear();
		tstair[0] = stair[0];
		tstair[1] = stair[1];
		sort(tstair[0].begin(), tstair[0].end(), compare);
		sort(tstair[1].begin(), tstair[1].end(), compare);
		calc();
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		stair[i].push_back(info{p[pindex].x,p[pindex].y,p[pindex].index, s1[i].time , abs(p[pindex].x -s1[i].x) + abs(p[pindex].y - s1[i].y) });
		DFS(pindex + 1);
		stair[i].pop_back();
	}
	
}

int main()
{
	int T = 0;
	cin >> T;
	int si = 0;

	for (int t = 1; t <= T; t++)
	{
		ii = 0;
		memset(map, 0, sizeof(map));
		ans = 99999;
		p.clear();
		stair[0].clear(); 
		stair[1].clear();
		si = 0;
		cin >> N;

		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> map[i][j];

				if (map[i][j] == 1)
				{
					p.push_back({ j,i,ii });
					ii++;
				}
				else if (map[i][j] >= 2)
				{
					s1[si].x = j;
					s1[si].y = i;
					s1[si].time = map[i][j];
					s1[si].index = si;
					si++;
				}
			}
		}

		DFS(0);

		printf("#%d %d\n", t, ans);
	}


}