#include<iostream>
#include <queue>
#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

vector <pair<int, int>> ch;
vector <pair<int, int>> house;
bool chickCheck[51] = { false, };
int map[51][51];
int ans = 999999;
int N, M;

void findMin()
{
	int chickDist[101];
	fill_n(chickDist, 101, 99999);

	for (int i = 0; i < ch.size(); i++)
	{
		if (chickCheck[i] == true)
		{
			for (int ii = 0; ii < house.size(); ii++)
			{
				int dist = abs(house[ii].first - ch[i].first) + abs(house[ii].second - ch[i].second);

				if (chickDist[ii] > dist)
				{
					chickDist[ii] = dist;
				}
			}
		}
	}
	int temp = 0;

	for (int ii = 0; ii < house.size(); ii++)
	{
		temp += chickDist[ii];
	}

	if (ans > temp)
		ans = temp;
}

void DFS(int chickCount, int chickIndex)
{
	if (chickIndex > ch.size())
		return;

	if (M == chickCount)
	{
		findMin();
		return;
	}
	
	chickCheck[chickIndex] = true;
	DFS(chickCount + 1, chickIndex + 1);
	chickCheck[chickIndex] = false;
	DFS(chickCount, chickIndex + 1);
	
}

int main()
{

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 1)
			{
				house.push_back(make_pair(i, j));
			}
			else if (map[i][j] == 2)
			{
				ch.push_back(make_pair(i, j));
			}
		}
	}

	DFS(0,0);

	cout << ans;
}