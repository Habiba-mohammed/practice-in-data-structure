#include <bits/stdc++.h>
using namespace std;

bool namesort=true;
int num;

class item {
    string itemname;
    string category;
    int price;
public:
    item() : itemname(""), category(""), price(0) {}
    item(string name, string cat, int p) : itemname(name), category(cat), price(p) {}

    string getItemName() const {
        return itemname;
    }

    string getCategory() const {
        return category;
    }

    int getPrice() const {
        return price;
    }

    bool operator<(const item& other) const {
        if(namesort)
            return itemname < other.itemname;
        else return price < other.price;
    }

    bool operator>(const item& other) const {
        if(namesort)
            return itemname > other.itemname;
        else return price > other.price;
    }

    bool operator<=(const item& other) const {
        if(namesort)
            return itemname <= other.itemname;
        else return price <= other.price;
    }

    bool operator>=(const item& other) const {
        if(namesort)
            return itemname >= other.itemname;
        else return price >= other.price;
    }

    bool operator==(const item& other) const {
        if(namesort)
            return itemname == other.itemname;
        else return price == other.price;
    }

    void print() const {
        cout << "Name: " << itemname << ", Category: " << category << ", Price: " << price << endl;
    }

    friend ostream& operator<<(ostream& os, const item& itm){
        itm.print();
        return os;
    }
};

class Heap {
protected:
    item* harr;
    int capacity;
    int heap_size;

public:
    Heap(int cap) : capacity(cap), heap_size(0) {
        harr = new item[cap];
    }

    virtual ~Heap() {
        delete[] harr;
    }

    int parent(int i) const {
        return (i - 1) / 2;
    }

    int left(int i) const {
        return (2 * i + 1);
    }

    int right(int i) const {
        return (2 * i + 2);
    }

    void printArray() const {
        for (int i = 0; i < heap_size; i++) {
            cout << harr[i] << " ";
        }
        cout << endl;
    }

    void printArrayOpposite() const { //  to add the option aslm
        for (int i = heap_size-1; i >=0; i--) {
            cout << harr[i] << " ";
        }
        cout << endl;
    }

    virtual void insertelement(const item& k) = 0;
    virtual item removeelement() = 0;

};

class MinHeap : public Heap {
public:
    MinHeap(int cap) : Heap(cap) {}

    ~MinHeap() {}

    void MinHeapify(int index) {
        int l = left(index);
        int r = right(index);
        int smallest = index;
        if (l < heap_size && harr[l] < harr[index])
            smallest = l;
        if (r < heap_size && harr[r] < harr[smallest])
            smallest = r;
        if (smallest != index) {
            swap(harr[index], harr[smallest]);
            MinHeapify(smallest);
        }
    }

    void minHeapSort() {
        int original_size = heap_size; // Preserve the original heap size

        for (int i = heap_size / 2 - 1; i >= 0; i--)
            MinHeapify(i);

        for (int i = heap_size - 1; i > 0; i--) {
            swap(harr[0], harr[i]);
            heap_size--;
            MinHeapify(0);
        }
        heap_size = original_size;
//        printArray();
    }

    item removeelement() {
        if (heap_size <= 0) {
            cout << "\nUnderflow: No element to remove\n";
            return   item();
        }

        if (heap_size == 1) {
            heap_size--;
            return harr[0];
        }
        item del=harr[0];

        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);
        return del;
    }

    void insertelement(const item& k) override {
        if (heap_size == capacity) {
            cout << "\nOverflow: Could not insert Key\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        while (i != 0 && harr[parent(i)] > harr[i]) {
            swap(harr[i], harr[parent(i)]);
            i = parent(i);
        }
    }
};

class MaxHeap : public Heap {
public:
    MaxHeap(int cap) : Heap(cap) {}

    ~MaxHeap() {}

    void MaxHeapify(int index) {
        int l = left(index);
        int r = right(index);
        int largest = index;
        if (l < heap_size && harr[l] > harr[largest])
            largest = l;
        if (r < heap_size && harr[r] > harr[largest])
            largest = r;
        if (largest != index) {
            swap(harr[largest], harr[index]);
            MaxHeapify(largest);
        }
    }

    void maxHeapSort() {
        int original_size = heap_size; // Preserve the original heap size

        for (int i = heap_size / 2 - 1; i >= 0; i--)
            MaxHeapify(i);

        for (int i = heap_size - 1; i > 0; i--) {
            swap(harr[0], harr[i]);
            heap_size--;
            MaxHeapify(0);
        }
        heap_size = original_size;
//        printArray();
    }

