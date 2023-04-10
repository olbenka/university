#pragma once
#include <string>

struct Action {
    int q_i_;
    char a_j_;
    int q_k_;
    char a_m_;
    char d_n_;
};

class TuringMachine {
    Action* actions_;
    int length_;
    int actCount_;
public:
    TuringMachine() : actCount_(0), actions_(nullptr), length_(0) {}

    ~TuringMachine();

    TuringMachine(int, Action*, int);

    TuringMachine(const TuringMachine&);

    TuringMachine(TuringMachine&&);

    TuringMachine& operator=(const TuringMachine&);

    TuringMachine& operator=(TuringMachine&&);

    std::string calc(std::string const&, int);
};
