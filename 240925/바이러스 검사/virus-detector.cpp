#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int H, T;
    cin >> H >> T;

    long long answer = 0;

    for (int i = 0; i < n; i++) {
        answer++;
        
        if (v[i] > H) {
            v[i] -= H;

            answer += v[i] / T;

            if (v[i] % T) answer++;
        }
    }

    cout << answer;

    return 0;
}