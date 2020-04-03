//
//  Created by izakharov on 3/04/20
//
//  7_2. LSD для long long.
//  Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
//  Отсортировать массив методом поразрядной сортировки LSD по байтам.
//

#include <iostream>
#include <cstring>
#include <cmath>

void radix_lsd_sort(unsigned long long* list, int size);
void counting_sort(unsigned long long* list, int size, int current_byte);


int main(){
    int n = 0;
    std::cin >> n;

    auto* array = new unsigned long long[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    radix_lsd_sort(array, n);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << ' ';
    }

    delete[] array;
    return 0;
}

void counting_sort(unsigned long long* list, int size, int current_byte) {
    int num_byte_variations = static_cast<int>(pow(2, 8));
    int* byte_count_list = new int[num_byte_variations];
    memset(byte_count_list, 0, sizeof(int) * num_byte_variations);

    for (int i = 0; i < size; i++) {
        int byte = (list[i] >> (8 * current_byte)) & 0xff;  //  this is how to get the nth byte of an integer
        byte_count_list[byte]++;
    }
    for (int i = 1; i < num_byte_variations; i++) {
        byte_count_list[i] += byte_count_list[i - 1];
    }

    auto* sorted_list = new unsigned long long[size];
    for (int i = size - 1; i >= 0; i--) {
        int byte = (list[i] >> (8 * current_byte)) & 0xff;
        sorted_list[--byte_count_list[byte]] = list[i];
    }
    memcpy(list, sorted_list, size * sizeof(unsigned long long));
    delete[] byte_count_list;
    delete[] sorted_list;
}

void radix_lsd_sort(unsigned long long* list, int size) {
    int ull_bytes_size = sizeof(unsigned long long);
    for (int byte_index = 0; byte_index < ull_bytes_size; byte_index++) {
        counting_sort(list, size, byte_index);
    }
}
