#include <iostream>

int run(const int* commands, int* elements, int size);

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

class Queue{
public:
    Queue() : buffer(nullptr), size(1), head(0), tail(0) {};
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(const Queue&&) = delete;
    Queue& operator=(const Queue&&) = delete;
    ~Queue() {delete[] buffer; };

    int pop_front();
    void push_back(int element);

    bool is_empty() const { return head == tail;};
private:
    int* buffer;
    int size;
    int initial_size = 4;

    int head;
    int tail;

    void grow();
};

void Queue::grow() {
    int new_size = std::max(size * 2, initial_size);
    int* new_buffer = new int[new_size];

    for (int i = 0; head != tail; i++) {
        new_buffer[i] = buffer[head];
        head = (head + 1) % size;
    }

    delete[] buffer;

    head = 0;
    tail = size - 1;
    size = new_size;
    buffer = new_buffer;
}

void Queue::push_back(int element) {
    if ((tail + 1) % size == head) {
        grow();
    }
    buffer[tail] = element;
    tail = (tail + 1) % size;
}

int Queue::pop_front() {
    int element = buffer[head];
    head = (head + 1) % size;
    return element;
}

int run(const int* commands, int* elements, int size) {
    Queue queue;

    int q_value = -1;
    for (int i = 0; i < size; i++) {
        switch (commands[i]) {
            case 2:
                if (!queue.is_empty()) {
                    q_value = queue.pop_front();
                }
                if (q_value != elements[i]) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
            case 3:
                queue.push_back(elements[i]);
                break;
            default:
                std::cout << "NO" << std::endl;
                return 0;
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
