#include "biginteger.h"

//функция, которая делит строку на два
void div2(std::string& str) {
    for (int idx = str.length() - 1; idx >= 0; --idx) {
        if ((str[idx] - '0') % 2 == 1) {
            str[idx] -= 1;
            str[idx + 1] += 5;
        }
        str[idx] = (str[idx] - '0') / 2 + '0';
    }
    if (str[0] == '0' && str.length() > 1) {
        str.erase(0, 1);
    }
}

//проверяет является ли строка числом
bool isNum(const std::string& str) {
    if (str.empty())
        return false;
    bool sign = (str[0] == '-');
    if (sign && str.size() == 1)
        return false;
    std::string tmp = "";
    if (sign) {
        for (int i = 1; i < str.size(); ++i) {
            tmp += str[i];
        }
    }
    else
        tmp = str;

    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] < '0' || tmp[i] > '9')
            return false;
    }
    return true;
}

//конструктор по умолчанию
BigInteger::BigInteger() {
    number_ = new unsigned int[1];
    number_[0] = 0;
    is_pos_ = true;
    count_ = 1;
}

//деструктор
BigInteger::~BigInteger() {
    if (number_) {
        delete[] number_;
        count_ = 0;
        number_ = nullptr;
    }
}

//конструкторы от целочисленных типов
BigInteger::BigInteger(short X) : count_(1) {
    if (X < 0) {
        X *= -1;
        is_pos_ = false;
    } else {
        is_pos_ = true;
    }
    number_ = new unsigned int[1];
    number_[0] = X;
}

BigInteger::BigInteger(unsigned short X) : count_(1), is_pos_(true) {
    number_ = new unsigned int[1];
    number_[0] = X;
}

BigInteger::BigInteger(int X) : count_(1) {
    if (X < 0) {
        X *= -1;
        is_pos_ = false;
    } else {
        is_pos_ = true;
    }
    number_ = new unsigned int[1];
    number_[0] = X;
}

BigInteger::BigInteger(unsigned int X) : count_(1), is_pos_(true) {
    number_ = new unsigned int[1];
    number_[0] = X;
}

BigInteger::BigInteger(long X) : count_(1) {
    if (X < 0) {
        X *= -1;
        is_pos_ = false;
    } else {
        is_pos_ = true;
    }
    number_ = new unsigned int[1];
    number_[0] = X;
}

BigInteger::BigInteger(unsigned long X) : count_(1), is_pos_(true) {
    number_ = new unsigned int[1];
    number_[0] = X;
}

BigInteger::BigInteger(long long X) {
    if (X < 0) {
        X *= -1;
        is_pos_ = false;
    } else {
        is_pos_ = true;
    }
    if (X < MAX_DIGIT_) {
        count_ = 1;
        number_ = new unsigned int[1];
        number_[0] = X;
    } else {
        count_ = 2;
        number_ = new unsigned int[2];
        number_[0] = X / MAX_DIGIT_;
        number_[1] = X % MAX_DIGIT_;
    }
}

BigInteger::BigInteger(unsigned long long X) : is_pos_(true) {
    if (X < MAX_DIGIT_) {
        count_ = 1;
        number_ = new unsigned int[1];
        number_[0] = X;
    }
    else {
        count_ = 2;
        number_ = new unsigned int[2];
        number_[0] = X / MAX_DIGIT_;
        number_[1] = X % MAX_DIGIT_;
    }
}

