#include <iostream>
#include <vector>

using namespace std;

int N, M, answer = 0;
vector<vector<int>> v;
vector<pair<int, int>> m_list;
vector<pair<int, int>> snail_route;
pair<int, int> d[4] = { {0,1},{1,0},{0,-1},{-1,0} };

void make_route()
{
    snail_route.push_back({ 0,0 });

    int x = 0;
    int y = 0;
    int dir = 0;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 1; j <= i; j++) {
            x += d[dir].first;
            y += d[dir].second;

            snail_route.push_back({ x,y });
        }
        dir++;
        dir %= 4;
        for (int j = 1; j <= i; j++) {
            x += d[dir].first;
            y += d[dir].second;

            snail_route.push_back({ x,y });
        }
        dir++;
        dir %= 4;
        if (i == N - 1) {
            for (int j = 1; j <= i; j++) {
                x += d[dir].first;
                y += d[dir].second;

                snail_route.push_back({ x,y });
            }
            dir++;
            dir %= 4;
        }
    }

    vector<pair<int, int>> tmp = snail_route;

    for (int i = 0; i < snail_route.size(); i++) {
        snail_route[i] = tmp[snail_route.size() - 1 - i];
    }
}

int attack(int dir, int pos)
{
    int x = N / 2;
    int y = N / 2;
    int cnt = 0;

    for (int i = 1; i <= pos; i++) {
        if (v[x + d[dir].first * i][y + d[dir].second * i] > 0) cnt++;

        answer += v[x + d[dir].first * i][y + d[dir].second * i];
        v[x + d[dir].first * i][y + d[dir].second * i] = 0;
    }

    return cnt;
}

void fill_blank(int cnt)
{
    int term = 0;

    for (int i = 1; i < snail_route.size(); i++) {
        int x = snail_route[i].first;
        int y = snail_route[i].second;
        int bx = snail_route[i - term].first;
        int by = snail_route[i - term].second;

        if (v[x][y] == 0) {
            term++;
            continue;
        }

        v[bx][by] = v[x][y];
    }

    for (int i = snail_route.size() - 1; i > 0; i--) {
        int x = snail_route[i].first;
        int y = snail_route[i].second;

        if (v[x][y] != 0) {
            for (int j = 0; j < cnt; j++) {
                int nx = snail_route[i - j].first;
                int ny = snail_route[i - j].second;

                v[nx][ny] = 0;
            }
            break;
        }
    }
}

void remove_sequence()
{
    while (true) {
        int cnt = 1;
        int blank_cnt = 0;
        int num = v[snail_route[1].first][snail_route[1].second];

        for (int i = 2; i < snail_route.size(); i++) {
            if (num == v[snail_route[i].first][snail_route[i].second]) {
                cnt++;
            }
            else {
                if (cnt >= 4) {
                    blank_cnt += cnt;
                    answer += (cnt * num);

                    for (int j = 1; j <= cnt; j++) {
                        v[snail_route[i - j].first][snail_route[i - j].second] = 0;
                    }
                }

                cnt = 1;
                num = v[snail_route[i].first][snail_route[i].second];
            }
        }

        if (blank_cnt == 0) break;

        fill_blank(blank_cnt);
    }
}

void refill()
{
    vector<vector<int>> tmp = v;

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) v[i][j] = 0;

    int cnt = 1;
    int num = tmp[snail_route[1].first][snail_route[1].second];

    vector<pair<int, int>> tmp2;

    for (int i = 2; i < snail_route.size(); i++) {
        if (tmp[snail_route[i].first][snail_route[i].second] == 0) {
            tmp2.push_back({ cnt,num });
            break;
        }

        if (num == tmp[snail_route[i].first][snail_route[i].second]) {
            cnt++;
        }
        else {
            tmp2.push_back({ cnt,num });

            cnt = 1;
            num = tmp[snail_route[i].first][snail_route[i].second];
        }
    }

    for (int i = 1; i <= 2 * tmp2.size(); i += 2) {
        if (i + 1 >= snail_route.size()) break;

        v[snail_route[i].first][snail_route[i].second] = tmp2[(i - 1) / 2].first;
        v[snail_route[i + 1].first][snail_route[i + 1].second] = tmp2[(i - 1) / 2].second;
    }
}

void print_grid()
{
    cout << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << v[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    cin >> N >> M;

    v.resize(N, vector<int>(N));
    m_list.resize(M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> v[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        cin >> m_list[i].first >> m_list[i].second;
    }

    make_route();
    //print_grid();

    for (int i = 0; i < M; i++) {
        int blank_cnt = attack(m_list[i].first, m_list[i].second);
        //print_grid();
        fill_blank(blank_cnt);
        //print_grid();
        remove_sequence();
        //print_grid();
        refill();
        //print_grid();
    }

    cout << answer;

    return 0;
}