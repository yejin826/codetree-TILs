#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int idx = 0;
vector<vector<int>> v;
vector<vector<bool>> visited;
vector<vector<pair<int, int>>> group(900);
pair<int, int> d[4] = { {0,1},{0,-1},{1,0},{-1,0} };

void BFS(int x, int y, int idx)
{
	int num = v[x][y];
	queue<pair<int, int>> q;

	visited[x][y] = true;
	group[idx].push_back({ x, y });
	q.push({ x,y });

	while (!q.empty()) {
		int xx = q.front().first;
		int yy = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = xx + d[i].first;
			int ny = yy + d[i].second;

			if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
			if (visited[nx][ny]) continue;
			if (v[nx][ny] != num) continue;

			visited[nx][ny] = true;
			group[idx].push_back({ nx, ny });
			q.push({ nx, ny });
		}
	}

	sort(group[idx].begin(), group[idx].end());
}

void make_group()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j]) continue;

			BFS(i, j, idx);
			idx++;
		}
	}
}

int count_line(int n, int m)
{
	int cnt = 0;

	for (int i = 0; i < group[n].size(); i++) {
		for (int j = 0; j < 4; j++) {
			int nx = group[n][i].first + d[j].first;
			int ny = group[n][i].second + d[j].second;

			if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
			if (v[nx][ny] == v[group[n][0].first][group[n][0].second]) continue;

			for (int k = 0; k < group[m].size(); k++) {
				if (group[m][k].first == nx && group[m][k].second == ny) {
					cnt++;
				}
			}
		}
	}

	return cnt;
}

int calculate_score()
{
	int i = 0;
	int j = 0;
	int score = 0;
	int temp = 0;

	for (i = 0; i < idx - 1; i++) {
		int line = 0;

		for (j = i + 1; j < idx; j++) {
			line = count_line(j, i);
			
			temp = (group[i].size() + group[j].size()) * v[group[i][0].first][group[i][0].second] * v[group[j][0].first][group[j][0].second] * line;
			score += temp;
		}
	}

	return score;
}

void rotate_10()
{
	vector<vector<int>> c_v(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			c_v[i][j] = v[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		v[N / 2][i] = c_v[i][N / 2];
	}

	for (int i = N - 1; i >= 0; i--) {
		v[N - 1 - i][N / 2] = c_v[N / 2][i];
	}
}

void rotate_square()
{
	vector<vector<int>> c_v(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			c_v[i][j] = v[i][j];
		}
	}

	int offset_x = 0;
	int offset_y = 0;

	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			v[i + offset_x][j + offset_y] = c_v[N / 2 - 1 - j + offset_x][i + offset_y];
		}
	}
	
	offset_x = 0;
	offset_y = N / 2 + 1;

	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			v[i + offset_x][j + offset_y] = c_v[N / 2 - 1 - j + offset_x][i + offset_y];
		}
	}

	offset_x = N / 2 + 1;
	offset_y = 0;

	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			v[i + offset_x][j + offset_y] = c_v[N / 2 - 1 - j + offset_x][i + offset_y];
		}
	}

	offset_x = N / 2 + 1;
	offset_y = N / 2 + 1;

	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			v[i + offset_x][j + offset_y] = c_v[N / 2 - 1 - j + offset_x][i + offset_y];
		}
	}
}

void print_grid()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}
}

void print_group()
{
	for (int i = 0; i < idx; i++) {
		cout << v[group[i][0].first][group[i][0].second] << endl;
		for (int j = 0; j < group[i].size(); j++) {
			cout << group[i][j].first << ' ' << group[i][j].second << endl;
		}
	}
}

void Initialize()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = false;
		}
	}

	for (int j = 0; j < idx; j++) group[j].clear();

	idx = 0;
}

int main()
{
	cin >> N;
	v.resize(N, vector<int>(N));
	visited.resize(N, vector<bool>(N, false));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> v[i][j];
		}
	}
    
	int answer = 0;

	for (int i = 1; i <= 4; i++) {
		// 초기화
		Initialize();

		if (i > 1) {
			rotate_10();
			rotate_square();
		}
		
		make_group();

		answer += calculate_score();
	}

	cout << answer;
	
	return 0;
}