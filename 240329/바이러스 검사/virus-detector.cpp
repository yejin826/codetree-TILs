#include <iostream>
#include <vector>

using namespace std;

int n, L, F, i;
long long answer;
vector<int> v;

int main()
{
	scanf("%d", &n);

    v.resize(n);

	for (i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}

	scanf("%d %d", &L, &F);

	// 팀장은 무조건 한 명이 있어야 하므로
	for (i = 0; i < n; i++) {
		v[i] -= L;
		answer++;

		if (v[i] > 0) {
			answer += v[i] / F;
			if (v[i] % F) answer++;
		}
	}

	printf("%lld", answer);

	return 0;
}