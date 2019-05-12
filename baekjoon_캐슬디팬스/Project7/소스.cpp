#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>

using namespace std;

int testcase = 0;
int realanswer = 0;
int mapindex = 0;
bool deeptrue = false;
int map[9][9] = { 0 };
int mount = 0;
int deepcount = 0;
bool check[9][9] = { false };


void findlong(int x, int y, int answer, bool deeptrue, int high) {

	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	if (realanswer < answer)
	{
		realanswer = answer;
	}

	for (int i = 0; i < 4; i++)
	{
		int temp_x = x + dx[i];
		int temp_y = y + dy[i];

		//주변 살피기
		if (check[temp_y][temp_x] == false && temp_x >= 0 && temp_x < mapindex && temp_y >= 0 && temp_y < mapindex)
		{
			//높이보다 작다
			if (map[y][x] > map[temp_y][temp_x])
			{
				check[temp_y][temp_x] = true;
				findlong(temp_x, temp_y, answer + 1, deeptrue, map[temp_y][temp_x]);
				check[temp_y][temp_x] = false;
			}
			else
			{

				if (map[y][x] > map[temp_y][temp_x] - deepcount && deeptrue == false)
				{
					int temp = map[temp_y][temp_x];
					map[temp_y][temp_x] = map[y][x] - 1;
					check[temp_y][temp_x] = true;
					findlong(temp_x, temp_y, answer + 1, true, map[temp_y][temp_x]);
					check[temp_y][temp_x] = false;
					map[temp_y][temp_x] = temp;
				}
			}
		}
	}
}

int main() {

	cin >> testcase;

	for(int tt=1;tt<=testcase;tt++)
	{
		memset(check, false, sizeof(check));
		memset(map, 0, sizeof(map));
		realanswer = 0;
		mount = 0;

		cin >> mapindex >> deepcount;

		for (int i = 0; i < mapindex; i++)
		{
			for (int j = 0; j < mapindex; j++)
			{
				cin >> map[i][j];

				if (mount < map[i][j])
				{
					mount = map[i][j];
				}
			}
		}

		for (int i = 0; i < mapindex; i++)
		{
			for (int j = 0; j < mapindex; j++)
			{
				if (map[i][j] == mount)
				{
					check[i][j] = true;
					findlong(j, i, 1, false, map[i][j]);
					check[i][j] = false;
				}
			}
		}

		printf("#%d %d\n", tt, realanswer);
	}

}