#include <iostream>
#include <vector>

using namespace std;

// 두 값 교환하는 함수
void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

// 파티셔닝 함수
// 피벗을 기준으로 작은 값은 start ~ i - 1까지 범위에
// 큰 값은 i + 1 ~ end까지의 범위에 존재함
int partition(vector<int> &v, int start, int end) {
    int pivot = v[start]; // 피벗으로 항상 첫 번재 원소를 선택 (최악의 경우 Θ(n^2)의 시간복잡도를 가지게 되는 방식)
    int i = start; // 피벗 위치와 동일한 위치에서 시작
    for (int j = start + 1; j <= end; j++) // i보다 1큰 위치에서 시작
        if (v[j] <= pivot) swap(v[++i], v[j]); // 피벗보다 현재의 원소가 더 작다면, 피벗보다 큰 수들이 있는 위치인 i+1과 현재 원소를 교환
    swap(v[start], v[i]); // 마지막에 피벗을 가운데로 옮겨줌

    // 피벗 인덱스 반환
    return i;
}

// 유효한 범위에 한해
// pivot을 기준으로 오른쪽 왼쪽 재귀호출
// 이미 정렬된 상태이거나, pivot으로 min, max 값만 선택하면
// 최악의 경우로 Θ(n^2) 의 시간복잡도를 가짐

// 최악의 경우가 아닌 경우 항상 Θ(n log n)의 시간복잡도를 가짐
// 최악의 경우를 방지하기 위해 랜덤 피벗을 선택하는 방법이 있으나,
// 나중에 구현할 예정임
void quick_sort(vector<int> &v, int start, int end) {
    if (start < end) {
        int q = partition(v, start, end); // 피벗 위치에서 오른쪽 왼쪽을 재귀호출
        quick_sort(v, start, q -  1);
        quick_sort(v, q + 1, end);
    }
}

int main(void) {

    vector<int> v = {3, 5, 6, 2, 7, 9, 10, 1, 4, 8};

    cout << "원본 벡터\n";
    for(int x : v) cout << x << ' ';
    cout << endl << endl;

    cout << "퀵 소트 후 벡터\n";
    quick_sort(v, 0, 9);
    for (int x : v) cout << x << ' ';
    cout << endl;

    return 0;
}