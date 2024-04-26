#include <iostream>
using namespace std;

#define ll long long

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

template<typename T>
class CLL_D {
private:
    Node<T>* tail;

public:
    CLL_D() : tail(nullptr) {}

    bool is_empty() {
        return tail == nullptr;
    }

    void insertAtTail(T newitem) { //done
        Node<T>* newNode = new Node<T>(newitem);
        if (tail == nullptr) {
            tail = newNode;
            tail->next = tail;
            tail->prev = tail;
            return;
        }

        newNode->next = tail->next;
        newNode->prev = tail;
        tail->next->prev = newNode;
        tail->next = newNode;
        tail = newNode;

    }

    void insertAtHead(T newitem) { //done
        if(tail==nullptr) {insertAtTail(newitem);return;}
        Node<T>* newNode = new Node<T>(newitem);

        newNode->next = tail->next;
        newNode->prev = tail;
        tail->next->prev = newNode;
        tail->next = newNode;

    }

    void removeAtTail() { //done
        if(is_empty()) {cout<<"list is empty!\n";return;}

        Node<T>* temp = tail;
        if (tail->next == tail) {
            tail = nullptr;
        } else {
            tail->prev->next = tail->next;
            tail->next->prev = tail->prev;
            tail = tail->prev;
        }
        delete temp; // points to old tail ( useless )

    }

    void removeAtHead() { //done
        if(is_empty()) {cout<<"list is empty!\n";return;}

        Node<T>* temp = tail;
        if (tail->next == tail) {
            tail = nullptr;
            return;
        }
        Node <T> *delptr=tail->next;
        tail->next = tail->next->next;
        tail->next->next->prev = tail;

        delete delptr;
    }

    void print() { //done
        if (tail == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node<T>* current = tail->next;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != tail->next);
        cout << endl;
    }


    void clear() { //done
        if (tail == nullptr) {
            return; // List is already empty
        }

        Node<T> *current = tail->next; // Start from the first node

        do {
            Node<T> *delptr = current;
            current = current->next;
            delete delptr; // points to current , so anything that points to current ,gets deleted (even new current.previous)
        } while (current != tail); // Continue until we circle back to the start
        // cout<<tail->prev->data; //garbage --> deleted ! :D
        tail = nullptr; // Reset the tail pointer
    }

    int size() { //done
        int count = 0;
        if (tail != nullptr) {
            Node<T>* current = tail->next;
            do {
                count++;
                current = current->next;
            } while (current != tail->next);
        }
        return count;
    }

    bool isItemAtEqual(T item, int idx){
        T temp=this->retrieveAt(idx);
        return (temp==item);
    }

    bool isExist(T item){
        if(tail->data == item) return true;

        Node<T> *temp=tail->next->next;
        while(temp!=tail->next && temp->data!=item){
            temp=temp->next;
        }
        return (temp->data==item);
    }

    T retrieveAt(int idx){

        if (is_empty()) {
            cout << "list is empty!\n";
            return T();
        }
        if (idx >= size()) {
            cout << "is not found this index in my list\n";
            return T();
        }


        Node <T>* temp=tail->next;
        ll curr_index=0;
        while(curr_index < idx ){
            temp=temp->next;
            curr_index++;
        }
        return temp->data;
    }
    void replaceAt(T item, int idx){ //zero based
        if (is_empty()) {
            cout << "list is empty!\n";
            return;
        }
        if (idx >= size()) {
            cout << "is not found this index in my list\n";
            return;
        }

        Node<T> *temp = tail->next;
        ll currindex = 0;
        while (currindex < idx) {
            temp = temp->next;
            currindex++;
        }
        temp->data = item;
    }

    void insertAt(T item, int idx){
        Node<T>* newnode= new Node<T>(item);

        if (is_empty()) {
            cout << "list is empty!\n";
            return;
        }
        if (idx >= size()) {
            cout << "is not found this index in my list\n";
            return;
        }

        if (idx == 0) {
            insertAtHead(item);
            return;
        }
        Node<T> *temp = tail->next->next; //second element
        Node<T> *Pre =tail->next; //head
        ll currindex = 1;
        while (currindex < idx) {
            Pre=temp;
            temp = temp->next;
            currindex++;
        }
        Pre->next=newnode;
        newnode->next=temp;
        newnode->prev=Pre;
        temp->prev=temp;


    }

