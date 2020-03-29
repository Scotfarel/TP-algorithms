//
//  Created by izakharov on 29/03/20
//
//  Требование для всех вариантов Задачи 4
//  Решение всех задач данного раздела предполагает использование кучи, реализованной в виде класса.
//  Решение должно поддерживать передачу функции сравнения снаружи.
//  Куча должна быть динамической.
//
//  4_3. Тупики.
//  На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является их конечной станцией.
//  Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия,
//  а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
//  Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
//  При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку,
//  которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
//  В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
//  Напишите программу, которая по данному расписанию определяет,
//  какое минимальное количество тупиков требуется для работы вокзала.
//  Формат входных данных. Вначале вводится n - количество электричек в расписании.
//  Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления.
//  Время - натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
//  Формат выходных данных. Натуральное число - минимальное количеством тупиков.
//  Максимальное время: 50мс, память: 5Мб.
//


#include <iostream>
#include <cassert>

int find_deadends_num(const int* arrivals, const int* departures, int trains_num);

int main() {
    int n = 0;
    std::cin >> n;
    int* arrivals = new int[n];
    int* departures = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arrivals[i] >> departures[i];
    }

    std::cout << find_deadends_num(arrivals, departures, n);

    delete[] arrivals;
    delete[] departures;
    return 0;
}

template <class T, class Comparator = std::less<int> >
class Heap {
public:
    Heap() : list(nullptr), capacity(0), size(0), comp(Comparator()) {};
    ~Heap() {delete[] list;};


    void insert(T element) {
        append(element);
        sift_up(get_size() - 1);
    }

    int extract_min() {
        if (!get_size()) {
            return 0;
        }
        T root = list[0];
        list[0] = get_last();
        delete_last();
        if (!is_empty()) {
            sift_down(0);
        }
        return root;
    }

    int peek_min() const {
        if (!get_size()) {
            return 0;
        }
        return list[0];
    }

    int get_size() const {
        return size;
    }

    bool is_empty() const {
        return !get_size();
    }

private:
    T* list;
    int size;
    int capacity;
    int initial_size = 4;

    Comparator comp;

    void append(T element) {
        if (size == capacity) {
            grow();
        }
        assert(size < capacity && list);
        list[size++] = element;
    }

    int get_last() {
        assert(size && list);
        return list[size - 1];
    }

    void delete_last() {
        int index = get_size() - 1;
        assert(index >= 0 && list);
        size--;
    }

    void grow() {
        int newCapacity = std::max(capacity * 2, initial_size);
        T* new_list = new T[newCapacity];
        std::copy(list, list + size, new_list);
        delete[] list;
        list = new_list;
        capacity = newCapacity;
    }

    void sift_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (comp(left, get_size()) && comp(list[left], list[i])) {
            smallest = left;
        }
        if (comp(right, get_size()) && comp(list[right], list[smallest])) {
            smallest = right;
        }
        if (smallest != i) {
            std::swap(list[i], list[smallest]);
            sift_down(smallest);
        }
    }

    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (!comp(list[i], list[parent])) {
                return;
            }
            std::swap(list[i], list[parent]);
            i = parent;
        }
    }
};

int find_deadends_num(const int* arrivals, const int* departures, int trains_num) {
    int result = 0;
    auto* heap = new Heap<int>;

    for (int i = 0; i < trains_num; i++) {
        while (!heap->is_empty() && heap->peek_min() < arrivals[i]) {
            heap->extract_min();
        }
        heap->insert(departures[i]);
        if (result < heap->get_size()) {
            result = heap->get_size();
        }
    }

    delete heap;
    return result;
}
