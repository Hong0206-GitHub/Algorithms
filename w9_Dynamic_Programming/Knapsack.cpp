#include <bits/stdc++.h>

using namespace std;

// 냅색 알고리즘 DP로 구현
void knapsack(vector<vector<int>> &table, vector<pair<int, int>> &v);

// 아이템 개수와 가능 무게
int N, W;

int main(void) {

    // 입출력 고속화
    ios::sync_with_stdio(false), cin.tie(NULL);

    // 4개의 아이템과 최대 허용 가능 무게 10
    N = 4, W = 10;
    
    // look-up table 선언
    vector<vector<int>> table(N + 1, vector<int>(W + 1));
    
    // <가치, 무게> 저장 벡터 선언 (개수 N)
    vector<pair<int, int>> v;

    // pdf 에서 제공된 예제 입력 값
    v.push_back({0, 0});
    v.push_back({10, 5});
    v.push_back({40, 4});
    v.push_back({30, 6});
    v.push_back({50, 3});

    // 함수 호출하여 look-up table 채우기
    knapsack(table, v);

    // 가장 마지막 원소가 답임
    cout << table[N][W] << '\n';

    return 0;
}

// 함수
void knapsack(vector<vector<int>> &table, vector<pair<int, int>> &v) {
    
    // 아이템들에 대해서
    for (int i = 1; i <= N; i++) {
        // 무게가 0~ 최대 허용 무게까지 
        for (int w = 0; w <= W; w++) {
            // 해당 아이템이 들어갈 수 있는 무게라면,
            // 해당 아이템을 포함했을 경우와 포함하지 않았을 경우의 최댓값을 선택해 넣음
            if (v[i].second <= w) table[i][w] = max(table[i - 1][w], v[i].first + table[i - 1][w - v[i].second]);
            else table[i][w] = table[i - 1][w]; // 넣을 수 없으면 이전 값 그대로 넣음
        }
    }
}