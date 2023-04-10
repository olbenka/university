#include "formulaenode.h"
#include <vector>
#include <cstring>

class BooleanExpression {
    FormulaNode* root_;
    FormulaNode* Postfix2Tree_(const char*);
    void Infix2Postfix_(const char*, char*);
    void InfixFilter_(const char*, char*);

    static const unsigned char ActionsTable[][13];
    static int ActionsRowNumber(char ch);
    static int ActionsColNumber(char ch);
public:
    //массив, в котором показано наличие переменной (замена на буквы английского алфавита)
    bool vars_[26] = { 0 };
    BooleanExpression(const char* str) {
        size_t Len = strlen(str);
        Len = (Len < 10) ? 20 : 2 * Len;
        char* str_infix = new char[Len];
        char* str_postfix = new char[Len];

        try {
            InfixFilter_(str, str_infix);
            Infix2Postfix_(str_infix, str_postfix);
            root_ = Postfix2Tree_(str_postfix);

        }
        catch (...) {
            delete[] str_postfix;
            delete[] str_infix;
            root_ = nullptr;
            throw;
        }
        delete[] str_infix;
        delete[] str_postfix;
    }

    bool calc();

    operator std::string() const;

    std::string str() const;

    void truthTable() const;

    BooleanExpression cnf() const;

    BooleanExpression dnf() const;

    BooleanExpression zhegalkin() const;

    bool classT0() const;

    bool classT1() const;

    bool classS() const;

    bool classM() const;

    bool classL() const;

    friend bool operator==(const BooleanExpression&, const BooleanExpression&);
};

bool isFullSystem(const std::vector<BooleanExpression> &);