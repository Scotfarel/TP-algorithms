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

int last_alive(int N, int k) {
    if (k == 1) {
        return N;
    }

    bool people[N];
    for (int i = 0; i < N; i++) {
        people[i] = true;
    }

    int alive = N;  // Number of alive people. At start = N.
    int index = 0;  // Iterator for people array.
    int step = 0;   // Step number, step = 1..k. Increasing only when iteration over alive people.

    while (alive) {
        if (people[index % N]) {
            if (!(step % k) && step) {
                people[index % N] = false;
                alive--;
            }
            step++;
        }
        index++;
        if (!alive) return index % N - 1;
    }
}

int main() {
    int N = 0;
    int k = 0;
    std::cin >> N >> k;
    std::cout << last_alive(N, k) << std::endl;
    return 0;
}
