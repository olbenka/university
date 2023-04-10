#include <iostream>
#include <fstream>
#include "boolexpr.h"
#include <cstring>


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cout << "Invalid using programm!\n";
    }
    else if (argc == 2) {
        std::cout << "boolcalc -calc input output - осуществляет вычисление выражений записанных в файле input\n"
            "(значения переменных запрашивает у пользователя) \n"
            "и записывает результаты в файл output(для каждой функции результат записывается в отдельной строке).\n"
                     "boolcalc -cnf input output - осуществляет построение конъюнктивной нормальной формы \n"
            "для выражений записанных в файле input и записывает результаты\n"
            "в файл output(для каждой функции результат записывается в отдельной строке).\n"
                     "boolcalc -dnf input output - осуществляет построение дизъюнктивной нормальной формы \n"
            "для выражений записанных в файле input и записывает результаты\n"
            "в файл output(для каждой функции результат записывается в отдельной строке).\n"
                     "boolcalc -zh input output - осуществляет построение Полинома Жегалкина \n"
            "для выражений записанных в файле input и записывает результаты\n"
            "в файл output(для каждой функции результат записывается в отдельной строке).\n"
                     "boolcalc -table input - выводит в консоль таблицу истинности для всех выражений записанных в файле input.\n"
                     "boolcalc -isfull input output проверяет систему функций на полноту. \n"
            "Если система функций в файле input полная, то в файл output выводится yes, иначе no\n."
                     "boolcalc ? - помощь по использованию программы\n";
                     "boolcalc -h - помощь по использованию программы\n";
    }
    else if (argc == 3) {
        std::ifstream fin(argv[2], std::ios_base::binary);
        if (fin.is_open()) {
            while (fin.peek() != EOF) {
                char str[256] = "";
                fin.getline(str, 256, '\n');
                BooleanExpression formula(str);
                formula.truthTable();
            }
        } else {
            std::cout << "isn't open" << std::endl;
            return 1;
        }
        fin.close();
        global::Workspace.clear();
    } else {
        if (argc != 4) {
            std::cout << "Invalid arguments!\n";
            return 1;
        }
        else if (strcmp("-calc", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios_base::binary);
            std::ofstream fout(argv[3], std::ios_base::binary);
            if (fin.is_open() && fout.is_open()) {
                while (fin.peek() != EOF) {
                    char str[256] = "";
                    fin.getline(str, 256, '\n');
                    BooleanExpression formula(str);
                    fout << formula.calc() << std::endl;
                }
            }
            else {
                std::cout << "bad files!" << std::endl;
                return 1;
            }
            fin.close();
            fout.close();
            global::Workspace.clear();
        }
        else if (strcmp("-cnf", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios_base::binary);
            std::ofstream fout(argv[3], std::ios_base::binary);
            if (fin.is_open() && fout.is_open()) {
                while (fin.peek() != EOF) {
                    char str[256] = "";
                    fin.getline(str, 256, '\n');
                    BooleanExpression formula(str);
                    fout << formula.cnf().str() << std::endl;
                }
            }
            else {
                std::cout << "bad files!" << std::endl;
                return 1;
            }
            fin.close();
            fout.close();
            global::Workspace.clear();
        }
        else if (strcmp("-dnf", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios_base::binary);
            std::ofstream fout(argv[3], std::ios_base::binary);
            if (fin.is_open() && fout.is_open()) {
                while (fin.peek() != EOF) {
                    char str[256] = "";
                    fin.getline(str, 256, '\n');
                    BooleanExpression formula(str);
                    fout << formula.dnf().str() << std::endl;
                }
            }
            else {
                std::cout << "bad files!" << std::endl;
                return 1;
            }
            fin.close();
            fout.close();
            global::Workspace.clear();
        }
        else if (strcmp("-zh", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios_base::binary);
            std::ofstream fout(argv[3], std::ios_base::binary);
            if (fin.is_open() && fout.is_open()) {
                while (fin.peek() != EOF) {
                    char str[256] = "";
                    fin.getline(str, 256, '\n');
                    BooleanExpression formula(str);
                    fout << formula.zhegalkin().str() << std::endl;
                }
            }
            else {
                std::cout << "bad files!" << std::endl;
                return 1;
            }
            fin.close();
            fout.close();
            global::Workspace.clear();
        }
        else if (strcmp("-isfull", argv[1]) == 0) {
            std::ifstream fin(argv[2], std::ios_base::binary);
            std::ofstream fout(argv[3], std::ios_base::binary);
            if (fin.is_open() && fout.is_open()) {
                std::vector<BooleanExpression> vec;
                while (fin.peek() != EOF) {
                    char str[256] = "";
                    fin.getline(str, 256, '\n');
                    BooleanExpression formula(str);
                    vec.push_back(formula);
                }
                if (isFullSystem(vec))
                    fout << "yes";
                else
                    fout << "no";
                std::cout << isFullSystem(vec);
            }
            else {
                std::cout << "bad files!" << std::endl;
                return 1;
            }
            fin.close();
            fout.close();
            global::Workspace.clear();
        }
        else {
            std::cout << "Invalid flag!\n";
            return 1;
        }
    }
    return 0;
}