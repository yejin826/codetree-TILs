#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
int answer = 0;
vector<vector<int>> tmp_arr;
struct Info {
    int num;
    int x;
    int y;
    int sunseo;
};
vector<vector<Info>> team;
vector<bool> team_head;
// T : 인덱스가 줄어드는 방향으로 이동, 즉 1이 머리 
// 1, 2, 2, 3, 4, 4, 4
// 2, 2, 3, 4, 4, 4, 1
// F : 인덱스가 늘어나는 방향ㅇ로 이동, 즉 3이 머리
// 1, 2, 2, 3, 4, 4, 4
// 4, 1, 2, 2, 3, 4, 4
vector<int> num_member;
pair<int, int> d[4] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

void DFS(int r, int c, int id, vector<vector<bool>> visited, int cnt)
{
    for (int i = 0; i < 4; i++) {
        int nx = r + d[i].first;
        int ny = c + d[i].second;

        if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
        if (visited[nx][ny]) continue;

        Info tmp;
        tmp.x = nx;
        tmp.y = ny;

        if ((tmp_arr[r][c] == 1 || tmp_arr[r][c] == 2) && tmp_arr[nx][ny] == 2) {
            tmp.num = 2;
            tmp.sunseo = cnt;

            visited[nx][ny] = true;
            team[id].push_back(tmp);
            DFS(nx, ny, id, visited, cnt + 1);
        }
        if ((tmp_arr[r][c] == 1 || tmp_arr[r][c] == 2) && tmp_arr[nx][ny] == 3) {
            tmp.num = 3;
            tmp.sunseo = cnt;
            num_member[id] = cnt;

            visited[nx][ny] = true;
            team[id].push_back(tmp);
            DFS(nx, ny, id, visited, cnt + 1);
        }
        if ((tmp_arr[r][c] == 3 || tmp_arr[r][c] == 4) && tmp_arr[nx][ny] == 4) {
            tmp.num = 4;

            visited[nx][ny] = true;
            team[id].push_back(tmp);
            DFS(nx, ny, id, visited, cnt + 1);
        }
    }

    return;
}

void make_team()
{
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    for (int i = 0; i < M; i++) {
        DFS(team[i][0].x, team[i][0].y, i, visited, 2);
    }
}

void Move()
{
    for (int i = 0; i < M; i++) {
        if (team_head[i]) {
            int tmp1 = team[i][0].num;
            int tmp2 = team[i][0].sunseo;

            for (int j = 1; j < team[i].size(); j++) {
                team[i][j - 1].num = team[i][j].num;
                team[i][j - 1].sunseo = team[i][j].sunseo;
            }

            team[i][team[i].size() - 1].num = tmp1;
            team[i][team[i].size() - 1].sunseo = tmp2;
        }
        else {
            int tmp1 = team[i][team[i].size() - 1].num;
            int tmp2 = team[i][team[i].size() - 1].sunseo;

            for (int j = team[i].size() - 1; j > 0; j--) {
                team[i][j].num = team[i][j - 1].num;
                team[i][j].sunseo = team[i][j - 1].sunseo;
            }

            team[i][0].num = tmp1;
            team[i][0].sunseo = tmp2;
        }
    }
}

void change_head(int id)
{
    team_head[id] = (team_head[id] == true) ? false : true;
}

int check_row(int R, bool left_right)
{
    Info tmp;
    tmp.num = 987654321;
    int team_num = 987654321;

    if (left_right) {
        tmp.x = 98654321;
        tmp.y = 987654321;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < team[i].size(); j++) {
                if (team[i][j].x == R && team[i][j].num != 4) {
                    if (tmp.y > team[i][j].y) {
                        tmp = team[i][j];
                        team_num = i;
                    }
                }
            }
        }
    }
    else {
        tmp.x = -98654321;
        tmp.y = -987654321;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < team[i].size(); j++) {
                if (team[i][j].x == R && team[i][j].num != 4) {
                    if (tmp.y < team[i][j].y) {
                        tmp = team[i][j];
                        team_num = i;
                    }
                }
            }
        }
    }

    int sum = 0;

    if (team_head[team_num]) {
        sum = tmp.sunseo * tmp.sunseo;
    }
    else {
        sum =  (num_member[team_num] + 1 - tmp.sunseo) * (num_member[team_num] + 1 - tmp.sunseo);
    }

    if (team_num <= M) change_head(team_num);

    return sum;
}

int check_col(int C, bool left_right)
{
    Info tmp;
    int team_num = 987654321;

    if (left_right) {
        tmp.num = 987654321;
        tmp.x = -98654321;
        tmp.y = -987654321;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < team[i].size(); j++) {
                if (team[i][j].y == C && team[i][j].num != 4) {
                    if (tmp.x < team[i][j].x) {
                        tmp = team[i][j];
                        team_num = i;
                    }
                }
            }
        }
    }
    else {
        tmp.num = 987654321;
        tmp.x = 98654321;
        tmp.y = 987654321;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < team[i].size(); j++) {
                if (team[i][j].y == C && team[i][j].num != 4) {
                    if (tmp.x > team[i][j].x) {
                        tmp = team[i][j];
                        team_num = i;
                    }
                }
            }
        }
    }

    int sum = 0;

    if (team_head[team_num]) {
        sum = tmp.sunseo * tmp.sunseo;
    }
    else {
        sum = (num_member[team_num] + 1 - tmp.sunseo) * (num_member[team_num] + 1 - tmp.sunseo);
    }

    if (team_num <= M) change_head(team_num);

    return sum;
}

void Throw_ball(int turn)
{
    turn %= 4 * N;

    if (1 <= turn && turn <= N) {
        answer += check_row(turn - 1, true);
    }
    else if (N + 1 <= turn && turn <= 2 * N) {
        answer += check_col(turn - (N + 1), true);
    }
    else if (2 * N + 1 <= turn && turn <= 3 * N) {
        answer += check_row(3 * N - turn, false);
    }
    else {
        if (turn != 0) answer += check_col(4 * N - turn, false);
        else answer += check_col(0, false);
    }
}

void print_grid()
{
    for (int i = 0; i < M; i++) {
        cout << i << endl;

        for (int j = 0; j < team[i].size(); j++) {
            cout << team[i][j].num << ' ' << team[i][j].x << ' ' << team[i][j].y  << ' ' << team[i][j].sunseo << endl;
        }
    }
}

int main()
{
    cin >> N >> M >> K;

    tmp_arr.resize(N, vector<int>(N));
    team.resize(M);
    team_head.resize(M, true);
    num_member.resize(M, 0);

    int team_idx = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> tmp_arr[i][j];

            if (tmp_arr[i][j] == 1) {
                Info tmp;
                tmp.num = 1;
                tmp.x = i;
                tmp.y = j;
                tmp.sunseo = 1;

                team[team_idx].push_back(tmp);
                team_idx++;
            }
        }
    }

    make_team();

    for (int i = 1; i <= K; i++) {
        Move();
        Throw_ball(i);
    }

    cout << answer;

    return 0;
}