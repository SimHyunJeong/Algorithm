#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

int N;
deque <int> map;
int oper[4];
int minAns = 1000000000;
int maxAns = -1000000000;
vector <int> v;

void Calcu()
{
	do {
		int temp1 = 0;
		int temp2 = 0;
		deque<int> dq = map;

		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] == 0)
			{
				temp1 = dq.front(); dq.pop_front();
				temp2 = dq.front(); dq.pop_front();
				dq.push_front(temp1 + temp2);
			}
			else if (v[i] == 1)
			{
				temp1 = dq.front(); dq.pop_front();
				temp2 = dq.front(); dq.pop_front();
				dq.push_front(temp1 - temp2);
			}
			else if (v[i] == 2)
			{
				temp1 = dq.front(); dq.pop_front();
				temp2 = dq.front(); dq.pop_front();
				dq.push_front(temp1 * temp2);
			}
			else if (v[i] == 3)
			{
				temp1 = dq.front(); dq.pop_front();
				temp2 = dq.front(); dq.pop_front();
				dq.push_front(temp1 / temp2);
			}
		}

		minAns = min(minAns, dq.front());
		maxAns = max(maxAns, dq.front());
		dq.pop_front();

	} while (next_permutation(v.begin(), v.end()));

}

int main()
{
	cin >> N;

	int temp;

	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		map.push_back(temp);
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> oper[i];
	}

	for (int i = 0; i < 4; i++)
	{
		temp = 0;

		while (temp != oper[i])
		{
			if (i == 0)
			{
				v.push_back(0);
			}
			else if (i == 1)
			{
				v.push_back(1);
			}
			else if (i == 2)
			{
				v.push_back(2);
			}
			else if (i == 3)
			{
				v.push_back(3);
			}
			temp++;
		}
	}

	sort(v.begin(), v.end());
	Calcu();

	cout << maxAns << endl;
	cout << minAns << endl;
}