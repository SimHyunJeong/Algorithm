#include <iostream>
#include"deque"
#include "stdio.h"
#include "string.h"
#include "vector"
#include <queue>
#include "algorithm"

using namespace std;

int block[6] = { 0,0,0,0,0,0 };
int map[21][21];
int K;
vector <int> v;
int M, N;
int xx, yy;

/*
  2
4 1 3
  5
  6
*/
// 0 뒤 1 위 2 앞 3 아래 4왼쪽 5오른쪽
void turn(int dir)
{
	int tx = xx;
	int ty = yy;
	
	deque <int> dq;

	//동
	if (dir == 1)
	{
		tx += 1;

		if (tx >= 0 && tx < M)
		{
			dq.push_back(block[5]);
			dq.push_back(block[3]); 
			dq.push_back(block[4]); 
			dq.push_back(block[1]); 

			block[3] = dq.front(); dq.pop_front();
			block[4] = dq.front(); dq.pop_front();
			block[1] = dq.front(); dq.pop_front();
			block[5] = dq.front(); dq.pop_front();

			if (map[ty][tx] == 0)
			{
				map[ty][tx] = block[3];
			}
			else
			{
				block[3] = map[ty][tx];
				map[ty][tx] = 0;
			}

			printf("%d\n", block[1]);

			xx = tx;
			yy = ty;
		}

	}
	else if (dir == 2)
	{
		tx -= 1;

		if (tx >= 0 && tx < M)
		{
			dq.push_back(block[4]); 
			dq.push_back(block[1]);
			dq.push_back(block[5]);
			dq.push_back(block[3]);

		
			block[3] = dq.front(); dq.pop_front();
			block[4] = dq.front(); dq.pop_front();
			block[1] = dq.front(); dq.pop_front();
			block[5] = dq.front(); dq.pop_front();

			if (map[ty][tx] == 0)
			{
				map[ty][tx] = block[3];
			}
			else
			{
				block[3] = map[ty][tx];
				map[ty][tx] = 0;
			}

			printf("%d\n", block[1]);

			xx = tx;
			yy = ty;
		}
	}
	else if (dir == 3)
	{
		ty -= 1;

		if (ty >= 0 && ty < N)
		{
			dq.push_back(block[0]);
			dq.push_back(block[1]);
			dq.push_back(block[2]);
			dq.push_back(block[3]);

			block[3] = dq.front(); dq.pop_front();
			block[0] = dq.front(); dq.pop_front();
			block[1] = dq.front(); dq.pop_front();
			block[2] = dq.front(); dq.pop_front();

			if (map[ty][tx] == 0)
			{
				map[ty][tx] = block[3];
			}
			else
			{
				block[3] = map[ty][tx];
				map[ty][tx] = 0;
			}

			printf("%d\n", block[1]);

			xx = tx;
			yy = ty;
		}
	}
	else if (dir == 4)
	{

		ty += 1;

		if (ty >= 0 && ty < N)
		{
			dq.push_back(block[2]);
			dq.push_back(block[1]);
			dq.push_back(block[0]);
			dq.push_back(block[3]);


			block[3] = dq.front(); dq.pop_front();
			block[2] = dq.front(); dq.pop_front();
			block[1] = dq.front(); dq.pop_front();
			block[0] = dq.front(); dq.pop_front();

			if (map[ty][tx] == 0)
			{
				map[ty][tx] = block[3];
			}
			else
			{
				block[3] = map[ty][tx];
				map[ty][tx] = 0;
			}

			printf("%d\n", block[1]);

			xx = tx;
			yy = ty;
		}
	}
}

void find()
{

	for (int i = 0; i < K; i++)
	{
		int dir = v[i];

		turn(dir);
	}

}

int main()
{
	cin >> N >> M >> yy >> xx >> K;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < K; i++)
	{
		int temp;
		cin >> temp;
		v.push_back(temp);
	}

	find();
}