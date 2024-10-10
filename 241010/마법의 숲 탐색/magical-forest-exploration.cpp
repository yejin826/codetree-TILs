#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int R, C, K;
vector<vector<int>> arr;
struct info {
    int x;
    int y;
    int d;
};
vector<info> k_list; // 골렘의 중심좌표 & 출구 방향
pair<int, int> dir[4] = { {-1,0},{0,1},{1,0},{0,-1} };

void move_south(int id)
{
    int x = 1;
    int y = k_list[id].y;

    while (true) {
        if (R + 2 < x + 2) break;

        if (arr[x + 1][y - 1] == 0 && arr[x + 2][y] == 0 && arr[x + 1][y + 1] == 0) {
            x++;
        }
        else {
            break;
        }
    }

    k_list[id].x = x;
    k_list[id].y = y;
    k_list[id].d = k_list[id].d;
}

void move_west(int id)
{
    int x = k_list[id].x;
    int y = k_list[id].y;
    int d = k_list[id].d;

    while (true) {
        if (R + 2 < x + 2) break;
        if (y - 2 < 1) break;

        if (arr[x - 1][y - 1] == 0 && arr[x][y - 2] == 0 && arr[x + 1][y - 1] == 0 && arr[x + 1][y - 2] == 0 && arr[x + 2][y - 1] == 0) {
            x++;
            y--;
            d = (d - 1 + 4) % 4;
        }
        else {
            break;
        }
    }

    k_list[id].x = x;
    k_list[id].y = y;
    k_list[id].d = d;
}

void move_east(int id)
{
    int x = k_list[id].x;
    int y = k_list[id].y;
    int d = k_list[id].d;

    while (true) {
        if (R + 2 < x + 2) break;
        if (C < y + 2) break;

        if (arr[x - 1][y + 1] == 0 && arr[x][y + 2] == 0 && arr[x + 1][y + 1] == 0 && arr[x + 1][y + 2] == 0 && arr[x + 2][y + 1] == 0) {
            x++;
            y++;
            d = (d + 1) % 4;
        }
        else {
            break;
        }
    }

    k_list[id].x = x;
    k_list[id].y = y;
    k_list[id].d = d;
}

void Move(int id)
{
    int x = 1;
    int y = k_list[id].y;
    int d = k_list[id].d;

    while (R + 1 > x) {
        if (arr[x + 1][y - 1] == 0 && arr[x + 2][y] == 0 && arr[x + 1][y + 1] == 0) {
            x++;
        }
        else {
            if (1 <= y - 2 && arr[x - 1][y - 1] == 0 && arr[x][y - 2] == 0 && arr[x + 1][y - 1] == 0 && arr[x + 1][y - 2] == 0 && arr[x + 2][y - 1] == 0) {
                x++;
                y--;
                d = (d - 1 + 4) % 4;
            }
            else {
                if (y + 2 <= C && arr[x - 1][y + 1] == 0 && arr[x][y + 2] == 0 && arr[x + 1][y + 1] == 0 && arr[x + 1][y + 2] == 0 && arr[x + 2][y + 1] == 0) {
                    x++;
                    y++;
                    d = (d + 1) % 4;
                }
                else {
                    break;
                }
            }
        }
    }

    k_list[id].x = x;
    k_list[id].y = y;
    k_list[id].d = d;
}

bool Check_in(int id)
{
    if (4 <= k_list[id].x) return true;
    else return false;
}

void empty_map()
{
    for (int i = 0; i <= R + 2; i++) {
        for (int j = 0; j <= C; j++) {
            arr[i][j] = 0;
        }
    }
}

void record_map(int id)
{
    arr[k_list[id].x][k_list[id].y] = id;
    arr[k_list[id].x - 1][k_list[id].y] = id;
    arr[k_list[id].x + 1][k_list[id].y] = id;
    arr[k_list[id].x][k_list[id].y - 1] = id;
    arr[k_list[id].x][k_list[id].y + 1] = id;
}

int go_down(int id)
{
    queue<int> q;
    vector<bool> visited(K + 1, false);

    q.push(id);
    visited[id] = true;
    int max_r = k_list[id].x + 1;

    while (!q.empty()) {
        int out_x = k_list[q.front()].x + dir[k_list[q.front()].d].first;
        int out_y = k_list[q.front()].y + dir[k_list[q.front()].d].second;

        if (max_r <= k_list[q.front()].x + 1) max_r = k_list[q.front()].x + 1;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = out_x + dir[i].first;
            int ny = out_y + dir[i].second;

            if (nx < 3 || R + 2 < nx || ny < 1 || C < ny) continue;
            if (arr[nx][ny] == 0) continue;
            if (visited[arr[nx][ny]]) continue;

            visited[arr[nx][ny]] = true;
            q.push(arr[nx][ny]);
        }
    }

    return max_r - 2;
}

void print_grid()
{
    cout << endl;

    for (int i = 3; i <= R + 2; i++) {
        for (int j = 1; j <= C; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    cin >> R >> C >> K;

    arr.resize(R + 3, vector<int>(C + 1, 0));
    k_list.resize(K + 1);

    for (int i = 1; i <= K; i++) cin >> k_list[i].y >> k_list[i].d;

    int answer = 0;

    for (int i = 1; i <= K; i++) {
        Move(i);

        if (Check_in(i)) {
            record_map(i);
        }
        else {
            empty_map();
            continue;
        }

        answer += go_down(i);
    }

    cout << answer;

    return 0;
}