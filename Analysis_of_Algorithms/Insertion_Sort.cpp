#include <iostream>

using namespace std;

// 삽입 정렬 알고리즘
void insertion_sort(int* arr, int size) {

    // 두 번째 원소부터 비교해서
    // 작은 값을 계속 앞으로 이동시킴
    for (int i = 1; i < size; i++) {
        
        int idx = i;
        while (idx > 0 && arr[idx -1] > arr[idx]) {
            int temp = arr[idx];
            arr[idx] = arr[idx - 1];
            arr[idx - 1] = temp;
            idx--;
        }
    }
}


int main(void) {

    // test code
    int *arr = new int[10]{3, 5, 6, 2, 1, 7, 9, 4, 8, 10};

    cout << "원본 배열\n";

    for (int i = 0; i < 10; i++) cout << arr[i] << ' ';
    cout << "\n\n";

    insertion_sort(arr, 10);

    cout << "정렬 후 내용\n";
    for (int i = 0; i < 10; i++) cout << arr[i] << ' ';
    cout << '\n';

    delete[] arr;

    return 0;
}