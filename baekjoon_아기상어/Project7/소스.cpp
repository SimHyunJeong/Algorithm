#include <stdio.h>
#include <string.h>
#include <deque>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct info
{
	int x;
	int y;
	int age;
	int eat;
	int time;
};

int map[21][21];
bool check[21][21] = { false, };
int ans = 0;
vector <info> eatFish;
vector <info> now;
queue <info> q;
int N = 0;

void find()
{
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int a = q.front().age;
		int e = q.front().eat;
		int t = q.front().time;

		q.pop();

		if (!eatFish.empty())
		{
			if (t > eatFish.front().time)
			{
				while (!q.empty())
				{
					q.pop();
				}
				break;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			int tx = x + dx[i];
			int ty = y + dy[i];

			if (check[ty][tx]==false && tx >= 0 && tx < N && ty >= 0 && ty < N)
			{
				if (map[ty][tx] == 0)
				{
					q.push({ tx, ty, a, e , t + 1 });
				}
				//물고기가 있다
				else
				{
					// 먹을수있다
					if (now.front().age > map[ty][tx])
					{
						if (now.front().eat + 1 == now.front().age)
						{
							eatFish.push_back({ tx,ty, now.front().age +1, 0 ,t + 1 });
						}
						else
						{
							eatFish.push_back({ tx,ty, now.front().age, now.front().eat + 1, t + 1 });
						}
					}
					else if (now.front().age < map[ty][tx])
					{
						//못지나감..
					}
					else
					{
						q.push({tx, ty, a, e , t + 1});
					}
				}
				check[ty][tx] = true;
			}


		}


	}

}

bool compare(info a, info b)
{
	if (a.time == b.time)
	{
		if (a.y == b.y)
		{
			return a.x < b.x;
		}
		else
		{
			return a.y < b.y;
		}
	}
	else
	{
		return a.time < b.time;
	}

}

void show()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

int main()
{
	info tt;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 9)
			{
				tt.x = j;
				tt.y = i;
				tt.age = 2;
				tt.eat = 0;
				tt.time = 0;
				check[i][j] = true;
				now.push_back(tt);
				q.push(tt);
			}
		}
	}

	while (1)
	{
		find();
		memset(check, false, sizeof(check));

		if (!eatFish.empty())
		{
			map[now.front().y][now.front().x] = 0;
			now.clear();
			sort(eatFish.begin(), eatFish.end(), compare);
			now.push_back(eatFish.front());
			map[eatFish.front().y][eatFish.front().x] = 9;
			check[eatFish.front().y][eatFish.front().x] = true;
			eatFish.clear();
			ans = now.front().time;
			//show();
			q.push(now.front());
		}
		else
		{
			break;
		}
	}

	cout << ans;

}