    item removeelement() {
        if (heap_size <= 0) {
            cout << "\nUnderflow: No element to remove\n";
            return item();
        }

        if (heap_size == 1) {
            heap_size--;
            return harr[0];
        }
        item del= harr[0];

        harr[0] = harr[heap_size - 1];
        heap_size--;
        MaxHeapify(0);
        return del;
    }

    void insertelement(const item& k) override {
        if (heap_size == capacity) {
            cout << "\nOverflow: Could not insert Key\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        while (i != 0 && harr[parent(i)] < harr[i]) {
            swap(harr[i], harr[parent(i)]);
            i = parent(i);
        }
    }
};

void removeItemMin(MinHeap& minHeap,vector<item>& items) {

    item del;
    del=minHeap.removeelement();
//    maxHeap.removeelement();
    for(auto it = items.begin(); it != items.end(); ) {
        if(it->getItemName() == del.getItemName() && it->getPrice() == del.getPrice() && it->getCategory() == del.getCategory())
        {
            it = items.erase(it);
            break;
        }
        else ++it;

    }

}
void removeItemMax(MaxHeap& maxHeap,vector<item>&items) {

    item del;
    del=maxHeap.removeelement();

    for(auto it = items.begin(); it != items.end(); ) {
        if(it->getItemName() == del.getItemName() && it->getPrice() == del.getPrice() && it->getCategory() == del.getCategory())
        {
            it = items.erase(it);
            break;
        }
        else ++it;

    }
}



struct node {
    item info;
    node *left;
    node *right;
};

class BST {
private:
    node *root;

public:
    BST() {
        root = nullptr;
    }

    bool is_empty() { return root == nullptr; }

    void insert(item data) {
        root = insertHelper(root, data);
    }

    bool search(item data) {
        return searchHelper(root, data);
    }



    void printasc() {
        printascHelper(root);
        cout << endl;
    }

    void printdes() {
        printdesHelper(root);
        cout << endl;
    }


    void remove(item data) {
        cout << "Removed this item: " << data << std::endl;
        root = removeHelper(root, data);
    }

private:
    node*insertHelper(node *curr, item data) {
        if (curr == nullptr) {
            node *newnode=new node;
            newnode->info = data;
            newnode->left = nullptr;
            newnode->right = nullptr;
            return newnode;
        } else if (data > curr->info)
            curr->right = insertHelper(curr->right, data);
        else
            curr->left = insertHelper(curr->left, data);
        return curr;
    }

    bool searchHelper(node *curr, item data) {
        if (curr == nullptr) return false;
        if (curr->info == data) return true;
        if (curr->info < data) return searchHelper(curr->right, data);
        return searchHelper(curr->left, data);
    }

    void printascHelper(node *curr) {
        if (curr == nullptr) return;
        printascHelper(curr->left);
        cout << curr->info << " ";
        printascHelper(curr->right);
    }

    void printdesHelper(node *curr) {
        if (curr == nullptr) return;
        printdesHelper(curr->right);
        cout << curr->info << " ";
        printdesHelper(curr->left);
    }

    node *removeHelper(node *curr, item data) {
        if (curr == nullptr) return curr;
        else if (data < curr->info) curr->left = removeHelper(curr->left, data);
        else if (data > curr->info) curr->right = removeHelper(curr->right, data);
        else { // found the element !! 3 cases
            // Case 1: No child
            if (curr->right == nullptr && curr->left == nullptr) {
                delete curr;
                curr = nullptr;
            }
                // Case 2: One child
            else if (curr->left == nullptr) {
                node *temp = curr;
                curr = curr->right;
                delete temp;
            } else if (curr->right == nullptr) {
                node *temp = curr;
                curr = curr->left;
                delete temp;
            }
                // Case 3: 2 children
            else {
                node *maxLeftSub = curr->left; // guranteed to exist and not be null cuz 2 children exist for curr !!
                while (maxLeftSub->right != nullptr) {
                    maxLeftSub = maxLeftSub->right;
                }
                curr->info = maxLeftSub->info;
                curr->left = removeHelper(curr->left, curr->info);
            }
        }
        return curr;
    }



};




struct Node {
    item info;
    int height;
    Node *left;
    Node *right;
    Node(item data) : info(data), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
private:
    Node *root;

public:
    AVL() {
        root = nullptr;
    }

    bool is_empty() { return root == nullptr; }

    void insert(item data) {
        root = insertHelper(root, data);
    }

