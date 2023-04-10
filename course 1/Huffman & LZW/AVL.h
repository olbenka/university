#pragma once

template <typename Element>
class AVLTree {
    struct Node {
        Node* left_;
        Node* right_;
        Node* parent_;
        Element data_;
        signed char balance_;
        Node(const Element& X) : right_(nullptr), left_(nullptr), parent_(nullptr), data_(X), balance_(0) {}
        ~Node() {
            if (left_) 
                delete left_;
            if (right_) 
                delete right_;
            left_ = right_ = parent_ = nullptr;
        }
        Node* minimum() {
            Node* now = this;
            while (now->left_)
                now = now->left_;
            return now;
        }
        Node* maximum() {
            Node* now = this;
            while (now->right_) 
                now = now->right_;
            return now;
        }
        Node* next() {
            if (right_) 
                return right_->minimum();
            Node* p = parent_;
            Node* now = this;
            while (p) {
                if (now == p->left_) 
                    break;
                now = p;
                p = p->parent_;
            }
            return p;
        }
        Node* prev() {
            if (left_) return left_->maximum();
            Node* p = parent_;
            Node* now = this;
            while (p) {
                if (now == p->right_) 
                    break;
                now = p;
                p = p->parent_;
            }
            return p;
        }
        int level()const {
            int L = (left_) ? left_->level() : 0;
            int R = (right_) ? right_->level() : 0;
            return L > R ? L + 1 : R + 1;
        }
    };

    Node* root;
    unsigned int count;
    Node* _RightRotate(Node*);
    Node* _LeftRotate(Node*);
    Node* _DoubleRightRotate(Node*);
    Node* _DoubleLeftRotate(Node*);

public:
    AVLTree() : root(nullptr), count(0) {}
    ~AVLTree() {
        if (root)
            delete root;
        root = nullptr;
    }
    unsigned int size()const { 
        return count; 
    }
    int height()const {
        return (root) ? root->level() : 0;
    }
    void insert(const Element& X) {
        ++count;
        if (root == nullptr) {
            root = new Node(X);
            return;
        }
        Node* now, * p;
        bool toLeft;
        now = root;
        do {
            p = now;
            if (X < now->data_) {
                now = now->left_; toLeft = true;
            } else {
                now = now->right_; toLeft = false;
            }
        } while (now);
        now = new Node(X);
        if (toLeft)
            p->left_ = now; 
        else
            p->right_ = now;
        now->parent_ = p;
        do {
            if (now->parent_->left_ == now)
                now->parent_->balance_ -= 1;
            else 
                now->parent_->balance_ += 1;
            now = now->parent_;
            switch (now->balance_) {
            case 2:
                if (now->right_->balance_ == -1)
                    now = _DoubleLeftRotate(now);
                else 
                    now = _LeftRotate(now);
                break;
            case -2:
                if (now->left_->balance_ == 1)
                    now = _DoubleRightRotate(now);
                else
                    now = _RightRotate(now);
                break;
            }
        } while (now != root && now->balance_ != 0);

    }
    class iterator {
        Node* now;
    public:
        iterator(Node* p = nullptr) : now(p) {}
        const Element& operator*()const { 
            return now->data_; 
        }
        bool operator==(const iterator& p)const {
            return now == p.now; 
        }
        bool operator!=(const iterator& p)const { 
            return now != p.now; 
        }
        iterator& operator++() { 
            if (now) 
                now = now->next();
            return *this; 
        }
        iterator operator++(int) {
            Node* tmp = now;
            if (now) 
                now = now->next();
            return iterator(tmp);
        }
        friend class AVLTree;
    };
    iterator begin()const {
        if (root) 
            return iterator(root->minimum());
        return end();
    }
    iterator end()const {
        return iterator(nullptr);
    }
    class reverse_iterator {
        Node* now;
    public:
        reverse_iterator(Node* p = nullptr) : now(p) {}
        const Element& operator*()const { 
            return now->data_;
        }
        bool operator==(const reverse_iterator& p)const {
            return now == p.now; 
        }
        bool operator!=(const reverse_iterator& p)const { 
            return now != p.now;
        }
        reverse_iterator& operator++() {
            if (now) now = now->prev();
            return *this;
        }
        reverse_iterator operator++(int) {
            Node* tmp = now;
            if (now) 
                now = now->prev();
            return reverse_iterator(tmp);
        }
    };
    reverse_iterator rbegin()const {
        if (root) 
            return reverse_iterator(root->maximum());
        return rend();
    }
    reverse_iterator rend()const {
        return reverse_iterator(nullptr); 
    }
    iterator find(const Element& X)const {
        Node* now = root;
        while (now) {
            if (X == now->data_) 
                break;
            if (X < now->data_) 
                now = now->left_;
            else 
                now = now->right_;
        }
        return iterator(now);
    }
    void erase(iterator); 
};

