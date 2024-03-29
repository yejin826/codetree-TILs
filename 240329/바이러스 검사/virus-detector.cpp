#include <iostream>
#include <vector>

using namespace std;

int n, L, F;
long long answer;
vector<int> v;
vector<bool> visited;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		v.push_back(x);
		visited.push_back(false);
	}

	cin >> L >> F;

	// 팀장은 무조건 한 명이 있어야 하므로
	for (int i = 0; i < n; i++) {
		v[i] -= L;
		answer++;

		if (v[i] < 0) visited[i] = true;
		else {
			answer += v[i] / F;
			if (v[i] % F) answer++;
		}
	}

	cout << answer;

	return 0;
}