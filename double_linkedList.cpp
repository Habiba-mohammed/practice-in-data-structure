#include <iostream>
#define ll long long

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node *next;
    Node *prev;
    Node() {
        next = NULL;
        prev = NULL;
    }
};

template<typename T>
class double_linkedList {
public:
    Node<T>* Head;
    Node<T>* Last;
    double_linkedList() {
        Head = NULL;
        Last = NULL;
    }
    bool isEmpty() {
        return (Head == NULL);
    }

    long long size() {
        long long size = 0;
        if (isEmpty()) {
            return size;
        }
        Node<T>* temp = Head;
        while (temp != NULL) {
            size++;
            temp = temp->next;
        }
        return size;
    }
    void append_at_tail(T new_item) {
        Node<T>* new_node = new Node<T>();
        new_node->data = new_item;
        if (isEmpty()) {
            new_node->next = NULL;
            new_node->prev = NULL;
            Head = new_node;
            Last = new_node;
            return;
        }

        Last->next = new_node;
        new_node->prev = Last;
        Last = new_node;
    }
    void append_at_first(T new_item) {
        if (isEmpty()) {
            append_at_tail(new_item);
            return;
        }
        Node<T>* newnode = new Node<T>();
        newnode->data = new_item;
        newnode->next = Head;
        Head->prev = newnode;
        Head = newnode;
    }
    void insert_at_pos(T new_item, long long index) {
        if (isEmpty()) {
            append_at_tail(new_item);
            return;
        }
        if (index <= 0) {
            append_at_first(new_item);
            return;
        }
        if (index >= size()) {
            append_at_tail(new_item);
            return;
        }

        long long cur = 0;
        Node<T>* temp = Head;
        Node<T>* newnode = new Node<T>();
        newnode->data = new_item;
        while (temp->next != NULL && cur < index) {
            cur++;
            temp = temp->next;
        }
        newnode->next = temp;
        newnode->prev = temp->prev;
        temp->prev->next = newnode;
        temp->prev = newnode;
    }
    void print() {
        if (isEmpty()) {
            cout << "This list is empty\n";
            return;
        }
        Node<T>* temp = Head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << '\n';
    }
    void clear() {
        if (!isEmpty()) {
            Node<T>* temp = Head;
            Node<T>* delptr = NULL;
            while (temp != NULL) {
                delptr = temp;
                temp = temp->next;
                delete delptr;
            }
            Head = NULL;
            Last = NULL;
        }
    }
    bool is_exist(T item) {
        Node<T>* temp = Head;
        while (temp != NULL) {
            if (temp->data == item) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    bool is_item_equal(T item, long long index) {
        long long cur = 0;
        Node<T>* temp = Head;
        while (temp != NULL && cur < index) {
            temp = temp->next;
            cur++;
        }
        if (temp != NULL && temp->data == item) {
            return true;
        }
        return false;
    }
    void remove_tail() {
        if (isEmpty())
            return;

        Node<T>* delptr = Last;
        if (Last->prev != NULL) {
            Last = Last->prev;
            Last->next = NULL;
        } else {
            Head = NULL;
            Last = NULL;
        }
        delete delptr;
    }

    void remove_Head() {

        if (isEmpty())
            return;

        Node<T>* delptr = Head;
        Head = Head->next;
        if (Head != NULL)
            Head->prev = NULL;
        delete delptr;
    }

    void remove_at_index(long long index) {
        if (isEmpty())
            return;
        if (index <= 0) {
            remove_Head();
            return;
        }
        if (index >= size()-1) {
            remove_tail();
            return;
        }

        long long cur = 0;
        Node<T>* temp = Head;

        while (temp != NULL && cur < index) {
            temp = temp->next;
            cur++;
        }

        if (temp == NULL)
            return; // index out of bounds

        Node<T>* delptr = temp;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete delptr;
    }
    T retrive_at(ll index){
        ll cur=0;
        Node<T>*temp=Head;
        if(index<=0){return temp->data;}
        while(temp->next !=NULL && cur<index){
            temp= temp->next;
            cur++;
        }
        return temp->data;
    }

    void replace_at(T newdata,ll index){
        ll cur=0;
        Node<T>*temp=Head;
        while(temp->next!=NULL&& cur<index){
            cur++;
            temp=temp->next;
        }
        temp->data=newdata;

    }
    void swap(T first_ele_index, T second_ele_index) {
        if (isEmpty()) return;

        Node<T>* temp1 = Head;
        Node<T>* temp2 = Head;

        ll cur = 0;
        while (temp1 != nullptr && cur < first_ele_index) {
            temp1 = temp1->next;
            cur++;
        }
        cur = 0;
        while (temp2 != nullptr && cur < second_ele_index) {
            temp2 = temp2->next;
            cur++;
        }

        if (temp1 == nullptr || temp2 == nullptr) return;

        if (temp1->prev != nullptr) temp1->prev->next = temp2;
        else Head = temp2;

        if (temp2->prev != nullptr) temp2->prev->next = temp1;
        else Head = temp1;

        Node<T>* temp = temp1->next;
        temp1->next = temp2->next;
        temp2->next = temp;
        temp = temp1->prev;
        temp1->prev = temp2->prev;
        temp2->prev = temp;
    }

};

int main() {
    double_linkedList<int> myList;
    double_linkedList<string> myList_string;

    // Appending elements to the list
    myList.append_at_tail(10);
    myList.replace_at(333,0);
    // Printing the list
    cout << "List after appending elements: ";
    myList.print();
    myList.append_at_tail(30);
    myList.append_at_tail(30);
    myList.append_at_tail(35);
    myList.append_at_tail(36);
    myList.append_at_tail(30);
    myList.remove_at_index(5);
    myList.replace_at(333,0);
    // Printing the list
    myList.append_at_tail(20);
    myList.append_at_tail(44);
    myList.append_at_tail(22);
    myList.swap(2,5);

    cout << "List after appending elements: ";
    myList.print(); // Output: 10 20 30
//    cout<<myList.retrive_at(7)<<'\n';

    return 0;
}
