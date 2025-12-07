#include <bits/stdc++.h>

using namespace std;

// DP로 LCS 구하는 함수
void LCS_bottom_up(vector<vector<int>> &table, string &x, string &y);
int LCS_top_down(vector<vector<int>> &table, string &x, string &y, int i, int j);

int main(void) {

    // 입출력 고속화
    ios::sync_with_stdio(false), cin.tie(NULL);

    // pdf 예시 입력
    string x = "ABCBDAB";
    string y = "BDCABA";

    // look-up table 선언
    vector<vector<int>> table(x.length() + 1, vector<int>(y.length() + 1));
    // 함수 호출하여, LCS 구하기
    LCS_bottom_up(table, x, y);

    // 답안 출력
    cout << table[x.length()][y.length()] << '\n';


    // 예상 출력: 4
    return 0;
}

// 바텀-업 (반복문)으로 구현
void LCS_bottom_up(vector<vector<int>> &table, string &x, string &y) {

    // 0번 인덱스의 경우, 두 문자열의 길이가 0인 경우 0이므로, 배제
    for (int i = 1; i <= x.length(); i++) {
        for (int j = 1; j <= y.length(); j++) {
            // 문자가 같다면, 이전 (대각선 위) 길이 불러오기
            if (x[i - 1] == y[j - 1]) table[i][j] = table[i - 1][j - 1] + 1;
            // 문자가 다르다면, 이전 길이에서 가장 긴 길이로 불러오기
            else table[i][j] = max(table[i][j - 1], table[i - 1][j]);
        }
    }
}

int LCS_top_down(vector<vector<int>> &table, string &x, string &y, int i, int j) {
    
    // prefix 길이가 0이면 0
    if (i == 0 || j == 0) return 0;

    // dp테이블에 기록되지 않은 상태라면, 아래 연산 수행
    if (table[i][j] == -1) {
        // 글자가 같은 경우, 이전 LCS 길이 + 1
        if (x[i - 1] == y[j - 1]) table[i][j] = LCS_top_down(table, x, y, i - 1, j - 1) + 1;
        
        // 글자가 다른 경우, x의 마지막 문자나, y의 마지막 문자를 제한 LCS 테이블에서 큰 값 선택
        else table[i][j] =  max(LCS_top_down(table, x, y, i - 1, j), LCS_top_down(table, x, y, i, j - 1));
    }

    return table[i][j];
}