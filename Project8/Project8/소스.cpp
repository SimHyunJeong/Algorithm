#include <stdio.h>
#include <deque>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct info{
	int first;
	int second;
	int cnt;
};

int N, M;
int map[51][51];
int cpymap[51][51];
vector <pair<int, int>> q;
vector <int> vIndex;
int ans = 999999;

void copy()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cpymap[i][j] = map[i][j];
		}
	}
}

bool ok()
{
	bool tt = true;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (cpymap[i][j] == 0)
			{
				tt = false;
				return tt;
			}
		}
	}

	return tt;
}

void spread()
{
	queue <info> temp;
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	int c = -9;

	for (int i = 0; i < M; i++)
	{
		temp.push({q[vIndex[i]].first,q[vIndex[i]].second, -9});
		cpymap[q[vIndex[i]].second][q[vIndex[i]].first] = -9;
	}


	while (!temp.empty())
	{
		if (c != temp.front().cnt)
		{
			if (ok() == true)
			{
				ans = min(ans, abs( -10 - c));
				break;
			}
		}

		int x = temp.front().first;
		int y = temp.front().second;
		c = temp.front().cnt;

		temp.pop();

		for (int i = 0; i < 4; i++)
		{
			int tx = x + dx[i];
			int ty = y + dy[i];

			if (tx >= 0 && tx < N && ty >= 0 && ty < N)
			{
				if (cpymap[ty][tx] == 0 || cpymap[ty][tx] == 2)
				{
					cpymap[ty][tx] = c + 1;
					temp.push({ tx,ty,c + 1 });
				}
			}
		}
	}

}

void pick(int index)
{
	if (vIndex.size() == M)
	{
		copy();
		spread();
		return;
	}

	for (int i = index; i < q.size(); i++)
	{
		vIndex.push_back(i);
		pick(i+1);
		vIndex.pop_back();
	}

}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 2)
			{
				q.push_back({j,i});
			}
		}
	}

	copy();
	if (ok() == true)
	{
		cout << "0";
	}
	else
	{
		pick(0);
		if (ans == 999999)
		{
			ans = -1;
		}

		cout << ans;

	}

	
}