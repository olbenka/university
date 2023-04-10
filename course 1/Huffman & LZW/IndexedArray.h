#pragma once
//шаблон класса для реализации массива с заданными границами (char)
template<long long from, long long to, class T>
class IndexedArray {
public:
    IndexedArray();

    IndexedArray(const T &def);

    T &operator[](long long index);

    const T &operator[](long long index) const;

    long long getFrom() const;

    long long getTo() const;

private:
    T data_[to - from + 1];
};

template<long long from, long long to, class T>
IndexedArray<from, to, T>::IndexedArray() {
    static_assert(from <= to, "Must have elements");
    static_assert(to - from + 1 >= 0, "Must be positive");
}

template<long long int from, long long int to, class T>
IndexedArray<from, to, T>::IndexedArray(const T &def) {
    static_assert(from <= to, "Must have elements");
    static_assert(to - from + 1 >= 0, "Must be positive");
    for (long long i = from; i <= to; ++i) {
        operator[](i) = def;
    }
}

template<long long from, long long to, class T>
T &IndexedArray<from, to, T>::operator[](long long index) {
    return data_[index - from];
}

template<long long from, long long to, class T>
const T &IndexedArray<from, to, T>::operator[](long long index) const {
    return data_[index - from];
}

template<long long int from, long long int to, class T>
long long IndexedArray<from, to, T>::getFrom() const {
    return from;
}

template<long long int from, long long int to, class T>
long long IndexedArray<from, to, T>::getTo() const {
    return to;
}
