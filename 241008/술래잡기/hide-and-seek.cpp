#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, M, H, K;
struct Info {
    int x;
    int y;
    int d; // 좌우 : 0 / 상하 : 1
    int dd; // 우/하 : 0, 좌/상 : 1
};
Info S;
vector<Info> S_list;
vector<Info> M_list;
vector<bool> M_isOut;
vector<pair<int, int>> H_list;
pair<int, int> dir[2][2] = { { {0,1}, {0,-1} }, { {1,0}, {-1,0} } };
pair<int, int> dir_s[4] = { {-1,0},{0,1},{1,0},{0,-1} };

void snail_route()
{
    int idx = 0;
    Info temp;
    temp.x = N / 2;
    temp.y = N / 2;
    temp.d = idx;
    S_list.push_back(temp);

    for (int i = 1; i <= N - 1; i++) {
        for (int j = 0; j < i; j++) {
            temp.x += dir_s[idx].first;
            temp.y += dir_s[idx].second;
            if (j == i - 1) {
                idx++;
                idx %= 4;
            }
            temp.d = idx;
            S_list.push_back(temp);
        }
        for (int j = 0; j < i; j++) {
            temp.x += dir_s[idx].first;
            temp.y += dir_s[idx].second;
            if (j == i - 1) {
                idx++;
                idx %= 4;
            }
            temp.d = idx;
            S_list.push_back(temp);
        }
        if (i == N - 1) {
            for (int j = 0; j < i; j++) {
                temp.x += dir_s[idx].first;
                temp.y += dir_s[idx].second;
                if (j == i - 1) {
                    idx = 2;
                }
                temp.d = idx;
                S_list.push_back(temp);
            }
        }
    }

    for (int i = N - 1; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            temp.x += dir_s[idx].first;
            temp.y += dir_s[idx].second;
            if (j == i - 1) {
                idx--;
                idx += 4;
                idx %= 4;
            }
            temp.d = idx;
            S_list.push_back(temp);
        }
        for (int j = 0; j < i; j++) {
            temp.x += dir_s[idx].first;
            temp.y += dir_s[idx].second;
            if (j == i - 1) {
                if (i == 1) break; // { N/2, N/2 } 중복 제거 미흡
                else {
                    idx--;
                    idx += 4;
                    idx %= 4;
                }
            }
            temp.d = idx;
            S_list.push_back(temp);
        }
        if (i == N - 1) {
            for (int j = 0; j < i; j++) {
                temp.x += dir_s[idx].first;
                temp.y += dir_s[idx].second;
                if (j == i - 1) {
                    idx--;
                    idx += 4;
                    idx %= 4;
                }
                temp.d = idx;
                S_list.push_back(temp);
            }
        }
    }
}

void MOVE_M()
{
    for (int i = 0; i < M; i++) {
        if (M_isOut[i]) continue;

        if (abs(S.x - M_list[i].x) + abs(S.y - M_list[i].y) <= 3) {
            int nx = M_list[i].x + dir[M_list[i].d][M_list[i].dd].first;
            int ny = M_list[i].y + dir[M_list[i].d][M_list[i].dd].second;

            if (nx < 0 || N <= nx || ny < 0 || N <= ny) {
                M_list[i].dd = (M_list[i].dd == 0) ? 1 : 0;

                nx = M_list[i].x + dir[M_list[i].d][M_list[i].dd].first;
                ny = M_list[i].y + dir[M_list[i].d][M_list[i].dd].second;
            }

            if (nx == S.x && ny == S.y) {
                continue;
            }
            else {
                M_list[i].x = nx;
                M_list[i].y = ny;
            }
        }
    }
}

bool CHECK_H(int x, int y)
{
    for (int i = 0; i < H_list.size(); i++) {
        if (H_list[i].first == x && H_list[i].second == y) return true;
    }

    return false;
}

int MOVE_S(int idx)
{
    if (idx >= S_list.size()) idx %= S_list.size(); // 이 부분 처리 미흡

    S = S_list[idx];

    int sum = 0;

    for (int i = 0; i < M_list.size(); i++) {
        if (M_isOut[i]) continue;

        if (S.x == M_list[i].x && S.y == M_list[i].y) {
            if (CHECK_H(M_list[i].x, M_list[i].y)) continue;
            sum++;
            M_isOut[i] = true;
        }

        if (S.x + dir_s[S.d].first < 0 || N <= S.x + dir_s[S.d].first || S.y + dir_s[S.d].second < 0 || N <= S.y + dir_s[S.d].second) continue;
        if (S.x + dir_s[S.d].first == M_list[i].x && S.y + dir_s[S.d].second == M_list[i].y) {
            if (CHECK_H(M_list[i].x, M_list[i].y)) continue;
            sum++;
            M_isOut[i] = true;
        }

        if (S.x + dir_s[S.d].first * 2 < 0 || N <= S.x + dir_s[S.d].first * 2 || S.y + dir_s[S.d].second * 2 < 0 || N <= S.y + dir_s[S.d].second * 2) continue;
        if (S.x + dir_s[S.d].first * 2 == M_list[i].x && S.y + dir_s[S.d].second * 2 == M_list[i].y) {
            if (CHECK_H(M_list[i].x, M_list[i].y)) continue;
            sum++;
            M_isOut[i] = true;
        }
        // 격자 밖 처리 미흡
    }

    return sum;
}

int main()
{
    cin >> N >> M >> H >> K;

    S.x = N / 2;
    S.y = N / 2;
    S.d = 1;

    M_list.resize(M);
    M_isOut.resize(M, false);
    H_list.resize(H);

    for (int i = 0; i < M; i++) {
        cin >> M_list[i].x >> M_list[i].y >> M_list[i].d;

        M_list[i].x--;
        M_list[i].y--;
        M_list[i].d--;
        M_list[i].dd = 0;
    }

    for (int i = 0; i < H; i++) {
        cin >> H_list[i].first >> H_list[i].second;

        H_list[i].first--;
        H_list[i].second--;
    }

    int answer = 0;

    snail_route();

    for (int i = 1; i <= K; i++) {
        MOVE_M();

        answer += MOVE_S(i) * i;
    }

    cout << answer;

    return 0;
}