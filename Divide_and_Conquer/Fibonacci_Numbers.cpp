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




// 행렬 거듭제곱
// Θ(log n)

// 행렬곱 연산만 하는 함수
// 피보나치 수열을 행렬로 표현하면, 2x2 행렬로만 표현되므로,
// 곱셈 8번과 덧셈 4번만 수행함.
// 이 경우의 시간복잡도는 Θ(1)
vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    vector<vector<long long>> result(2, vector<long long>(2));
    
    result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
    
    return result;
}

// 지수 연산을 분할 정복 알고리즘으로 구현
vector<vector<long long>> matrix_pow(vector<vector<long long>> base, int n) {

    // 지수가 1인 경우 그 자신 리턴
    if (n == 1) return base;

    // 행렬의 n / 2승을 구하고 그 둘이 곱하면 n의 제곱승을 한 값을 구할 수 있음
    auto half = matrix_pow(base, n / 2);
    auto result = multiply(half, half);

    // n이 홀수인 경우 자기 자신을 마지막에 한 번 더 곱해줌
    if (n % 2 == 1) result = multiply(result, base);

    return result;

}

long long fibonacci_matrix(int n) {

    // n == 0인 경우의 점화식은 0
    if (n == 0) return 0;

    // 기본 베이스 행렬 선언
    // {fn+1, fn}
    // {fn    ,  fn-1}
    // 로 피보나치 수열의 원소를 2x2 행렬로 표현
    vector<vector<long long>> base = {{1, 1}, {1, 0}};

    // 함수 선언 해서 원하는 n값 -1 만큼 행렬 거듭제곱 연산을 수행
    // n - 1 인 이유는 해당 행렬 [0][0]이 fn+1까지 표현하므로,
    // 굳이 n번 연산할 필요가 없음
    auto result = matrix_pow(base, n - 1);

    // 결과 출력
    return result[0][0];
}

int main(void) {

    // test code
    int n = 10;

    cout << "반복문: " << fibonacci_iter(n) << '\n';
    cout << "naive 재귀문: " << fibonacci_recur(n) << '\n';
    //cout << "dp 재귀문: " << fibonacci_dp(n) << '\n';
    cout << "행렬: " << fibonacci_matrix(n) << '\n';

    return 0;
}
