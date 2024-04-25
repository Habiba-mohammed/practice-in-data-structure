#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node *next;
};

template<typename T>
class Stack {
    int size;
    Node<T> *Top;
    Node<T> *Pop;
public:
    Stack();

    void push(T ele);

    void print() const;

    T pop();

    T top() const;

    bool isEmpty() const;

    int stackSize() const;

    void clear();

    ~Stack();


};

template<typename T>
Stack<T>::Stack() {
    Top = Pop = nullptr;
    size = 0;
}

template<typename T>
void Stack<T>::print() const {
    if (!size)
        cout << "Stack is Empty :(";
    else {
        Node<T> *cur = Top;
        for (int i = 0; i < size; ++i) {
            cout << cur->data << ' ';
            cur = cur->next;
        }
        cout << '\n';
        delete cur;
    }
}

template<typename T>
void Stack<T>::push(T ele) {
    auto *newnode = new Node<T>;
    newnode->data = ele;
    newnode->next = Top;
    Top = newnode;
    size++;
}

template<typename T>
T Stack<T>::pop() {
    if (size != 0) {
        Pop = Top;
        Top = Top->next;
        size--;
        return Pop->data;
    }
    //Stack underflow happens when we try to pop (remove) an item from the stack,
    // when nothing is actually there to remove.
    // This will raise an alarm of sorts in the computer because we told it to do
    throw runtime_error("you can't pop any element from stack because it's empty!");
}

template<typename T>
T Stack<T>::top() const {
    if (!size)
        throw runtime_error("Stack is Empty!");
    return Top->data;
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return (!size);
}

template<typename T>
int Stack<T>::stackSize() const {
    return size;
}

template<typename T>
void Stack<T>::clear() {
    if (size){
        Node<T> *cur;
        while (Top != nullptr) {
            cur = Top;
            Top = Top->next;
            delete cur;
        }
        delete Pop;
        size = 0;
    }
    else
        cout << "Stack is Empty";
}

template<typename T>
Stack<T>::~Stack() {
    if (size)
        this->clear();
}


int main() {
    /*
    Stack st;
    st.push(5);
    st.push(6);
    st.push(7);
    //st.clear();
    st.print();
    st.pop();
    cout << st.top() << '\n';
    cout << st.isEmpty() << '\n';
    cout << st.stackSize() << '\n';
    st.pop();
    cout << st.top();
     */

    Stack<string> st2;
    st2.push("maro");
    st2.push("lol");
    st2.push("hello");
    st2.print();
    cout << st2.top() << '\n';
    cout << st2.stackSize() << '\n';
    cout << st2.pop() << '\n';
    cout << st2.top() << '\n';
    cout << st2.stackSize() << '\n';
    cout << st2.isEmpty() << '\n';
    cout << st2.pop() << '\n';
    cout << st2.top() << '\n';

}
