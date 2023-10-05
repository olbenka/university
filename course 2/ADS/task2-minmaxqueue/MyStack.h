//Реализация стека с поддержкой минимума и максимума.
struct Element {
    int num_;
    int min_ = 2147483647;
    int max_ = -2147483647;
};

class MyStack {
    Element* data_;    //массив для элементов
    int capacity_;     //ёмкость
    int headIdx_;      //индекс верхнего элемента
public:
    MyStack(int size = 1000001);
    ~MyStack();

    void push(int X);
    int pop();
    int top();
    int size() const;
    bool isEmpty() const;
    bool isFull() const;
    int maxx() const;
    int minn() const;
};

//Конструктор
MyStack::MyStack(int size) : capacity_(size),
                    data_(nullptr), headIdx_(-1){
    if (capacity_ > 0) {
        data_ = new Element[capacity_];
    }
}

//Деструктор
MyStack::~MyStack() {
    if (data_ != nullptr) {
        delete[] data_;
        data_ = nullptr;
    }
}

//Вставка элемента
void MyStack::push(int X) {
    Element tmp;
    if (headIdx_ >= 0) {
        tmp = data_[headIdx_];
    } else {
        tmp.min_ = 2147483647;
        tmp.max_ = -2147483647;
    }
    tmp.num_ = X;
    if (X < tmp.min_) {
        tmp.min_ = X;
    }
    if (X > tmp.max_) {
        tmp.max_ = X;
    }
    data_[++headIdx_] = tmp;
}

//Извлечь верхний элемент
int MyStack::pop() {
    return data_[headIdx_--].num_;
}

//Возврат верхнего элемента
int MyStack::top() {
    return data_[headIdx_].num_;
}

//Возврат размера стека
int MyStack::size() const {
    return headIdx_ + 1;
}

//Проверка на пустоту
bool MyStack::isEmpty() const {
    return (size() == 0);
}

//Проверка на полноту
bool MyStack::isFull() const {
    return (size() == capacity_);
}

//максимальный элемент
int MyStack::maxx() const {
    if (headIdx_ >= 0) {
        return data_[headIdx_].max_;
    }
    return -2147483647;
}

//минимальный элемент
int MyStack::minn() const {
    if (headIdx_ >= 0) {
        return data_[headIdx_].min_;
    }
    return 2147483647;
}