    bool search(item data) {
        return searchHelper(root, data);
    }

    void printasc() {
        printascHelper(root);
        cout << endl;
    }

    void printdes() {
        printdesHelper(root);
        cout << endl;
    }

    void remove(item data) {
//        cout << "Removed this item: " << data << std::endl;
        removeHelper(root, data);
    }

private:
    int height(Node *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int getBalance(Node *N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* rightRotate(Node *C) {
        Node *B = C->left;
        Node *T2 = B->right;

        B->right = C;
        C->left = T2;

        C->height = max(height(C->left), height(C->right)) + 1;
        B->height = max(height(B->left), height(B->right)) + 1;

        return B;
    }

    Node* leftRotate(Node *A) {
        Node *B = A->right;
        Node *T2 = B->left;

        B->left = A;
        A->right = T2;

        A->height = max(height(A->left), height(A->right)) + 1;
        B->height = max(height(B->left), height(B->right)) + 1;

        return B;
    }

    // height of a leaf = 1 , so height of a node = number of nodes including it longest path
    Node* insertHelper(Node *Node, item data) {
        if (Node == nullptr)
            return(new struct Node(data));

        if (data <= Node->info)
            Node->left = insertHelper(Node->left, data);

        else if (data > Node->info)
            Node->right = insertHelper(Node->right, data);

        Node->height = max(height(Node->left), height(Node->right));


        int balance = getBalance(Node);

        if (balance > 1 && data < Node->left->info)
            return rightRotate(Node);

        if (balance < -1 && data > Node->right->info)
            return leftRotate(Node);

        if (balance > 1 && data > Node->left->info) {
            Node->left = leftRotate(Node->left);
            return rightRotate(Node);
        }

        if (balance < -1 && data < Node->right->info) {
            Node->right = rightRotate(Node->right);
            return leftRotate(Node);
        }

        return Node;
    }

    bool searchHelper(Node *curr, item data) {
        if (curr == nullptr) return false;
        if (curr->info == data) return true;
        if (curr->info < data) return searchHelper(curr->right, data);
        return searchHelper(curr->left, data);
    }

    void printascHelper(Node *curr) {
        if (curr == nullptr) return;
        printascHelper(curr->left);
        cout << curr->info << " ";
        printascHelper(curr->right);
    }

    void printdesHelper(Node *curr) {
        if (curr == nullptr) return;
        printdesHelper(curr->right);
        cout << curr->info << " ";
        printdesHelper(curr->left);
    }

    Node* minValueNode(Node* Node) {
        struct Node* current = Node;
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node* removeHelper(Node* curr, item data) {
        if (curr == nullptr)
            return curr;

        if (data < curr->info)
            curr->left = removeHelper(curr->left, data);

        else if(data > curr->info)
            curr->right = removeHelper(curr->right, data);

        else {
            if((curr->left == nullptr) || (curr->right == nullptr)) {
                Node *temp = curr->left ? curr->left : curr->right;

                if (temp == nullptr) {
                    temp = curr;
                    curr = nullptr;
                } else
                    *curr = *temp;

                delete temp;
            } else {
                Node* temp = minValueNode(curr->right);
                curr->info = temp->info;
                curr->right = removeHelper(curr->right, temp->info);
            }
        }

        if (curr == nullptr)
            return curr;

        curr->height = 1 + max(height(curr->left), height(curr->right));

        int balance = getBalance(curr);

        if (balance > 1 && getBalance(curr->left) >= 0)
            return rightRotate(curr);

        if (balance > 1 && getBalance(curr->left) < 0) {
            root->left = leftRotate(curr->left);
            return rightRotate(curr);
        }

        if (balance < -1 && getBalance(curr->right) <= 0)
            return leftRotate(curr);

        if (balance < -1 && getBalance(curr->right) > 0) {
            root->right = rightRotate(curr->right);
            return leftRotate(curr);
        }

        return curr;
    }
};

void delitem(vector<item>&items, AVL &avlPrices, AVL &avlNames, BST &prices, BST &names) {
    string name, category; int price;
    cout << "Please enter the item's data :-\n";
    cout << "Name: "; cin >> name; cout << "\n";
    cout << "Category: "; cin >> category; cout << "\n";
    cout << "Price: "; cin >> price; cout << "\n";

    for(auto it = items.begin(); it != items.end(); ) {
        if(it->getItemName() == name && it->getPrice() == price && it->getCategory() == category) {
            it = items.erase(it);
            break;
        } else ++it;
    }
    item i = item(name, category, price);
    avlNames.remove(i);
    names.remove(i);
    namesort = false;
    avlPrices.remove(i);
    prices.remove(i);
    namesort = true;
}

void additem(vector<item>&items, AVL &avlPrices, AVL &avlNames, MinHeap& minHeap, MaxHeap& maxHeap, BST &prices, BST &names) {
    string name, category; int price;
    cout << "Please enter the item's data :-\n";
    cout << "Name: "; cin >> name;
    cout << "Category: "; cin >> category;
    cout << "Price: "; cin >> price;

    item i = item(name, category, price);
    items.push_back(i);
    avlNames.insert(i);
    minHeap.insertelement(i);
    maxHeap.insertelement(i);
    names.insert(i);
    namesort = false;
    avlPrices.insert(i);
    prices.insert(i);
    namesort = true;
}


void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1- Add item data\n";
    cout << "2- Remove item data\n";
    cout << "3- Display the item data normally\n";
    cout << "4- Display all the items sorted by their name ascending\n";
    cout << "5- Display all the items sorted by their name descending\n";
    cout << "6- Display all the items sorted by their prices ascending\n";
    cout << "7- Display all the items sorted by their prices descending\n";
    cout << "8- Quit\n";
    cout << "Enter your choice: ";
}

int main() {
    BST prices, names;
    AVL avlPrices, avlNames;
    MinHeap minHeap(100);
    MaxHeap maxHeap(100);
    vector<item> items;
    ifstream ifile;
    ifile.open("item.txt");
    ifile >> num;
    ifile.ignore();
    string name, category;
    int price;
    for (int i = 0; i < num; ++i) {
        getline(ifile, name);
        getline(ifile, category);
        ifile >> price;
        ifile.ignore();
        item it = item(name, category, price);
        items.emplace_back(it);
        avlNames.insert(it);
        minHeap.insertelement(it);
        maxHeap.insertelement(it);
        names.insert(it);
        namesort = false;
        avlPrices.insert(it);
        prices.insert(it);
        namesort = true;
    }

    int choiceApp, choiceHeap = 5;
    cout << "Welcome to our Item app ^_^\n"
            "Choose the data structure that you want to deal with:\n"
            "1) Binary Search Tree\n"
            "2) Heap Sort\n"
            "3) AVL Tree\n";

    cin >> choiceApp;
    if (choiceApp == 2){
        cout << "1) Max Heap\n"
                "2) Min Heap\n";
        cin >> choiceHeap;
        choiceHeap--;
    }

    displayMenu();
    int choice; cin >> choice;
    while(choice != 8) {
        switch (choice) {
            case 1:
                additem(items, avlPrices, avlNames, minHeap, maxHeap, prices, names);
                break;
            case 2:
                (choiceApp == 1 || choiceApp == 3)? delitem(items, avlPrices, avlNames, prices, names) : (choiceApp == 2 && choiceHeap)? removeItemMin(minHeap, items) :  removeItemMax(maxHeap, items);;
                break;
            case 3:
                for(auto &item: items) item.print();
                break;
            case 4:
                (choiceApp == 1)? names.printasc() : (choiceApp == 3)? avlNames.printasc() : (choiceApp == 2 && choiceHeap)? (minHeap.minHeapSort(), minHeap.printArrayOpposite()) :  (maxHeap.maxHeapSort(), maxHeap.printArray());
                break;
            case 5:
                (choiceApp == 1)? names.printdes() : (choiceApp == 3)? avlNames.printdes() : (choiceApp == 2 && choiceHeap)? (minHeap.minHeapSort(), minHeap.printArray()) :  (maxHeap.maxHeapSort(), maxHeap.printArrayOpposite());
                break;
            case 6:
                namesort = false;
                (choiceApp == 1)? prices.printasc() : (choiceApp == 3)? avlPrices.printasc() : (choiceApp == 2 && choiceHeap)?  (minHeap.minHeapSort(), minHeap.printArrayOpposite()) :  (maxHeap.maxHeapSort(), maxHeap.printArray());
                namesort = true;
                break;
            case 7:
                namesort = false;
                (choiceApp == 1)? prices.printdes() : (choiceApp == 3)? avlPrices.printdes() : (choiceApp == 2 && choiceHeap)?  (minHeap.minHeapSort(), minHeap.printArray()) : (maxHeap.maxHeapSort(), maxHeap.printArrayOpposite());
                namesort = true;
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        displayMenu();
        cin >> choice;
    }
    return 0;
}

