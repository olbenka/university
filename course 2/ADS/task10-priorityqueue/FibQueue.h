//реализация приоритетной очереди с помощью фибоначчиевой пирамиды

struct Node {
    int key_;
    Node* parent_;
    Node* child_;
    Node* left_;
    Node* right_;
    int degree_;
    bool mark_;

    Node(int X) : key_(X), parent_(nullptr), child_(nullptr), left_(this), 
        right_(this), degree_(0), mark_(false) {}
};

class FibonacciHeap {
    Node* min_;
    int size_;

    static void Link(Node* y, Node* x) {
        y->left_->right_ = y->right_;
        y->right_->left_ = y->left_;
        y->parent_ = x;
	    ++x->degree_;
	    y->mark_ = false;
        if (x->child_ == nullptr) {
            x->child_ = y;
            y->left_ = y;
            y->right_ = y;
        } else {
            y->right_ = x->child_->right_;
            y->left_ = x->child_;
            x->child_->right_->left_ = y;
            x->child_->right_ = y;
        }
    }

    void Consolidate() {
        //int maxDegree = log2(size_) + 1;
        int maxDegree = 64;
        Node** degrees = new Node * [maxDegree];
        for (int i = 0; i < maxDegree; ++i) {
		    degrees[i] = nullptr;
	    }
        Node* first = min_;
        Node* x = min_;
        while (true) {
            int deg = x->degree_;
            if (degrees[deg] != nullptr) {
				Node* y = degrees[deg];
				if (y == x) {
					break;
				}
				if (x == first) {
					break;
				}
				if (x->key_ > y->key_) {
					Node* tmp = x;
					x = y;
					y = tmp;
				}
				Link(y, x);
				degrees[deg] = nullptr;
				++deg;
				continue;
            } 
			degrees[deg] = x;
			++deg;
			
			x = x->right_;
        } 

	    min_ = nullptr;
	    for (int i = 0; i < maxDegree; ++i) {
		    if (degrees[i] != nullptr) {
			    if (min_ == nullptr || degrees[i]->key_ < min_->key_) {
				    min_ = degrees[i];
			    }
		    }
	    }
        delete[] degrees;
    }

    static void Union(Node* a, Node* b) {
        if (a != nullptr && b != nullptr) {
            a->left_->right_ = b->right_;
		    b->right_->left_ = a->left_;
		    b->right_ = a;
		    a->left_ = b;
        }
    }

    void Cut(Node* x, Node* y) {
        x->left_->right_ = x->right_;
        x->right_->left_ = x->left_;
        y->degree_--;

        if (y->child_ == x) {
            y->child_ = x->right_;
        }

        if (y->degree_ == 0) {
            y->child_ = nullptr;
        }

        if (min_ != nullptr) {
            x->left_ = min_;
            x->right_ = min_->right_;
            min_->right_->left_ = x;
            min_->right_ = x;
        }

        x->parent_ = nullptr;
        x->mark_ = false;
    }

    void CascadingCut(Node* y) {
        Node* z = y->parent_;
        if (z != nullptr) {
            if (!y->mark_) {
                y->mark_ = true;
            } else {
                Cut(y, z);
                CascadingCut(z);
            }
        }
    }

public:
    FibonacciHeap() : min_(nullptr), size_(0) {}

    int getMin() const {
        return min_->key_;
    }

    int getSize() const {
        return size_;
    }

    Node* Insert(int X) {
        Node* res = new Node(X);
        if (min_ == nullptr) {
            min_ = res;
        } else {
            Node* tmp = min_->right_;
            min_->right_ = res;
            res->left_ = min_;
            res->right_= tmp;
            tmp->left_ = res;
            if (res->key_ < min_->key_) {
                min_ = res;
            }
        }
        ++size_;
        return res;
    }

    int ExtractMin() {
        if (min_ == nullptr) {
            return 2147483647;
        }
        Node* z = min_;
		int key = z->key_;
        if (min_->child_ != nullptr) {
            Union(min_->right_, min_->child_);
            min_->child_->parent_ = nullptr; 
        }
        min_->left_->right_ = min_->right_;
        min_->right_->left_ = min_->left_;
        if (min_ == min_->right_) {
            min_ = min_->child_;
            if (min_ != nullptr) {
                min_->parent_ = nullptr;
            }
        } else {
            min_ = min_->right_;
        }
        --size_;
        if (min_ != nullptr) {
            Consolidate();
        }
		
        delete z;
        return key;
    }

    void decreaseKey(Node* x, int k) {
        x->key_ = k;
        Node* y = x->parent_;
        if (y != nullptr && x->key_ < y->key_) {
            Cut(x, y);
            CascadingCut(y);
        }
        if (min_ == nullptr || x->key_ < min_->key_ ) {
            min_ = x;
        }
    }
};

