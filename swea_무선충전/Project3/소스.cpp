#include "stdio.h"
#include "string.h"
#include "iostream"
#include "algorithm"
#include "deque"
#include "queue"
#include "vector"

using namespace std;

struct info
{
	int x;
	int y;
	int c;
	int p;
	int s;
};

vector <pair<int, int>> v[2];
vector <info> wifi;

//map�� first�� ������ BC,�ι�°�� wifi index(������ ��ĥ��� wifi index�� �ĺ��ϱ� ����)
vector <pair<int, int>> map[11][11];

int T, M, A;

void spread(int index)
{

	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	bool check[11][11] = { false, };

	check[wifi[index].y][wifi[index].x] = true;
	queue <info> q;
	q.push({ wifi[index].x,wifi[index].y,wifi[index].c,wifi[index].p ,0 });
	map[wifi[index].y][wifi[index].x].push_back({ wifi[index].p ,index });

	//bfs�� wifi ���� ������ Ȯ���Ѵ�

	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int c = q.front().c;
		int p = q.front().p;
		int s = q.front().s;
		q.pop();

		//c��ŭ spread �������� Ż��
		if (s == c)
		{
			break;
		}

		for (int j = 0; j < 4; j++)
		{
			int tx = x + dx[j];
			int ty = y + dy[j];

			if (check[ty][tx] == false && tx >= 1 && tx <= 10 && ty >= 1 && ty <= 10)
			{
				check[ty][tx] = true;
				map[ty][tx].push_back(make_pair(p, index));
				q.push({ tx,ty,c,p,s + 1 });
			}
		}
	}

}

bool compare(pair<int, int> a, pair<int, int> b)
{
	return a.first > b.first;
}

void init()
{

	v[0].clear();
	v[1].clear();
	wifi.clear();

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			map[i][j].clear();
		}
	}
}

int main()
{

	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		cin >> M >> A;

		init();

		int x1 = 1;
		int y1 = 1;
		int x2 = 10;
		int y2 = 10;

		int dx[5] = { 0, 0,1,0,-1 };
		int dy[5] = { 0, -1,0,1,0 };
		v[0].push_back(make_pair(1, 1));
		v[1].push_back(make_pair(10, 10));

		//ù��° ������� ���
		for (int i = 0; i < M; i++)
		{
			int temp;
			cin >> temp;
			x1 += dx[temp];
			y1 += dy[temp];
			v[0].push_back(make_pair(x1, y1));
		}
		//�ι�° ������� ���
		for (int i = 0; i < M; i++)
		{
			int temp;
			cin >> temp;
			x2 += dx[temp];
			y2 += dy[temp];
			v[1].push_back(make_pair(x2, y2));
		}

		info a;

		for (int i = 0; i < A; i++)
		{
			cin >> a.x >> a.y >> a.c >> a.p;
			wifi.push_back(a);
		}

		//wifi ���� ���� ǥ��
		for (int i = 0; i < wifi.size(); i++)
		{
			spread(i);
		}

		//BC�� ���� ������ sort
		for (int i = 1; i <= 10; i++)
		{
			for (int j = 1; j <= 10; j++)
			{
				if (map[i][j].size() > 1)
				{
					sort(map[i][j].begin(), map[i][j].end(), compare);
				}
			}
		}

		int sum1 = 0;
		int sum2 = 0;

		//wifi Ȯ��
		for (int i = 0; i <= M; i++)
		{
			int vx1 = v[0][i].first;
			int vy1 = v[0][i].second;

			int vx2 = v[1][i].first;
			int vy2 = v[1][i].second;

			//map�� BC�� ���� ���
			if (map[vy1][vx1].size() == 0 && map[vy2][vx2].size() == 0)
			{

			}
			//2��° ����ڸ� BC�� ���� ���
			else if (map[vy1][vx1].size() == 0 && map[vy2][vx2].size() == 1)
			{
				sum2 += map[vy2][vx2].front().first;

			}
			//2��° ����ڸ� ��밡���� BC�� ������ ���� ���
			else if (map[vy1][vx1].size() == 0 && map[vy2][vx2].size() >= 2)
			{
				sum2 += map[vy2][vx2].front().first;
			}
			//1��° ����ڸ� BC�� ���� ���
			else if (map[vy1][vx1].size() == 1 && map[vy2][vx2].size() == 0)
			{
				sum1 += map[vy1][vx1].front().first;
			}
			//1��° 2��° ����� ��� ���Ӱ����� BC�� �ϳ��� ���
			else if (map[vy1][vx1].size() == 1 && map[vy2][vx2].size() == 1)
			{
				//���� ���������ϰ�� (map�� �ι�° ���ڴ� wifi index��)
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					sum1 += map[vy1][vx1].front().first / 2;
					sum2 += map[vy2][vx2].front().first / 2;
				}
				//�ƴ� ���
				else
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2].front().first;
				}
			}
			//1��° ����� ���� �������̰� 1���� 2��° ����� ���� �������� 2���̻��϶�
			else if (map[vy1][vx1].size() == 1 && map[vy2][vx2].size() > 1)
			{
				//���� ū BC�� ���� ���������ϰ��
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2][1].first;
				}
				//�ƴ� ���
				else
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2].front().first;
				}
			}
			//1��° ����� ���Ӱ��� �������̰� 2���̻��ϰ��
			else if (map[vy1][vx1].size() > 1 && map[vy2][vx2].size() == 0)
			{
				sum1 += map[vy1][vx1].front().first;
			}
			//1��° ����� ���Ӱ��� �������̰� 2���̻��ϰ�� && 2��° ����� ���Ӱ��� �������� 1���ϰ��
			else if (map[vy1][vx1].size() > 1 && map[vy2][vx2].size() == 1)
			{
				//���� ���������ϰ��
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					sum1 += map[vy1][vx1][1].first;
					sum2 += map[vy2][vx2].front().first;
				}
				else
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2].front().first;
				}
			}
			//�Ѵ� ���Ӱ��� �������̰� 2���̻��� ���
			else if (map[vy1][vx1].size() > 1 && map[vy2][vx2].size() > 1)
			{
				//����ū BC �������̰� ���� ���
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					//�ι�° ū BC ���� ��
					if (map[vy1][vx1][1].first > map[vy2][vx2][1].first)
					{
							sum1 += map[vy1][vx1][1].first;
							sum2 += map[vy2][vx2][0].first;
					}
					else
					{
							sum1 += map[vy1][vx1][0].first;
							sum2 += map[vy2][vx2][1].first;
					}
				}
				else
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2].front().first;
				}
			}
		}
		printf("#%d %d\n", t, sum1 + sum2);

	}

}