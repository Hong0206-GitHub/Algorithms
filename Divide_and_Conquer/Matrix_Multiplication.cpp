#include <iostream>
#include <vector>

using namespace std;

// 함수의 인자는 행렬곱을 수행할 수 있는 크기의 행렬만 받는다고 가정
// 추가로 2의 거듭제곱 크기만을 사용하여 학습

// Θ(n^3)
// 0번 인덱스부터 사용하므로 n-1까지 n은 행렬의 곱이 가능한지 확인하는 A의 열 크기이거나 B의 행 크기
// i는 A의 행 크기, j는 B의 열 크기
// C[i][j]=k=0∑n−1​A[i][k]×B[k][j]
vector<vector<long long>> matrix_multiplication_naive(const vector<vector<long long>> &A, const vector<vector<long long>> &B) {
    
    vector<vector<long long>> result(A.size(), vector<long long>(B[0].size()));

    for (size_t i = 0; i < result.size(); i++)
        for (size_t j = 0; j < result[0].size(); j++)
            for (size_t k = 0; k < A[0].size(); k++)
                result[i][j] = result[i][j] + A[i][k] * B[k][j];

    return result;
}

// 나이브한 방식의 분할정복 알고리즘을 사용하여 구현한 함수
// 시간복잡도는 위의 단순 반복함수와 동일하게
// T(n) = 8T(n/2) + Θ(n^2)
// Θ(n^3)
vector<vector<long long>> matrix_multiplication_naive_re(const vector<vector<long long>> &A, const vector<vector<long long>> &B) {
    
    int n = A.size();
    
    // Base Case
    if (n == 1) return {{A[0][0] * B[0][0]}};
    
    // 행렬을 4등분 함
    int mid = n / 2;
    vector<vector<long long>> A11(mid, vector<long long>(mid));
    vector<vector<long long>> A12(mid, vector<long long>(mid));
    vector<vector<long long>> A21(mid, vector<long long>(mid));
    vector<vector<long long>> A22(mid, vector<long long>(mid));

    vector<vector<long long>> B11(mid, vector<long long>(mid));
    vector<vector<long long>> B12(mid, vector<long long>(mid));
    vector<vector<long long>> B21(mid, vector<long long>(mid));
    vector<vector<long long>> B22(mid, vector<long long>(mid));

    // 각 부분행렬 복사
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid;j ++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][mid + j];
            A21[i][j] = A[mid + i][j];
            A22[i][j] = A[mid + i][mid + j];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][mid + j];
            B21[i][j] = B[mid + i][j];
            B22[i][j] = B[mid + i][mid + j];
        }
    }

    // 부분행렬의 곱 (재귀호출)
    auto C11 = matrix_multiplication_naive_re(A11, B11);
    auto temp1 = matrix_multiplication_naive_re(A12, B21);
    for(int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C11[i][j] += temp1[i][j];
        }
    }

    auto C12 = matrix_multiplication_naive_re(A11, B12);
    auto temp2 = matrix_multiplication_naive_re(A12, B22);
    for(int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C12[i][j] += temp2[i][j];
        }
    }

    auto C21 = matrix_multiplication_naive_re(A21, B11);
    auto temp3 = matrix_multiplication_naive_re(A22, B21);
    for(int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C21[i][j] += temp3[i][j];
        }
    }

    auto C22 = matrix_multiplication_naive_re(A21, B12);
    auto temp4 = matrix_multiplication_naive_re(A22, B22);
    for(int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C22[i][j] += temp4[i][j];
        }
    }

    // 4개의 부분행렬 합치기
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i+ mid][j + mid] = C22[i][j];
        }
    }

    return C;

}
//------------------------------------------ 보조 함수 ------------------------------------------
// 행렬 덧셈 함수
vector<vector<long long>> add(const vector<vector<long long>> &A, const vector<vector<long long>> &B) {
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

// 행렬 뺄셈 함수
vector<vector<long long>> sub(const vector<vector<long long>> &A, const vector<vector<long long>> &B) {
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}
//-------------------------------------------------------------------------------------------------------------



// 스트라센 아이디어를 적용하여
// 기존 분할 정복 알고리즘에서 사용했던
// 8개의 곱셈과 4개의 덧셈을

// 7개의 곱셈과 18개의 덧셈 + 뺄셈으로 바꾸어 구현
// 단, 상수항이 커서 실제 구현 효율은 큰 n에서만 효과적

// T(n) = 7T(n/2) + Θ(n^2)
// Θ(n^log 7) ~= Θ(n^2.81)
vector<vector<long long>> matrix_multiplication_strassen(const vector<vector<long long>> &A, const vector<vector<long long>> &B) {

    int n = A.size();

    // Base Case
    if (n == 1)
        return {{A[0][0] * B[0][0]}};

    int mid = n / 2;

    // 행렬을 4등분 함
    vector<vector<long long>> A11(mid, vector<long long>(mid));
    vector<vector<long long>> A12(mid, vector<long long>(mid));
    vector<vector<long long>> A21(mid, vector<long long>(mid));
    vector<vector<long long>> A22(mid, vector<long long>(mid));

    vector<vector<long long>> B11(mid, vector<long long>(mid));
    vector<vector<long long>> B12(mid, vector<long long>(mid));
    vector<vector<long long>> B21(mid, vector<long long>(mid));
    vector<vector<long long>> B22(mid, vector<long long>(mid));

    // 각 부분행렬 복사
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][mid + j];
            A21[i][j] = A[mid + i][j];
            A22[i][j] = A[mid + i][mid + j];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][mid + j];
            B21[i][j] = B[mid + i][j];
            B22[i][j] = B[mid + i][mid + j];
        }
    }

    // 7개의 핵심 곱셈
    auto M1 = matrix_multiplication_strassen(add(A11, A22), add(B11, B22));
    auto M2 = matrix_multiplication_strassen(add(A21, A22), B11);
    auto M3 = matrix_multiplication_strassen(A11, sub(B12, B22));
    auto M4 = matrix_multiplication_strassen(A22, sub(B21, B11));
    auto M5 = matrix_multiplication_strassen(add(A11, A12), B22);
    auto M6 = matrix_multiplication_strassen(sub(A21, A11), add(B11, B12));
    auto M7 = matrix_multiplication_strassen(sub(A12, A22), add(B21, B22));

    // 결과 조합
    auto C11 = add(sub(add(M1, M4), M5), M7);
    auto C12 = add(M3, M5);
    auto C21 = add(M2, M4);
    auto C22 = add(sub(add(M1, M3), M2), M6);

    // 4개의 부분행렬 합치기
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    return C;
}

