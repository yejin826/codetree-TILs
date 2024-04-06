#include <iostream>
#include <vector>
#include <queue>

#define MAX 987654321

using namespace std;

int N, M, K;
vector<vector<int>> arr;
vector<vector<int>> last_time;
pair<int, int> attackter, target;
vector<vector<bool>> nothing;

void select_attackter()
{
	int a_x = 0;
	int a_y = 0;
	int min_damage = MAX;
	int attack_time = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == 0) continue;
			
			if (min_damage < arr[i][j]) continue;
			else if (min_damage > arr[i][j]) {
				a_x = i;
				a_y = j;
				min_damage = arr[i][j];
				attack_time = last_time[i][j];
			}
			else {
				if (attack_time > last_time[i][j]) continue;
				else if (attack_time < last_time[i][j]) {
					a_x = i;
					a_y = j;
					min_damage = arr[i][j];
					attack_time = last_time[i][j];
				}
				else {
					if (a_x + a_y > i + j) continue;
					else if (a_x + a_y < i + j) {
						a_x = i;
						a_y = j;
						min_damage = arr[i][j];
						attack_time = last_time[i][j];
					}
					else {
						if (a_y < j) {
							a_x = i;
							a_y = j;
							min_damage = arr[i][j];
							attack_time = last_time[i][j];
						}
					}
				}
			}
		}
	}

	attackter = { a_x, a_y };
}

void select_target()
{
	int a_x = 0;
	int a_y = 0;
	int max_damage = 0;
	int attack_time = MAX;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == attackter.first && j == attackter.second) continue;
			if (arr[i][j] == 0) continue;

			if (max_damage > arr[i][j]) continue;
			else if (max_damage < arr[i][j]) {
				a_x = i;
				a_y = j;
				max_damage = arr[i][j];
				attack_time = last_time[i][j];
			}
			else {
				if (attack_time < last_time[i][j]) continue;
				else if (attack_time > last_time[i][j]) {
					a_x = i;
					a_y = j;
					max_damage = arr[i][j];
					attack_time = last_time[i][j];
				}
				else {
					if (a_x + a_y < i + j) continue;
					else if (a_x + a_y > i + j) {
						a_x = i;
						a_y = j;
						max_damage = arr[i][j];
						attack_time = last_time[i][j];
					}
					else {
						if (a_y > j) {
							a_x = i;
							a_y = j;
							max_damage = arr[i][j];
							attack_time = last_time[i][j];
						}
					}
				}
			}
		}
	}

	target = { a_x, a_y };
}

int dx[8] = { 0,1,0,-1,-1,-1,1,1 };
int dy[8] = { 1,0,-1,0,-1,1,-1,1 };
vector<vector<pair<int, int>>> trace;

bool check_raser()
{
	vector<vector<bool>> visited(N, vector<bool>(M, false));
	trace.resize(N, vector<pair<int, int>>(M, {-1,-1}));

	queue<pair<int, int>> q;
	q.push(attackter);

	bool is_possible = false;

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();
		visited[now.first][now.second] = true;

		if (now.first == target.first && now.second == target.second) {
			is_possible = true;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nx = (now.first + dx[i] + N) % N;
			int ny = (now.second + dy[i] + M) % M;

			if (arr[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;

			if (trace[nx][ny].first == -1 && trace[nx][ny].second == -1) trace[nx][ny] = now;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}

	if (!is_possible) return false;

	// go raser
	int x = target.first;
	int y = target.second;
	int d = arr[attackter.first][attackter.second] / 2;

	nothing.resize(N, vector<bool>(M, true));
	nothing[attackter.first][attackter.second] = false;
	nothing[x][y] = false;

	arr[x][y] -= arr[attackter.first][attackter.second];
	
	while (true) {
		int nx = trace[x][y].first;
		int ny = trace[x][y].second;
		
		nothing[nx][ny] = false;

		if (nx == attackter.first && ny == attackter.second) break;

		arr[nx][ny] -= d;
		x = nx;
		y = ny;
	}

	// jaejungbee
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] <= 0) {
				arr[i][j] = 0;
				continue;
			}
			if (i == attackter.first && j == attackter.second) continue;
			if (i == target.first && j == target.second) continue;
			
			if (nothing[i][j]) arr[i][j]++;
		}
	}

	return true;
}

void go_bomb()
{
	nothing.resize(N, vector<bool>(M, true));
	nothing[attackter.first][attackter.second] = false;
	nothing[target.first][target.second] = false;

	int d = arr[attackter.first][attackter.second] / 2;

	arr[target.first][target.second] -= arr[attackter.first][attackter.second];

	for (int i = 0; i < 8; i++) {
		int nx = (target.first + dx[i] + N) % N;
		int ny = (target.second + dy[i] + M) % M;
		nothing[nx][ny] = false;

		if (arr[nx][ny] == 0) continue;

		arr[nx][ny] -= d;

	}

	// jaejungbee
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] <= 0) {
				arr[i][j] = 0;
				continue;
			}
			if (i == attackter.first && j == attackter.second) continue;
			if (i == target.first && j == target.second) continue;

			if (nothing[i][j]) arr[i][j]++;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;

	arr.resize(N, vector<int>(M));
	last_time.resize(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		// select attackter
		select_attackter();

		arr[attackter.first][attackter.second] += (N + M);
		last_time[attackter.first][attackter.second] = i;

		// select victim
		select_target();

		// raser
		if (check_raser() == false) go_bomb();
	}

	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (answer < arr[i][j]) answer = arr[i][j];
		}
	}
	cout << answer;

	return 0;
}