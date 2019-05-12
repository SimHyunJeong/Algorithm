#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

int map[17][17];
vector <int> v;
int N,M, D;
bool loop = true;
int ans = 0;

struct info {

	int x;
	int y;
	int d;

};

bool compare(info a, info b)
{
	if (a.d == b.d)
	{
		return a.x < b.x;
	}

	return a.d < b.d;

}

void drop()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = N-2; j >= 0; j--)
		{
			if (map[j][i] == 1)
			{
				loop = true;
			}

			map[j + 1][i] = map[j][i];
		}

		map[0][i] = 0;
	}


}

void put()
{
	queue <info> q;
	vector <info> kill;
	deque <info> temp;
	int copymap[17][17];

	do {

		memcpy(copymap, map, sizeof(map));
		int killnum = 0;

			while (loop)
			{
		
			loop = false;
		
			for (int i = 0; i < M; i++)
			{
				bool check[17][17] = { false, };
				int mind = -1;

				if (v[i] == 1)
				{
					q.push({ i,N,0 });
				}


				while (!q.empty())
				{
					int x = q.front().x;
					int y = q.front().y;
					int d = q.front().d;
					q.pop();

					if (d > D)
					{
						break;
					}

					if (mind != -1 && d > mind)
					{
						break;
					}

					int dx[4] = { 1,-1,0,0 };
					int dy[4] = { 0,0,1,-1 };

					for (int ii = 0; ii < 4; ii++)
					{
						int tx = x + dx[ii];
						int ty = y + dy[ii];

						if (tx >= 0 && tx < M && ty >= 0 && ty < N)
						{
							if (check[ty][tx] == false)
							{
								check[ty][tx] = true;
								q.push({ tx,ty,d + 1 });

								if (map[ty][tx] == 1 && d < D)
								{
									temp.push_back({ tx,ty,d + 1 });
									if (mind == -1)
									{
										mind = d + 1;
									}
								}

							}
						}
					}
				}

				if (temp.size() > 0)
				{
					sort(temp.begin(), temp.end(), compare);
					kill.push_back(temp.front());
				}

				temp.clear();

				while (!q.empty())
				{
					q.pop();
				}

			}

			for (int i = 0; i < kill.size(); i++)
			{
				if (map[kill[i].y][kill[i].x] == 1)
				{
					map[kill[i].y][kill[i].x] = 0;
					killnum++;
				}
			}
			drop();
			kill.clear();

		}

		ans = max(killnum, ans);
		memcpy(map, copymap, sizeof(map));
		kill.clear();
		loop = true;
	} while (next_permutation(v.begin(), v.end()));
	


}


int main()
{
	cin >> N >> M >> D;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	
	for (int j = 3; j < M; j++)
	{
		v.push_back(0);
	}

	v.push_back(1);
	v.push_back(1);
	v.push_back(1);


	put();
	
	cout << ans;
}