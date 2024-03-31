#include <iostream>
#include <vector>

using namespace std;

int L, N, Q;
vector<vector<pair<int, int>>> board; // 기물, 위치한 기사의 번호
struct G {
	int r;
	int c;
	int h;
	int w;
	int k;
	bool check;
};
vector<G> gisa;
vector<pair<bool, int>> enable;
pair<int, int> d[4] = { {-1,0},{0,1},{1,0},{0,-1} };

bool isWall(int num, int dir)
{
	int end_r = gisa[num].r + gisa[num].h - 1;
	int end_c = gisa[num].c + gisa[num].w - 1;
	int i;

	if (gisa[num].r < 0 || L <= gisa[num].r || gisa[num].c < 0 || L <= gisa[num].c) {
		enable[num].first = false;
		return false;
	}
	if (gisa[num].r + gisa[num].h - 1 < 0 || L <= gisa[num].r + gisa[num].h - 1 || gisa[num].c + gisa[num].w - 1 < 0 || L <= gisa[num].c + gisa[num].w - 1) {
		enable[num].first = false;
		return false;
	}

	if (dir == 0) {
		gisa[num].r--;
		if (gisa[num].r < 0 || L <= gisa[num].r) return false;

		for (i = gisa[num].c; i <= end_c; i++) {
			if (board[gisa[num].r][i].first == 2) return false;
			if (board[gisa[num].r][i].second != 0) {
				if (isWall(board[gisa[num].r][i].second, dir) == false) return false;
			}
		}
	}
	else if (dir == 1) {
		end_c++;
		if (end_c < 0 || L <= end_c) return false;

		for (i = gisa[num].r; i <= end_r; i++) {
			if (board[i][end_c].first == 2) return false;
			if (board[i][end_c].second != 0) {
				if (isWall(board[i][end_c].second, dir) == false) return false;
			}
		}
	}
	else if (dir == 2) {
		end_r++;
		if (end_r < 0 || L <= end_r) return false;

		for (i = gisa[num].c; i <= end_c; i++) {
			if (board[end_r][i].first == 2) return false;
			if (board[end_r][i].second != 0) {
				if (isWall(board[end_r][i].second, dir) == false) return false;
			}
		}
	}
	else {
		gisa[num].c--;
		if (gisa[num].c < 0 || L <= gisa[num].c) return false;

		for (i = gisa[num].r; i <= end_r; i++) {
			if (board[i][gisa[num].c].first == 2) return false;
			if (board[i][gisa[num].c].second != 0) {
				if (isWall(board[i][gisa[num].c].second, dir) == false) return false;
			}
		}
	}

	return true;
}

void moving(int num, int dir)
{
	int end_r = gisa[num].r + gisa[num].h - 1;
	int end_c = gisa[num].c + gisa[num].w - 1;
	int i;

	if (dir == 0) {
		// remove before
		for (i = gisa[num].c; i <= end_c; i++) {
			board[end_r][i].second = 0;
		}
		// move
		gisa[num].r--;
		for (i = gisa[num].c; i <= end_c; i++) {
			if (board[gisa[num].r][i].second != 0) moving(board[gisa[num].r][i].second, dir);
			board[gisa[num].r][i].second = num;
		}
		// update gisa's info
		gisa[num].r = gisa[num].r - 1;
	}
	else if (dir == 1) {
		for (i = gisa[num].r; i <= end_r; i++) {
			board[i][gisa[num].c].second = 0;
		}
		end_c++;
		for (i = gisa[num].r; i <= end_r; i++) {
			if (board[i][end_c].second != 0) moving(board[i][end_c].second, dir);
			board[i][end_c].second = num;
		}
		gisa[num].c = gisa[num].c + 1;
	}
	else if (dir == 2) {
		for (i = gisa[num].c; i <= end_c; i++) {
			board[gisa[num].r][i].second = 0;
		}
		end_r++;
		for (i = gisa[num].c; i <= end_c; i++) {
			if (board[end_r][i].second != 0) moving(board[end_r][i].second, dir);
			board[gisa[num].r][i].second = num;
		}
		gisa[num].r = gisa[num].r + 1;
	}
	else {
		for (i = gisa[num].r; i <= end_r; i++) {
			board[i][end_c].second = 0;
		}
		gisa[num].c--;
		for (i = gisa[num].r; i <= end_r; i++) {
			if (board[i][gisa[num].c].second != 0) moving(board[i][gisa[num].c].second, dir);
			board[i][gisa[num].c].second = num;
		}
		gisa[num].c = gisa[num].c - 1;
	}

	gisa[num].check = true;
}

bool move_gisa(int num, int dir)
{
	// check possiblity of moving
	if (isWall(num, dir)) {
		moving(num, dir);
		return true;
	}

	return false;
}

void cal_damage(int num)
{
	for (int i = 1; i <= N; i++) {
		if (i == num) continue;
		if (gisa[i].check == false) continue;
		if (enable[i].first == false) continue;

		if (gisa[i].r < 0 || L <= gisa[i].r || gisa[i].c < 0 || L <= gisa[i].c) {
			enable[i].first = false;
			continue;
		}
		if (gisa[i].r + gisa[i].h - 1 < 0 || L <= gisa[i].r + gisa[i].h - 1 || gisa[i].c + gisa[i].w - 1 < 0 || L <= gisa[i].c + gisa[i].w - 1) {
			enable[i].first = false;
			continue;
		}

		for (int j = gisa[i].r; j < gisa[i].r + gisa[i].h; j++) {
			for (int l = gisa[i].c; l < gisa[i].c + gisa[i].w; l++) {
				if (j < 0 || L <= j || l < 0 || L <= l) continue;

				if (board[j][l].first == 1) {
					gisa[i].k--;
					enable[i].second++;
				}
			}
		}

		if (gisa[i].k <= 0) enable[i].first = false;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// input
	cin >> L >> N >> Q;

	board.resize(L, vector<pair<int, int>>(L, { 0,0 }));
	gisa.resize(N + 1);
	enable.resize(N + 1, { true,0 });

	int i, j;

	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			cin >> board[i][j].first;
		}
	}

	for (i = 1; i <= N; i++) {
		cin >> gisa[i].r >> gisa[i].c >> gisa[i].h >> gisa[i].w >> gisa[i].k;
		
		gisa[i].r--; gisa[i].c--; gisa[i].check = false;
	}

	for (i = 1; i <= N; i++) {
		for (j = gisa[i].r; j < gisa[i].r + gisa[i].h; j++) {
			for (int k = gisa[i].c; k < gisa[i].c + gisa[i].w; k++) {
				if (j < 0 || L <= j || k < 0 || L <= k) continue;

				board[j][k].second = i;
			}
		}
	}

	// input & calculate : for memory save
	for (i = 0; i < Q; i++) {
		int num, dir;
		cin >> num >> dir;

		// check enable
		if (enable[num].first == false) continue;
		for (j = 1; j <= N; j++ ) gisa[j].check = false;

		// move gisa
		bool isMove = move_gisa(num, dir);
		// calculate damage
		if (isMove) cal_damage(num);
	}

	int answer = 0;

	for (i = 1; i <= N; i++) {
		if (enable[i].first) answer += enable[i].second;
	}

	cout << answer;

	return 0;
}