//конструктор от строки
BigInteger::BigInteger(const std::string& str) {
    if (!(isNum(str))) {
        throw std::invalid_argument(str);
    }
    if (str[0] == '-') {
        is_pos_ = false;
    }
    else
        is_pos_ = true;
    //строка без минуса
    std::string tmp = "";
    for (size_t i = (!is_pos_); i < str.length(); ++i) {
        tmp += str[i];
    }
    int tmp_size = tmp.size();
    if (tmp == "0") {
        number_ = new unsigned int[1];
        number_[0] = 0;
        count_ = 1;
        is_pos_ = true;
    } else {
        int len = 0;
        if (tmp.size() <= 9) {
            len = 1;
        } else
            len = tmp_size / 9 + 1;
        unsigned int* digit = new unsigned int[len];
        for (int i = 0; i < len; ++i) {
            digit[i] = 0;
        }
        unsigned int arr[33];
        int numb = 1;
        for (int i = 0; i < 32; ++i) {
            arr[i] = numb;
            numb *= 2;
        }
        arr[32] = 0;
        int degree = 0;
        int idx = len - 1;
        do {
            if (degree == 32) {
                degree = 0;
                idx -= 1;
            }
            if (((tmp[tmp.size() - 1] - '0') % 2) == 1) {
                digit[idx] += arr[degree];
            }
            div2(tmp);
            ++degree;
        } while (tmp != "0");
        //удалить ведущие нули
        int zeroes = 0;
        for (int i = 0; i < len; ++i) {
            if (digit[i] == 0)
                zeroes += 1;
            else break;
        }
        if (zeroes == len) {
            count_ = 1;
            number_ = new unsigned int[1];
            number_[0] = 0;
        }
        else {
            count_ = len - zeroes;
            number_ = new unsigned int[count_];
            for (size_t i = 0; i < count_; ++i) {
                number_[i] = digit[i + zeroes];
            }
        }
        delete[] digit;
    }
}

//конструктор копирования
BigInteger::BigInteger(const BigInteger& X) {
    count_ = X.count_;
    is_pos_ = X.is_pos_;
    number_ = new unsigned int[count_];
    for (size_t i = 0; i < count_; ++i) {
        number_[i] = X.number_[i];
    }
}

//конструктор перемещения
BigInteger::BigInteger(BigInteger&& X) {
    number_ = X.number_;
    count_ = X.count_;
    is_pos_ = X.is_pos_;
    X.number_ = nullptr;
    X.count_ = 0;
}

//оператор копирования
BigInteger& BigInteger::operator= (const BigInteger& X) {
    if (this != &X) {
        if (number_)
            delete[] number_;
        count_ = X.count_;
        is_pos_ = X.is_pos_;
        number_ = new unsigned int[count_];
        for (size_t i = 0; i < count_; ++i) {
            number_[i] = X.number_[i];
        }
    }
    return *this;
}

//оператор перемещения
BigInteger& BigInteger::operator= (BigInteger&& X) {
    if (this != &X) {
        if (number_)
            delete[] number_;
        number_ = X.number_;
        count_ = X.count_;
        is_pos_ = X.is_pos_;
        X.number_ = nullptr;
        X.count_ = 0;
    }
    return *this;
}

//операции сравнения
bool operator==(const BigInteger& l, const BigInteger& r) {
    if (l.is_pos_ != r.is_pos_)
        return false;
    if (l.count_ != r.count_)
        return false;
    for (size_t i = 0; i < l.count_; ++i) {
        if (l.number_[i] != r.number_[i])
            return false;
    }
    return true;
}

bool operator!=(const BigInteger& l, const BigInteger& r) {
    return !(l == r);
}

bool operator<(const BigInteger& l, const BigInteger& r) {
    if (l == r) 
        return false;
    if ((l.is_pos_ == false) && (r.is_pos_ == true))
        return true;
    if ((l.is_pos_ == true) && (r.is_pos_ == false)) 
        return false;
    if ((l.is_pos_ == true) && (r.is_pos_ == true)) {
        if (l.count_ > r.count_) 
            return false;
        else if (l.count_ < r.count_) 
            return true; 
        else {
            for (size_t i = 0; i < l.count_; ++i) {
                if (l.number_[i] == r.number_[i]) 
                    continue;
                else if (l.number_[i] < r.number_[i]) 
                    return true;
                else if (l.number_[i] > r.number_[i]) 
                    return false;
            }
            return false;
        }
    } else {
        if (l.count_ > r.count_) 
            return true;
        else if (l.count_ < r.count_) 
            return false;
        else {
            for (size_t i = 0; i < l.count_; ++i) {
                if (l.number_[i] == r.number_[i]) 
                    continue;
                else if (l.number_[i] < r.number_[i]) 
                    return false;
                else if (l.number_[i] > r.number_[i])
                    return true;
            }
            return false;
        }
    }
}

bool operator<=(const BigInteger& l, const BigInteger& r) {
    return ((l < r) || (l == r));
}

bool operator>(const BigInteger& l, const BigInteger& r) {
    return !(l <= r);
}

bool operator>=(const BigInteger& l, const BigInteger& r) {
    return !(l < r);
}

