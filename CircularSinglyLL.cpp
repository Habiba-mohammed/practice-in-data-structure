#include <iostream>
#define ll long long
using namespace std;

// problems of linked list , can't access randomly

template<typename T>
class Node {
public:
    T data;
    Node* next;
//    Node* pre;
};

template<typename T>
class CLL_S {
private:
    Node<T> *tail; // better to be tail than head to insert at tail or head in o(1) time; ( head would take o(n) to insert at tail )
public:
    CLL_S() {
        tail = nullptr;
    }

    bool is_empty() {
        return (tail == nullptr);
    }


    void insertAtTail(T newitem) {
        Node<T> *newnode = new Node<T>(); // Create a new node
        newnode->data = newitem;           // Set data for the new node

        if (is_empty()) {
            // If the list is empty, make the new node the only node
            newnode->next = newnode;
            tail = newnode;
            return;
        }
        newnode->next = tail->next; // head
        tail->next = newnode;
        tail=newnode;

    }

    void insertAtHead(T newitem){
        Node<T> *newnode = new Node<T>();
        newnode->data = newitem;

        if (is_empty()) {
            insertAtTail(newitem);
            return;
        }
        newnode->next = tail->next; // head
        tail->next = newnode;


    }
    void insertAt(T item, int idx){ //zero based
        Node<T>* newnode= new Node<T>();
        newnode->data=item;

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
        while (temp->next != tail->next && currindex < idx) {
            Pre=temp;
            temp = temp->next;
            currindex++;
        }
        Pre->next=newnode;
        newnode->next=temp;
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
        }
        pre->next=temp->next;

    }

    void removeAtHead(){
        if(is_empty()) {cout<<"list is empty!\n";return;}
        Node<T> *delptr=tail->next;
        tail->next=tail->next->next;
        delete delptr;
    }

    void removeAtTail(){
        if(is_empty()) {cout<<"list is empty!\n";return;}

        Node<T> *pre,*temp;
        pre=tail->next;
        temp=tail->next->next;

        while(temp!=tail){
            pre=temp;
            temp=temp->next;
        }
        pre->next=temp->next;
        tail=pre;
        delete temp;
    }



    void print() {
        if (is_empty()) {
            cout << "List is empty!" << endl;
            return;
        }

        Node<T> *temp = tail->next;
        cout<<temp->data<<" ";
        temp=temp->next;

        while (temp != tail->next) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << "\n";
    }
    int size(){
        Node<T> *temp=tail->next->next;
        int cnt=1;
        while(temp!=tail->next){
            temp=temp->next;
            cnt++;
        }
        return cnt;
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

    bool isExist(T item){
        if(tail->data == item) return true;

        Node<T> *temp=tail->next->next;
        while(temp!=tail->next && temp->data!=item){
            temp=temp->next;
        }
        return (temp->data==item);
    }

    bool isItemAtEqual(T item, int idx){
        T temp=this->retrieveAt(idx);
        return (temp==item);
    }
    void clear() {
        if (tail == nullptr) {
            return; // List is already empty
        }

        Node<T>* current = tail->next; // Start from the first node

        do {
            Node<T> *delptr=current;
            current=current->next;
            delete delptr;
        } while (current != tail); // Continue until we circle back to the start

        tail = nullptr; // Reset the tail pointer
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
            curr1->next = curr2->next;
            curr2->next = curr1;
        } else if (curr2->next == curr1) {
            // Nodes are adjacent but in reverse order
            prev2->next = curr1;
            curr2->next = curr1->next;
            curr1->next = curr2;
        } else {
            // Nodes are not adjacent
            prev1->next = curr2;
            Node<T> *tempNext1 = curr1->next;
            curr1->next = curr2->next;
            prev2->next = curr1;
            curr2->next = tempNext1;
        }

        // Update tail pointer if necessary
        if (tail == curr1)  tail = curr2;
        else if (tail == curr2) tail = curr1;

        temp=nullptr;

    }


};

int main(){
    CLL_S <int> k,kk,test;
    k.insertAtTail(0);k.insertAtTail(1);k.insertAtTail(2);k.insertAtTail(3);k.insertAtTail(4);k.insertAtTail(5);
    kk.insertAtHead(0);kk.insertAtHead(1);kk.insertAtHead(2);kk.insertAtHead(3);kk.insertAtHead(4);kk.insertAtHead(5);

    test.insertAtTail(5);
    test.insertAtTail(6);
    test.insertAtHead(4);



    k.print();
    kk.print();
    test.print();

    test.replaceAt(6,0);
    test.replaceAt(5,1);
    test.replaceAt(4,2);

    test.print();
    test.insertAt(7,0);
    test.insertAt(8,2);
    test.print(); //76854
    cout<<test.size()<<"\n";

//    test.removeAtHead();//6854
//    test.removeAtTail();//685
//    test.removeAt(1);//65

    test.print();
    cout<<test.retrieveAt(1)<<"\n";
    cout<<test.isExist(5)<<"\n";
    cout<<test.isItemAtEqual(5,1)<<"\n";
//    test.clear();
    test.print();

    test.swap(2,3); //76854 ->
    test.print();
//     test.insertAtTail(5);
//     test.insertAtTail(6);
//     test.insertAtHead(4);
//     test.print();
// //    test.clear();
//     test.removeAtTail();

// //cout<<"  ";
//     test.removeAtHead();
//     test.print();

     test.clear();
     test.removeAtHead();
     test.removeAtTail();
     test.removeAt(5);
     test.retrieveAt(5);
     test.insertAt(5,4);
     test.replaceAt(5,4);
     test.clear();
     test.insertAtTail(5);
     test.insertAtTail(2);
    test.insertAtTail(2);
    test.removeAt(2);
    test.insertAt(1,0) ;//152
    test.print();
    test.swap(0,test.size()-1);
    test.print();
    test.removeAtTail();
    test.removeAtTail();
test.print();

    test.clear();
kk.clear();
k.clear();




}
