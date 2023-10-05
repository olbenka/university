#include <fstream>
#include "FibQueue.h"

int strToInt(const char str[], int &idx) {
    int res = 0;
    bool minus = false;
    if (str[idx] == '-') {
        ++idx;
        minus = true;
    }
    res = (str[idx] - '0');
    ++idx;
    while (str[idx] >= '0' && str[idx] <= '9') {
        res = res * 10 + (str[idx] - '0');
        ++idx;
    }
    if (minus) {
        res *= -1;
    }
    return res;
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
    char str[1024];
    int n = 0;
    while (fin.peek() != EOF) {
        fin.getline(str, 1024, '\n');
        ++n;
    }
    fin.clear();
    fin.seekg(0);
    Node** arr = new Node * [n];
    FibonacciHeap queue;
    int x = 0;
    int y = 0;
    int e = 0;
    for (int i = 0; i < n; ++i) {
        int idx = 0;
        fin.getline(str, 1024, '\n');
        switch (str[0]) {
            case 'p':
                idx = 5;
                x = strToInt(str, idx);
                arr[i] = queue.Insert(x);
                break;
            case 'e':
                e = queue.ExtractMin();
                if (e == 2147483647) {
                    fout << "*\n";
                } else {
                    fout << e << '\n';
                }
                break;
            default:
                idx = 13;
                x = strToInt(str, idx);
                ++idx;
                y = strToInt(str, idx);
                queue.decreaseKey(arr[x - 1], y);
                break;
        }
        
    }
    delete[] arr;
    fin.close();
    fout.close();
    return 0;
}