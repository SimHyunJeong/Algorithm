#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

#define MAX 21

using namespace std;

int map[MAX][MAX];
int ans = 99999;
bool check[MAX] ;
vector <int> v;
vector <int> vv;
int N;



int Find()
{
	int tempv = 0;

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			if (i != j)
			{
				tempv += map[v[i]][v[j]];
			}
		}
	}
	int tempvv = 0;

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			if (i != j)
			{
				tempvv += map[vv[i]][vv[j]];
			}
		}
	}

	return abs(tempv - tempvv);
}

void DFS(int count, int index)
{

	if (N / 2 == v.size())
	{
		vv.clear();

		for (int i = 0; i < N; i++)
		{
			bool temp = true;

			for (int j = 0; j < v.size(); j++)
			{
				if (i == v[j])
				{
					temp = false;
				}
			}

			if (temp)
			{
				vv.push_back(i);
			}
		}

		ans = min(ans, Find());
		return;
	}

	for (int i = index; i < N; i++)
	{
		v.push_back(i);
		DFS(count + 1,i+1);
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

	DFS(0,0);

	cout << ans;
}

