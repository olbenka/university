#include <fstream>
#include "aa-tree.h"

int strToint(const char str[]) {
    int num = 0;
    int idx = 2;
    int minus = 0;
    if (str[2] == '-') {
        idx = 3;
        minus = 1;
    }
    num = str[idx] - '0';
    ++idx;
    while (str[idx] >= '0' && str[idx] <= '9') {
        num = num * 10 + (str[idx] - '0');
        ++idx;
    }
    if (minus != 0) {
        num *= -1;
    }
    return num;
}

int main(int argc, char* argv[]){
    if (argc != 3) {
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        return 1;
    }
    std::ofstream fout(argv[2]);
    if (!fout.is_open()) {
        return 1;
    }

    AATree Tree;
    int n = 0;
    fin >> n;
    char str[20];
    fin.getline(str, 20, '\n');
    int number = 0;
    for (int i = 0; i < n; ++i) {
        fin.getline(str, 20, '\n');
        number = strToint(str);
        if (str[0] == '?') {
            if (Tree.isInTree(number)) {
                fout << "true" << std::endl;
            } else {
                fout << "false" << std::endl;
            }
        } else if (str[0] == '+') {
            Tree.add(number);
            fout << Tree.getLevel() << std::endl;
        } else {
            Tree.remove(number);
            if (Tree.Root()) {
                fout << 0 << std::endl;
            } else {
                fout << Tree.getLevel() << std::endl;
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}