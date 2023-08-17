#pragma once
#include <vector>
#include <array>

namespace deques {

    constexpr unsigned int BLOCK_SIZE = 5;

    template <typename T>
    class ArrayDeque {
    public:
        ArrayDeque()
            : blocks_(0)
            , start_{0}
            , size_{0} {}
        ~ArrayDeque() = default;

        void push_front(T);
        void push_back(T);

        void pop_front();
        void pop_back();

        T& front();
        T front() const;

        T& back();
        T back() const;

        T& operator[](int);
        T operator[](int) const;
    private:
        std::vector<std::array<T, BLOCK_SIZE>> blocks_;
        int start_;
        int size_;
        void expand_blocks();
        void shrink_blocks();
    };
}

template <typename T>
void deques::ArrayDeque<T>::expand_blocks() {
    assert(size_ == BLOCK_SIZE * blocks_.size());
    int start_block = start_ / BLOCK_SIZE;
    if (start_block) {
        for (int i = 0; i < blocks_.size() - 1; ++i) {
            int idx = start_ + (i % (blocks_.size() - start_));
            if (i != idx) {
                std::swap(blocks_[i], blocks_[idx]);
            }
        }
    }
    start_ %= BLOCK_SIZE;
    if (blocks_.size()) {
        blocks_.resize(2 * blocks_.size());
    } else {
        blocks_.resize(1);
    }
    for (int i = 0; i < start_; ++i) {
        blocks_[(i + size_) / BLOCK_SIZE][(i + size_) % BLOCK_SIZE] = blocks_[0][i];
    }
}

template <typename T>
void deques::ArrayDeque<T>::push_front(T val) {
    int end_block = ((start_ + size_) % (BLOCK_SIZE * blocks_.size())) / BLOCK_SIZE;
    int start_block = (start_ / BLOCK_SIZE);
    int next_block = start_ ? ((start_ - 1) / BLOCK_SIZE) : (blocks_.size() - 1);
    if (size_ == BLOCK_SIZE * blocks_.size() || (next_block == end_block && start_block != end_block)) {
        expand_blocks();
    }
    start_--;
    if (start_ == -1) {
        start_ += BLOCK_SIZE * blocks_.size();
    }
    size_++;
    blocks_[start_ / BLOCK_SIZE][start_ % BLOCK_SIZE] = val;
}

template <typename T>
void deques::ArrayDeque<T>::push_back(T val) {
    int end_block = ((start_ + size_) % (BLOCK_SIZE * blocks_.size())) / BLOCK_SIZE;
    int start_block = (start_ / BLOCK_SIZE);
    int next_block = ((start_ + size_ + 1) % (BLOCK_SIZE * blocks_.size())) / BLOCK_SIZE;
    if (size_ == BLOCK_SIZE * blocks_.size() || (next_block == start_block && start_block != end_block)) {
        expand_blocks();
    }
    int idx = start_ + size_;
    idx %= BLOCK_SIZE * blocks_.size();
    blocks_[idx / BLOCK_SIZE][idx % BLOCK_SIZE] = val;
    size_++;
}

template <typename T>
void deques::ArrayDeque<T>::pop_front() {
    start_++;
    if (start_ == BLOCK_SIZE * blocks_.size()) {
        start_ = 0;
    }
    size_--;
}

template <typename T>
void deques::ArrayDeque<T>::pop_back() {
    size_--;
}

template <typename T>
T& deques::ArrayDeque<T>::front() {
    return blocks_[start_ / BLOCK_SIZE][start_ % BLOCK_SIZE];
}

template <typename T>
T deques::ArrayDeque<T>::front() const {
    return blocks_[start_ / BLOCK_SIZE][start_ % BLOCK_SIZE];
}

template <typename T>
T& deques::ArrayDeque<T>::back() {
    int idx = ((start_ + size_ - 1) % (BLOCK_SIZE * blocks_.size()));
    return blocks_[idx / BLOCK_SIZE][idx % BLOCK_SIZE];
}

template <typename T>
T deques::ArrayDeque<T>::back() const {
    int idx = ((start_ + size_ - 1) % (BLOCK_SIZE * blocks_.size()));
    return blocks_[idx / BLOCK_SIZE][idx % BLOCK_SIZE];
}

template <typename T>
T& deques::ArrayDeque<T>::operator[](int i) {
    int idx = ((start_ + i) % (BLOCK_SIZE * blocks_.size()));
    return blocks_[idx / BLOCK_SIZE][idx % BLOCK_SIZE];
}

template <typename T>
T deques::ArrayDeque<T>::operator[](int i) const {
    int idx = ((start_ + i) % (BLOCK_SIZE * blocks_.size()));
    return blocks_[idx / BLOCK_SIZE][idx % BLOCK_SIZE];
}
