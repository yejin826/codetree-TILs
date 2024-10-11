#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int K, M, answer = 0;
vector<vector<int>> v(5, vector<int>(5));
queue<int> m_list;
pair<int, int> O = { 0,0 }; // 3 x 3 격자의 중심 좌표
int max_value_first = 0; // 1차 획득 최대 가치
int angle = 3; // 회전 각도 : 0 = 90도 / 1 = 180도 / 2 = 270도
pair<int, int> d[4] = { {0,1},{0,-1},{1,0},{-1,0} };

void print_grid()
{
	cout << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}

	cout << endl;
}

void find_first_value(int x, int y, int a, vector<vector<int>> arr)
{
	int sum = 0;

	vector<vector<bool>> visited(5, vector<bool>(5, false));

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (visited[i][j]) continue;

			int val = arr[i][j];
			int cnt = 1;

			queue<pair<int, int>> q;
			visited[i][j] = true;
			q.push({ i,j });

			while (!q.empty()) {
				int x = q.front().first;
				int y = q.front().second;

				q.pop();

				for (int k = 0; k < 4; k++) {
					int nx = x + d[k].first;
					int ny = y + d[k].second;

					if (nx < 0 || 5 <= nx || ny < 0 || 5 <= ny) continue;
					if (visited[nx][ny]) continue;
					if (arr[nx][ny] != val) continue;

					visited[nx][ny] = true;
					q.push({ nx, ny });
					cnt++;
				}
			}

			if (cnt >= 3) sum += cnt;
		}
	}

	if (max_value_first < sum) {
		O = { x + 1, y + 1 };
		max_value_first = sum;
		angle = a;
	}
	else if (max_value_first == sum) {
		if (angle > a) {
			O = { x + 1, y + 1 };
			max_value_first = sum;
			angle = a;
		}
		else if (angle == a) {
			if (O.second > y + 1) {
				O = { x + 1, y + 1 };
				max_value_first = sum;
				angle = a;
			}
			else if (O.second == y + 1) {
				if (O.first > x + 1) {
					O = { x + 1, y + 1 };
					max_value_first = sum;
					angle = a;
				}
			}
		}
	}
}

void rotate_0(int x, int y, vector<vector<int>> copy)
{
	vector<vector<int>> tmp = copy;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i + x][j + y] = copy[2 - j + x][i + y];
		}
	}

	find_first_value(x, y, 0, tmp);
}

void rotate_1(int x, int y, vector<vector<int>> copy)
{
	vector<vector<int>> tmp = copy;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i + x][j + y] = copy[2 - i + x][2 - j + y];
		}
	}
	
	find_first_value(x, y, 1, tmp);
}

void rotate_2(int x, int y, vector<vector<int>> copy)
{
	vector<vector<int>> tmp = copy;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i + x][j + y] = copy[j + x][2 - i + y];
		}
	}

	find_first_value(x, y, 2, tmp);
}

void select_area()
{
	// 원본 배열 복사
	vector<vector<int>> copy(5, vector<int>(5));

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			copy[i][j] = v[i][j];
		}
	}

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			int x = i - 1;
			int y = j - 1;

			rotate_0(x, y, copy);
			rotate_1(x, y, copy);
			rotate_2(x, y, copy);
		}
	}
}

void rotate()
{
	vector<vector<int>> tmp = v;

	int x = O.first - 1;
	int y = O.second - 1;

	if (angle == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i + x][j + y] = tmp[2 - j + x][i + y];
			}
		}
	}
	else if (angle == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i + x][j + y] = tmp[2 - i + x][2 - j + y];
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i + x][j + y] = tmp[j + x][2 - i + y];
			}
		}
	}
}

bool cmp(pair<int, int> a, pair<int, int> b)
{
	if (a.second < b.second) return true;
	else if (a.second > b.second) return false;
	else {
		if (a.first > b.first) return true;
		else return false;
	}
}

vector<pair<int, int>> candidate;
vector<pair<int, int>> new_value;

bool record_coord()
{
	int sum = 0;
	vector<vector<bool>> visited(5, vector<bool>(5, false));

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (visited[i][j]) continue;

			int val = v[i][j];
			int cnt = 1;

			queue<pair<int, int>> q;
			visited[i][j] = true;
			q.push({ i,j });

			while (!q.empty()) {
				int x = q.front().first;
				int y = q.front().second;

				q.pop();

				for (int k = 0; k < 4; k++) {
					int nx = x + d[k].first;
					int ny = y + d[k].second;

					if (nx < 0 || 5 <= nx || ny < 0 || 5 <= ny) continue;
					if (visited[nx][ny]) continue;
					if (v[nx][ny] != val) continue;

					visited[nx][ny] = true;
					q.push({ nx, ny });
					cnt++;
				}
			}

			if (cnt >= 3) {
				sum += cnt;
				candidate.push_back({ i,j });
			}
		}
	}

	if (sum == 0) return false;
	else return true;
}

int get_value()
{
	int value = 0;

	for (int i = 0; i < candidate.size(); i++) {
		int val = v[candidate[i].first][candidate[i].second];
		new_value.push_back({ candidate[i].first,candidate[i].second });
		value++;

		queue<pair<int, int>> q;
		vector<vector<bool>> check(5, vector<bool>(5, false));

		check[candidate[i].first][candidate[i].second] = true;
		q.push({ candidate[i].first,candidate[i].second });

		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;

			q.pop();

			for (int k = 0; k < 4; k++) {
				int nx = x + d[k].first;
				int ny = y + d[k].second;

				if (nx < 0 || 5 <= nx || ny < 0 || 5 <= ny) continue;
				if (check[nx][ny]) continue;
				if (v[nx][ny] != val) continue;

				check[nx][ny] = true;
				new_value.push_back({ nx, ny });
				q.push({ nx, ny });
				value++;
			}
		}
	}

	return value;
}

bool find()
{
	int sum_turn = 0; // 이번 턴에서 획득한 값

	while (true) {
		candidate.clear();
		new_value.clear();

		// 유물의 좌표 저장
		if (record_coord() == false) break;

		// 유물 획득
		sum_turn = get_value();
		answer += sum_turn;

		sort(new_value.begin(), new_value.end(), cmp);

		// 새로운 유물 채우기
		for (int i = 0; i < new_value.size(); i++) {
			v[new_value[i].first][new_value[i].second] = m_list.front();
			m_list.pop();
		}
	}

	if (sum_turn == 0) return false;
	else return true;
}

int main()
{
	cin >> K >> M;

	for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) cin >> v[i][j];

	for (int i = 0; i < M; i++) {
		int t; cin >> t;

		m_list.push(t);
	}

	for (int i = 1; i <= K; i++) {
		// 초기화
		answer = 0;
		O = { 0,0 };
		max_value_first = 0;
		angle = 3;

		select_area();

		if (max_value_first == 0) break;
		
		rotate();

		if (find() == false) break;
		
		cout << answer << ' ';
	}
	
	return 0;
}