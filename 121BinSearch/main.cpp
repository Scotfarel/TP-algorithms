//
//  Created by izakharov on 21/03/20
//
//  2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
//  Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A,
//  равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
//  Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)).
//  Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для
//  бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.
//

#include <iostream>
#include <cassert>


int find_range(const int* arr, int size, int num);
int find_insertion_point(const int* arr, int l_range, int r_range, int num);

int main() {
    int N = 0, M = 0;
    std::cin >> N >> M;
    assert(N > 0 && M > 0);

    int* sorted_list = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> sorted_list[i];
    }

    int* searching_list = new int[M];
    int* results_list = new int[M];
    for (int j = 0; j < M; j++) {
        std::cin >> searching_list[j];
        int r_index = find_range(sorted_list, N, searching_list[j]);
        results_list[j] = find_insertion_point(sorted_list, r_index / 2, r_index, searching_list[j]);
    }

    for (int k = 0; k < M; k++) {
        std::cout << results_list[k] << ' ';
    }

    delete[] sorted_list;
    delete[] searching_list;
    delete[] results_list;
    return 0;
}

int find_range(const int* arr, int size, int num) {
    if (num <= arr[0]) return 0;

    int step_index = 1;
    while (step_index < size && arr[step_index] < num) {
        step_index *= 2;
    }
    if (step_index >= size) {
        step_index = size - 1;
    }

    return step_index;
}

int find_insertion_point(const int* arr, int l_range, int r_range, int num) {
    int left = l_range;
    int right = r_range + 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] < num) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}