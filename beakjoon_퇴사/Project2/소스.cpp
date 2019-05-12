#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
int map[16][2];
int ans = 0;

void dfs(int index, int curday, int profit)
{
	if (index >= N)
	{
		ans = max(ans, profit);
		return;
	}
	
	for (int i = index; i < N; i++)
	{
		if (curday + map[i][0] <= N)
		{
			dfs(i+map[i][0], curday + map[i][0], profit + map[i][1]);
		}
		else
		{
			dfs(i + map[i][0], curday + map[i][0], profit);
		}
		curday++;
	}

}

int main()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> map[i][0] >> map[i][1];
	}

	dfs(0, 0, 0);

	cout << ans;
}