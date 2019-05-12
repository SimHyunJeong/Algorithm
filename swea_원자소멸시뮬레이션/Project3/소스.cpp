#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int N, K;

struct info
{
	int i;
	int x;
	int y;
	int d;
	int p;
};

vector <info> v;
int ans = 0;
int check[2000][2000] = { -1, };


void find()
{
	int dx[4] = {0,0,-1,1};
	int dy[4] = {-1,1,0,0};

	deque <pair<int, int>> bomp;

	while (!v.empty())
	{

		for (int i = 0; i < v.size(); i++)
		{
			int index = v[i].i;
			int x = v[i].x;
			int y = v[i].y;
			int d = v[i].d;
			int p = v[i].p;

			int tx = x + dx[d];
			int ty = y + dy[d];

			if (tx >= -1000 && tx <= 1000 && ty >= -1000 && ty <= 1000)
			{
				if (check[tx + 1000][ty + 1000] == -1)
				{
					check[tx + 1000][ty + 1000] = index;
				}
				else if (check[tx + 1000][ty + 1000].size() == 1)
				{
					bomp.push_back({ check[tx + 1000][ty + 1000].front().first, check[tx + 1000][ty + 1000].front().second});
					bomp.push_back({ index,p });
					check[tx + 1000][ty + 1000].push_back({ index,p });
				}
				else
				{
					bomp.push_back({ index,p });
					check[tx + 1000][ty + 1000].push_back({ index,p });
				}
			}
		}

		vector <info> temp;

		//겹치는거 터트리기
		for (int i = 0; i < v.size() ; i++)
		{
			if (!bomp.empty())
			{
				if (bomp.front().first == i)
				{
					ans += v[i].p;
					bomp.pop_front();
				}
				else
				{
					temp.push_back({ v[i].i, v[i].x, v[i].y, v[i].d, v[i].p });
				}
			}
			else
			{
				temp.push_back({ v[i].i, v[i].x, v[i].y, v[i].d, v[i].p });
			}
		}
		v.clear();
		v= temp;
	}
	
}


int main()
{
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			int a, b, c, d;
			cin >> a >> b >> c >> d;

			v.push_back({i,a,b,c,d });
		}

		find();

		printf("#%d %d\n", t, ans);

	}

}