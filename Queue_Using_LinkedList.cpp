#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node *next;
};

template<typename T>
class Queue {
    int size;
    Node<T> *front;
    Node<T> *back;
    Node<T> *deq;
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
    front = back = nullptr;
    size = 0;
}

template<typename T>
void Queue<T>::print() const {
    if (!size)
        cout << "Queue is Empty :(";
    else {
        Node<T> *cur = front;
        for (int i = 0; i < size; ++i) {
            cout << cur->data << ' ';
            cur = cur->next;
        }
        cout << '\n';
        delete cur;
    }
}

template<typename T>
void Queue<T>::enqueue(T ele) {
    auto *newnode = new Node<T>;
    newnode->data = ele;
    if (front == nullptr) {
        front = back = newnode;
    } else {
        back->next = newnode;
        back = newnode;
    }
    newnode->next = nullptr;
    size++;
}

template<typename T>
T Queue<T>::dequeue() {
    if (size != 0) {
        deq = front;
        front = front->next;
        size--;
        return deq->data;
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
    return front->data;
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
    Node<T> *cur;
    while (front != nullptr) {
        cur = front;
        front = front->next;
        delete cur;
    }
    delete deq;
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
    q.clear();
    cout << (q.isEmpty()? "YES": "NO");

}