#include <iostream>
#include <fstream>

#include "MyQueue.h"

int main(int argc, char* argv[]){
    if (argc != 2) {
        return 1;
    }
    
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        return 1;
    } 

    MyQueue player1(52);
    MyQueue player2(52);

    char str[10];
    char symbol;
    int number = 0;
    int idx = 0;
    while (fin.peek() != -1) {
        fin.getline(str, 10, '\n');
        if (str[1] == ' ') {
            symbol = str[0];
        } else {
            symbol = '1';
        }

        if (symbol >= '2' && symbol <= '9') {
            number = symbol - '0';
        } else if (symbol == '1') {
            number = 10;
        } else {
            if (symbol == 'J') {
                number = 11;
            } else if (symbol == 'Q') {
                number = 12;
            } else if (symbol == 'K') {
                number = 13;
            } else {
                number = 14;
            }
        }

        if (idx < 26) {
            player1.enqueue(number);
        } else {
            player2.enqueue(number);
        }
        ++idx;
    }

    fin.close();
    int move = 0;
    int top1 = 0;
    int top2 = 0;
    int tmpSize = 0;
    MyQueue tmp(52);
    while (!player1.isEmpty() && !player2.isEmpty()) {
        if (move > 1000000) {
            std::cout << "unknown";
            break;
        }
        top1 = player1.dequeue();
        tmp.enqueue(top1);
        top2 = player2.dequeue();
        tmp.enqueue(top2);
        tmpSize = tmp.size();
        if (top1 == 14 && top2 == 2) {
            for (int i = 0; i < tmpSize; ++i) {
                player2.enqueue(tmp.dequeue());
            }
        } else if (top1 == 2 && top2 == 14) {
            for (int i = 0; i < tmpSize; ++i) {
                player1.enqueue(tmp.dequeue());
            }
        } else {
            if (top1 < top2) {
                for (int i = 0; i < tmpSize; ++i) {
                    player2.enqueue(tmp.dequeue());
                }
            } else if (top1 > top2) {
                for (int i = 0; i < tmpSize; ++i) {
                    player1.enqueue(tmp.dequeue());
                }
            }
        }
        ++move;
    }

    if (player1.isEmpty() && player2.isEmpty()) {
        std::cout << "draw";
    } else if (player1.isEmpty()) {
        std::cout << "second";
    } else if (player2.isEmpty()){
        std::cout << "first";
    } 
    
    return 0;
}

//A K Q J 10 9 8 7 6 5 4 3 2
//14 13 12 11 10 9 8 7 6 5 4 3 2


