// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T m[size];
    int top_i;

public:
    TStack() : top_i(-1) {}

    void push(T value) {
        if (top_i < size - 1) {
            m[++top_i] = value;
        }
    }

    T pop() {
        if (top_i >= 0) {
            return m[top_i--];
        }
        return T();
    }

    T top() const {
        if (top_i >= 0) {
            return m[top_i];
        }
        return T();
    }

    bool isEmpty() const {
        return top_i == -1;
    }

    bool isFull() const {
        return top_i == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
