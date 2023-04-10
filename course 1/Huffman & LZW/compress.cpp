#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "huffman.h"
#include "LZW.h"
#include "IndexedArray.h"

std::string readTextFromFile(std::istream &fin) {
    std::string text;
    char nextSym = fin.peek();
    while (!fin.eof()) {
        text += nextSym;
        fin.ignore();
        nextSym = fin.peek();
    }
    return text;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Invalid using programm!\n";
        return 1;
    } else if (argc == 2) {
        std::cout << "compress -lzw input output - сжатие файла input методом LZW и записывает результат в файл output\n"
                     "compress -huffman input output - сжатие файла input алгоритмом Хаффмана и записывает результат в файл output\n"
                     "compress -d input output - декомпрессию файла input и записывает результат в файл output\n"
                     "compress -h - помощь по использованию программы\n"
                     "compress ? - помощь по использованию программы";
    } else {
        if (argc != 4) {
            std::cout << "Invalid arguments!\n";
        } else if (strcmp("-huffman", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios::binary);
            std::ofstream fout(argv[3], std::ios::binary);
            if (!fin.is_open() || !fout.is_open()) {
                std::cout << "Bad files!\n";
                return 1;
            } else {
                std::string text = readTextFromFile(fin);
                Huffman huffman;
                std::string zipped = huffman.load(text); //кодировка
                //запись в файл данных для раскодировки
                fout << 0 << '\n'; //символ для раскодировки по Хаффману
                IndexedArray<std::numeric_limits<char>::min(), std::numeric_limits<char>::max(), int> cnt(0);
                for (int i = 0; i < text.size(); ++i) {
                    cnt[text[i]]++;
                }
                int nChar = 0;
                for (int i = cnt.getFrom(); i <= cnt.getTo(); ++i) {
                    if (cnt[i] != 0) {
                        ++nChar;
                    }
                }
                fout << nChar << '\n'; //кол-во различных символов
                //символы + их частота
                for (int i = cnt.getFrom(); i <= cnt.getTo(); ++i) {
                    if (cnt[i] != 0) {
                        fout << (char)i << ' ' << cnt[i] << '\n';
                    }
                }

                //запись закодированных данных
                fout << zipped;
                fin.close();
                fout.close();
            }
        } else if (strcmp("-lzw", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios::binary);
            std::ofstream fout(argv[3], std::ios::binary);
            if (!fin.is_open() || !fout.is_open()) {
                std::cout << "Bad files!\n";
                return 1;
            } else {
                fout << 1 << '\n'; //символ для раскодировки с помощью LZW
                std::string text = readTextFromFile(fin);
                fout << encodeLZW(text); //кодировка
            }
        } else if (strcmp("-d", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios::binary);
            std::ofstream fout(argv[3], std::ios::binary);
            if (!fin.is_open() || !fout.is_open()) {
                std::cout << "Bad files!\n";
                return 1;
            } else {
                char type; //тип раскодировки
                fin >> type;
                if (type == '0') {
                    //раскодировка по Хаффману
                    IndexedArray<std::numeric_limits<char>::min(), std::numeric_limits<char>::max(), int> cnt(0);
                    int nChar;
                    fin >> nChar;
                    for (int i = 0; i < nChar; ++i) {
                        fin.ignore();
                        char c = fin.get();
                        int count;
                        fin >> count;
                        cnt[c] = count;
                    }
                    fin >> std::ws; //пропускаем белые символы
                    std::string zipped = readTextFromFile(fin);
                    Huffman huffman;
                    huffman.loadFreq(cnt);
                    fout << huffman.decode(zipped);
                } else {
                    //раскодировка по LZW
                    std::vector<int> zipped;
                    int x;
                    while (fin >> x) {
                        zipped.push_back(x);
                    }
                    fout << decodeLZW(zipped);
                }
            }
        } else {
            std::cout << "Invalid flag!\n";
            return 1;
        }
    }
    return 0;
}