template <typename Element>
void AVLTree<Element>::erase(typename AVLTree<Element>::iterator pos) {
    Node* toDelete = pos.now;
    if (toDelete == nullptr) 
        return;
    Node* Alt;
    if (toDelete->right_ == nullptr)
        Alt = toDelete->left_;
    else if (toDelete->left_ == nullptr)
        Alt = toDelete->right_;
    else {
        Alt = toDelete->right_->minimum();
        if (Alt->parent_ != toDelete) {
            Alt->parent_->left_ = Alt->right_;
            if (Alt->right_) 
                Alt->right_->parent_ = Alt->parent_;
            Alt->right_ = toDelete->right_;
            toDelete->right_->parent_ = Alt;
        }
        Alt->left_ = toDelete->left_;
        toDelete->left_->parent_ = Alt;
    }

    Node* notBalanced;
    if (Alt == nullptr) {
        notBalanced = toDelete->parent_;
        if (notBalanced) {
            if (notBalanced->left_ == toDelete) 
                notBalanced->balance_ += 1;
            else 
                notBalanced->balance_ -= 1;
        }
    }else {
        Alt->balance_ = toDelete->balance_;
        if (Alt->parent_ == toDelete) {
            notBalanced = Alt;
            if (Alt == toDelete->left_) 
                notBalanced->balance_ += 1;
            else 
                notBalanced->balance_ -= 1;
        }
        else {
            notBalanced = Alt->parent_;
            notBalanced->balance_ += 1;
        }
    }


    if (toDelete->parent_ == nullptr) {
        root = Alt;
    } else {
        if (toDelete->parent_->left_ == toDelete)
            toDelete->parent_->left_ = Alt;
        else
            toDelete->parent_->right_ = Alt;
    }
    if (Alt != nullptr) {
        Alt->parent_ = toDelete->parent_;
    }

    toDelete->right_ = nullptr; 
    toDelete->left_ = nullptr;
    delete toDelete;
    --count;

    while (notBalanced) {
        switch (notBalanced->balance_) {
        case 2:
            if (notBalanced->right_->balance_ == -1)
                notBalanced = _DoubleLeftRotate(notBalanced);
            else
                notBalanced = _LeftRotate(notBalanced);
            break;
        case -2:
            if (notBalanced->left_->balance_ == 1)
                notBalanced = _DoubleRightRotate(notBalanced);
            else
                notBalanced = _RightRotate(notBalanced);
            break;
        }
        if (notBalanced->balance_ == 1 || notBalanced->balance_ == -1)
            break;
        if (notBalanced->parent_) {
            if (notBalanced->parent_->left_ == notBalanced)
                notBalanced->parent_->balance_ += 1;
            else
                notBalanced->parent_->balance_ -= 1;
        }
        notBalanced = notBalanced->parent_;
    }
}

