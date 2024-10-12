#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 987654321

using namespace std;

int N, M, K;
vector<vector<int>> v;
vector<vector<int>> latest_time;

pair<int, int> attackter;
pair<int, int> target;

pair<int, int> d[4] = { {0,1},{1,0},{0,-1},{-1,0} };

bool check_finish()
{
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (v[i][j] != 0) cnt++;
		}
	}

	if (cnt == 1) return true;
	else return false;
}

void select_attackter(int t)
{
	int power = INF;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (v[i][j] == 0) continue;

			if (v[i][j] < power) {
				power = v[i][j];
				attackter = { i,j };
			}
			else if (v[i][j] > power) continue;
			else {
				if (latest_time[i][j] > latest_time[attackter.first][attackter.second]) {
					power = v[i][j];
					attackter = { i,j };
				}
				else if (latest_time[i][j] < latest_time[attackter.first][attackter.second]) continue;
				else {
					if (i + j > attackter.first + attackter.second) {
						power = v[i][j];
						attackter = { i,j };
					}
					else if (i + j < attackter.first + attackter.second) continue;
					else {
						if (j > attackter.second) {
							power = v[i][j];
							attackter = { i,j };
						}
						else continue;
					}
				}
			}
		}
	}

	// 공격력 증가
	v[attackter.first][attackter.second] += (N + M);
	latest_time[attackter.first][attackter.second] = t;

	//cout << "공격자 좌표 : " << attackter.first << "," << attackter.second << endl;
}

void select_tower(int t)
{
	int power = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (v[i][j] == 0) continue;
			if (i == attackter.first && j == attackter.second) continue;

			if (v[i][j] > power) {
				power = v[i][j];
				target = { i,j };
			}
			else if (v[i][j] < power) continue;
			else {
				if (latest_time[i][j] < latest_time[target.first][target.second]) {
					power = v[i][j];
					target = { i,j };
				}
				else if (latest_time[i][j] > latest_time[target.first][target.second]) continue;
				else {
					if (i + j < target.first + target.second) {
						power = v[i][j];
						target = { i,j };
					}
					else if (i + j > target.first + target.second) continue;
					else {
						if (j < target.second) {
							power = v[i][j];
							target = { i,j };
						}
						else continue;
					}
				}
			}
		}
	}

	latest_time[target.first][target.second] = t;

	//cout << "대상자 좌표 : " << target.first << "," << target.second << endl;
}

bool check_laser()
{
	int dist = INF;

	queue<pair<pair<int, int>, int>> q;
	vector<vector<bool>> visited(N, vector<bool>(M, false));

	q.push({ attackter,0 });
	visited[attackter.first][attackter.second] = true;

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int cnt = q.front().second;

		q.pop();

		if (x == target.first && y == target.second) {
			dist = cnt;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + d[i].first;
			int ny = y + d[i].second;

			if (nx < 0 || N <= nx || ny < 0 || M <= ny) {
				if (nx < 0) nx = N - 1;
				else if (N <= nx) nx = 0;

				if (ny < 0) ny = M - 1;
				else if (M <= ny) ny = 0;
			}

			if (v[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;

			visited[nx][ny] = true;
			q.push({ {nx,ny},cnt + 1 });
		}
	}
	
	if (dist != INF) return true;
	else return false;
}

vector<pair<int, int>> route;

void find_route()
{
	vector<vector<int>> back_x(N, vector<int>(M));
	vector<vector<int>> back_y(N, vector<int>(M));
	vector<vector<bool>> visited(N, vector<bool>(M, false));
	queue<pair<int, int>> q;
	
	q.push({ target.first,target.second });
	visited[target.first][target.second] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;

		q.pop();

		if (x == attackter.first && y == attackter.second) {
			break;
		}

		for (int i = 3; i >= 0; i--) {
			int nx = x + d[i].first;
			int ny = y + d[i].second;

			if (nx < 0 || N <= nx || ny < 0 || M <= ny) {
				if (nx < 0) nx = N - 1;
				else if (N <= nx) nx = 0;

				if (ny < 0) ny = M - 1;
				else if (M <= ny) ny = 0;
			}

			if (v[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;

			q.push({ nx, ny });

			visited[nx][ny] = true;
			back_x[nx][ny] = x;
			back_y[nx][ny] = y;
		}
	}

	int x = attackter.first;
	int y = attackter.second;

	route.push_back({ x,y });

	while (x != target.first || y != target.second) {
		int nx = back_x[x][y];
		int ny = back_y[x][y];

		route.push_back({ nx,ny });

		x = nx;
		y = ny;
	}
	/*
	cout << "공격 루트" << endl;

	for (int i = 0; i < route.size(); i++) {
		cout << route[i].first << ' ' << route[i].second << endl;
	}
	*/
}

void attack_laser()
{
	find_route();

	int damage = v[attackter.first][attackter.second];

	for (int i = 1; i < route.size(); i++) {
		if (i == route.size() - 1) {
			v[route[i].first][route[i].second] -= damage;
		}
		else {
			v[route[i].first][route[i].second] -= (damage / 2);
		}
	}
}

void attack_bomb()
{
	//cout << "포탄 공격" << endl;

	int damage = v[attackter.first][attackter.second];

	pair<int, int> dd[8] = { {-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1} };
	
	route.push_back(attackter);
	v[target.first][target.second] -= damage;
	route.push_back(target);

	for (int i = 0; i < 8; i++) {
		int nx = target.first + dd[i].first;
		int ny = target.second + dd[i].second;

		if (nx < 0 || N <= nx || ny < 0 || M <= ny) {
			if (nx < 0) nx = N - 1;
			else if (N <= nx) nx = 0;

			if (ny < 0) ny = M - 1;
			else if (M <= ny) ny = 0;
		}

		if (nx == attackter.first && ny == attackter.second) continue;

		v[nx][ny] -= (damage / 2);
		route.push_back({ nx,ny });
	}
}

void collapse()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (v[i][j] <= 0) v[i][j] = 0;
		}
	}
}

void attack()
{
	bool is_laser = check_laser();

	route.clear();

	if (is_laser) attack_laser();
	else attack_bomb();

	collapse();
}

void restore()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (v[i][j] == 0) continue;

			bool check = true;

			for (int k = 0; k < route.size(); k++) {
				if (i == route[k].first && j == route[k].second) {
					check = false;
					route.erase(route.begin() + k);
					break;
				}
			}

			if (check) v[i][j]++;
		}
	}
}

void print_grid()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}
}

int main()
{
	cin >> N >> M >> K;

	v.resize(N, vector<int>(M));
	latest_time.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> v[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		bool is_finish = check_finish();

		if (is_finish) break;

		select_attackter(i);
		select_tower(i);

		attack();
		//print_grid();

		restore();
		//print_grid();
	}

	int answer = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (answer < v[i][j]) {
				answer = v[i][j];
			}
		}
	}

	cout << answer;

	return 0;
}