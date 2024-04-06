#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int L, N, Q;
vector<vector<int>> arr;
struct G {
	int r;
	int c;
	int h;
	int w;
	int k;
};
vector<G> gisa;
vector<int> nr;
vector<int> nc;
vector<int> damage;
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void BFS(int num, int dir)
{
	queue<int> q;
	q.push(num);

	for (int i = 1; i <= N; i++) {
		nr[i] = -1; nc[i] = -1;
	}

	while (!q.empty()) {
		int idx = q.front();
		G now = gisa[idx];

		q.pop();

		if (now.r + dr[dir] < 1 || L < now.r + dr[dir] || now.c + dc[dir] < 1 || L < now.c + dc[dir]) return;
		if (now.r + now.h - 1 + dr[dir] < 1 || L < now.r + now.h - 1 + dr[dir] || now.c + now.w - 1 + dc[dir] < 1 || L < now.c + now.w - 1 + dc[dir]) return;

		for (int i = now.r + dr[dir]; i <= now.r + now.h - 1 + dr[dir]; i++) {
			for (int j = now.c + dc[dir]; j <= now.c + now.w - 1 + dc[dir]; j++) {
				if (arr[i][j] == 2) return;
			}
		}

		nr[idx] = now.r + dr[dir];
		nc[idx] = now.c + dc[dir];

		for (int i = 1; i <= N; i++) {
			if (i == idx) continue;

			G next = gisa[i];

			if (next.r + next.h - 1 < now.r + dr[dir] || now.r + now.h - 1 + dr[dir] < next.r) continue;
			if (next.c + next.w - 1 < now.c + dc[dir] || now.c + now.w - 1 + dc[dir] < next.c) continue;

			q.push(i);
		}
	}

	// move
	for (int i = 1; i <= N; i++) {
		if (i == num) continue;

		if (nr[i] != -1 && nc[i] != -1) {
			gisa[i].r = nr[i];
			gisa[i].c = nc[i];

			// damage
			for (int j = gisa[i].r; j < gisa[i].r + gisa[i].h; j++) {
				for (int k = gisa[i].c; k < gisa[i].c + gisa[i].w; k++) {
					if (arr[j][k] == 1) {
						gisa[i].k--;
						damage[i]++;
					}
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> L >> N >> Q;

	arr.resize(L + 1, vector<int>(L + 1));

	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cin >> arr[i][j];
		}
	}

	gisa.resize(N + 1);
	nr.resize(N + 1, 0);
	nc.resize(N + 1, 0);
	damage.resize(N + 1, 0);

	for (int i = 1; i <= N; i++) {
		cin >> gisa[i].r >> gisa[i].c >> gisa[i].h >> gisa[i].w >> gisa[i].k;
	}

	for (int i = 0; i < Q; i++) {
		int num, dir;
		cin >> num >> dir;

		if (gisa[num].k > 0) BFS(num, dir);
	}

	for (int i = 1; i <= N; i++) {
		if (gisa[i].k <= 0) continue;
		damage[0] += damage[i];
	}

	cout << damage[0];

	return 0;
}