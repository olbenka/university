#include <fstream>
#include "hash.h"

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
    HashTable table;
    int n = 0;
    fin >> n;
    char str;
    int number = 0;
    for (int i = 0; i < n; ++i) {
        fin >> str;
        fin >> number;
        switch (str) {
            case '+':
                table.insert(number);
                break;
            case '-':
                table.erase(number);
                break;
            default:
                bool res = table.search(number);
                if (res){
                    fout << "true\n";
                } else{
                    fout << "false\n";
                }
                break;

        }
    }
    fin.close();
    fout.close();

    return 0;
}