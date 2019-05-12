#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

long long ans = 0;
vector <int> v;
int N, A, B, C;

void calc()
{
	for (int i = 0; i < N; i++)
	{
		int temp = v[i];

		if (temp > B)
		{
			temp -= B;
			ans += 1;
		}
		else
		{
			temp = 0;
			ans += 1;
		}
		
		if (temp != 0)
		{
			if (temp / C > 0)
			{
				ans += temp / C;
			}

			if (temp % C > 0)
			{
				ans += 1;
			}

		}

	}

}

int main()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> A;
		v.push_back(A);
	}

	cin >> B >> C;

	calc();

	cout << ans;
}