//Реализация очереди на двух стеках.
#include "MyStack.h"

class MyQueue {
    MyStack leftStack_;
    MyStack rightStack_;
public:
    MyQueue();
    void enqueue(int X);
    int dequeue();
    int minn() const;
    int maxx() const;
};

//Конструктор
MyQueue::MyQueue() {}

//Вставка в конец очереди
void MyQueue::enqueue(int X) {
    leftStack_.push(X);
}

//Удаление из начала очереди
int MyQueue::dequeue() {
    if (rightStack_.isEmpty()) {
        while (!leftStack_.isEmpty()) {
            rightStack_.push(leftStack_.pop());
        }
    }
    return rightStack_.pop();
}

//минимальный элемент
int MyQueue::minn() const {
    if (leftStack_.minn() < rightStack_.minn()) {
        return leftStack_.minn();
    } 
    return rightStack_.minn();
}

//максимальный элемент
int MyQueue::maxx() const {
    if (leftStack_.maxx() > rightStack_.maxx()) {
        return leftStack_.maxx();
    } 
    return rightStack_.maxx();
}
