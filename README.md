# Deques
A couple of deque implementations (linked list, circular array, array of arrays) benchmarked alongside the standard deque data structure. Results shown below
```
List Deque took 10872 microseconds to run
Circular Deque took 660 microseconds to run
Array Deque took 1373 microseconds to run
Standard Deque took 587 microseconds to run
```
Further optimizations are planned for these data structures, including the use of `std::copy` for the array of arrays deque and potentially block bitmaps. 