template <typename Element>
typename AVLTree<Element>::Node*
AVLTree<Element>::_LeftRotate(typename AVLTree<Element>::Node* a) {
    if (a->balance_ != 2) 
        return a;
    Node* b = a->right_;
    if (b->balance_ == -1)
        return a;

    a->right_ = b->left_;
    if (b->left_) 
        b->left_->parent_ = a;

    b->parent_ = a->parent_;
    if (a->parent_) {
        if (a->parent_->left_ == a)
            a->parent_->left_ = b;
        else
            a->parent_->right_ = b;
    } else {
        root = b;
    }

    b->left_ = a;
    a->parent_ = b;

    if (b->balance_ == 1) {
        a->balance_ = 0; 
        b->balance_ = 0;
    } else {
        a->balance_ = 1; 
        b->balance_ = -1;
    }
    return b;
}

template <typename Element>
typename AVLTree<Element>::Node*
AVLTree<Element>::_RightRotate(typename AVLTree<Element>::Node* b) {
    if (b->balance_ != -2) 
        return b;
    Node* a = b->left_;
    if (a->balance_ == 1) 
        return b;

    b->left_ = a->right_;
    if (a->right_) 
        a->right_->parent_ = b;

    a->parent_ = b->parent_;
    if (b->parent_) {
        if (b->parent_->left_ == b)
            b->parent_->left_ = a;
        else
            b->parent_->right_ = a;
    } else {
        root = a;
    }

    a->right_ = b;
    b->parent_ = a;

    if (a->balance_ == -1) {
        a->balance_ = 0; 
        b->balance_ = 0;
    } else {
        a->balance_ = 1; 
        b->balance_ = -1;
    }

    return a;
}

template <typename Element>
typename AVLTree<Element>::Node*
AVLTree<Element>::_DoubleLeftRotate(typename AVLTree<Element>::Node* a) {
    if (a->balance_ != 2) 
        return a;
    Node* c = a->right_;
    if (c->balance_ != -1) 
        return a;
    Node* b = c->left_;

    a->right_ = b->left_; 
    if (b->left_) 
        b->left_->parent_ = a;
    c->left_ = b->right_; 
    if (b->right_) 
        b->right_->parent_ = c;

    b->parent_ = a->parent_;
    if (a->parent_) {
        if (a->parent_->left_ == a)
            a->parent_->left_ = b;
        else
            a->parent_->right_ = b;
    } else {
        root = b;
    }

    b->left_ = a;  
    a->parent_ = b;
    b->right_ = c; 
    c->parent_ = b;

    if (b->balance_ == 0) {
        a->balance_ = 0;  
        c->balance_ = 0;
    }
    else if (b->balance_ == 1) {
        a->balance_ = -1;
        c->balance_ = 0;
    } else {
        a->balance_ = 0;  
        c->balance_ = 1;
    }
    b->balance_ = 0;
    return b;
}

template <typename Element>
typename AVLTree<Element>::Node*
AVLTree<Element>::_DoubleRightRotate(typename AVLTree<Element>::Node* c) {
    if (c->balance_ != -2) 
        return c;
    Node* a = c->left_;
    if (a->balance_ != 1) 
        return c;
    Node* b = a->right_;

    a->right_ = b->left_; 
    if (b->left_) 
        b->left_->parent_ = a;
    c->left_ = b->right_; 
    if (b->right_) 
        b->right_->parent_ = c;

    b->parent_ = c->parent_;
    if (c->parent_) {
        if (c->parent_->left_ == c)
            c->parent_->left_ = b;
        else
            c->parent_->right_ = b;
    }
    else {
        root = b;
    }

    b->left_ = a;  
    a->parent_ = b;
    b->right_ = c; 
    c->parent_ = b;

    if (b->balance_ == 0) {
        a->balance_ = 0;  
        c->balance_ = 0;
    }
    else if (b->balance_ == 1) {
        a->balance_ = -1; 
        c->balance_ = 0;
    } else {
        a->balance_ = 0; 
        c->balance_ = 1;
    }
    b->balance_ = 0;

    return b;
}
