#include <iostream>

using namespace std;

// 병합 과정
// 시간복잡도 O(n)
void merge(int *arr, int start, int mid, int end) {
    int i = start, j = mid + 1, k = 0;
    int *sorted = new int[end - start + 1];

    // 정렬 된 두 배열에 대해
    // 두 배열의 원소를 비교해서 작은 값을 새로운 정렬된 배열에 삽입
    // 이 과정은 두 배열 중 하나의 배열의 모든 원소가 사용될 때까지 반복됨
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) sorted[k++] = arr[i++];
        else sorted[k++] = arr[j++];
    }

    // 두 배열중 원소가 남아있는 배열은
    // 이미 정렬된 상태이므로 남은 원소를 그대로 넣어주면 됨
    while (i <= mid) sorted[k++] = arr[i++];
    while (j <= end) sorted[k++] = arr[j++];

    // 정렬된 배열은 임시배열이므로, 기존 배열에 값을 복사함
    for (int i = start, k = 0; i <= end; i++, k++) arr[i] = sorted[k];
    
    delete[] sorted;
}

// 병합 정렬 함수 (재귀사용)
// 원 입력 n을 점진적으로 2분할 하고 2번 계산을 하기 때문에
// 2T(n/2) + O(n) 의 시간복잡도를 가지며
// 2T(n/2) 는 재귀 트리를 그려보면
// 높이가 lg n 각 층 마다 결합 비용 O(n) 의 비용이 들기 때문에

// 총 시간 복잡도는 O(n lg n)
void merge_sort(int *arr, int start, int end) {

    if (start < end) {
        int mid = (start + end) / 2;        // O(1)
        merge_sort(arr, start, mid);      // T(n/2)
        merge_sort(arr, mid + 1, end);  // T(n/2)
        merge(arr, start, mid, end);       // O(n)
    }
}

int main(void) {

    // test code
    int *arr = new int[10]{3, 5, 6, 2, 1, 7, 9, 4, 8, 10};

    cout << "원본 배열\n";

    for (int i = 0; i < 10; i++) cout << arr[i] << ' ';
    cout << "\n\n";

    merge_sort(arr, 0, 9);

    cout << "정렬 후 내용\n";
    for (int i = 0; i < 10; i++) cout << arr[i] << ' ';
    cout << '\n';

    delete[] arr;

    return 0;
}