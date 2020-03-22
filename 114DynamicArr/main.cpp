//
//  Created by izakharov on 18/03/20
//
//  1_4. “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
//  Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
//  Необходимо определить номер уцелевшего.
//  N, k ≤ 10000.
//  Требования:  Решить перебором.
//

#include <iostream>
#include <cassert>


int search_last_alive(int N, int k);

int main() {
    int N = 0, k = 0;
    std::cin >> N >> k;
    assert(N > 0 && k > 0);
    std::cout << search_last_alive(N, k);
    return 0;
}

class DynamicArr {
public:
    DynamicArr() : buffer(nullptr), capacity(0), size(0) {};
    DynamicArr(const DynamicArr&) = delete;
    DynamicArr(DynamicArr&&) = delete;
    DynamicArr& operator= (const DynamicArr&) = delete;
    DynamicArr& operator= (DynamicArr&&) = delete;
    ~DynamicArr() { delete[] buffer; }

    int get_size() const { return size; }
    int get_at(int index) const;
    void append(int element);
    void remove(int index);

private:
    int *buffer;
    int capacity;
    int size;
    int initialSize = 4;

    void grow();
};


void DynamicArr::remove(int index) {
    assert(index >= 0 && index < size && buffer);
    std::copy(buffer + index + 1, buffer + size, buffer + index);
    size--;
}

int DynamicArr::get_at(int index) const {
    assert(index >= 0 && index < size && buffer);
    return buffer[index];
}

void DynamicArr::grow() {
    int newCapacity = std::max(capacity * 2, initialSize);
    int *newBuffer = new int[newCapacity];
    std::copy(buffer, buffer + size, newBuffer);
    delete[] buffer;
    buffer = newBuffer;
    capacity = newCapacity;
}

void DynamicArr::append(int element) {
    if (size == capacity) {
        grow();
    }
    assert(size < capacity && buffer);
    buffer[size++] = element;
}

int search_last_alive(int N, int k) {
    if (k == 1) {
        return N;
    }

    auto *arr = new DynamicArr;
    for(int i = 0; i < N; i++) {
        arr->append(i + 1);
    }

    int step = 0;
    while (arr->get_size() > 1) {
        for (int i = 0; i < arr->get_size(); i++) {
            step++;
            if (!(step % k)) {
                arr->remove(i);
                i--;
            }
        }
    }

    int winner = arr->get_at(0);
    delete arr;
    return winner;
}
