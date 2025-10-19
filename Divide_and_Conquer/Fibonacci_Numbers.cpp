#include <iostream>
#include <vector>

using namespace std;

// 반복문
// Θ(n)
long long fibonacci_iter(int n) {
    long long fn_1= 0;
    long long fn_2 = 1;
    long long answer = 0;

    if (n == 0) return 0;
    else if (n == 1) return 1;

    for (int i = 2; i <= n; i++) {
        answer = fn_1 + fn_2;
        fn_1 = fn_2;
        fn_2 = answer;
    }

    return answer;
}

// 재귀
// Θ(2^n)
long long fibonacci_recur(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return fibonacci_recur(n - 1) + fibonacci_recur(n - 2);

}

// // 재귀를 동적 계획법(DP)로 작성하면 시간복잡도를
// // Θ(n) 까지 줄일 수 있으나, 아직 학습하지 않았으므로, 학습후 추가 예정

// long long fibonacci_dp(int n) {

// }

// // 행렬 거듭제곱
// // Θ(log n)
// vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {


// }

// vector<vector<long long>> matrix_pow(vector<vector<long long>> base, int n) {


// }

// long long fibonacci_matrix(int n) {
    
// }

int main(void) {

    // test code
    int n = 10;

    cout << "반복문: " << fibonacci_iter(n) << '\n';
    cout << "재귀문: " << fibonacci_recur(n) << '\n';
    // cout << "행렬: " << fibonacci_matrix(n) << '\n';

    return 0;
}
