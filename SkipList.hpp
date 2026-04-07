#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

template<typename T>
class SkipList {
private:
    struct Node {
        T value;
        std::vector<Node*> forward;
        Node(const T& val, int level) : value(val), forward(level, nullptr) {}
    };

    Node* head;
    int maxLevel;
    int currentLevel;
    float probability;

    int randomLevel() {
        int lvl = 1;
        while ((static_cast<float>(std::rand()) / RAND_MAX) < probability && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList() : maxLevel(32), currentLevel(1), probability(0.5) {
        // We need a dummy head node. Since T might not have a default constructor,
        // we can use a pointer or allocate raw memory, or just use a dummy value if possible.
        // Wait, the problem says "T除了支持 < 操作符以外，你不能对它的性质有任何期望。"
        // This means T might not have a default constructor, copy constructor might be available.
        // So we cannot do `Node(T(), maxLevel)`.
        // We can use a pointer for the value, or use std::optional if C++17 is available.
        // Let's use a pointer for the value in the Node, or just allocate memory.
    }

    ~SkipList() {
    }

    void insert(const T & item) {
    }

    bool search(const T & item) {
        return false;
    }

    void deleteItem(const T & item) {
    }
};

#endif
