//
//  Created by izakharov on 28-29/03/20
//
//  6_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
//  Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
//  Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
//  Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с
//  индексом k (0..n-1) в отсортированном массиве.
//
//  Требования: к дополнительной памяти: O(n). Среднее время работы: O(n).
//  Должна быть отдельно выделенная функция partition. Рекурсия запрещена.
//  Решение должно поддерживать передачу функции сравнения снаружи.
//
//
//  Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
//  Описание для случая прохода от начала массива к концу:
//  Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
//  Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
//  Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
//  Последним элементом лежит опорный.
//  Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
//  Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
//  Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
//  Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
//  В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
//

#include <iostream>
#include <cassert>

template <class Comparator = std::less_equal<int>>
int find_median_of_three(const int* arr, int left, int right, Comparator comp);

template <class Comparator = std::less_equal<int>>
int partition(int* arr, int left, int right, Comparator comp);

template <class Comparator = std::less_equal<int>>
void set_kth_element(int* arr, int size, int k, Comparator comp = Comparator());


int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    assert(n >= 0 && k >= 0 && k < n);

    int* unordered_list = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> unordered_list[i];
    }

    set_kth_element(unordered_list, n, k);
    std::cout << unordered_list[k];

    delete[] unordered_list;
    return 0;
}


template<class Comparator>
int find_median_of_three(const int *arr, int left, int right, Comparator comp) {
    int mid = left + (right - left) / 2;
    if (comp(arr[left], arr[right])) {
        if (comp(arr[left], arr[mid])) {
            if (comp(arr[mid], arr[right])) {
                return mid;     //  l < mid < r
            } else {
                return right;   //  l < r < mid
            }
        } else {
            return left;        //  mid < l < r
        }
    } else {
        if (comp(arr[left], arr[mid])) {
            return left;        //  r < l < mid
        } else {
            if (comp(arr[mid], arr[right])) {
                return right;   //  mid < r < l
            } else {
                return mid;     //  r < mid < l
            }
        }
    }
}

template<class Comparator>
int partition(int *arr, int left, int right, Comparator comp) {
    int pivot_idx = find_median_of_three(arr, left, right - 1, comp);
    int pivot = arr[pivot_idx];
    std::swap(arr[pivot_idx], arr[left]);      //  Swap the pivot and the first (left) elem of sub-array

    int i = right - 1;                               //  Set i, j = r - 1, to start from the end of array
    int j = right - 1;                               //  _______ ___________ ______________ _______________
    while (left < j) {                               // |       |           |              |               |
        if (comp(arr[j], pivot)) {                   // | pivot |    ?      | a[j] > pivot | a[j] <= pivot |
            j--;                                     // |_______|___________|______________|_______________|
        } else {                                     //   arr[l]            j              i
            std::swap(arr[j], arr[i]);          //
            i--;                                     //   created by izakharov
            j--;
        }
    }
    std::swap(arr[left], arr[i]);               // Swap the pivot back with i-index element

    return i;
}

template<class Comparator>
void set_kth_element(int *arr, int size, int k, Comparator comp) {
    int left = 0;
    int right = size;
    while (left < right) {
        int m = partition(arr, left, right, comp);
        if (m < k) {
            left = m + 1;
        } else {
            right = m;
        }
    }
}
