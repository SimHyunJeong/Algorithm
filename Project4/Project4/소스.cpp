#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <math.h>

using namespace std;

vector <int> oper;
deque <long long> num;
int T, N;
long long minNum = 999999;
long long maxNum = 0;

void calc()
{

	do {

		deque <long long> t = num;

		for (int i = 0; i < oper.size(); i++)
		{
			int a = t.front(); t.pop_front();
			int b = t.front(); t.pop_front();

			if (oper[i] == 0)
			{
				t.push_front(a + b);
			}
			else if (oper[i] == 1)
			{
				t.push_front(a - b);
			}
			else if (oper[i] == 2)
			{
				t.push_front(a * b);
			}
			else if (oper[i] == 3)
			{
				t.push_front(a / b);
			}
		}

		minNum = min(t.front(), minNum);
		maxNum = max(t.front(), maxNum);
		t.clear();

	} while (next_permutation(oper.begin(), oper.end()));

}

int main()
{
	int temp;

	cin >> T;

	for (int t = 1; t <= T; t++)
	{

		minNum = 999999;
		maxNum = 0;
		
		cin >> N;

		for (int i = 0; i < 4; i++)
		{
			cin >> temp;
			int count = 0;

			while (temp != count)
			{
				oper.push_back(i);
				count++;
			}
		}

		for (int i = 0; i < N; i++)
		{
			int number = 0;
			cin >> number;
			num.push_back({ number });
		}

		calc();

		oper.clear();
		num.clear();

		printf("#%d %d\n", t, abs(maxNum - minNum));
	}
	
}