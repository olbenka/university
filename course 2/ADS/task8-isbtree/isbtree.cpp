#include <fstream>
#include <iostream>

struct Node {
    unsigned int number_;
    bool isLeaf_;
    int countKeys_;
    int countChildren_;
    int* keys_;
    unsigned int* children_;
    bool ok_;

    Node() : number_(0), isLeaf_(true), countKeys_(0), countChildren_(0), keys_(nullptr), children_(nullptr), ok_(true) {}
    ~Node() {
        delete[] keys_;
        delete[] children_;
    }
};

int strToInt(const char str[], int &idx, char symbol) {
    int res = 0;
    bool minus = false;
    if (str[idx] == '-') {
        ++idx;
        minus = true;
    }
    res = (str[idx] - '0');
    ++idx;
    while (str[idx] != symbol) {
        res *= 10;
        res += (str[idx] - '0');
        ++idx;
    } 
    if (minus) {
        res *= -1;
    }
    return res;
}

unsigned int strToUInt(const char str[], int &idx, char symbol) {
    unsigned int res = 0;
    res = (str[idx] - '0');
    ++idx;
    while (str[idx] != symbol) {
        res *= 10;
        res += (str[idx] - '0');
        ++idx;
    } 
    return res;
}

int find(Node* nodes, unsigned int ch, unsigned int N) {
    for (int i = 0; i < N; ++i) {
        if (nodes[i].number_ == ch) {
            return i;
        }
    }
    return -1;
}


bool check(Node* nodes, unsigned int N, int left, int right, int idx) {
    if (idx == -1 || !nodes[idx].ok_) {
        return false;
    }
    nodes[idx].ok_ = false;
    if (nodes[idx].keys_[0] < left || nodes[idx].keys_[nodes[idx].countKeys_ - 1] > right) {
		return false;
	}
    if (!nodes[idx].isLeaf_) {
		for (int i = 0; i < nodes[idx].countChildren_; ++i) {
            if (!check(nodes, N, i == 0 ? left : nodes[idx].keys_[i - 1], i == (nodes[idx].countChildren_ - 1) ? right : nodes[idx].keys_[i], find(nodes, nodes[idx].children_[i], N))) {
                return false;
            }
		}
	}
    return true;
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        return 1;
    }

    unsigned int N = 0;
    unsigned int t = 0;
    unsigned int root = 0;
    fin >> N >> t >> root;
    Node* nodes = new Node[N];
    char str[1024];
    int idx = 0;
    fin.getline(str, 1024, '\n');
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 1024; ++j) {
            str[j] = '\0';
        }
        fin.getline(str, 1024, '\n'); 
        if (str[0] == 'b') {
            nodes[i].isLeaf_ = false;
            idx = 10;
        } else {
            nodes[i].isLeaf_ = true;
            idx = 8;
        }
        nodes[i].number_ = strToUInt(str, idx, ' ');
        idx += 2;
        nodes[i].countKeys_ = strToInt(str, idx, ':'); 
        if (root == nodes[i].number_) {
            if (!(nodes[i].countKeys_ >= 1 && nodes[i].countKeys_ <= (2 * t - 1))) {
                std::cout << "no";
                delete[] nodes;
                fin.close();
                return 0;
            }
        } else {
            if (!(nodes[i].countKeys_ >= (t - 1) && nodes[i].countKeys_ <= (2 * t - 1))) {
                std::cout << "no";
                delete[] nodes;
                fin.close();
                return 0;
            }
        }
        idx += 2;
        nodes[i].keys_ = new int[nodes[i].countKeys_];
        for (int j = 0; j < nodes[i].countKeys_ - 1; ++j) {
            nodes[i].keys_[j] = strToInt(str, idx, ' ');
            ++idx;
        }
        nodes[i].keys_[nodes[i].countKeys_ - 1] = strToInt(str, idx, ')');
        for (int j = 1; j < nodes[i].countKeys_; ++j) {
            if (nodes[i].keys_[j - 1] > nodes[i].keys_[j]) {
                std::cout << "no";
                delete[] nodes;
                fin.close();
                return 0;
            }
        }
        if (!nodes[i].isLeaf_) { 
            idx += 3;
            nodes[i].countChildren_ = strToInt(str, idx, ':'); 
            idx += 2;
            if (nodes[i].countChildren_ != nodes[i].countKeys_ + 1) {
                std::cout << "no";
                delete[] nodes;
                fin.close();
                return 0;
            }
            nodes[i].children_ = new unsigned int[nodes[i].countChildren_];
            for (int j = 0; j < nodes[i].countChildren_ - 1; ++j) {
                nodes[i].children_[j] = strToUInt(str, idx, ' ');
                ++idx;
            }
            nodes[i].children_[nodes[i].countChildren_ - 1] = strToUInt(str, idx, ')');
        } else {
            if (str[idx + 2] == '(') {
                std::cout << "no";
                delete[] nodes;
                fin.close();
                return 0;
            }
        }
    }

    if (check(nodes, N, -2147483647, 2147483647, 0)) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }

    delete[] nodes;

    fin.close();
    return 0;
}