        void removeAt(int idx){
            if (is_empty()) {
                cout << "list is empty!\n";
                return;
            }
            if (idx >= size()) {
                cout << "is not found this index in my list\n";
                return;
            }
            if(idx==0) {removeAtHead();return;}
            if(idx==size()-1){removeAtTail();return;}

            Node<T>*pre,*temp;
            pre=tail->next;
            temp=tail->next->next;

            ll curr_index=1;

            while(curr_index<idx ){
                pre=temp;
                temp=temp->next;
                curr_index++;
            }
            pre->next=temp->next;
            temp->next->prev=pre;
            delete temp;
        }


    void swap(int idx1, int idx2) {
        if (is_empty() || idx1 < 0 || idx2 < 0 || idx1 >= size() || idx2 >= size()) {
            std::cout << "Invalid indices or empty list.\n";
            return;
        }

        if (idx1 == idx2) {
            return;
        }

        // Ensure idx1 is less than idx2 for easier processing
        if (idx1 > idx2)
            std::swap(idx1, idx2);

        Node<T> *prev1 = tail, *curr1 = tail->next, *prev2 = nullptr, *curr2 = nullptr;

        // Locate the nodes at idx1 and idx2
        Node<T> *temp = tail->next; // Start from the head (tail->next)
        int i = 0;
        while (i <= idx2) {
            if (i == idx1 - 1) {
                prev1 = temp;
                curr1 = temp->next;
            }
            if (i == idx2 - 1) {
                prev2 = temp;
                curr2 = temp->next;
            }

            temp = temp->next;
            ++i;
        }

        // Swap nodes
        if (curr1->next == curr2) {
            // Nodes are adjacent
            prev1->next = curr2;
            curr2->prev=prev1;

            curr1->next = curr2->next;
            curr2->next = curr1;

            curr1->prev=curr2;
            curr1->next->prev=curr1;

        } else if (curr2->next == curr1) {
            // Nodes are adjacent but in reverse order
            prev2->next = curr1;
            curr1->prev=prev2;

            curr2->next = curr1->next;
            curr1->next->prev = curr2;

            curr2->prev=curr1;
            curr1->next=curr2;
        } else {
            // Nodes are not adjacent
            Node<T> *after1=curr1->next,*after2=curr2->next;
            prev1->next = curr2;
            curr2->prev=prev1;


            curr1->next = curr2->next;
            curr2->next->prev=curr1;


            prev2->next = curr1;
            curr1->prev=prev2;

            curr2->next=after1;
            after1->prev=curr1;


        }

        // Update tail pointer if necessary
        if (tail == curr1)  tail = curr2;
        else if (tail == curr2) tail = curr1;

        temp=nullptr;

    }




    ~CLL_D() {
        while (!is_empty()) {
            removeAtTail();
        }
    }
};

int main() {
    // Test cases for Doubly Circular Linked List

//    CLL_D<int> myCLL;
//
//    // Insert elements
//    myCLL.insertAtTail(10);
//    myCLL.insertAtTail(20);
//    myCLL.insertAtTail(30);
//    myCLL.insertAtTail(40);
//
//    // Print the list
//    cout << "Current list: ";
//    myCLL.print(); // Output: 10 20 30 40
//
//    // Insert at head
//    myCLL.insertAtHead(5);
//    cout << "After inserting at head: ";
//    myCLL.print(); // Output: 5 10 20 30 40
//
//    // Remove from tail
//    myCLL.removeAtTail();
//    cout << "After removing from tail: ";
//    myCLL.print(); // Output: 5 10 20 30
//
//    // Remove from head
//    myCLL.removeAtHead();
//    cout << "After removing from head: ";
//    myCLL.print(); // Output: 10 20 30
//
//    // Display size of the list
//    cout << "Size of the list: " << myCLL.size() << endl; // Output: 3
//    myCLL.insertAt(15,1);
//    myCLL.insertAt(25,3);
//    myCLL.insertAt(5,0);
//    myCLL.insertAtTail(55500);
//    myCLL.print();
//    myCLL.removeAt(myCLL.size()-1);
//    myCLL.print();
//    myCLL.removeAt(2);
//    myCLL.print();
//    myCLL.clear();
//    myCLL.print();
////    cout<<myCLL.size();
//    return 0;

    CLL_D <int> s;
s.insertAtTail(5);
s.insertAtHead(4);
s.insertAt(3,0);
s.print();
s.swap(0,1);
s.print();
s.swap(1,2);
s.print();
s.removeAtTail();
s.print();
s.swap(0,1);
s.print();
s.removeAtHead();
s.swap(0,0);
s.print();
}
