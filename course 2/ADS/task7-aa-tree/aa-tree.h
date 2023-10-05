//Реализация АА-дерева
class AATree {
    struct Node {
        Node* left_;
        Node* right_;
        int level_;
        int data_;
        Node() :left_(nullptr), right_(nullptr), level_(0), data_(0) {}
        Node(const int& X) : left_(nullptr), right_(nullptr), level_(1), data_(X){}
        ~Node() {
            delete left_;
            delete right_;
            left_ = right_ = nullptr;
        }
    };

    Node* root_;
    static Node* skew(Node* X);
    static Node* split(Node* X);
    Node* insert(const int& X, Node* root);
    static Node* decreaseLevel(Node* root);
    static Node* sucessor(Node* root);
    static Node* predecessor(Node* root);
    Node* erase(const int& X, Node* root);
    bool find(const int& X, Node* root);
public:
    AATree() : root_(nullptr) {}
    ~AATree() {
        delete root_;
        root_ = nullptr;
    }

    void add(const int& X) {
        root_ = insert(X, root_);
    }

    void remove(const int& X) {
        root_ = erase(X, root_);
    }

    int getLevel() const {
        return root_->level_;
    }

    bool Root() const {
        return (root_ == nullptr);
    }

    bool isInTree(const int& X) {
        return find(X, root_);
    }
};

AATree::Node* AATree::skew(Node* X) {
    if (X == nullptr) {
        return nullptr;
    } 
    if (X->left_ == nullptr){
        return X;
    } 
    if (X->left_->level_ == X->level_) {
        Node* L = X->left_;
        X->left_ = L->right_;
        L->right_ = X;
        return L;
    } 
    return X;
}

AATree::Node* AATree::split(Node* X) {
    if (X == nullptr) {
        return nullptr;
    } 
    if (X->right_ == nullptr || X->right_->right_ == nullptr) {
        return X;
    } 
    if (X->level_ == X->right_->right_->level_) {
        Node* R = X->right_;
        X->right_ = R->left_;
        R->left_ = X;
        R->level_ += 1;
        return R;
    } 
    return X;
}

AATree::Node* AATree::insert(const int &X, Node* root) {
    if (root == nullptr) {
        Node* newroot = new Node(X);
        return newroot;
    } 
    if (X < root->data_) {
        root->left_ = insert(X, root->left_);
    } else if (X > root->data_) {
        root->right_ = insert(X, root->right_);
    } else {
        root->data_ = X;
    }
    root = skew(root);
    root = split(root); 
    return root;
}

AATree::Node* AATree::decreaseLevel(Node* root) {
    int minimum = 0;
    if (root->left_ == nullptr || root->right_ == nullptr) {
        minimum = 1;
    } else {
        minimum = root->left_->level_ < root->right_->level_ ? root->left_->level_ : root->right_->level_;
        minimum += 1;
    }
    if (minimum < root->level_) {
        root->level_ = minimum;
        if (root->right_ != nullptr && minimum < root->right_->level_) {
            root->right_->level_ = minimum;
        }
    }
    return root;
}

AATree::Node* AATree::sucessor(Node* root) {
    root = root->right_;
    while (root->left_ != nullptr) {
        root = root->left_;
    }
    return root;
}

AATree::Node* AATree::predecessor(Node* root) {
    root = root->left_;
    while (root->right_ != nullptr) {
        root = root->right_;
    }
    return root;
}

AATree::Node* AATree::erase(const int &X, Node* root) {
    if (root == nullptr) {
        return root;
    }
    if (X < root->data_) {
        root->left_ = erase(X, root->left_);
    } else if (X > root->data_) {
        root->right_ = erase(X, root->right_);
    } else {
        if (root->left_ == nullptr && root->right_ == nullptr) {
            delete root;
            return nullptr;
        }
        if (root->left_ == nullptr) {
            Node* tmp = sucessor(root);
            int dataTmp = tmp->data_;
            root->right_ = erase(tmp->data_, root->right_);
            root->data_ = dataTmp;
        } else {
            Node* tmp = predecessor(root);
            int dataTmp = tmp->data_;
            root->left_ = erase(tmp->data_, root->left_);
            root->data_ = dataTmp;
        }
    }
    root = decreaseLevel(root);
    root = skew(root);
    root->right_ = skew(root->right_);
    if (root->right_ != nullptr) {
        root->right_->right_ = skew(root->right_->right_);
    }
    root = split(root);
    root->right_ = split(root->right_);
    return root;
}

bool AATree::find(const int& X, Node* root) {
    if (root == nullptr) {
        return false;
    }
    if (X > root->data_) {
        return find(X, root->right_);
    } 
    if (X < root->data_) {
        return find(X, root->left_);
    }
    return true;
}