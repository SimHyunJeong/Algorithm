#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct info
{
	int rx;
	int ry;
	int bx;
	int by;
	int dir;
	int count;
};

int N, M;
char map[50][50];
deque <info> ball;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int ans = 0;

int findPri(int rx, int ry, int bx, int by, int dir)
{
	int priority; // r 0 b 1

	//r b 우선순위 찾기
	if (dir == 0)
	{
		if (ry < by)
		{
			priority = 0;
		}
		else
		{
			priority = 1;
		}
	}
	else if (dir == 1)
	{
		if (ry > by)
		{
			priority = 0;
		}
		else
		{
			priority = 1;
		}
	}
	else if (dir == 2)
	{
		if (rx < bx)
		{
			priority = 0;
		}
		else
		{
			priority = 1;
		}
	}
	else if (dir == 3)
	{
		if (rx > bx)
		{
			priority = 0;
		}
		else
		{
			priority = 1;
		}
	}

	return priority;

}

void bfs()
{
	while (!ball.empty())
	{
		int dir = ball.front().dir;
		int rx = ball.front().rx;
		int ry = ball.front().ry;
		int bx = ball.front().bx;
		int by = ball.front().by;
		int count = ball.front().count;

		if (ans > 0)
		{
			if (ans < count)
			{
				break;
			}
		}

		if (count > 10)
		{
			ans = -1;
			break;
		}

	
		ball.pop_front();

		//우선순위
		int pri = findPri(rx, ry, bx, by, dir);

		//빨간공부터
		if (pri == 0)
		{
			bool blueshot = false;
			bool redshot = false;
			
			//빨강공 움직이기
			while (1)
			{
				rx += dx[dir];
				ry += dy[dir];

				if (map[ry][rx] == '#')
				{
					rx -= dx[dir];
					ry -= dy[dir];
					break;
				}

				if (rx == bx && ry == by)
				{
					rx -= dx[dir];
					ry -= dy[dir];
					break;
				}

				if (map[ry][rx] == 'O')
				{
					rx = 0;
					ry = 0;
					redshot = true;
					break;
				}

			}

			while (1)
			{
				bx += dx[dir];
				by += dy[dir];

				if (map[by][bx] == '#')
				{
					bx -= dx[dir];
					by -= dy[dir];
					break;
				}

				if (rx == bx && ry == by)
				{
					bx -= dx[dir];
					by -= dy[dir];
					break;
				}

				if (map[by][bx] == 'O')
				{
					by = 0;
					bx = 0;
					blueshot=true;
					break;
				}
			}

			//파란공만
			if (blueshot == true)
			{
				continue;
			}
			//빨간공만
			else if (redshot == true)
			{
				ans = count;
			}
			//안들어 갔을 경우
			else if (blueshot == false && redshot == false)
			{

				if (dir == 0 || dir == 1)
				{
					ball.push_back({ rx,ry,bx,by,2,count + 1 });
					ball.push_back({ rx,ry,bx,by,3,count + 1 });
				}
				else
				{
					ball.push_back({ rx,ry,bx,by,0,count + 1 });
					ball.push_back({ rx,ry,bx,by,1,count + 1 });
				}
			}
		}
		//파란공
		else
		{
			bool blueshot = false;
			bool redshot = false;

			//파란공 움직이기
			while (1)
			{
				bx += dx[dir];
				by += dy[dir];

				if (map[by][bx] == '#')
				{
					bx -= dx[dir];
					by -= dy[dir];
					break;
				}

				if (rx == bx && ry == by)
				{
					bx -= dx[dir];
					by -= dy[dir];
					break;
				}

				if (map[by][bx] == 'O')
				{
					bx = 0;
					by = 0;
					blueshot = true;
					break;
				}
			}

			//빨강공 움직이기
			while (1)
			{
				rx += dx[dir];
				ry += dy[dir];

				if (map[ry][rx] == '#')
				{
					rx -= dx[dir];
					ry -= dy[dir];
					break;
				}

				if (rx == bx && ry == by)
				{
					rx -= dx[dir];
					ry -= dy[dir];
					break;
				}

				if (map[ry][rx] == 'O')
				{
					rx = 0;
					ry = 0;
					redshot = true;
					break;
				}
			}

			//파란공
			if (blueshot == true)
			{
				continue;
			}
			// 둘다
			else if (redshot == true)
			{
				ans = count;
			}
			//안들어 갔을 경우
			else if (blueshot == false && redshot == false)
			{
				if (dir == 0 || dir == 1)
				{
					ball.push_back({ rx,ry,bx,by,2,count + 1 });
					ball.push_back({ rx,ry,bx,by,3,count + 1 });
				}
				else
				{
					ball.push_back({ rx,ry,bx,by,0,count + 1 });
					ball.push_back({ rx,ry,bx,by,1,count + 1 });
				}

			}
		}
	}
}

int main()
{
	int rx, ry, bx, by;

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];

			if (map[i][j] == 'R')
			{
				rx = j;
				ry = i;
				map[i][j] = '.';
			}

			if (map[i][j] == 'B')
			{
				bx = j;
				by = i;
				map[i][j] = '.';
			}
		}
	}

	ball.push_back({ rx,ry,bx,by,0,1 });
	ball.push_back({ rx,ry,bx,by,1,1 });
	ball.push_back({ rx,ry,bx,by,2,1 });
	ball.push_back({ rx,ry,bx,by,3,1 });

	bfs();


	cout << ans;
}