#include <iostream>
#include <vector>

using namespace std;

int N, M, K, C;
struct info_arr {
    int tree;
    int remain;
};
vector<vector<info_arr>> arr;
pair<int, int> d[4] = { {0,1},{0,-1},{1,0},{-1,0} };
pair<int, int> dc[4] = { {-1,-1},{-1,1},{1,-1},{1,1} };

void grow_up()
{
    vector<vector<int>> tmp_grow(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (1 <= arr[i][j].tree) {
                for (int k = 0; k < 4; k++) {
                    int nx = i + d[k].first;
                    int ny = j + d[k].second;

                    if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;

                    if (1 <= arr[nx][ny].tree) {
                        tmp_grow[i][j]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j].remain > 0) continue;

            arr[i][j].tree += tmp_grow[i][j];
        }
    }
}

void breed()
{
    vector<vector<int>> tmp_breed(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (1 <= arr[i][j].tree) {
                int cnt = 0;
                vector<pair<int, int>> coord_list;

                for (int k = 0; k < 4; k++) {
                    int nx = i + d[k].first;
                    int ny = j + d[k].second;

                    if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
                    if (arr[nx][ny].tree == -1 || 1 <= arr[nx][ny].tree || arr[nx][ny].remain > 0) continue;
                    
                    coord_list.push_back({ nx, ny });
                    cnt++;
                }
                
                for (int k = 0; k < coord_list.size(); k++) {
                    tmp_breed[coord_list[k].first][coord_list[k].second] += (arr[i][j].tree / cnt);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j].remain > 0) continue;

            arr[i][j].tree += tmp_breed[i][j];
        }
    }
}

pair<int, int> select()
{
    vector<vector<int>> tmp_max(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j].tree == -1) continue;
            
            tmp_max[i][j] = arr[i][j].tree;

            if (arr[i][j].tree == 0) continue;

            for (int l = 0; l < 4; l++) {
                for (int k = 1; k <= K; k++) {
                    int x = i + dc[l].first * k;
                    int y = j + dc[l].second * k;

                    if (x < 0 || N <= x || y < 0 || N <= y) continue;

                    if (arr[x][y].tree == -1 || arr[x][y].tree == 0) break;

                    tmp_max[i][j] += arr[x][y].tree;
                }
            }
        }
    }

    int max = 0;
    pair<int, int> target = {-1,-1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tmp_max[i][j] > max) {
                max = tmp_max[i][j];
                target = { i,j };
            }
        }
    }

    return target;
}

int spread(int x, int y)
{
    if (x == -1 && y == -1) return 0;

    int total = arr[x][y].tree;

    arr[x][y].tree = 0;
    arr[x][y].remain = C + 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= K; j++) {
            int nx = x + dc[i].first * j;
            int ny = y + dc[i].second * j;

            if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
            
            if (arr[nx][ny].tree == 0 || arr[nx][ny].tree == -1) {
                arr[nx][ny].remain = C + 1;
                break;
            }

            if (1 <= arr[nx][ny].tree) {
                total += arr[nx][ny].tree;
                arr[nx][ny].tree = 0;
                arr[nx][ny].remain = C + 1;
            }
        }
    }

    return total;
}

void minus_drug()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j].remain--;

            if (arr[i][j].remain <= 0) arr[i][j].remain = 0;
        }
    }
}

void print_grid()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j].tree << ' ';
        }
        cout << endl;
    }
}

void print_grid2()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j].remain << ' ';
        }
        cout << endl;
    }
}

int main()
{
    cin >> N >> M >> K >> C;

    arr.resize(N, vector<info_arr>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int t;
            cin >> t;

            arr[i][j].tree = t;
            arr[i][j].remain = 0;
        }
    }

    int answer = 0;

    /*
    grow_up();
    cout << "\n성장 후 나무양\n";
    print_grid();
    breed();
    cout << "\n번식 후 나무양\n";
    print_grid();
    pair<int, int> selected = select();
    cout << "\n제초제를 뿌릴 좌표\n" << selected.first << ' ' << selected.second;
    answer += spread(selected.first, selected.second);
    cout << "\n박멸한 나무의 개수\n" << answer << endl;
    cout << "\n남은 제초제의 양\n";
    print_grid2();
    */
    
    for (int i = 1; i <= M; i++) {
        grow_up();
        breed();
        pair<int, int> selected = select();
        answer += spread(selected.first, selected.second);
        minus_drug();
    }

    cout << answer;
    
    return 0;
}