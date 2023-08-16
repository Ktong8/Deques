#pragma once
#include<list>
#include<memory>

namespace deques {
    template <typename T>
    class ListDeque {
    public:
        ListDeque() : head_{nullptr}, tail_{nullptr} {}
        ~ListDeque() = default;

        void push_front(T);
        void push_back(T);

        T& front();
        T front() const;

        T& back();
        T back() const;

        T& operator[](int);
        T operator[](int) const;
    private:
        struct ListNode {
            ListNode(T val)
                : val_{val}
                , next_{nullptr}
                , prev_{nullptr} {}

            ListNode(T val, std::unique_ptr<ListNode> next)
                : val_{val}
                , next_{std::move(next)}
                , prev_{nullptr} {}

            ListNode(T val, ListNode* prev)
                : val_{val}
                , next_{nullptr}
                , prev_{prev} {}
            T val_;
            std::unique_ptr<ListNode> next_;
            ListNode* prev_;
        };
        std::unique_ptr<ListNode> head_;
        ListNode* tail_;
    };
}

template <typename T>
void deques::ListDeque<T>::push_front(T val) {
    head_ = std::make_unique<ListNode>(val, std::move(head_));
    if (tail_) {
        head_->next_->prev_ = head_.get();
    } else {
        tail_ = head_.get();
    }
}

template <typename T>
void deques::ListDeque<T>::push_back(T val) {
    if (!tail_) {
        push_front(val);
        return;
    }
    tail_->next_ = std::make_unique<ListNode>(val, tail_);
    tail_ = tail_->next_.get();
}

template <typename T>
T& deques::ListDeque<T>::front() {
    return head_->val_;
}

template <typename T>
T deques::ListDeque<T>::front() const {
    return head_->val_;
}

template <typename T>
T& deques::ListDeque<T>::back() {
    return tail_->val_;
}

template <typename T>
T deques::ListDeque<T>::back() const {
    return tail_->val_;
}

template <typename T>
T& deques::ListDeque<T>::operator[](int i) {
    if (i < 0) {
        throw std::invalid_argument("index out of range");
    }
    ListNode* cur = head_.get();
    while (i && cur->next_) {
        cur = cur->next_.get();
        i--;
    }
    if (i) {
        throw std::invalid_argument("index out of range");
    }
    return cur->val_;
}

template <typename T>
T deques::ListDeque<T>::operator[](int i) const {
    if (i < 0) {
        throw std::invalid_argument("index out of range");
    }
    ListNode* cur = head_.get();
    while (i && cur->next_.get()) {
        cur = cur->next_.get();
        i--;
    }
    if (i) {
        throw std::invalid_argument("index out of range");
    }
    return cur->val_;
}
