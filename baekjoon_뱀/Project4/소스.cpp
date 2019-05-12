#include <stdio.h>
#include <string.h>
#include <iostream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

int N, K, L;

deque <pair<int, char>> turn;
deque <pair<int, int>> dq;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int map[101][101];

int dir = 0;
int ans = 0;

void go()
{
	while (1)
	{
		ans++;

		int x = dq.front().first + dx[dir];
		int y = dq.front().second + dy[dir];

		if (x >= 1 && x <= N && y >= 1 && y <= N)
		{
			//apple 
			if (map[y][x] == 1)
			{
				dq.push_front({x,y});
				map[y][x] = 2;
			}
			//blank
			else if(map[y][x]==0)
			{
				map[dq.back().second][dq.back().first] = 0;
				dq.pop_back();
				dq.push_front({ x,y });
				map[y][x] = 2;
			}
			//snack
			else
			{
				break;
			}
		}
		else
		{
			break;
		}


		if (!turn.empty())
		{
			if (turn.front().first == ans)
			{
				//turn right
				if (turn.front().second == 'D')
				{
					dir = (dir + 1) % 4;
				}
				//turn left
				else
				{
					dir = (dir + 3) % 4;
				}
				turn.pop_front();
			}

		}


	}

}

int main()
{
	cin >> N;
	cin >> K;

	for (int i = 0; i < K; i++)
	{
		int y, x;
		cin >> y >> x;
		map[y][x] = 1;
	}
	cin >> L;

	for (int i = 0; i < L; i++)
	{
		int second;
		char dir;
		cin >> second >> dir;
		turn.push_back({ second,dir });
	}

	dq.push_back({ 1,1 });
	map[1][1] = 2;
	go();

	cout << ans;
}