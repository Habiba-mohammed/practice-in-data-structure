 
#include <iostream>
#define ll long long
using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;
};

template<typename T>
class LinkedList {
public:
    Node<T> *Head;

    LinkedList() {
        Head = nullptr;
    }

    bool is_empty() {
        return (Head == nullptr);
    }

    void insert_first(T newitem) {
        Node<T> *newnode = new Node<T>();
        newnode->data = newitem;

        if (is_empty()) {
            newnode->next = nullptr;
            Head = newnode;
        } else {
            newnode->next = Head;
            Head = newnode;
        }
    }

    void print() {
        Node<T> *temp = Head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    ll size() {
        ll count = 0;
        Node<T> *temp = Head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    bool is_found(T item) {
        Node<T> *temp = Head;
        while (temp != nullptr) {
            if (temp->data == item)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void insert_before(T current, T newitem) {
        if (is_empty()) {
            cout << "List is empty\n";
            return;
        }
        if (!is_found(current)) {
            cout << "Current item not found in the list\n";
            return;
        }

        Node<T> *newnode = new Node<T>();
        newnode->data = newitem;

        if (Head->data == current) {
            newnode->next = Head;
            Head = newnode;
            return;
        }

        Node<T> *temp = Head;
        while (temp->next != nullptr && temp->next->data != current) {
            temp = temp->next;
        }

        newnode->next = temp->next;
        temp->next = newnode;
    }

    void insert_before_index(T item, ll index) {
        ll cur_index = 0;
        if (index > size()) return;
        Node<T> *temp = Head;
        Node<T> *prev = nullptr;
        Node<T> *newnode = new Node<T>();
        newnode->data = item;
        if (index < 1) {
            newnode->next = Head;
            Head = newnode;
            return;
        }
        while (temp->next != nullptr && cur_index < index) {
            prev = temp;
            temp = temp->next;
            cur_index++;
        }
        prev->next = newnode;
        newnode->next = temp;
    }

    void append(T newitem) {
        if (is_empty()) {
            insert_first(newitem);
        } else {
            Node<T> *newnode = new Node<T>();
            newnode->data = newitem;
            Node<T> *temp = Head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->next = nullptr;
        }
    }

    void delete_item(T itemdelete) {
        if (is_empty()) {
            cout << "This list is empty\n";
            return;
        }
        Node<T> *delptr = Head;
        if (Head->data == itemdelete) {
            Head = Head->next;
        } else {
            Node<T> *prvptr = nullptr;
            while (delptr != nullptr && delptr->data != itemdelete) {
                prvptr = delptr;
                delptr = delptr->next;
            }
            if (delptr != nullptr) {
                prvptr->next = delptr->next;
                delete delptr;
            } else {
                cout << "Item not found in the list\n";
            }
        }
    }

    bool iselement_equal(T element, ll index) {
        if (is_empty()) {
            cout << "This list is empty\n";
            return false;
        }
        Node<T> *temp = Head;
        ll curindex = 0;
        while (temp != nullptr) {
            if (temp->data == element && curindex == index) {
                return true;
            }
            temp = temp->next;
            curindex++;
        }
        return false;
    }

    void return_index(T item) {
        if (is_empty() || !is_found(item)) {
            cout << "This element is not exist\n";
            return;
        }
        Node<T> *temp = Head;
        ll index = 0;
        while (temp != nullptr) {
            if (temp->data == item) {
                cout << index;
                return;
            }
            temp = temp->next;
            index++;
        }
    }

    void clear() {
        Node<T> *temp = Head;
        Node<T> *delptr = nullptr;
        while (temp != nullptr) {
            delptr = temp;
            temp = temp->next;
            delete delptr;
        }
        Head = nullptr;
    }

    void replaceAt(T current_item, ll index) {
        if (is_empty()) {
            cout << "This list is empty\n";
            return;
        }
        if (index < 1) {
            Head->data = current_item;
            return;
        }
        Node<T> *temp = Head;
        ll currindex = 0;
        while (temp->next != nullptr && currindex < index) {
            temp = temp->next;
            currindex++;
        }
        temp->data = current_item;
    }

    void swap(ll first_index, ll second_index) {
        if (first_index == second_index || first_index >= size() || second_index >= size()) return;
        Node<T> *temp1 = Head;
        Node<T> *pre1 = nullptr;
        Node<T> *temp2 = Head;
        Node<T> *pre2 = nullptr;

        // Traverse to the nodes to be swapped
        for (ll index = 0; temp1 != nullptr && index < first_index; ++index) {
            pre1 = temp1;
            temp1 = temp1->next;
        }
        for (ll index = 0; temp2 != nullptr && index < second_index; ++index) {
            pre2 = temp2;
            temp2 = temp2->next;
        }
        if (pre1 != nullptr)
            pre1->next = temp2;
        else
            Head = temp2;
        if (pre2 != nullptr)
            pre2->next = temp1;
        else
            Head = temp1;

        // Swap the next pointers of the nodes being swapped
        Node<T> *temp = temp1->next;
        temp1->next = temp2->next;
        temp2->next = temp;
    }

    void delete_byindex(ll index) {
        if (is_empty()) {
            cout << "my list is empty\n";
            return;
        }
        if (index >= size()) {
            cout << "is not found this index in my list\n";
            return;
        }
        Node<T> *temp = Head;
        Node<T> *delptr = nullptr;
        Node<T> *pre = nullptr;

        ll cur = 0;
        if (index < 1) {
            delptr = Head;
            Head = Head->next;
            delete delptr;
            return;
        }
        while (temp->next != nullptr && cur < index) {
            pre = temp;
            cur++;
            temp = temp->next;
        }
        if (temp != nullptr) {
            delptr = temp;
            pre->next = temp->next;
            delete delptr;
        }
    }
    T retrieveAt(int index) {
        if (is_empty()) {
            return T();
        }

        if (index < 0 || index >= size()) {
            return T();
        }

        Node<T> *temp = Head;
        int currentIndex = 0;
        while (currentIndex < index && temp->next != nullptr) {
            temp = temp->next;
            currentIndex++;
        }

        return temp->data;
    }
};
int main() {
    LinkedList<int> intList;

    // Inserting integer elements at the beginning of the list
    intList.append(6);
    intList.append(50);
    intList.append(7);
    intList.append(8);
    intList.append(9);
    cout << "Integer List:\n";
    intList.print();
    cout << '\n';
    cout << '\n';

    // Test with string data type
    LinkedList<string> strList;

    // Inserting string elements at the beginning of the list
     strList.insert_first("whynot?");
    strList.insert_first("thing");

    strList.insert_first("any");

    strList.insert_first("do");

    strList.insert_first("can");

    strList.insert_first("I");

    cout << "String List:\n";
    strList.print();
    cout << '\n';
    strList.swap(0,strList.size());
    strList.retrieveAt(4);

 }



