#include <iostream>

using namespace std;
using ll = long long;

// 분할 정복 알고리즘 사용

// 짝수인 경우 A^(B/2) * A^(B/2)를
// 홀수인 경우 A^((B-1)/2) * A^((B-1)/2)

// 함수 시간복잡도 Θ(log n)
ll power(ll A, ll B) {

    if (B == 0) return 1;
    ll half = power(A, B / 2);
    ll result = half * half;
    if (B % 2 == 1) result = result * A;
    return result;
}

int main(void) {

    // test code
    ll A = 1020, B = 5;
    cout << power(A, B) << '\n';

    return 0;
}