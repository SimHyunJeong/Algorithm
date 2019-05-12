#include <stdio.h>
#include <string.h>
#include <deque>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int T;
int N, M, K, A, B;
int reception[11];
int fix[11];
int ans = 0;

struct info
{
	int index;
	int Rearrive;
	int Fixarrive;
	int Reception;
	int Fix;
};

deque <info> person;
deque <info> recepLine;
deque <info> fixLine;
deque <pair<int,int>> fixdq[11];
deque <pair<int, int>> recepdq[11];


bool compare(info a, info b)
{

	if (a.Fixarrive == b.Fixarrive)
	{
		return a.Reception < b.Reception;
	}
	else
	{
		return a.Fixarrive < b.Fixarrive;
	}

}

void calc()
{
	int time = 0;
	bool check = true;

	while(check)
	{
		check = false;
		//reception
		for (int n = 0; n < N; n++)
		{
			//비었으면 사람이 간다.
			if (recepdq[n].empty())
			{
				if (!recepLine.empty())
				{
					check = true;

					//도착시간 비교
					if (recepLine.front().Rearrive <= time)
					{
						recepdq[n].push_back({ recepLine.front().index ,reception[n] });
						//사람에게 reception index 넣어주기
						person[recepLine.front().index].Reception = n;
						recepLine.pop_front();
					}
				}
			}
			else
			{
				check = true;
				//고치는 시간
				if (recepdq[n].front().second == 1)
				{
					//접수다하고 fixline으로
					fixLine.push_back({ recepdq[n].front().first,0, time, n,0});
					recepdq[n].pop_back();

					if (!recepLine.empty())
					{
						//도착시간 비교
						if (recepLine.front().Rearrive <= time)
						{
							recepdq[n].push_back({ recepLine.front().index ,reception[n] });
							//사람에게 reception index 넣어주기
							person[recepLine.front().index].Reception = n;
							recepLine.pop_front();
						}
					}

				}
				else
				{
					recepdq[n].front().second--;
				}
			}
			
		}

		//fix
		for (int n = 0; n < M; n++)
		{
			if (fixdq[n].empty())
			{
				//기다리는 사람이 있으면
				if (!fixLine.empty())
				{
					check = true;
					fixdq[n].push_back({ fixLine.front().index ,fix[n] });
					//사람에게 reception index 넣어주기
					person[fixLine.front().index].Fix = n;
					fixLine.pop_front();
				}
			}
			else
			{
				check = true;

				//고치는 시간
				if (fixdq[n].front().second == 1)
				{
					fixdq[n].pop_back();

					//기다리는 사람이 있으면
					if (!fixLine.empty())
					{
						fixdq[n].push_back({ fixLine.front().index ,fix[n] });
						//사람에게 reception index 넣어주기
						person[fixLine.front().index].Fix = n;
						fixLine.pop_front();
					}

				}
				else
				{
					fixdq[n].front().second--;
				}
			}
			
		}

		time++;
	}

	for (int i = 0; i < K; i++)
	{
		if (person[i].Reception == A - 1 && person[i].Fix == B - 1)
		{
			ans += i + 1;
		}
	}

	if (ans == 0)
	{
		ans = -1;
	}
}

int main()
{
	int temp;

	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		cin >> N >> M >> K >> A >> B;
		ans = 0;
		person.clear();
		recepLine.clear();
		fixLine.clear();

		for (int n = 0; n < N; n++)
		{
			cin >> reception[n];
		}

		for (int n = 0; n < M; n++)
		{
			cin >> fix[n];
		}

		for (int i = 0; i < K; i++)
		{
			cin >> temp;
			person.push_back({i,temp,0,-1,-1});
			recepLine.push_back({ i,temp,0,0,0 });
		}

		calc();

		for (int n = 0; n < M; n++)
		{
			fixdq[n].clear();
		}

		for (int n = 0; n < N; n++)
		{
			recepdq[n].clear();
		}

		printf("#%d %d\n", t, ans);
	}


}