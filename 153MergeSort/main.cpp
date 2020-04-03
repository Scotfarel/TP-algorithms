//
//  Created by izakharov on 3/04/20
//
//  Требование для всех вариантов Задачи 5
//  Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием.
//  Решение должно поддерживать передачу функции сравнения снаружи.
//  Общее время работы алгоритма O(n log n).
//
//  5_3. Закраска прямой 1.
//  На числовой прямой окрасили N отрезков.
//  Известны координаты левого и правого концов каждого отрезка (Li и Ri).
//  Найти длину окрашенной части числовой прямой.
//


#include <iostream>
#include <cstring>

class Point{
public:
    Point() = default;;
    Point(int x, bool begin) : coordinate(x), is_begin(begin) {};
    ~Point() = default;

    friend bool operator<(const Point& l, const Point& r) {
        return l.coordinate < r.coordinate;
    }

    int coordinate = 0;
    bool is_begin = true;
};

template <class T, class Comparator = std::less<Point>>
void merge(T* sorted_list, const T* l_list, int l_size, const T* r_list, int r_size, Comparator comp);

template <class T, class Comparator = std::less<T>>
void merge_sort(T* list, int size, Comparator comp = Comparator());

int count_length_painted_lines(Point* list, int size);

int main() {
    int n = 0;
    std::cin >> n;

    auto* points = new Point[2 * n];
    for (int i = 0; i < 2 * n; i += 2) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        points[i] = Point(x, true);
        points[i + 1] = Point(y, false);
    }

    merge_sort(points, 2 * n);
    std::cout << count_length_painted_lines(points, 2 * n);

    delete[] points;
    return 0;
}

template <class T, class Comparator>
void merge(T* sorted_list, const T* l_list, int l_size, const T* r_list, int r_size, Comparator comp) {
    int sorted_index = 0;
    int i = 0;
    int j = 0;
    while ((i < l_size) and (j < r_size)) {
        if (comp(l_list[i], r_list[j])) {
            sorted_list[sorted_index++] = l_list[i++];
        } else {
            sorted_list[sorted_index++] = r_list[j++];
        }
    }

    while (i < l_size) {
        sorted_list[sorted_index++] = l_list[i++];
    }
    while (j < r_size) {
        sorted_list[sorted_index++] = r_list[j++];
    }
}

template <class T, class Comparator>
void merge_sort(T* list, int size, Comparator comp) {
    if (size == 1) return;
    int mid = size / 2;
    merge_sort(list, mid);
    merge_sort(list + mid, size - mid);

    T* sorted_list = new T[size];
    merge(sorted_list, list, mid, list + mid, size - mid, comp);
    memcpy(list, sorted_list, size * sizeof(T));
    delete[] sorted_list;
}

int count_length_painted_lines(Point* list, int size) {
    int res = 0;
    int lines = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].is_begin) {
            lines++;
        } else {
            lines--;
        }
        if (lines > 0) {
            res += list[i + 1].coordinate - list[i].coordinate;
        }
    }
    return res;
}
