#include "iostream"
#include "string.h"
#include "stdio.h"
#include "queue"
#include "vector"
#include "deque"

using namespace std;

int N;
int map[21][21];

vector <int> v;
deque <int> dq[21];
int temp = 0;
int ans = 0;

void move(int dir)
{
	memset(map, 0, sizeof(map));

	for (int i = 0; i < N; i++)
	{
		deque <int> tdq;

		if (dq[i].size() > 1)
		{
			int size = dq[i].size();

			for (int ii = 0; ii < size-1; ii++)
			{
				int temp1 = dq[i].front(); dq[i].pop_front();
				int temp2 = dq[i].front(); dq[i].pop_front();

				if (temp1 != temp2)
				{
					tdq.push_back(temp1);
					dq[i].push_front(temp2);
					//continue;
				}
				else
				{
					tdq.push_back(temp1 * 2);
					//dq[i].pop_front();
					//dq[i].pop_front();
					ii++;
				}
			}
		}
		

		if (!dq[i].empty())
		{
			tdq.push_back(dq[i].front());
		}


		if (dir == 0)
		{
			for (int j = 0; j < tdq.size(); j++)
			{
				map[j][i] = tdq[j];
				temp = max(temp, tdq[j]);
			}
		}
		else if (dir == 1)
		{
			for (int j = 0; j < tdq.size(); j++)
			{
				map[i][j] = tdq[j];
				temp = max(temp, tdq[j]);
			}
		}
		else if (dir == 2)
		{
			for (int j = N-1; j >=0 ; j--)
			{
				if (!tdq.empty())
				{
					map[i][j] = tdq.front(); tdq.pop_front();
					temp = max(temp, map[i][j]);
				}
			}
		}
		else if (dir == 3)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				if (!tdq.empty())
				{
					map[j][i] = tdq.front(); tdq.pop_front();
					temp = max(temp, map[j][i]);
				}
			}
		}
	}
}

void calc()
{
	if (v.back() == 0)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[j][i] != 0)
				{
					dq[i].push_back(map[j][i]);
				}
			}
		}
	}
	else if (v.back() == 1)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] != 0)
				{
					dq[i].push_back(map[i][j]);
				}
			}
		}
	}
	else if (v.back() == 2)
	{
		for (int i = N-1; i >=0; i--)
		{
			for (int j = N-1; j >= 0; j--)
			{
				if (map[i][j] != 0)
				{
					dq[i].push_back(map[i][j]);
				}
			}
		}
	}
	else if (v.back() == 3)
	{
		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				if (map[j][i] != 0)
				{
					dq[i].push_back(map[j][i]);
				}
			}
		}
	}

	move(v.back());
	
	for (int i = 0; i < N; i++)
	{
		dq[i].clear();
	}
}

void copy(int a[21][21], int b[21][21])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}

void DFS(int cnt)
{
	int tmap[21][21];

	if (cnt == 5)
	{
		ans = max(ans, temp);
		temp = 0;
		return;
	}


	for (int i = 0; i < 4; i++)
	{
		v.push_back(i);
		copy(tmap,map);
		calc();
		DFS(cnt + 1);
		copy(map, tmap);
		v.pop_back();
	}

}

int main()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	
	
	DFS(0);

	cout << ans;

}