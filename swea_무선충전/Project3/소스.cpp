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

//map의 first는 가능한 BC,두번째는 wifi index(영역이 겹칠경우 wifi index로 식별하기 위해)
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

	//bfs로 wifi 가능 영역을 확인한다

	while (!q.empty())
	{
		int x = q.front().x;
		int y = q.front().y;
		int c = q.front().c;
		int p = q.front().p;
		int s = q.front().s;
		q.pop();

		//c만큼 spread 시켰으면 탈출
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

		//첫번째 사용자의 경로
		for (int i = 0; i < M; i++)
		{
			int temp;
			cin >> temp;
			x1 += dx[temp];
			y1 += dy[temp];
			v[0].push_back(make_pair(x1, y1));
		}
		//두번째 사용자의 경로
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

		//wifi 가능 영역 표시
		for (int i = 0; i < wifi.size(); i++)
		{
			spread(i);
		}

		//BC가 높은 순으로 sort
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

		//wifi 확인
		for (int i = 0; i <= M; i++)
		{
			int vx1 = v[0][i].first;
			int vy1 = v[0][i].second;

			int vx2 = v[1][i].first;
			int vy2 = v[1][i].second;

			//map에 BC가 없을 경우
			if (map[vy1][vx1].size() == 0 && map[vy2][vx2].size() == 0)
			{

			}
			//2번째 사용자만 BC가 있을 경우
			else if (map[vy1][vx1].size() == 0 && map[vy2][vx2].size() == 1)
			{
				sum2 += map[vy2][vx2].front().first;

			}
			//2번째 사용자만 사용가능한 BC가 여러개 있을 경우
			else if (map[vy1][vx1].size() == 0 && map[vy2][vx2].size() >= 2)
			{
				sum2 += map[vy2][vx2].front().first;
			}
			//1번째 사용자만 BC가 있을 경우
			else if (map[vy1][vx1].size() == 1 && map[vy2][vx2].size() == 0)
			{
				sum1 += map[vy1][vx1].front().first;
			}
			//1번째 2번째 사용자 모두 접속가능한 BC가 하나일 경우
			else if (map[vy1][vx1].size() == 1 && map[vy2][vx2].size() == 1)
			{
				//같은 와이파이일경우 (map의 두번째 인자는 wifi index임)
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					sum1 += map[vy1][vx1].front().first / 2;
					sum2 += map[vy2][vx2].front().first / 2;
				}
				//아닐 경우
				else
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2].front().first;
				}
			}
			//1번째 사용자 접속 와이파이가 1개고 2번째 사용자 접속 와이파이 2개이상일때
			else if (map[vy1][vx1].size() == 1 && map[vy2][vx2].size() > 1)
			{
				//가장 큰 BC가 같은 와이파이일경우
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2][1].first;
				}
				//아닐 경우
				else
				{
					sum1 += map[vy1][vx1].front().first;
					sum2 += map[vy2][vx2].front().first;
				}
			}
			//1번째 사용자 접속가능 와이파이가 2개이상일경우
			else if (map[vy1][vx1].size() > 1 && map[vy2][vx2].size() == 0)
			{
				sum1 += map[vy1][vx1].front().first;
			}
			//1번째 사용자 접속가능 와이파이가 2개이상일경우 && 2번째 사용자 접속가능 와이파이 1개일경우
			else if (map[vy1][vx1].size() > 1 && map[vy2][vx2].size() == 1)
			{
				//같은 와이파이일경우
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
			//둘다 접속가능 와이파이가 2개이상일 경우
			else if (map[vy1][vx1].size() > 1 && map[vy2][vx2].size() > 1)
			{
				//가장큰 BC 와이파이가 같을 경우
				if (map[vy1][vx1].front().second == map[vy2][vx2].front().second)
				{
					//두번째 큰 BC 서로 비교
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