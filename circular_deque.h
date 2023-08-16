#pragma once
#include <vector>
#include <iostream>
#include <cassert>

namespace deques {
    template <typename T>
    class CircularDeque {
    public:
        CircularDeque() : start_{3}, end_{0}, size_{0}, container_(4) {}
        ~CircularDeque() = default;
        
        void push_front(T) noexcept;
        void push_back(T) noexcept;
        void pop_front();
        void pop_back();

        T& front();
        T front() const;

        T& back();
        T back() const;

        T& operator[](int);
        T operator[](int) const;
    private:
        int start_;
        int end_;
        int size_;
        std::vector<T> container_;

        void expand_container();

        void shrink_container();
    };
}

template <typename T>
void deques::CircularDeque<T>::expand_container() {
    assert(size_ == container_.size());
    container_.resize(size_ * 2);
    if (start_ != size_-1) {
        std::copy(
            container_.begin() + start_ + 1,
            container_.begin() + size_,
            container_.begin() + size_ + start_ + 1
        );
        start_ += size_;
    } else {
        start_ = container_.size() - 1;
    }
}

template <typename T>
void deques::CircularDeque<T>::shrink_container() {
    assert(size_ <= container_.size() / 4);
    if (start_ < end_ || !end_) {
        std::copy(
            container_.begin() + start_ + 1,
            container_.begin() + end_,
            container_.begin()
        );
    } else {
        std::copy(
            container_.begin(),
            container_.begin() + end_,
            container_.begin() + size_ - end_
        );
        std::copy(
            container_.begin() + start_ + 1,
            container_.end(),
            container_.begin()
        );
    }
    container_.resize(container_.size() / 2);
    start_ = container_.size() - 1;
    end_ = size_;
}

template <typename T>
void deques::CircularDeque<T>::push_front(T val) noexcept {
    if (size_ == container_.size()) {
        expand_container();
    }
    container_[start_--] = val;
    if (start_ < 0) {
        start_ += container_.size();
    }
    size_++;
}

template <typename T>
void deques::CircularDeque<T>::push_back(T val) noexcept {
    if (size_ == container_.size()) {
        expand_container();
    }
    container_[end_++] = val;
    if (end_ == container_.size()) {
        end_ = 0;
    }
    size_++;
}

template <typename T>
void deques::CircularDeque<T>::pop_front() {
    start_++;
    if (start_ == container_.size()) {
        start_ = 0;
    }
    size_--;
}

template <typename T>
void deques::CircularDeque<T>::pop_back() {
    end_--;
    if (end_ == -1) {
        end_ = container_.size() - 1;
    }
    size_--;
}

template <typename T>
T& deques::CircularDeque<T>::front() {
    return start_ == container_.size() - 1 ? container_.front() : container_[start_ + 1];
}

template <typename T>
T deques::CircularDeque<T>::front() const {
    return start_ == container_.size() - 1 ? container_.front() : container_[start_ + 1];
}

template <typename T>
T& deques::CircularDeque<T>::back() {
    return end_ == 0 ? container_.back() : container_[end_ - 1];
}

template <typename T>
T deques::CircularDeque<T>::back() const {
    return end_ == 0 ? container_.back() : container_[end_ - 1];
}

template <typename T>
T& deques::CircularDeque<T>::operator[](int i) {
    if (i < 0 || i >= size_) {
        throw std::invalid_argument("index out of bounds");
    }
    return container_[(start_ + 1 + i) % container_.size()];
}

template <typename T>
T deques::CircularDeque<T>::operator[](int i) const {
    if (i < 0 || i >= size_) {
        throw std::invalid_argument("index out of bouns");
    }
    return container_[(start_ + 1 + i) % container_.size()];
}
