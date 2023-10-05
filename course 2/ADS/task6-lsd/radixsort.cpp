#include <fstream>

void radixSort(char** str, int n, int m, int k) {
    int symbols[59];
    char** B = new char* [n];
    int d = 0;
    int tmp = 0;
    int count = 0;
    for (int i = m - 1; i >= m - k; --i) {
        for (int j = 65; j < 123; ++j) {
            symbols[j - 65] = 0;
        }
        for (int j = 0; j < n; ++j) {
            d = str[j][i] - 65;
            ++symbols[d];
        }
        count = 0;
        for (int j = 65; j < 123; ++j) {
            tmp = symbols[j - 65];
            symbols[j - 65] = count;
            count += tmp;
        }
        for (int j = 0; j < n; ++j) {
            d = str[j][i] - 65;
            B[symbols[d]] = str[j];
            ++symbols[d];
        }
        for (int j = 0; j < n; ++j) {
            str[j] = B[j];
        }
    }
    delete[] B;
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
    int n, m, k;
    fin >> n >> m >> k;
    char** symbols = new char* [n];
    for (int i = 0; i < n; ++i) {
        symbols[i] = new char[m];
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> symbols[j][i];
        }
    }
    radixSort(symbols, n, m, k);
    for (int i = 0; i < n; ++i) {
        fout << symbols[i][0];
    }
    for (int i = 0; i < n; ++i) {
        delete[] symbols[i];
    }
    delete[] symbols;
    fin.close();
    fout.close();
    return 0;
}