//унарные операторы
BigInteger BigInteger::operator+() const {
    return *this;
}

BigInteger BigInteger::operator-() const {
    BigInteger tmp(*this);
    if (count_ == 1 && number_[0] == 0) {
        return tmp;
    }
    tmp.is_pos_ = !is_pos_;
    return tmp;
}

//арифметические операции присваивания
BigInteger& BigInteger::operator+=(const BigInteger& X) {
    *this = *this + X;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& X) {
    *this = *this - X;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& X) {
    *this = *this * X;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& X) {
    *this = *this / X;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& X) {
    *this = *this % X;
    return *this;
}

size_t maxx(size_t l, size_t r) {
    if (l >= r) {
        return l;
    }
    else
        return r;
}

//бинарные операции
const BigInteger operator+(const BigInteger& l, const BigInteger& r) {
    if (l.is_pos_ == r.is_pos_) {
        BigInteger res;
        res.is_pos_ = l.is_pos_;
        res.count_ = maxx(l.count_, r.count_) + 1;
        res.number_ = new unsigned int[res.count_];
        for (size_t i = 0; i < res.count_; ++i) {
            res.number_[i] = 0;
        }

        unsigned long long ull_num = 0;
        int add = 0;
        unsigned int l_tmp = 0;
        unsigned int r_tmp = 0;
        for (size_t i = 0; i < res.count_ || add; ++i) {
            if (i < l.count_) {
                l_tmp = l.number_[l.count_ - 1 - i];
            }
            else 
                l_tmp = 0;
            if (i < r.count_) {
                r_tmp = r.number_[r.count_ - 1 - i];
            }
            else 
                r_tmp = 0;

            ull_num = (unsigned long long)l_tmp + (unsigned long long)r_tmp + add;
            if (ull_num >= MAX_DIGIT_) {
                res.number_[res.count_ - 1 - i] = ull_num - MAX_DIGIT_;
                add = 1;
            }
            else {
                res.number_[res.count_ - 1 - i] = ull_num;
                add = 0;
            }
        }
        if (add) 
            res.number_[0] = add;

        //удалить ведущие нули
        BigInteger answer;
        answer.is_pos_ = res.is_pos_;
        int zeroes = 0;
        for (size_t i = 0; i < res.count_; ++i) {
            if (res.number_[i] == 0)
                zeroes += 1;
            else 
                break;
        }
        if (zeroes != 0) {
            answer.count_ = res.count_ - zeroes;
        }
        else
            answer.count_ = res.count_;
        answer.number_ = new unsigned int[answer.count_];
        for (size_t i = 0; i < answer.count_; ++i) {
            answer.number_[i] = res.number_[i + zeroes];
        }
        return answer;
    }
    else {
        BigInteger positive, negative;
        if (l > r) {
            positive = l;
            negative = r;
        }
        else {
            positive = r;
            negative = l;
        }
        return (positive - -(negative));
    }
}

const BigInteger operator-(const BigInteger& l, const BigInteger& r) {
    if (l == r)
        return 0;
    if (l.is_pos_ == true && r.is_pos_ == true) {
        BigInteger res;
        BigInteger max, min;
        if (l > r) {
            res.is_pos_ = true;
            max = l;
            min = r;
        } else {
            res.is_pos_ = false;
            max = r;
            min = l;
        }
        res.count_ = max.count_;
        res.number_ = new unsigned int[res.count_];
        for (size_t i = 0; i < res.count_; ++i) {
            res.number_[i] = 0;
        }
        long long ll_num = 0;
        int add = 0;
        unsigned int tmp;
        for (size_t i = 0; i < max.count_ || add; ++i) {
            if (i < min.count_) {
                tmp = min.number_[min.count_ - i - 1];
            } else {
                tmp = 0;
            }
            ll_num = (long long)max.number_[max.count_ - i - 1] - add - (long long)tmp;
            if (ll_num < 0) {
                add = 1;
                ll_num += MAX_DIGIT_;
            } else {
                add = 0;
            }
            res.number_[res.count_ - i - 1] = (unsigned int)(ll_num);
        }
        //удалить ведущие нули
        BigInteger answer;
        answer.is_pos_ = res.is_pos_;
        int zeroes = 0;
        for (size_t i = 0; i < res.count_; ++i) {
            if (res.number_[i] == 0)
                zeroes += 1;
            else 
                break;
        }
        if (zeroes != 0) {
            answer.count_ = res.count_ - zeroes;
        }
        else 
            answer.count_ = res.count_;
        answer.number_ = new unsigned int[answer.count_];
        for (size_t i = 0; i < answer.count_; ++i) {
            answer.number_[i] = res.number_[i + zeroes];
        }
        return answer;
    }
    else if (l.is_pos_ == true && r.is_pos_ == false) {
        BigInteger tmp = -r;
        return l + tmp;
    }
    else if (l.is_pos_ == false && r.is_pos_ == true) {
        BigInteger tmp = -l;
        return -(r + tmp);
    }
    else if (l.is_pos_ == false && r.is_pos_ == false) {
        BigInteger tmp = -r;
        return tmp + l;
    }
}

