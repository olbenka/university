//Реализация очереди на одномерном массиве.
class MyQueue {
    int size_;      //текущий размер
    int capacity_;  //максимальная ёмкость
    int* data_;     //массив для элементов
    int front_;     //передний элемент
    int last_;      //последний элемент

public: 
    MyQueue(int size);
    ~MyQueue();

    void enqueue(int X);
    int dequeue();
    int peek();
    int size() const;
    bool isEmpty() const;
    bool isFull() const;
};

//Конструктор
MyQueue::MyQueue(int size) : size_(0), capacity_(size), 
                  data_(nullptr), front_(0), last_(-1) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
    }
}

//Деструктор
MyQueue::~MyQueue() {
    if (data_ != nullptr) {
        delete[] data_;
        data_ = nullptr;
    }
}

//Вставка в конец очереди
void MyQueue::enqueue(int X) {
    last_ = (last_ + 1) % capacity_;
    data_[last_] = X;
    size_++;
}

//Извлечь из начала очереди
int MyQueue::dequeue() {
    int tmp = data_[front_];
    front_ = (front_ + 1) % capacity_;
    size_--;
    return tmp;
}

//Возврат первого элемента очереди
int MyQueue::peek() {
    return data_[front_];
}

//Возврат текущего размера очереди
int MyQueue::size() const {
    return size_;
}

//Проверка на пустоту
bool MyQueue::isEmpty() const {
    return (size() == 0);
}

//Проверка на полноту
bool MyQueue::isFull() const {
    return (size() == capacity_);
}