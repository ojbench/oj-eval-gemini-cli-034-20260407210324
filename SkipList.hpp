#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <random>

template<typename T>
class SkipList {
private:
    struct Node {
        T* value;
        Node** forward;
        Node(const T& val, int level) : value(new T(val)) {
            forward = new Node*[level];
            for(int i = 0; i < level; ++i) forward[i] = nullptr;
        }
        Node(int level) : value(nullptr) {
            forward = new Node*[level];
            for(int i = 0; i < level; ++i) forward[i] = nullptr;
        }
        ~Node() {
            if (value) delete value;
            delete[] forward;
        }
    };

    Node* head;
    int maxLevel;
    int currentLevel;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

    int randomLevel() {
        int lvl = 1;
        while (dist(rng) && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList() : maxLevel(32), currentLevel(1), rng(1337), dist(0, 1) {
        head = new Node(maxLevel);
    }

    ~SkipList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(const T & item) {
        Node* update[32];
        for(int i=0; i<32; ++i) update[i] = nullptr;
        Node* current = head;

        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr && *(current->forward[i]->value) < item) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && !(*(current->value) < item) && !(item < *(current->value))) {
            return;
        }

        int lvl = randomLevel();

        if (lvl > currentLevel) {
            for (int i = currentLevel; i < lvl; i++) {
                update[i] = head;
            }
            currentLevel = lvl;
        }

        Node* newNode = new Node(item, lvl);
        for (int i = 0; i < lvl; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool search(const T & item) {
        Node* current = head;
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr && *(current->forward[i]->value) < item) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        if (current != nullptr && !(*(current->value) < item) && !(item < *(current->value))) {
            return true;
        }
        return false;
    }

    void deleteItem(const T & item) {
        Node* update[32];
        for(int i=0; i<32; ++i) update[i] = nullptr;
        Node* current = head;

        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr && *(current->forward[i]->value) < item) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && !(*(current->value) < item) && !(item < *(current->value))) {
            for (int i = 0; i < currentLevel; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;

            while (currentLevel > 1 && head->forward[currentLevel - 1] == nullptr) {
                currentLevel--;
            }
        }
    }
};

#endif
