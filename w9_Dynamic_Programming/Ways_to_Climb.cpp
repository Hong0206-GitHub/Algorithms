#include <bits/stdc++.h>

using namespace std;

// 재귀방식으로 구현
int ways_top_down(int n, vector<int> &v) {
    // 기저 조건
    // n이 0인 경우는 아무것도 안하는 1가지의 경우의 수만 존재함.
    // n이 음수인 경우는 경우의 수가 존재하지 않음.
    if (n == 0) return 1;
    if (n < 0) return 0;

    // dp 테이블에 저장된 값이 존재하는 경우 그 값을 사용
    // 중복 연산 회피 -> DP의 본질
    if (v[n] != -1) return v[n];

    // 위에서 걸러지지 않은 경우,
    // 연산이 필요함

    // 연산해서 이를 벡터에 저장하여 중복 연산을 피함
    v[n] = ways_top_down(n - 1, v) + ways_top_down(n - 2, v) + ways_top_down(n - 3, v);
    
    // 저장한 값을 리턴
    return v[n];
}

// 반복문 방식으로 구현
int ways_bottom_up(int n) {
    
    // 기저 조건
    if (n < 0) return 0;
    if (n == 0) return 1;

    // dp 테이블 선언 (벡터의 크기는 n + 1이어야 함. 이유는 모든 하위문제(본 문제 포함)를 테이블에 포함해야 하기 때문)
    vector<int> dp(n + 1, -1);
    
    // 초기값 삽입
    dp[0] = 1;

    // 범위 벗어나지 않게 범위 조절 해주고, dp 반복문엔 점화식 하나만 넣어주기 위해서
    // 초기값 추가 삽입
    if (n >= 1) dp[1] = 1;
    if (n >= 2) dp[2] = 2;

    // 점화식
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
    }

    return dp[n];
}

// 3변수를 사용하여 구현 (반복문 보다 공간 복잡도가 적음)
int ways_bottom_up_clear(int n) {

    // 기저 조건
    if (n < 0) return 0;
    if (n == 0) return 1;

    // dp 테이블 사용 대신, 연산 루틴을 고려하여 3개의 변수만 사용
    int temp1 = 0, temp2 = 0, temp3 = 1, answer = 0;

    // 점화식
    for (int i = 1; i <= n; i++) {
        answer = temp3 + temp2 + temp1;
        temp1 = temp2;
        temp2 = temp3;
        temp3 = answer;
    }

    return answer;
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