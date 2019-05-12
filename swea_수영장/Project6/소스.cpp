#include <stdio.h>
#include <string.h>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int money[4];
int month[13];
int minMoney = 99999;

void DFS(int mm, int total)
{
	if (mm > 12)
	{
		minMoney = min(total, minMoney);
		return;
	}

	if (month[mm] == 0)
	{
		DFS(mm + 1, total);
	}
	else
	{
		DFS(mm + 1, total + (month[mm] * money[0]));
		DFS(mm + 1, total + money[1]);
		DFS(mm + 3, total + money[2]);
		DFS(mm + 12,total + money[3]);
	}

}

int main()
{
	int TC = 0;

	cin >> TC;

	for (int t = 1; t <= TC; t++)
	{
		memset(money, 0, sizeof(money));
		memset(month, 0, sizeof(month));
		minMoney = 999999;

		for (int i = 0; i < 4; i++)
		{
			cin >> money[i];
		}

		for (int i = 1; i <= 12; i++)
		{
			cin >> month[i];
		}

		DFS(1, 0);

		printf("#%d %d\n", t, minMoney);
	}
	

	
}