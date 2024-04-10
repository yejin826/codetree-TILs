#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// define variables
int N, M, K;
vector<vector<int>> arr;
vector<vector<int>> rev;
struct coord {
	int x;
	int y;
};
vector<coord> m;
coord E;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int dist = 0;

void move()
{
	for (int i = 1; i <= M; i++) {
		if (m[i].x == E.x && m[i].y == E.y) continue;

		// now dist (m[i] & exit)
		int now_dist = abs(m[i].x - E.x) + abs(m[i].y - E.y);

		for (int j = 0; j < 4; j++) {
			int nx = m[i].x + dx[j];
			int ny = m[i].y + dy[j];

			if (nx < 1 || N < nx || ny < 1 || N < ny) continue;
			if (arr[nx][ny] > 0) continue;

			if (abs(nx - E.x) + abs(ny - E.y) < now_dist) {
				m[i] = {nx,ny};
				dist++;
				break;
			}
		}
	}
}

struct s {
	int x;
	int y;
	int s;
} ms;

// O(N^4) : max N -> 10
void find_square()
{
	for (int s = 2; s <= N; s++) {
		for (int i = 1; i <= N - s + 1; i++) {
			for (int j = 1; j <= N - s + 1; j++) {
				if (E.x < i || i + s - 1 < E.x || E.y < j || j + s - 1 < E.y) continue;

				for (int k = 1; k <= M; k++) {
					if (m[k].x == E.x && m[k].y == E.y) continue;

					if (i <= m[k].x && m[k].x <= i + s - 1 && j <= m[k].y && m[k].y <= j + s - 1) {
						ms = { i,j,s };
						return;
					}
				}
			}
		}
	}
}

void rotate()
{
	vector<vector<int>> rev(N + 1, vector<int>(N + 1));

	// minus brick
	for (int i = ms.x; i < ms.x + ms.s; i++) {
		for (int j = ms.y; j < ms.y + ms.s; j++) {
			if (arr[i][j]) arr[i][j]--;
		}
	}

	// copy
	for (int i = ms.x; i < ms.x + ms.s; i++) {
		for (int j = ms.y; j < ms.y + ms.s; j++) {
			int ox = i - ms.x;
			int oy = j - ms.y;
			int rx = oy;
			int ry = ms.s - ox - 1;

			rev[rx + ms.x][ry + ms.y] = arr[i][j];
		}
	}

	// rotate maze
	for (int i = ms.x; i < ms.x + ms.s; i++) {
		for (int j = ms.y; j < ms.y + ms.s; j++) {
			arr[i][j] = rev[i][j];
		}
	}

	// rotate exit & man
	int ox = E.x - ms.x;
	int oy = E.y - ms.y;
	int rx = oy;
	int ry = ms.s - ox - 1;
	E.x = rx + ms.x;
	E.y = ry + ms.y;

	for (int i = 1; i <= M; i++) {
		if (ms.x <= m[i].x && m[i].x < ms.x + ms.s && ms.y <= m[i].y && m[i].y < ms.y + ms.s) {
			ox = m[i].x - ms.x;
			oy = m[i].y - ms.y;
			rx = oy;
			ry = ms.s - ox - 1;
			m[i].x = rx + ms.x;
			m[i].y = ry + ms.y;
		}
	}
}

bool check_out()
{
	bool check = true;

	for (int i = 1; i <= M; i++) {
		if (!(m[i].x == E.x && m[i].y == E.y)) {
			check = false;
		}
	}

	return check;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// input N, M, K
	cin >> N >> M >> K;

	// initialize
	arr.resize(N + 1, vector<int>(N + 1));
	m.resize(M + 1);

	// input maze info
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	// input initial coord
	for (int i = 1; i <= M; i++) {
		cin >> m[i].x >> m[i].y;
	}

	// input exit coord
	cin >> E.x >> E.y;

	// run K seconds
	for (int i = 1; i <= K; i++) {
		// move people
		move();

		// check out
		if (check_out()) break;

		// find square
		find_square();

		// rotate square
		rotate();
	}

	cout << dist << '\n' << E.x << ' ' << E.y;

	return 0;
}