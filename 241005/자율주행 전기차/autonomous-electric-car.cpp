#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, C;
vector<vector<int>> load;
pair<int, int> vehicle;
struct info {
    int s_x;
    int s_y;
    int d_x;
    int d_y;
};
vector<info> passenger;
vector<bool> is_arrived;
pair<int, int> direction[4] = { {0,1},{0,-1},{1,0},{-1,0} };

int BFS(int sx, int sy, int ex, int ey) // charging은 승객 -> 도착지 여정인지 확인
{
    vector<vector<bool>> visited;
    visited.resize(N, vector<bool>(N, false));
    queue<pair<pair<int, int>, int>> q; // { { 행, 열 }, 거리 }
    int dist = -1;

    q.push({ {sx, sy}, 0 });
    visited[sx][sy] = true;

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int c = q.front().second;

        q.pop();

        if (x == ex && y == ey) {
            dist = c;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + direction[i].first;
            int ny = y + direction[i].second;

            if (nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
            if (load[nx][ny] == 1) continue;
            if (visited[nx][ny]) continue;

            visited[nx][ny] = true;
            q.push({ {nx, ny}, c + 1 });
        }
    }

    return dist;
}

bool cmp(pair<int, int> A, pair<int, int> B)
{
    if (A.first < B.first) return true;
    else if (A.first > B.first) return false;
    else {
        if (passenger[A.second].s_x < passenger[B.second].s_x) return true;
        else if (passenger[A.second].s_x > passenger[B.second].s_x) return false;
        else {
            if (passenger[A.second].s_y < passenger[B.second].s_y) return true;
            else return false;
        }
    }
}

int search_move_to_passenger()
{
    vector<pair<int, int>> candidate; // { 최단 거리, 해당 승객의 번호 }

    for (int i = 1; i <= M; i++) {
        if (is_arrived[i]) continue;

        int dist = BFS(vehicle.first, vehicle.second, passenger[i].s_x, passenger[i].s_y);

        if (dist == -1) return -1;

        candidate.push_back({ dist, i });
    }

    sort(candidate.begin(), candidate.end(), cmp);

    // 승객의 위치로 이동 & 배터리 소모 확인
    vehicle = { passenger[candidate[0].second].s_x, passenger[candidate[0].second].s_y };
    C -= candidate[0].first;

    if (C <= 0) return -1;
    else return candidate[0].second;
}

bool move_to_destination(int id)
{
    int dist = BFS(passenger[id].s_x, passenger[id].s_y, passenger[id].d_x, passenger[id].d_y);

    if (dist == -1) return false;

    vehicle = { passenger[id].d_x, passenger[id].d_y };
    C -= dist;

    // 도착하는 과정의 배터리 소모 확인
    if (C < 0) return false;
    else {
        C += dist * 2;
        is_arrived[id] = true;
        return true;
    }
}

void print_coord()
{
    cout << "vehicle : " << vehicle.first << ", " << vehicle.second << endl;
    cout << "battery : " << C << endl;
    cout << endl;
}

int main()
{
    cin >> N >> M >> C;

    load.resize(N, vector<int>(N));
    passenger.resize(M + 1);
    is_arrived.resize(M + 1, false);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> load[i][j];
        }
    }

    cin >> vehicle.first >> vehicle.second;
    vehicle.first--;
    vehicle.second--;

    for (int i = 1; i <= M; i++) {
        cin >> passenger[i].s_x >> passenger[i].s_y >> passenger[i].d_x >> passenger[i].d_y;
        passenger[i].s_x--;
        passenger[i].s_y--;
        passenger[i].d_x--;
        passenger[i].d_y--;
    }

    int answer = 0;

    for (int t = 1; t <= M; t++) {
        //print_coord();

        int target_num = search_move_to_passenger();

        if (target_num == -1) {
            answer = -1;
            break;
        }

        //print_coord();

        // 승객 -> 목적지
        bool check_arrive = move_to_destination(target_num);

        if (check_arrive == false) {
            answer = -1;
            break;
        }

        //print_coord();

        answer = C;
    }

    for (int i = 1; i <= M; i++) {
        if (is_arrived[i] == false) answer = -1;
    }

    cout << answer;

    return 0;
}