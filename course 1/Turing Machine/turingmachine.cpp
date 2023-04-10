#include "turingmachine.h"

TuringMachine::~TuringMachine() {
    if (actions_) {
        delete[] actions_;
        actCount_ = 0;
        length_ = 0;
        actions_ = nullptr;
    }
}

//Аргументы: размер ленты, программа + количество действий (тоже является частью программы)
TuringMachine::TuringMachine(int len, Action* act, int count) {
    length_ = len;
    actCount_ = count;
    actions_ = new Action[count];
    for (int i = 0; i < count; ++i) {
        actions_[i] = act[i];
    }
}

TuringMachine::TuringMachine(const TuringMachine& X) {
    length_ = X.length_;
    actCount_ = X.actCount_;
    actions_ = new Action[X.actCount_];
    for (int i = 0; i < X.actCount_; ++i) {
        actions_[i] = X.actions_[i];
    }
}

TuringMachine::TuringMachine(TuringMachine&& X) {
    length_ = X.length_;
    actCount_ = X.actCount_;
    actions_ = X.actions_;
    X.length_ = 0;
    X.actCount_ = 0;
    X.actions_ = nullptr;
}

TuringMachine& TuringMachine::operator=(const TuringMachine& X) {
    if (this != &X) {
        length_ = X.length_;
        actCount_ = X.actCount_;
        if (actions_)
            delete[] actions_;
        actions_ = new Action[X.actCount_];
        for (int i = 0; i < X.actCount_; ++i) {
            actions_[i] = X.actions_[i];
        }
    }
    return *this;
}

TuringMachine& TuringMachine::operator=(TuringMachine&& X) {
    if (this != &X) {
        length_ = X.length_;
        actCount_ = X.actCount_;
        if (actions_)
            delete[] actions_;
        actions_ = X.actions_;
        X.length_ = 0;
        X.actions_ = nullptr;
        X.actCount_ = 0;
    }
    return *this;
}


std::string TuringMachine::calc(std::string const& init, int maxsteps) {
    if (init.size() > length_) {
        return "Not applicable";
    }
    std::string tape = init;
    int steps = 0;
    int state = actions_[0].q_i_;
    int index = 0;
    bool conditional;
    while (steps <= maxsteps) {
        conditional = 0;
        for (int i = 0; i < actCount_; ++i) {
            if ((state == actions_[i].q_i_) && (tape[index] == actions_[i].a_j_)) {
                state = actions_[i].q_k_;
                tape[index] = actions_[i].a_m_;
                if (actions_[i].d_n_ == 'R') {
                    if (index == length_) {
                        index = 0;
                    }
                    else {
                        index += 1;
                    }
                }
                else if (actions_[i].d_n_ == 'L') {
                    if (index == 0) {
                        index = length_ - 1;
                    }
                    else {
                        index -= 1;
                    }
                }
                //else if (actions_[i].d_n == 'N') {
                //    continue;
                //}
                conditional = 1;
                break;
            }
        }
        if (conditional == 0)
            break;
        if (steps >= maxsteps && conditional == 1)
            return "Not applicable";
        ++steps;
    }

    std::string res = "";
    int end = index;
    for (int i = 0; i < length_; ++i) {
        if (index == length_)
            index = 0;
        res += tape[index];
        index = (index + 1) % length_;
        if (index == end)
            break;
    }
    int zeroes = 0;
    for (int i = length_ - 1; i >= 0; --i) {
        if (res[i] == '1')
            break;
        else
            zeroes += 1;
    }

    for (int i = length_ - 1; i >= length_ - zeroes; --i) {
        res[i] = '\0';
    }
    std::string answ = "";
    for (int i = 0; i < length_; ++i) {
        if (res[i] != '\0') {
            answ += res[i];
        }
    }
    return answ;
}
