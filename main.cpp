#include "list_deque.h"
#include "circular_deque.h"
#include <iostream>

int main() {
    deques::ListDeque<int> q;
    q.push_front(2);
    q.push_back(3);
    q.push_back(10);
    std::cout << q.front() << ", " << q[1] << ", " << q.back() << "\n";

    deques::CircularDeque<int> cq;
    cq.push_front(2);
    cq.push_back(3);
    cq.push_back(10);
    std::cout << cq.front() << ", " << cq[1] << ", " << cq.back() << "\n";
    return 0;
}
