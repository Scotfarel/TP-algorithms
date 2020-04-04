//
//  Created by izakharov on 05/04/20
//
//  Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
//  Формат входных данных.
//  В первой строке количество команд n. n ≤ 1000000.
//  Каждая команда задаётся как 2 целых числа: a b.
//  a = 1 - push front
//  a = 2 - pop front
//  a = 3 - push back
//  a = 4 - pop back
//  Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
//  Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
//  Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных,
//  то ожидается “-1”.
//  Формат выходных данных.
//  Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось,
//  то напечатать NO.
//
//  3_1. Реализовать очередь с динамическим зацикленным буфером.
//  Требования: Очередь должна быть реализована в виде класса.
//

#include <iostream>


constexpr int POP_FRONT = 2;
constexpr int PUSH_BACK = 3;

int run(const int* commands, int* elements, int size);

template<class T>
class DynamicArray;

template<class T>
class Queue;

int main() {
    int n = 0;
    std::cin >> n;
    int* commands = new int[n];
    int* elements = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> commands[i] >> elements[i];
    }

    run(commands, elements, n);

    delete[] commands;
    delete[] elements;
    return 0;
}

template<class T>
class DynamicArray {
public:
    DynamicArray();
    ~DynamicArray() {delete[] arr;};

    T &operator[](int index);
    DynamicArray &operator= (const DynamicArray &other);

    void append(T element);
    void remove(int index);

    int get_size() { return size; };

private:
    T* arr;
    int size;
    int capacity;
    int initial_capacity = 4;

    void grow();
};


template<class T>
void DynamicArray<T>::append(T element) {
    if (size == capacity) {
        grow();
    }
    arr[size] = element;
    size++;
}

template<class T>
void DynamicArray<T>::grow() {
    int new_capacity = std::max(capacity * 2, initial_capacity);
    T* new_arr = new T[new_capacity];
    std::copy(arr, arr + size, new_arr);

    delete[] arr;

    arr = new_arr;
    capacity = new_capacity;
}

template<class T>
void DynamicArray<T>::remove(int index) {
    std::copy(arr + index + 1, arr + size, arr + index);
    size--;
}

template<class T>
DynamicArray<T>::DynamicArray() {
    arr = nullptr;
    size = 0;
    capacity = 0;
    append(0);
    remove(get_size() - 1);
}

template<class T>
T &DynamicArray<T>::operator[](int index) {
    if (size <= index) {
        size++;
    }
    if (size == capacity) {
        grow();
    }
    return arr[index];
}

template<class T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &other) {
    if (this == &other) {
        return *this;
    }
    size = other.size;
    capacity = other.capacity;
    arr = new T[size];
    std::copy(other.arr, other.arr + size, arr);
    return *this;
}


template <class T>
class Queue{
public:
    Queue() : size(4), head(0), tail(0) {};
    ~Queue() = default;

    T pop_front();
    void push_back(T element);

    bool is_empty() const { return head == tail;};

private:
    DynamicArray<T> buffer;
    int size;
    int head;
    int tail;

    void grow();
};

template<class T>
void Queue<T>::grow() {
    int new_size = size * 2;
    auto* new_buffer = new DynamicArray<T>;
    *new_buffer = buffer;
    for (int i = 0; head != tail; i++) {
        buffer[i] = (*new_buffer)[head];
        head = (head + 1) % size;
    }
    delete new_buffer;

    head = 0;
    tail = size - 1;
    size = new_size;
}

template<class T>
T Queue<T>::pop_front() {
    T element = buffer[head];
    head = (head + 1) % size;
    return element;
}

template<class T>
void Queue<T>::push_back(T element) {
    if ((tail + 1) % size == head) {
        grow();
    }
    buffer[tail] = element;
    tail = (tail + 1) % size;
}


int run(const int* commands, int* elements, int size) {
    Queue<int> queue;
    int q_value = -1;
    bool result = true;
    for (int i = 0; i < size; i++) {
        switch (commands[i]) {
            case POP_FRONT:
                if (queue.is_empty()) {
                    result = (result && elements[i] == q_value);
                } else {
                    result = (elements[i] == queue.pop_front());
                }
                break;
            case PUSH_BACK:
                queue.push_back(elements[i]);
                break;
        }
    }
    if (result) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
