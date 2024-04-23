#include <bits/stdc++.h>

using namespace std;

const int Mx_Size = 5;


template<typename T>
class Queue {
    int size;
    T arr[Mx_Size];
public:
    Queue();

    void enqueue(T ele);

    T dequeue();

    T first() const;

    bool isEmpty() const;

    int queueSize() const;

    void clear();

    void print() const;

    ~Queue();


};

template<typename T>
Queue<T>::Queue() {
    size = 0;
}

template<typename T>
void Queue<T>::print() const {
    if (!size)
        cout << "Queue is Empty :(";
    else {
        for (int i = 0; i < size; ++i) {
           cout << arr[i] << ' ';
        }

    }
    cout << '\n';
}

template<typename T>
void Queue<T>::enqueue(T ele) {
    if (size == Mx_Size)
        throw overflow_error("Queue is full!");
    arr[size++] = ele;
}

template<typename T>
T Queue<T>::dequeue() {
    if (size != 0) {
        T ele = arr[0];
        for (int i = 1; i < size; ++i) {
            arr[i-1] = arr[i];
        }
        size--;
        return ele;
    }
    //Queue underflow happens when we try to pop (remove) an item from the stack,
    // when nothing is actually there to remove.
    // This will raise an alarm of sorts in the computer because we told it to do
    throw runtime_error("you can't pop any element from stack because it's empty!");
}

template<typename T>
T Queue<T>::first() const {
    if (!size)
        throw runtime_error("Queue is Empty!");
    return arr[0];
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return (!size);
}

template<typename T>
int Queue<T>::queueSize() const {
    return size;
}

template<typename T>
void Queue<T>::clear() {
    size = 0;
}

template<typename T>
Queue<T>::~Queue() {
    if (size)
        this->clear();
}


int main() {

    Queue<string> q;
    q.enqueue("Hello,");
    q.enqueue("Welcome");
    q.enqueue("Marawan");
    q.enqueue("Today");
    q.print();
    cout << q.dequeue() << '\n';
    cout << q.first() << '\n';
    cout << q.isEmpty() << '\n';
    cout << q.queueSize() << '\n';
    q.enqueue("I'm");
    q.enqueue("Good");
    cout << q.queueSize() << '\n';
    q.dequeue();
    cout << q.first() << '\n';
    q.clear();
    cout << (q.isEmpty()? "YES": "NO");

}