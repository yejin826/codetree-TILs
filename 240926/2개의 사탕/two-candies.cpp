#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
pair<int, int> R, B, O;
vector<vector<char>> v;

struct P {
    pair<int, int> red;
    pair<int, int> blue;
    int dir;
    int cnt;
};

queue<P> q;

void MOVE_UP(P coord)
{
    pair<int, int> next_red;
    pair<int, int> next_blue;

    if (coord.red.first < coord.blue.first) {
        // RED
        int x = coord.red.first;
        int y = coord.red.second;

        while (true) {
            x--;

            if (x < 0 || N <= x) {
                x++;
                break;
            }
            if (v[x][y] == '#') {
                x++;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
        }

        next_red = { x,y };

        // BLUE
        x = coord.blue.first;
        y = coord.blue.second;

        while (true) {
            x--;

            if (x < 0 || N <= x) {
                x++;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                x++;
                break;
            }
            if (x == next_red.first && y == next_red.second) {
                if (next_red == O) {
                    return;
                }
                else {
                    x++;
                    break;
                }
            }
        }

        next_blue = { x,y };
    }
    else {
        // BLUE
        int x = coord.blue.first;
        int y = coord.blue.second;

        while (true) {
            x--;

            if (x < 0 || N <= x) {
                x++;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                x++;
                break;
            }
        }

        next_blue = { x,y };

        // RED
        x = coord.red.first;
        y = coord.red.second;

        while (true) {
            x--;

            if (x < 0 || N <= x) {
                x++;
                break;
            }
            if (v[x][y] == '#') {
                x++;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
            if (x == next_blue.first && y == next_blue.second) {
                x++;
                break;
            }
        }

        next_red = { x,y };
    }

    if (coord.red.first == next_red.first && coord.red.second == next_red.second) {
        return;
    }
    else {
        P new_coord;
        new_coord.red = next_red;
        new_coord.blue = next_blue;
        new_coord.dir = 0;
        new_coord.cnt = coord.cnt + 1;

        q.push(new_coord);
    }
}

void MOVE_RIGHT(P coord)
{
    pair<int, int> next_red;
    pair<int, int> next_blue;

    if (coord.red.second < coord.blue.second) {
        // BLUE
        int x = coord.blue.first;
        int y = coord.blue.second;

        while (true) {
            y++;

            if (y < 0 || M <= y) {
                y--;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                y--;
                break;
            }
        }

        next_blue = { x,y };

        // RED
        x = coord.red.first;
        y = coord.red.second;

        while (true) {
            y++;
            
            if (y < 0 || M <= y) {
                y--;
                break;
            }
            if (v[x][y] == '#') {
                y--;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
            if (x == next_blue.first && y == next_blue.second) {
                y--;
                break;
            }
        }

        next_red = { x,y };
    }
    else {
        // RED
        int x = coord.red.first;
        int y = coord.red.second;

        while (true) {
            y++;

            if (y < 0 || M <= y) {
                y--;
                break;
            }
            if (v[x][y] == '#') {
                y--;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
        }

        next_red = { x,y };

        // BLUE
        x = coord.blue.first;
        y = coord.blue.second;

        while (true) {
            y++;

            if (y < 0 || M <= y) {
                y--;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                y--;
                break;
            }
            if (x == next_red.first && y == next_red.second) {
                if (next_red == O) {
                    return;
                }
                else {
                    y--;
                    break;
                }
            }
        }

        next_blue = { x,y };
    }

    if (coord.red.first == next_red.first && coord.red.second == next_red.second) {
        return;
    }
    else {
        P new_coord;
        new_coord.red = next_red;
        new_coord.blue = next_blue;
        new_coord.dir = 1;
        new_coord.cnt = coord.cnt + 1;

        q.push(new_coord);
    }
}

void MOVE_DOWN(P coord)
{
    pair<int, int> next_red;
    pair<int, int> next_blue;

    if (coord.red.first < coord.blue.first) {
        // BLUE
        int x = coord.blue.first;
        int y = coord.blue.second;

        while (true) {
            x++;

            if (x < 0 || x >= N) {
                x--;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                x--;
                break;
            }
        }

        next_blue = { x,y };

        // RED
        x = coord.red.first;
        y = coord.red.second;

        while (true) {
            x++;

            if (x < 0 || x >= N) {
                x--;
                break;
            }
            if (v[x][y] == '#') {
                x--;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
            if (x == next_blue.first && y == next_blue.second) {
                x--;
                break;
            }
        }

        next_red = { x,y };
    }
    else {
        // RED
        int x = coord.red.first;
        int y = coord.red.second;

        while (true) {
            x++;

            if (x < 0 || x >= N) {
                x--;
                break;
            }
            if (v[x][y] == '#') {
                x--;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
        }

        next_red = { x,y };

        // BLUE
        x = coord.blue.first;
        y = coord.blue.second;

        while (true) {
            x++;

            if (x < 0 || x >= N) {
                x--;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                x--;
                break;
            }
            if (x == next_red.first && y == next_red.second) {
                if (next_red == O) {
                    return;
                }
                else {
                    x--;
                    break;
                }
            }
        }

        next_blue = { x,y };
    }

    if (coord.red.first == next_red.first && coord.red.second == next_red.second) {
        return;
    }
    else {
        P new_coord;
        new_coord.red = next_red;
        new_coord.blue = next_blue;
        new_coord.dir = 2;
        new_coord.cnt = coord.cnt + 1;

        q.push(new_coord);
    }
}

void MOVE_LEFT(P coord)
{
    pair<int, int> next_red;
    pair<int, int> next_blue;

    if (coord.red.second < coord.blue.second) {
        // RED
        int x = coord.red.first;
        int y = coord.red.second;

        while (true) {
            y--;

            if (y < 0 || M <= y) {
                y++;
                break;
            }
            if (v[x][y] == '#') {
                y++;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
        }

        next_red = { x,y };

        // BLUE
        x = coord.blue.first;
        y = coord.blue.second;

        while (true) {
            y--;

            if (y < 0 || M <= y) {
                y++;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                y++;
                break;
            }
            if (x == next_red.first && y == next_red.second) {
                if (next_red == O) {
                    return;
                }
                else {
                    y++;
                    break;
                }
            }
        }

        next_blue = { x,y };
    }
    else {
        // BLUE
        int x = coord.blue.first;
        int y = coord.blue.second;

        while (true) {
            y--;

            if (y < 0 || M <= y) {
                y++;
                break;
            }
            if (v[x][y] == 'O') {
                return;
            }
            if (v[x][y] == '#') {
                y++;
                break;
            }
        }

        next_blue = { x,y };
        
        // RED
        x = coord.red.first;
        y = coord.red.second;

        while (true) {
            y--;

            if (y < 0 || M <= y) {
                y++;
                break;
            }
            if (v[x][y] == '#') {
                y++;
                break;
            }
            if (v[x][y] == 'O') {
                break;
            }
            if (x == next_blue.first && y == next_blue.second) {
                y++;
                break;
            }
        }

        next_red = { x,y };
    }

    if (coord.red.first == next_red.first && coord.red.second == next_red.second) {
        return;
    }
    else {
        P new_coord;
        new_coord.red = next_red;
        new_coord.blue = next_blue;
        new_coord.dir = 3;
        new_coord.cnt = coord.cnt + 1;

        q.push(new_coord);
    }
}

int FIND()
{
    P init;
    init.red = R;
    init.blue = B;
    init.dir = -1;
    init.cnt = 0;

    q.push(init);

    while (!q.empty()) {
        P now = q.front();

        if (now.red.first == O.first && now.red.second == O.second) {
            if (now.blue.first == O.first && now.blue.second == O.second) {
                q.pop();
                continue;
            }
            else return now.cnt;
        }
        if (now.cnt >= 10) {
            q.pop();
            continue;
        }

        q.pop();
        
        if (now.dir == 0) {
            MOVE_UP(now);
            MOVE_RIGHT(now);
            MOVE_LEFT(now);
        }
        else if (now.dir == 1) {
            MOVE_UP(now);
            MOVE_RIGHT(now);
            MOVE_DOWN(now);
        }
        else if (now.dir == 2) {
            MOVE_RIGHT(now);
            MOVE_DOWN(now);
            MOVE_LEFT(now);
        }
        else if (now.dir == 3) {
            MOVE_UP(now);
            MOVE_DOWN(now);
            MOVE_LEFT(now);
        }
        else {
            MOVE_UP(now);
            MOVE_RIGHT(now);
            MOVE_DOWN(now);
            MOVE_LEFT(now);
        }
    }

    return -1;
}

int main()
{
    cin >> N >> M;

    v.resize(N, vector<char>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> v[i][j];

            if (v[i][j] == 'R') {
                R = { i,j };
                v[i][j] = '.';
            }
            if (v[i][j] == 'B') {
                B = { i,j };
                v[i][j] = '.';
            }
            if (v[i][j] == 'O') O = { i,j };
        }
    }

    cout << FIND();

    return 0;
}