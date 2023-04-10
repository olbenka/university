#pragma once

#include <string>
#include <limits>
#include "AVL.h"
#include "IndexedArray.h"

class Huffman {
    struct Node {
        char symb_;
        int freq_;
        Node *left_;
        Node *right_;
        Node(char symb, int freq, Node *left_ = nullptr, Node *right_ = nullptr);
    };

    //массив кодов для символов
    IndexedArray<std::numeric_limits<char>::min(), std::numeric_limits<char>::max(), std::string> bySymbCode;
    Node *root;
    void destroy(Node *node);
    void encode(Node *node, const std::string& code = "");
public:
    Huffman();

    ~Huffman();

    std::string load(const std::string&);

    //дерево
    template<class T>
    void loadFreq(const T& cnt) {
        AVLTree<std::pair<int, Node*>> tree; //частота, узел
        for (int i = cnt.getFrom(); i <= cnt.getTo(); ++i) {
            if (cnt[i] != 0) {
                tree.insert(std::make_pair(cnt[i], new Node(i, cnt[i]))); //присваиваем значения полям first, second
            }
        }
        while (tree.size() > 1) {
            auto a = *tree.begin(); //begin указывает на минимальный элемент (сортируется по частоте)
            tree.erase(tree.begin());
            auto b = *tree.begin(); //берем минимум и предминимум
            tree.erase(tree.begin());
            tree.insert(std::make_pair(a.first + b.first, new Node('#', a.first + b.first,
                a.second,
                b.second)));//объединяем два символа с наименьшими частотами
        }
        root = (*tree.begin()).second;
    }

    std::string decode(const std::string&);
};
