#include "list_deque.h"
#include "circular_deque.h"
#include "array_deque.h"
#include "timer.h"
#include <iostream>
#include <deque>

template <typename T>
void simulateDeque() {
    T q;
    for (int i = 0; i < 62000; ++i) {
        if (i % 3) {
            q.push_front(i);
        } else {
            q.push_back(i);
        }
        if (!(i % 20)) {
            q.pop_front();
        } else if (!(i % 21)) {
            q.pop_back();
        }
    }
    int sum = 0;
    for (int i = 0; i < 20; ++i) {
        sum += q[i];
    }
}


template <typename T>
void testDeque() {
    T q;
    q.push_front(2);
    q.push_back(3);
    q.push_back(10);
    std::cout << q.front() << ", " << q[1] << ", " << q.back() << "\n";
    q.pop_front();
    q.pop_back();
    std::cout << q.front() << ", " << q.back() << ", " << q[0] << "\n";
}


int main() {
    timer::timeFunction(simulateDeque<deques::ListDeque<int>>, "List Deque");
    timer::timeFunction(simulateDeque<deques::CircularDeque<int>>, "Circular Deque");
    timer::timeFunction(simulateDeque<deques::ArrayDeque<int>>, "Array Deque");
    timer::timeFunction(simulateDeque<std::deque<int>>, "Standard Deque");
    return 0;
}
