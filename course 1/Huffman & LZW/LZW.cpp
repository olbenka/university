#include "LZW.h"
#include <map>
#include <algorithm>
#include <limits>
#include<vector>

std::string encodeLZW(const std::string &text) {
    std::map<std::string, int> byWordNum; //словарь 
    for (int i = std::numeric_limits<char>::min(); i <= std::numeric_limits<char>::max(); ++i) {
        byWordNum[std::string(1, i)] = i - std::numeric_limits<char>::min();
    } //заполняем всеми символами в char
    std::string res;
    std::string s;
    for (int i = 0; i < text.size(); ++i) {
        if (byWordNum.count(s + text[i]) > 0) {
            s += text[i]; //удлиняем слово
        } else {
            byWordNum[s + text[i]] = byWordNum.size();
            res += std::to_string(byWordNum[s]) + ' '; //записываем код 
            s = text[i];
        }
    }
    res += std::to_string(byWordNum[s]);

    return res;
}

std::string decodeLZW(const std::vector<int> &arr) {
    std::vector<std::string> byNumWord;
    for (int i = std::numeric_limits<char>::min(); i <= std::numeric_limits<char>::max(); ++i) {
        byNumWord.push_back(std::string(1, i));
    } //заполняем всеми символами в char
    std::string res;
    for (int i = 0; i < arr.size(); ++i) {
        if (byNumWord.size() < arr[i] + 1) {
            byNumWord.push_back(byNumWord[arr[i - 1]] + byNumWord[arr[i - 1]][0]); //предыдущее + первый символ предыдущей
        } else if (i > 0) {
            byNumWord.push_back(byNumWord[arr[i - 1]] + byNumWord[arr[i]][0]); //предыдущее + первый символ новой
        }
        res += byNumWord[arr[i]];
    }

    return res;
}
