//Реализация хэш-таблицы
#include <iostream>
const int MAX_SIZE = 100003;

struct Item {
    int key_;
    Item* next_ = nullptr;
};


class HashTable {
    Item** table_ = nullptr;
    void free_(Item* el) {
        if (el != nullptr && el->next_ != nullptr) {
            free_(el->next_);
        }
        delete el;
    }

public:
    HashTable();
    ~HashTable();
    void insert(int key);
    void erase(int key);
    bool search(int key);
    static int function(int K);
};

int HashTable::function(int K) {
    return std::abs(K % MAX_SIZE);
}



HashTable::HashTable() {
    table_ = new Item * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
        table_[i] = nullptr;
    }

}

HashTable::~HashTable() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        free_(table_[i]);
    }
    delete[] table_;
}

void HashTable::insert(int key) {
    int hashKey = function(key);
    Item* tmp = new Item;
    tmp->key_ = key;
    tmp->next_ = nullptr;

    if (table_[hashKey] != nullptr) {
        Item* current = table_[hashKey];
        while (current->next_ != nullptr) {
            current = current->next_;
        }
        current->next_ = tmp;
    } else {
        table_[hashKey] = tmp;
    }
}

void HashTable::erase(int key) {
    int hashKey = function(key);
    Item* current = table_[hashKey];
    Item* prev = nullptr;
    while (current != nullptr) {
        if (current->key_ == key) {
            if (prev == nullptr) {
                table_[hashKey] = current->next_;
            } else {
                prev->next_ = current->next_;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next_;
    }
}

bool HashTable::search(int key) {
    int hashKey = function(key);
    Item* current = table_[hashKey];
    while (current != nullptr) {
        if (current->key_ == key) {
            return true;
        } 
        current = current->next_;
    }
    return false;
}