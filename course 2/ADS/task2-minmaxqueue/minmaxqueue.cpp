#include <fstream>

#include "MyQueue.h"

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
    int n = 0;
    fin >> n;
    MyQueue queue;
    char str[20];
    int num = 0;
    int idx = 0;
    int minus = 0;
    for (int i = 0; i <= n; ++i) {
        fin.getline(str, 20, '\n');
        if (str[0] == '?') {
            fout << (queue.maxx() - queue.minn()) << std::endl;
        } else if (str[0] == '-') {
            queue.dequeue();
        } else if (str[0] == '+') {
            if (str[2] == '-') {
                idx = 3;
                minus = 1;
            } else {
                idx = 2;
                minus = 0;
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
            queue.enqueue(num);
        }
    }

    fin.close();
    fout.close();
    return 0;
}



