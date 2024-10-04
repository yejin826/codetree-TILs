#include <iostream>
#include <vector>
#include <algorithm>

#define PII pair<int, int>

using namespace std;

int N, M, K;
vector<vector<PII>> ground; // 소유자 번호, 남은 시간
vector<vector<vector<int>>> candidate;
vector<PII> coord_player;
vector<PII> info_player; // 현재 방향, 생존 여부 (0 == 아웃/1 == 생존)
vector<vector<vector<int>>> dir_priority;
PII direction[4] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

void move_player()
{
    for (int i = 1; i <= M; i++) {
        if (info_player[i].second == 0) continue;

        int x = coord_player[i].first;
        int y = coord_player[i].second;
        int d = info_player[i].first;
        bool is_done = false;

        for (int j = 0; j < 4; j++) {
            if (is_done) break;

            int nx = x + direction[dir_priority[i][d][j]].first;
            int ny = y + direction[dir_priority[i][d][j]].second;

            if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
            if (ground[nx][ny].first != 0) continue;

            candidate[nx][ny].push_back(i);
            coord_player[i].first = nx;
            coord_player[i].second = ny;
            info_player[i].first = dir_priority[i][d][j];

            is_done = true;
        }

        if (is_done) continue;

        for (int j = 0; j < 4; j++) {
            if (is_done) break;

            int nx = x + direction[dir_priority[i][d][j]].first;
            int ny = y + direction[dir_priority[i][d][j]].second;

            if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
            if (ground[nx][ny].first != i) continue;

            candidate[nx][ny].push_back(i);
            coord_player[i].first = nx;
            coord_player[i].second = ny;
            info_player[i].first = dir_priority[i][d][j];

            is_done = true;
        }
    }
}

void minus_time()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ground[i][j].second--;

            if (ground[i][j].second <= 0) {
                ground[i][j].second = 0;
                ground[i][j].first = 0;
            }
        }
    }
}

void check_double()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (candidate[i][j].size() == 0) continue;

            sort(candidate[i][j].begin(), candidate[i][j].end());
            
            ground[i][j].first = candidate[i][j][0];
            ground[i][j].second = K;

            for (int k = 1; k < candidate[i][j].size(); k++) {
                info_player[candidate[i][j][k]].second = 0;
            }

            candidate[i][j].clear();
        }
    }
}

bool is_end()
{
    for (int i = 2; i <= M; i++) {
        if (info_player[i].second == 1) return false;
    }

    return true;
}

int main()
{
    cin >> N >> M >> K;

    ground.resize(N, vector<PII>(N));
    candidate.resize(N, vector<vector<int>>(N));
    coord_player.resize(M + 1);
    info_player.resize(M + 1);
    dir_priority.resize(M + 1, vector<vector<int>>(4, vector<int>(4)));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> ground[i][j].first;

            if (ground[i][j].first == 0) {
                ground[i][j].second = 0;
            }
            else {
                ground[i][j].second = K;
                coord_player[ground[i][j].first] = { i,j };
            }
        }
    }

    for (int i = 1; i <= M; i++) {
        cin >> info_player[i].first;
        info_player[i].first--;
        info_player[i].second = 1;
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> dir_priority[i][j][0] >> dir_priority[i][j][1] >> dir_priority[i][j][2] >> dir_priority[i][j][3];
            
            dir_priority[i][j][0]--;
            dir_priority[i][j][1]--;
            dir_priority[i][j][2]--;
            dir_priority[i][j][3]--;
        }
    }

    int cnt = 0;

    for (cnt = 1; ; cnt++) {
        if (cnt >= 1000) {
            cnt = -1;
            break;
        }

        move_player();
        minus_time();
        check_double();
        if (is_end()) break;
    }

    cout << cnt;

    return 0;
}