const BigInteger operator*(const BigInteger& l, const BigInteger& r) {
    if (l == 0 || r == 0)
        return 0;
    BigInteger res;
    res.count_ = l.count_ + r.count_ + 1;
    res.number_ = new unsigned int[res.count_];
    for (size_t i = 0; i < res.count_; ++i) {
        res.number_[i] = 0;
    }
    if (l.is_pos_ == r.is_pos_) {
        res.is_pos_ = true;
    } else {
        res.is_pos_ = false;
    }

    unsigned long long ull_num = 0;
    unsigned int add = 0;
    unsigned int l_tmp = 0;
    unsigned int r_tmp = 0;
    for (size_t i = 0; i < l.count_; ++i) {
        for (size_t j = 0; j < r.count_ || add; ++j) {
            if (i < l.count_) {
                l_tmp = l.number_[l.count_ - 1 - i];
            }
            else 
                l_tmp = 0;
            if (j < r.count_) {
                r_tmp = r.number_[r.count_ - 1 - j];
            }
            else 
                r_tmp = 0;
            ull_num = (unsigned long long)res.number_[res.count_ - 1 - i - j] +
                (unsigned long long)l_tmp * (unsigned long long)r_tmp + add;
            res.number_[res.count_ - 1 - i - j] = ull_num % MAX_DIGIT_;
            add = ull_num / MAX_DIGIT_;
        }
    }
    //удалить ведущие нули
    BigInteger answer;
    answer.is_pos_ = res.is_pos_;
    int zeroes = 0;
    for (size_t i = 0; i < res.count_; ++i) {
        if (res.number_[i] == 0)
            zeroes += 1;
        else 
            break;
    }
    if (zeroes != 0) {
        answer.count_ = res.count_ - zeroes;
    }
    else 
        answer.count_ = res.count_;
    answer.number_ = new unsigned int[answer.count_];
    for (size_t i = 0; i < answer.count_; ++i) {
        answer.number_[i] = res.number_[i + zeroes];
    }
    return answer;
}

