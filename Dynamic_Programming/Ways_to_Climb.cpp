#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 재귀방식으로 구현
int ways_top_down(int n, vector<int> &v) {
    if (n == 0) return 1;
    if (n < 0) return 0;

    if (v[n] != -1) return v[n];

    v[n] = ways_top_down(n - 1, v) + ways_top_down(n - 2, v) + ways_top_down(n - 3, v);
    return v[n];
}

// 반복문 방식으로 구현
int ways_bottom_up(int n) {
    
    if (n < 0) return 0;
    if (n == 0) return 1;

    vector<int> dp(n + 1, -1);
    dp[0] = 0;
    if (n >= 1) dp[1] = 1;
    if (n >= 2) dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    return dp[n];

}


int main(void) {

    int n = 10;

    vector<int> v(1001, -1);
    
    cout << "top down 방식\n";
    cout << ways_top_down(n, v) << endl;

    cout  << endl << endl;

    cout << "bottom up 방식 \n";
    cout << ways_bottom_up(n) << endl;

    return 0;
}