#include <bits/stdc++.h>

using namespace std;

// 함수 선언
void knapsack(int N, int W);
void print_backtracking(int N, int W);

// 기본 자료형 선언
vector<int> value;
vector<int> weight;
vector<vector<int>> table;
vector<vector<bool>> keep;

int main(void) {

    // 입출력 고속화
    ios::sync_with_stdio(false), cin.tie(NULL);

    // pdf 예제 값 입력
    int N = 4, W = 10;

    // 자료형 초기화
    value.resize(N + 1);
    weight.resize(N + 1);
    table.resize(N + 1, vector<int>(W + 1));
    keep.resize(N + 1, vector<bool>(W + 1, false));


    value[1] = 10;
    value[2] = 40;
    value[3] = 30;
    value[4] = 50;
    
    weight[1] = 5;
    weight[2] = 4;
    weight[3] = 6;
    weight[4] = 3;

    // 초기값 설정
    for (int i = 0; i <= W; i++) table[0][i] = 0;

    // 함수호출 및 답안 출력
    knapsack(N, W);
    cout << table[N][W] << '\n';
    print_backtracking(N, W);
    cout << '\n';

    return 0;
}

// DP 알고리즘으로 구현한 냅색 함수
void knapsack(int N, int W) {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= W; j++) {
            // 선택할 수 있는 경우
            if (weight[i] <= j) {
                // 해당 아이템을 선택한 경우와 선택하지 않은 경우 중 가치가 큰 값을 선택
                table[i][j] = max(table[i - 1][j], value[i] + table[i - 1][j - weight[i]]);

                // 선택한 것을 keep 벡터에 기록
                if (table[i - 1][j] <= value[i] + table[i - 1][j - weight[i]]) keep[i][j] = true;          
                else keep[i][j] = false;      
            }
            else {
                // 선택할 수 없는 경우는 이전 값 그대로 불러옴
                table[i][j] = table[i - 1][j]; 
                keep[i][j] = false;
            }
        }
    }
}

// 선택한 아이템 인덱스 출력하는 함수
void print_backtracking(int N, int W) {

    // DP는 하위에서 상위로 올라왔기 때문에
    // 역추적은 상위에서 하위로 추적
    for (int i = N; i >= 1; i--) {
        // 기록 되어있는 경우 출력해주고,
        if (keep[i][W]) {
            cout << i << ' ';
            // 무게 갱신해줌
            W = W - weight[i];
        }
    }
}