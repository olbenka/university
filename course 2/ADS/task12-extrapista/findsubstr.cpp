#include <iostream>
#include <fstream>

int myStrlen(const char word[]) {
    int index = 0;
    int len = 0;
    while (word[index] != '\0') {
        ++len;
        ++index;
    }
    return len;
}

int find(const char* str, const char* subStr) {
    int count = 0;
    int lenStr = myStrlen(str);
    int lenSub = myStrlen(subStr);

    for (int i = 0; i <= lenStr - lenSub; i++) {
        int j = 0;
        while (j < lenSub && subStr[j] == str[i + j]) {
            j++;
        }
        if (j == lenSub) {
            count++;
        }
    }
    return count;
}

int main(int argc, char* argv[]){
    if (argc != 3) {
        return 1;
    }
    char* subStr = argv[1];
    std::ifstream fin(argv[2]);
    if (!fin.is_open()) {
        return 1;
    }
    int count = 0;
    char str[1024];
    while (fin.getline(str, 1024)) {
        count += find(str, subStr);
    }
    std::cout << count;
    fin.close();
    return 0;
}