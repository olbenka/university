#include "huffman.h"
#include "IndexedArray.h"

Huffman::Huffman() :
        root(nullptr) {
}

Huffman::~Huffman() {
    destroy(root);
}

std::string Huffman::load(const std::string &text) {
    destroy(root);
    //массив, в который записываются частоты появления символов в тексе
    IndexedArray<std::numeric_limits<char>::min(), std::numeric_limits<char>::max(), int> cnt(0);
    for (int i = 0; i < text.size(); ++i) {
        ++cnt[text[i]];
    }

    loadFreq(cnt); //строим дерево
    if (root->left_ == nullptr && root->right_ == nullptr) {
        bySymbCode[root->symb_] = "0";
    } else {
        encode(root);
    }
    std::string res;
    for (int i = 0; i < text.size(); ++i) {
        res += bySymbCode[text[i]];
    }

    return res;
}

std::string Huffman::decode(const std::string &zip) {
    //проверяем лист
    if (root->left_ == nullptr && root->right_ == nullptr) {
        return std::string(root->freq_, root->symb_);
    }
    std::string res;
    Node *now = root;
    for (int i = 0; i < zip.size(); ++i) {
        if (zip[i] == '0') {
            now = now->left_;
        } else {
            now = now->right_;
        }
        if (now->left_ == nullptr && now->right_ == nullptr) {
            res += now->symb_;
            now = root;
        }
    }

    return res;
}

Huffman::Node::Node(char symb, int freq, Huffman::Node *left_, Huffman::Node *right_) :
        symb_(symb),
        freq_(freq),
        left_(left_),
        right_(right_) {
}

void Huffman::destroy(Node *node) {
    if (node != nullptr) {
        destroy(node->left_);
        destroy(node->right_);
        delete node;
    }
}

void Huffman::encode(Huffman::Node *node, const std::string &code) {
    if (node != nullptr) {
        //проверяем лист
        if (node->left_ == nullptr && node->right_ == nullptr) {
            bySymbCode[node->symb_] = code;
        } else {
            encode(node->left_, code + '0');
            encode(node->right_, code + '1');
        }
    }
}