int main(void) {

    // test code

    // 행렬 곱 기본
    // A = x * y, B = p * q 일 때
    // y == p 인 경우에 한해서 곱셈을 할 수 있으며, 곱셈 결과 행렬의 크기는
    // x * q 크기가 됨

    vector<vector <long long>> A = {{1, 2}, {3,  4}};
    vector<vector <long long>> B = {{5, 6}, {9, 10}};

    cout << "행렬 A\n";
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[0].size(); j++) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << endl << endl;

    cout << "행렬 B" << endl;
    for(size_t i = 0; i < B.size(); i++) {
        for (size_t j = 0; j < B[0].size(); j++) {
            cout << B[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl << endl;

    auto result = matrix_multiplication_naive(A, B);
    auto result1 = matrix_multiplication_naive_re(A, B);
    auto result2 = matrix_multiplication_strassen(A, B);
    
    cout << "----------------- naive 방식 -----------------\n";
    cout << "곱셈 결과" << endl;
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            cout << result[i][j] << ' ';
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "----------------- naive 분할 정복 방식 -----------------\n";
    for (size_t i = 0; i < result1.size(); i++) {
        for (size_t j = 0; j < result1[0].size(); j++) {
            cout << result1[i][j] << ' ';
        }
        cout << endl;
    }

    
    cout << endl;
    cout << "----------------- strassen 방식 -----------------\n";
    for (size_t i = 0; i < result2.size(); i++) {
        for (size_t j = 0; j < result2[0].size(); j++) {
            cout << result2[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}