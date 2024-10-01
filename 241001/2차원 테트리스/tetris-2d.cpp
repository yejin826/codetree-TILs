#include <iostream>
#include <vector>

using namespace std;

int k;
vector<vector<bool>> board(10, vector<bool>(10, false));
struct Info {
    int t;
    int x;
    int y;
};
int score = 0;

void Move_red(Info I)
{
    int i = 0;

    // 1. 내리기
    if (I.t == 1) {
        for (i = 4; i < 10; i++) {
            if (board[I.x][i] == false) continue;
            else break;
        }
        board[I.x][i - 1] = true;
    }
    else if (I.t == 2) {
        for (i = 4; i < 10; i++) {
            if (board[I.x][i] == false) continue;
            else break;
        }
        board[I.x][i - 1] = true;
        board[I.x][i - 2] = true;
    }
    else {
        for (i = 4; i < 10; i++) {
            if (board[I.x][i] == false && board[I.x + 1][i] == false) continue;
            else break;
        }
        board[I.x][i - 1] = true;
        board[I.x + 1][i - 1] = true;
    }
}

void Move_yel(Info I)
{
    int i = 0;

    // 1. 내리기
    if (I.t == 1) {
        for (i = 4; i < 10; i++) {
            if (board[i][I.y] == false) continue;
            else break;
        }
        board[i - 1][I.y] = true;
    }
    else if (I.t == 2) {
        for (i = 4; i < 10; i++) {
            if (board[i][I.y] == false && board[i][I.y + 1] == false) continue;
            else break;
        }
        board[i - 1][I.y] = true;
        board[i - 1][I.y + 1] = true;
    }
    else {
        for (i = 4; i < 10; i++) {
            if (board[i][I.y] == false) continue;
            else break;
        }
        board[i - 2][I.y] = true;
        board[i - 1][I.y] = true;
    }
}

void Down_red(int idx)
{
    for (int i = idx; i > 3; i--) {
        for (int j = 0; j < 4; j++) {
            board[j][i + 1] = board[j][i];
            board[j][i] = false;
        }
    }
}

void Down_yel(int idx)
{
    for (int i = idx; i > 3; i--) {
        for (int j = 0; j < 4; j++) {
            board[i + 1][j] = board[i][j];
            board[i][j] = false;
        }
    }
}

void Check_line()
{
    // 빨강 확인 : 점수 & 내리기
    for (int i = 9; i > 5; i--) {
        if (board[0][i] == true && board[1][i] == true && board[2][i] == true && board[3][i] == true) {
            score++;

            board[0][i] = false;
            board[1][i] = false;
            board[2][i] = false;
            board[3][i] = false;

            Down_red(i - 1);
        }
    }

    // 노랑 확인 : 점수 & 내리기
    for (int i = 9; i > 5; i--) {
        if (board[i][0] == true && board[i][1] == true && board[i][2] == true && board[i][3] == true) {
            score++;

            board[i][0] = false;
            board[i][1] = false;
            board[i][2] = false;
            board[i][3] = false;

            Down_yel(i - 1);
        }
    }
}

void Check_area()
{
    // 연한 빨강 영역 확인
    for (int i = 4; i <= 5; i++) {
        bool is_in = false;

        for (int j = 0; j < 4; j++) {
            if (board[j][i] == true) is_in = true;
        }

        if (is_in) Down_red(8);
    }

    // 연한 노랑 영역 확인
    for (int i = 4; i <= 5; i++) {
        bool is_in = false;

        for (int j = 0; j < 4; j++) {
            if (board[i][j] == true) is_in == true;
        }

        if (is_in) Down_yel(8);
    }
}

int main()
{
    cin >> k;

    Info tmp;

    for (int i = 0; i < k; i++) {
        cin >> tmp.t >> tmp.x >> tmp.y;

        Move_red(tmp);
        Move_yel(tmp);

        Check_line();
        Check_area();
    }

    cout << score << '\n';

    int remain = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 6; j <= 9; j++) {
            if (board[i][j] == true) remain++;
            if (board[j][i] == true) remain++;
        }
    }

    cout << remain;

    return 0;
}