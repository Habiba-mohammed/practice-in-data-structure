#include <bits/stdc++.h>

using namespace std;

const int Mx_Size = 5;

template<typename T>
class Stack {
    int size;
    T arr[Mx_Size];
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
    size = 0;
}


template<typename T>
void Stack<T>::print() const {
    if (!size)
        cout << "Stack is Empty :(";
    else {
        for (int i = size - 1; i >= 0; --i) {
            cout << arr[i] << ' ';
        }
        cout << '\n';
    }
}


template<typename T>
void Stack<T>::push(T ele) {
    if (size == Mx_Size)
        throw overflow_error("Stack is full!");
    arr[size++] = ele;
}

template<typename T>
T Stack<T>::pop() {
    if (size != 0) {
        return arr[--size];
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
    return arr[size - 1];
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
    size = 0;
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
    st2.clear();
    st2.print();

}