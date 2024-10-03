#include <iostream>
#include <vector>
#include <queue>

#define PII pair<int, int>

using namespace std;

PII board[4][4]; // 말의 번호, 방향
PII list[17];
bool alive[17] = { false };
PII dir[8] = { {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1} };
int answer;

// 도둑의 이동
void MOVE_T(int xx, int yy)
{
    for (int i = 1; i <= 16; i++) {
        if (alive[i] == false) continue;

        int x = list[i].first;
        int y = list[i].second;

        bool is_move = false;

        for (int j = 0; j < 8; j++) {
            if (is_move) break;

            int nd = (board[x][y].second + j) % 8;
            int nx = x + dir[nd].first;
            int ny = y + dir[nd].second;

            if (nx < 0 || 3 < nx || ny < 0 || 3 < ny) continue;
            if (nx == xx && ny == yy) continue;

            board[x][y].second = nd;

            PII tmp = board[nx][ny];
            board[nx][ny] = board[x][y];
            board[x][y] = tmp;

            list[board[x][y].first] = { x,y };
            list[board[nx][ny].first] = { nx,ny };

            is_move = true;
        }
    }
}

// 술래의 이동
void DFS(int x, int y, int d, int sum)
{
    answer = (answer < sum) ? sum : answer;

    PII copy_board[4][4];
    PII copy_list[17];

    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) copy_board[i][j] = board[i][j];
    for (int i = 1; i <= 16; i++) copy_list[i] = list[i];

    MOVE_T(x, y);

    for (int i = 1; i <= 3; i++) {
        int nx = x + i * dir[d].first;
        int ny = y + i * dir[d].second;

        if (nx < 0 || 3 < nx || ny < 0 || 3 < ny) continue;
        if (alive[board[nx][ny].first] == false) continue;

        alive[board[nx][ny].first] = false;
        DFS(nx, ny, board[nx][ny].second, sum + board[nx][ny].first);
        alive[board[nx][ny].first] = true;
    }

    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) board[i][j] = copy_board[i][j];
    for (int i = 1; i <= 16; i++) list[i] = copy_list[i];
}

int main()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> board[i][j].first >> board[i][j].second;
            board[i][j].second--;

            list[board[i][j].first] = { i,j };
            alive[board[i][j].first] = true;
        }
    }

    alive[board[0][0].first] = false;

    DFS(0,0, board[0][0].second, board[0][0].first);

    cout << answer;

    return 0;
}