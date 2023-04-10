#include <fstream>
#include <iostream>
#include "turingmachine.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Wrong input." << std::endl;
        return 1;
    }
    std::ifstream mt(argv[1]);
    if (!mt.is_open()) {
        std::cerr << "MT-file error." << std::endl;
        return 1;
    }
    std::ifstream fin(argv[2]);
    if (!fin.is_open()) {
        std::cerr << "Input file error." << std::endl;
        return 1;
    }
    std::ofstream fout(argv[3]);
    if (!fout.is_open()) {
        std::cerr << "Output file error." << std::endl;
        return 1;
    }

    //подсчет тактов
    int tacts = 0;
    char tactsStr[1024];
    while (mt.peek() != EOF) {
        mt.getline(tactsStr, 1024, '\n');
        ++tacts;
    }
    mt.clear();
    mt.seekg(0);

    //заполнение action
    Action* act = new Action[tacts];
    char symbol;
    char qi;
    char qk;
    char aj;
    char am;
    char dn;
    for (int i = 0; i < tacts; ++i) {
        act[i].q_i_ = 0;
        act[i].q_k_ = 0;
        act[i].a_j_ = 0;
        act[i].a_m_ = 0;
        act[i].d_n_ = 0;
        symbol = mt.get();
        mt >> qi >> aj;
        symbol = mt.get();
        while (symbol != 'q') symbol = mt.get();
        mt >> qk >> am >> dn;
        act[i].q_i_ = qi - '0';
        act[i].q_k_ = qk - '0';
        act[i].a_j_ = aj;
        act[i].a_m_ = am;
        act[i].d_n_ = dn;
        while (symbol != EOF && symbol != '\n') symbol = mt.get();
    }

    //считывание из input
    int len = 0;
    int maxTacts = 0;
    int intTape = 0;
    fin >> len >> maxTacts >> intTape;
    //заполнение ленты
    std::string tape = std::to_string(intTape);
    while (tape.size() != len) {
        tape += '0';
    }

    mt.close();
    fin.close();
    TuringMachine turing_machine(len, act, tacts);
    std::string res = turing_machine.calc(tape, maxTacts);
    fout << res;
    fout.close();
    delete[] act;
    return 0;
}
