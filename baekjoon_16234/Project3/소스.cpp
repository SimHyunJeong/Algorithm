#include<iostream>
#include<queue>
#include<vector>
#include <string.h>

using namespace std;

int N, L, R;
int Map[51][51];
int tempMap[51][51];
bool check[51][51] = { false, };
bool tempCheck[51][51] = { false, };

struct info
{
	int x;
	int y;
	int people;
};

vector <info> v;
queue <info> q;
bool bl = true;

void copy()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tempMap[i][j] != 0)
			{
				Map[i][j] = tempMap[i][j];
			}
		}
	}
}

int main()
{
	int ans = -1;
	cin >> N >> L >> R;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
		}
	}

	while (bl)
	{
		bl = false;
		ans++;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (check[i][j] == false && tempCheck[i][j] == false)
				{
					q.push({i, j,Map[i][j]});
					check[i][j] = true;

					while (!q.empty())
					{
						int dx[4] = { 1,-1,0,0 };
						int dy[4] = { 0,0,1,-1 };

						int x = q.front().x;
						int y = q.front().y;
						q.pop();

						for (int ii = 0; ii < 4; ii++)
						{
							int tx = x + dx[ii];
							int ty = y + dy[ii];

							if (tempCheck[tx][ty]==false && tx>=0 && tx<N &&ty>=0 && ty<N  &&
								abs(Map[x][y] - Map[tx][ty]) >= L && abs(Map[x][y] - Map[tx][ty]) <= R)
							{
								if (check[tx][ty] == false)
								{
									tempCheck[tx][ty] = true;
									q.push({ tx, ty, Map[tx][ty] });
									v.push_back({ tx, ty, Map[tx][ty] });
								}
							}
							check[tx][ty] = true;
						}

						memset(check, false, sizeof(check));
					}

					int sum = 0;

					for (int ss = 0; ss < v.size(); ss++)
					{
						bl = true;
						sum += v.at(ss).people;
					}

					for (int ss = 0; ss < v.size(); ss++)
					{
						int x = v.at(ss).x;
						int y = v.at(ss).y;

						tempMap[x][y] = sum / v.size();
					}
					v.clear();
				}
				memset(check, false, sizeof(check));
			}
		}
		copy();
		memset(tempCheck, false, sizeof(tempCheck));
		memset(tempMap, false, sizeof(tempMap));
	}

	cout << ans << endl;
	return 0;

}