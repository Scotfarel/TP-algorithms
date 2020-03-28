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


void input_list(int* arr, int size);
void print_list(const int* arr, int size);

void search_greater_or_equal(int* result_list, const int* sorted_list, int sorted_size,
        const int* searching_list, int searching_size);
int find_range(const int* arr, int size, int num);
int find_insertion_point(const int* arr, int l_range, int r_range, int num);


int main() {
    int N = 0, M = 0;
    std::cin >> N >> M;
    assert(N > 0 && M > 0);

    int* sorted_list = new int[N];
    input_list(sorted_list, N);

    int* searching_list = new int[M];
    input_list(searching_list, M);

    int* result_list = new int[M];
    search_greater_or_equal(result_list, sorted_list, N, searching_list, M);

    print_list(result_list, M);

    delete[] sorted_list;
    delete[] searching_list;
    delete[] result_list;
    return 0;
}

void input_list(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
}

void print_list(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
}

void search_greater_or_equal(int* result_list, const int* sorted_list, int sorted_size,
        const int* searching_list, int searching_size) {
    for (int i = 0; i < searching_size; i++) {
        int r_index = find_range(sorted_list, sorted_size, searching_list[i]);
        result_list[i] = find_insertion_point(sorted_list, r_index / 2, r_index, searching_list[i]);
    }
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