const BigInteger operator/(const BigInteger& l, const BigInteger& r) {
    if (r == 0)
        throw std::invalid_argument("Wrong input");
    if (l == r) {
        return 1;
    }
    if (l < r && l.is_pos_ == true && r.is_pos_ == true)
        return 0;
    if (l > r && l.is_pos_ == false && r.is_pos_ == false)
        return 0;
    BigInteger res;
    res.count_ = maxx(l.count_, r.count_);
    res.number_ = new unsigned int[res.count_];
    for (size_t i = 0; i < res.count_; ++i) {
        res.number_[i] = 0;
    }
    if (l.is_pos_ == r.is_pos_) {
        res.is_pos_ = true;
    } else {
        res.is_pos_ = false;
    }

    BigInteger curr = 0;
    BigInteger r_tmp = r;
    r_tmp.is_pos_ = true;
    for (size_t i = 0; i < l.count_; ++i) {
        curr *= MAX_DIGIT_;
        curr.number_[curr.count_ - 1] = l.number_[i];
        BigInteger ans;
        ans.is_pos_ = curr.is_pos_;
        int zeroes = 0;
        for (size_t i = 0; i < curr.count_; ++i) {
            if (curr.number_[i] == 0)
                zeroes += 1;
            else 
                break;
        }
        if (zeroes != 0) {
            ans.count_ = curr.count_ - zeroes;
        } else 
            ans.count_ = curr.count_;
        ans.number_ = new unsigned int[ans.count_];
        for (size_t i = 0; i < ans.count_; ++i) {
            ans.number_[i] = curr.number_[i + zeroes];
        }
        unsigned long long x = 0;
        unsigned long long l = 0;
        unsigned long long r = MAX_DIGIT_;
        while (l <= r) {
            unsigned long long m = (l + r) / 2;
            BigInteger curr_mult = r_tmp * (BigInteger)m;
            if (curr_mult <= curr) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        res.number_[i] = x;
        curr -= r_tmp * (BigInteger)x;
    }

    //удалить ведущие нули
    BigInteger answer;
    answer.is_pos_ = res.is_pos_;
    int zeroes = 0;
    for (size_t i = 0; i < res.count_; ++i) {
        if (res.number_[i] == 0)
            zeroes += 1;
        else 
            break;
    }
    if (zeroes != 0) {
        answer.count_ = res.count_ - zeroes;
    }
    else 
        answer.count_ = res.count_;
    answer.number_ = new unsigned int[answer.count_];
    for (size_t i = 0; i < answer.count_; ++i) {
        answer.number_[i] = res.number_[i + zeroes];
    }

    return answer;
}

const BigInteger operator%(const BigInteger& l, const BigInteger& r) {
    BigInteger res = l - (l / r) * r;
    if (res != 0) {
        res.is_pos_ = l.is_pos_;
    }
    return res;
}

//префиксный инкремент
BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

//постфиксный инкремент
BigInteger BigInteger::operator++(int) {
    BigInteger tmp = *this;
    *this += 1;
    return tmp;
}

//префиксный декремент
BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

//постфиксный декремент
BigInteger BigInteger::operator--(int) {
    BigInteger tmp = *this;
    *this -= 1;
    return tmp;
}

//побитовые операции
BigInteger BigInteger::operator~() {
    BigInteger res = *this;
    res.is_pos_ = !is_pos_;
    res -= 1;
    return res;
}

BigInteger operator|(const BigInteger& l, const BigInteger& r) {
    BigInteger l_tmp = l;
    BigInteger r_tmp = r;
    BigInteger res;
    if (!l_tmp.is_pos_) {
        l_tmp = ~l_tmp;
        for (int i = 0; i < l_tmp.count_; ++i) {
            l_tmp.number_[i] = ~l_tmp.number_[i];
        }
    }
    if (!r_tmp.is_pos_) {
        r_tmp = ~r_tmp;
        for (int i = 0; i < r_tmp.count_; ++i)
        {
            r_tmp.number_[i] = ~r_tmp.number_[i];
        }
    }
    if (l_tmp.count_ > r_tmp.count_) {
        res = l_tmp;
        for (int i = r_tmp.count_ - 1; i >= 0; --i) {
            res.number_[res.count_ - r_tmp.count_ + i] = res.number_[res.count_ - r_tmp.count_ + i] | r_tmp.number_[i];
        }
    } else {
        res = r_tmp;
        for (int i = l_tmp.count_ - 1; i >= 0; --i)
        {
            res.number_[res.count_ - l_tmp.count_ + i] = res.number_[res.count_ - l_tmp.count_ + i] | l_tmp.number_[i];
        }
    }
    if (res.number_[0] & (1 << 31)) {
        res.is_pos_ = false;
        res = ~res;
        for (int i = 0; i < res.count_; ++i) {
            res.number_[i] = ~res.number_[i];
        }
        res.is_pos_ = false;
    } else {
        res.is_pos_ = true;
    }
    return res;
}

BigInteger operator&(const BigInteger& l, const BigInteger& r) {
    BigInteger l_tmp = l;
    BigInteger r_tmp = r;
    BigInteger res;
    if (!l_tmp.is_pos_) {
        l_tmp = ~l_tmp;
        for (int i = 0; i < l_tmp.count_; ++i) {
            l_tmp.number_[i] = ~l_tmp.number_[i];
        }
    }
    if (!r_tmp.is_pos_) {
        r_tmp = ~r_tmp;
        for (int i = 0; i < r_tmp.count_; ++i) {
            r_tmp.number_[i] = ~r_tmp.number_[i];
        }
    }
    if (l_tmp.count_ > r_tmp.count_) {
        res = l_tmp;
        for (int i = r_tmp.count_ - 1; i >= 0; --i) {
            res.number_[res.count_ - r_tmp.count_ + i] = res.number_[res.count_ - r_tmp.count_ + i] & r_tmp.number_[i];
        }
    } else {
        res = r_tmp;
        for (int i = l_tmp.count_ - 1; i >= 0; --i) {
            res.number_[res.count_ - l_tmp.count_ + i] = res.number_[res.count_ - l_tmp.count_ + i] & l_tmp.number_[i];
        }
    }
    if (res.number_[0] & (1 << 31)) {
        res.is_pos_ = false;
        res = ~res;
        for (int i = 0; i < res.count_; ++i) {
            res.number_[i] = ~res.number_[i];
        }
        res.is_pos_ = false;
    } else {
        res.is_pos_ = true;
    }
    return res;
}

BigInteger operator^(const BigInteger& l, const BigInteger& r)
{
    BigInteger l_tmp = l;
    BigInteger r_tmp = r;
    BigInteger res;
    if (!l_tmp.is_pos_) {
        l_tmp = ~l_tmp;
        for (int i = 0; i < l_tmp.count_; ++i) {
            l_tmp.number_[i] = ~l_tmp.number_[i];
        }
    }
    if (!r_tmp.is_pos_) {
        r_tmp = ~r_tmp;
        for (int i = 0; i < r_tmp.count_; ++i) {
            r_tmp.number_[i] = ~r_tmp.number_[i];
        }
    }
    if (l_tmp.count_ > r_tmp.count_) {
        res = l_tmp;
        for (int i = r_tmp.count_ - 1; i >= 0; --i) {
            res.number_[res.count_ - r_tmp.count_ + i] = res.number_[res.count_ - r_tmp.count_ + i] ^ r_tmp.number_[i];
        }
    } else {
        res = r_tmp;
        for (int i = l_tmp.count_ - 1; i >= 0; --i) {
            res.number_[res.count_ - l_tmp.count_ + i] = res.number_[res.count_ - l_tmp.count_ + i] ^ l_tmp.number_[i];
        }
    }
    if (res.number_[0] & (1 << 31)) {
        res.is_pos_ = false;
        res = ~res;
        for (int i = 0; i < res.count_; ++i) {
            res.number_[i] = ~res.number_[i];
        }
        res.is_pos_ = false;
    } else {
        res.is_pos_ = true;
    }
    return res;
}

BigInteger BigInteger::operator<<(int shift) {
    int shift_numbers = shift % 32;
    int shift_array = shift / 32;
    BigInteger res;
    res.is_pos_ = is_pos_;
    res.count_ = count_ + shift_array + 1;
    res.number_ = new unsigned int[res.count_];
    for (size_t i = 0; i < res.count_; ++i) {
        res.number_[i] = 0;
    }
    unsigned int value;
    for (size_t i = 0; i < count_ / 2; ++i) {
        value = number_[i];
        number_[i] = number_[count_ - 1 - i];
        number_[count_ - 1 - i] = value;
    }
    unsigned int shift1 = 0;
    unsigned int shift2 = 0;
    for (int i = 0; i < (count_ + 1); ++i) {
        if (i == 0) {
            shift2 = 0;
        }
        else {
            shift2 = (number_[i - 1] >> (32 - shift_numbers));
        }
        if (i == count_) {
            shift1 = 0;
        }
        else {
            shift1 = (number_[i] << shift_numbers);
        }
        res.number_[shift_array + i] = shift1 + shift2;
    }
    BigInteger answer;
    answer.is_pos_ = res.is_pos_;
    int zeroes = 0;
    for (size_t i = res.count_ - 1; i >= 0; --i) {
        if (res.number_[i] == 0)
            zeroes += 1;
        else break;
    }
    if (zeroes != 0) {
        answer.count_ = res.count_ - zeroes;
    }
    else answer.count_ = res.count_;
    answer.number_ = new unsigned int[answer.count_];
    for (size_t i = 0; i < answer.count_; ++i) {
        answer.number_[i] = res.number_[i];
    }
    for (size_t i = 0; i < answer.count_ / 2; ++i) {
        value = answer.number_[i];
        answer.number_[i] = answer.number_[answer.count_ - 1 - i];
        answer.number_[answer.count_ - 1 - i] = value;
    }
    return answer;
}

BigInteger BigInteger::operator>>(int shift)
{
    int shift_numbers = shift % 32;
    int shift_array = shift / 32;
    if (shift_array > count_) {
        return 0;
    }
    BigInteger res;
    res.is_pos_ = is_pos_;
    res.count_ = count_ - shift_array;
    res.number_ = new unsigned int[res.count_];
    for (size_t i = 0; i < res.count_; ++i) {
        res.number_[i] = 0;
    }

    unsigned int value;
    for (size_t i = 0; i < count_ / 2; ++i) {
        value = number_[i];
        number_[i] = number_[count_ - 1 - i];
        number_[count_ - 1 - i] = value;
    }
    unsigned int shift1 = 0;
    for (int i = shift_array; i < count_; ++i) {
        if (i == count_ - 1) {
            shift1 = 0;
        }
        else {
            shift1 = (number_[i + 1] << (32 - shift_numbers));
        }
        res.number_[i - shift_array] = shift1 + (number_[i] >> shift_numbers);
    }
    BigInteger answer;
    answer.is_pos_ = res.is_pos_;
    int zeroes = 0;
    for (size_t i = res.count_ - 1; i >= 0; --i) {
        if (res.number_[i] == 0)
            zeroes += 1;
        else break;
    }
    if (zeroes != 0) {
        answer.count_ = res.count_ - zeroes;
    }
    else 
        answer.count_ = res.count_;
    answer.number_ = new unsigned int[answer.count_];
    for (size_t i = 0; i < answer.count_; ++i) {
        answer.number_[i] = res.number_[i];
    }
    for (size_t i = 0; i < answer.count_ / 2; ++i) {
        value = answer.number_[i];
        answer.number_[i] = answer.number_[answer.count_ - 1 - i];
        answer.number_[answer.count_ - 1 - i] = value;
    }
    if (!answer.is_pos_ && (answer % MAX_DIGIT_ != 0)) {
        --answer;
    }

    return answer;
}

BigInteger& BigInteger::operator >>=(int shift) {
    *this = *this >> shift;
    return *this;
}

BigInteger& BigInteger::operator <<=(int shift) {
    *this = *this << shift;
    return *this;
}

BigInteger& BigInteger::operator|=(const BigInteger& X) {
    *this = *this | X;
    return *this;
}

BigInteger& BigInteger::operator&=(const BigInteger& X) {
    *this = *this & X;
    return *this;
}

BigInteger& BigInteger::operator^=(const BigInteger& X) {
    *this = *this ^ X;
    return *this;
}



//to_string
std::string to_string(const BigInteger& X) {
    if (X == 0) {
        return "0";
    }
    std::string res;
    if (X.count_ == 1) {
        if (X.is_pos_ == false) {
            res += "-";
        }
        res += std::to_string(X.number_[0]);
        return res;
    }
    BigInteger tmp = X;
    while (tmp.number_[0] != 0 || tmp.count_ != 1) {
        int add = 0;
        unsigned long long ull_num = 0;
        for (size_t i = 0; i < tmp.count_; ++i) {
            ull_num = (unsigned long long)tmp.number_[i] + MAX_DIGIT_ * add;
            tmp.number_[i] = ull_num / 10;
            add = (int)(ull_num % 10);
        }
        res += std::to_string(add);
        if (tmp.number_[0] == 0 && tmp.count_ > 1) {
            int zeroes = 0;
            for (size_t i = 0; i < tmp.count_; ++i) {
                if (tmp.number_[i] == 0)
                    zeroes += 1;
                else 
                    break;
            }
            int new_count = tmp.count_ - zeroes;
            BigInteger newTmp;
            newTmp.is_pos_ = tmp.is_pos_;
            newTmp.count_ = new_count;
            newTmp.number_ = new unsigned int[new_count];
            for (size_t i = 0; i < new_count; ++i) {
                newTmp.number_[i] = tmp.number_[i + zeroes];
            }
            tmp = newTmp;
        }
    }
    if (tmp.is_pos_ == false) {
        res += "-";
    }
    std::string answer = "";
    for (int i = res.size() - 1; i >= 0; --i) {
        answer += res[i];
    }
    return answer;
}

//оператор вывода
std::ostream& operator<< (std::ostream& out, const BigInteger& X)
{
    out << to_string(X);
    return out;
}

