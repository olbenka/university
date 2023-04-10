#include <iostream>
#include "database.h"

char* menu(char choice[1024]) {
    for (int i = 0; i < 30; ++i)
        std::cout << "*";
    std::cout << std::endl;
    std::cout << "CHOOSE AN ACTION" << std::endl;
    std::cout << "* load file.txt" << std::endl;
    std::cout << "* save file.txt" << std::endl;
    std::cout << "* add date count floor area address price" << std::endl;
    std::cout << "* del ID" << std::endl;
    std::cout << "* print" << std::endl;
    std::cout << "* print N" << std::endl;
    std::cout << "* export file.txt" << std::endl;
    std::cout << "* find ID" << std::endl;
    std::cout << "* exit" << std::endl;
    std::cout << "Your choice: ";
    std::cin.getline(choice, 1024, '\n');
    choice[myStrlen(choice)] = '\0';
    return choice;
}


int main() {
    char choice[1024];
    menu(choice);
    DataBase DB = { 0, nullptr };
    DB.count_ = 0;
    while (myStrcmp(choice, "exit") != 0) {
        if (myStrcmp(choice, "print") == 0) {
            printDB(DB);
            menu(choice);
        }
        char firstWord[128];
        int idx = 0;
        while (choice[idx] != ' ') {
            firstWord[idx] = choice[idx];
            ++idx;
        }
        firstWord[idx] = '\0';
        if (myStrcmp(firstWord, "add") == 0) {
            add(DB, choice);
        }
        else if (myStrcmp(firstWord, "load") == 0) {
            char argument[64];
            ++idx;
            int indArg = 0;
            while (choice[idx] != '\0') {
                argument[indArg] = choice[idx];
                ++indArg;
                ++idx;
            }
            argument[indArg] = '\0';
            load(DB, argument);
        }
        else if (myStrcmp(firstWord, "save") == 0) {
            char argument[64];
            ++idx;
            int indArg = 0;
            while (choice[idx] != '\0') {
                argument[indArg] = choice[idx];
                ++indArg;
                ++idx;
            }
            argument[indArg] = '\0';
            save(DB, argument);
        }
        else if (myStrcmp(firstWord, "del") == 0) {
            int id = 0;
            ++idx;
            while (choice[idx] != '\0') {
                id = id * 10 + (choice[idx] - '0');
                ++idx;
            }
            deleteID(DB, id);
        }
        else if (myStrcmp(firstWord, "print") == 0) {
            int id = 0;
            ++idx;
            while (choice[idx] != '\0') {
                id = id * 10 + (choice[idx] - '0');
                ++idx;
            }
            sortByPrice(DB.data_, DB.count_, compByPrice);
            for (int i = 0; i < DB.count_; ++i) {
                if (DB.data_[i].numberOfRooms_ == id) {
                    std::cout << DB.data_[i];
                }
            }
        }
        else if (myStrcmp(firstWord, "export") == 0) {
            char argument[64];
            ++idx;
            int indArg = 0;
            while (choice[idx] != '\0') {
                argument[indArg] = choice[idx];
                ++indArg;
                ++idx;
            }
            argument[indArg] = '\0';
            exportDB(DB, argument);
        }
        else if (myStrcmp(firstWord, "find") == 0) {
            int id = 0;
            ++idx;
            while (choice[idx] != '\0') {
                id = id * 10 + (choice[idx] - '0');
                ++idx;
            }
            int res = find(DB, id);
            if (res <= 0) {
                std::cout << "Not founded" << std::endl;
            }
            else {
                std::cout << DB.data_[res - 1] << std::endl;
            }
        }
        else {
            std::cout << "unknown command: " << choice << std::endl;
        }
        menu(choice);
    }
    if (DB.data_)
        delete[] DB.data_;
    return 0;
}
