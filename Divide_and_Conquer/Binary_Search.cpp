#include <iostream>
#include <vector>

using namespace std;

// 이진탐색 알고리즘

// 정렬된 배열로만 사용할 수 있음
// 배열의 가운데 값을 기준으로
// v[mid] == key 인 경우 key 탐색 성공 -> mid 인덱스 반환
// v[mid] > key 인 경우 가운데 값을 기준으로 왼쪽 부분에 있음 -> end 인덱스를 mid - 1로 조정
// v[mid] < key 인 경우 가운데 값을 기준으로 오른쪽 부분에 있음 -> start 인덱스를 mid + 1로 조정

// 분할 갯수 1개, 입력개수 1/2, 결합비용 상수시간
// T(n) = 1 T(n/2) + 1
// Θ(log n)


// 반복문으로 이진탐색 구현
int binary_search(const vector<int>& v, int key) {
    int start = 0, end = v.size() - 1;

    while (start <= end) {
        int mid = (start + end) / 2;
        if (v[mid] == key) return mid;
        else if (v[mid] > key) end = mid - 1;
        else start = mid + 1;
    }

    return -1;
}

// 재귀문으로 이진탐색 구현
int binary_search_re(const vector<int>& v, int start, int end, int key) {
    if (start > end) return -1;
    
    int mid = (start + end) / 2;
    if (v[mid] == key) return mid;
    else if (v[mid] > key) return binary_search_re(v, start, mid - 1, key);
    else return binary_search_re(v, mid + 1, end, key);
}

int main(void) {

    // test code
    vector<int> v(5);

    // {3, 6, 9, 12, 15}
    for (int i = 0, j = 3; i < 5; i++, j += 3) v[i] = j;

    cout << "벡터 모든 원소\n";
    for (int x : v) cout << x << ' ';
    cout << '\n';
    cout << '\n';
    
    cout << "----------------- 반복문 기반 -----------------\n";
    cout << "key = 3 인 경우 해당 인덱스 출력\n";
    cout << binary_search(v, 3) << '\n';
    cout << '\n';
    
    cout << "key = 4 인 경우 해당 인덱스 출력\n";
    cout << binary_search(v, 4) << '\n';
    cout << '\n';

    cout << "----------------- 재귀문 기반 -----------------\n";
    cout << "key = 3 인 경우 해당 인덱스 출력\n";
    cout << binary_search(v, 3) << '\n';
    cout << '\n';
    
    cout << "key = 4 인 경우 해당 인덱스 출력\n";
    cout << binary_search(v, 4) << '\n';
    cout << '\n';

    return 0;
}