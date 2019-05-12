#include <stdio.h>
#include <string.h>
#include <deque>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

char map[12][6];
int ans;

void drop()
{
	deque <char> dq;

	for (int j = 0; j < 6; j++)
	{
		for (int i = 11; i >= 0; i--)
		{
			if (map[i][j] != '.')
			{
				dq.push_back(map[i][j]);
				map[i][j] = '.';
			}
		}

		for (int ii = 0; ii < dq.size(); ii++)
		{
			map[11 - ii][j] = dq[ii];
		}

		dq.clear();
	}

}

void bamp()
{
	queue <pair<int, int>> q;
	deque <pair<int, int>> bamp;
	bool check[12][6] = { false, };
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	int j = 0;
	bool ch = true;

	while (ch)
	{
		ch = false;

		for (int i = 11; i >= 0; i--)
		{
			j = 0;

			for (; j < 6; j++)
			{
				if (map[i][j] != '.')
				{
					q.push({ j,i });
					bamp.push_back({ j,i });
					check[i][j] = true;

					while (!q.empty())
					{
						int x = q.front().first;
						int y = q.front().second;
						q.pop();

						for (int i = 0; i < 4; i++)
						{
							int tx = x + dx[i];
							int ty = y + dy[i];

							if (tx >= 0 && tx < 6 && ty >= 0 && ty < 12)
							{
								if (check[ty][tx] == false && map[ty][tx] == map[y][x])
								{
									check[ty][tx] = true;
									q.push({ tx,ty });
									bamp.push_back({ tx,ty });
								}

							}
						}
					}

					if (bamp.size() >= 4)
					{
						int size = bamp.size();

						for (int i = 0; i < size; i++)
						{
							map[bamp[i].second][bamp[i].first] = '.';
						}

						ch = true;
						j = -1;
						//drop();
					}
					//bamp.clear();
					//memset(check, false, sizeof(check));

				}
				bamp.clear();
				memset(check, false, sizeof(check));
			}
		}

		if (ch == true)
		{
			ans++;
		}

		drop();
	}
	

}

int main()
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cin >> map[i][j];
		}
	}


	bamp();

	cout << ans;
}