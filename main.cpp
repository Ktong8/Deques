#include "list_deque.h"
#include <iostream>

int main() {
    deques::ListDeque<int> q;
    q.push_front(2);
    q.push_back(3);
    q.push_back(10);
    std::cout << q.front() << ", " << q[1] << ", " << q.back() << "\n";
    return 0;
}
