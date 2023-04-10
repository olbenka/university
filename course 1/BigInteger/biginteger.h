#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

const unsigned long long MAX_DIGIT_ = 4294967296;

class BigInteger {
    unsigned int* number_;
    bool is_pos_;
    size_t count_;
public:
    //конструктор по умолчанию
    BigInteger();

    //деструктор
    ~BigInteger();

    //конструкторы от целочисленных типов
    BigInteger(short);

    BigInteger(unsigned short);

    BigInteger(int);

    BigInteger(unsigned int);

    BigInteger(long);

    BigInteger(unsigned long);

    BigInteger(long long);

    BigInteger(unsigned long long);

    //конструктор от строки
    BigInteger(const std::string&);

    //конструктор копирования
    BigInteger(const BigInteger&);

    //конструктор перемещения
    BigInteger(BigInteger&&);

    //операторы копирования и перемещения
    BigInteger& operator= (const BigInteger&);
    BigInteger& operator= (BigInteger&&);

    //операции сравнения
    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);

    //унарные операторы
    BigInteger operator+() const;
    BigInteger operator-() const;

    //арифметические операции присваивания
    BigInteger& operator+=(const BigInteger&);
    BigInteger& operator-=(const BigInteger&);
    BigInteger& operator*=(const BigInteger&);
    BigInteger& operator/=(const BigInteger&);
    BigInteger& operator%=(const BigInteger&);

    //бинарные арифметичсекие операции
    friend const BigInteger operator+(const BigInteger&, const BigInteger&);
    friend const BigInteger operator-(const BigInteger&, const BigInteger&);
    friend const BigInteger operator*(const BigInteger&, const BigInteger&);
    friend const BigInteger operator/(const BigInteger&, const BigInteger&);
    friend const BigInteger operator%(const BigInteger&, const BigInteger&);

    //префиксный инкремент
    BigInteger& operator++();

    //постфиксный инкремент
    BigInteger operator++(int);

    //префиксный декремент
    BigInteger& operator--();

    //постфиксный декремент
    BigInteger operator--(int);

    //побитовые операции
    BigInteger operator~();
    friend BigInteger operator|(const BigInteger&, const BigInteger&);
    friend BigInteger operator^(const BigInteger&, const BigInteger&);
    friend BigInteger operator&(const BigInteger&, const BigInteger&);
    BigInteger operator<<(int);
    BigInteger operator>>(int);
    BigInteger& operator >>=(int);
    BigInteger& operator <<=(int);
    BigInteger& operator|=(const BigInteger&);
    BigInteger& operator^=(const BigInteger&);
    BigInteger& operator&=(const BigInteger&);

    //to_string
    friend std::string to_string(const BigInteger&);

    //операция вывода
    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
};

//функция, которая делит строку на два
void div2(std::string&);

//проверяет является ли строка числом
bool isNum(const std::string&);

size_t maxx(size_t, size_t);
