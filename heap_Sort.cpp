#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

bool namesort = true;

class Item {
    string itemname;
    string category;
    int price;

public:
    Item() : itemname(""), category(""), price(0) {}
    Item(string name, string catagory, int p) : itemname(name), category(catagory), price(p) {}

    string getItemName() const {
        return itemname;
    }

    string getCategory() const {
        return category;
    }

    int getPrice() const {
        return price;
    }

    bool operator<(const Item& other) const {
        if (namesort)
            return itemname < other.itemname;
        return price < other.price;
    }

    bool operator>(const Item& other) const {
        if (namesort)
            return itemname > other.itemname;
        return price > other.price;
    }

    void print() const {
        cout << "Name: " << itemname << ", Category: " << category << ", Price: " << price << endl;
    }

    friend ostream& operator<<(ostream& os, const Item& itm) {
        itm.print();
        return os;
    }
};

class Heap {
protected:
    Item* harr;
    int capacity;
    int heap_size;

public:
    Heap(int cap) : capacity(cap), heap_size(0) {
        harr = new Item[cap];
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

    virtual void insertelement(const Item& k) = 0;
    virtual Item removeelement() = 0;

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

    Item removeelement() {
        if (heap_size <= 0) {
            cout << "\nUnderflow: No element to remove\n";
            return   Item();
        }

        if (heap_size == 1) {
            heap_size--;
            return harr[0];
        }
        Item del=harr[0];

        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);
        return del;
    }

    void insertelement(const Item& k) override {
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

    Item removeelement() {
        if (heap_size <= 0) {
            cout << "\nUnderflow: No element to remove\n";
            return Item();
        }

        if (heap_size == 1) {
            heap_size--;
            return harr[0];
        }
        Item del= harr[0];

        harr[0] = harr[heap_size - 1];
        heap_size--;
        MaxHeapify(0);
        return del;
    }

    void insertelement(const Item& k) override {
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



void addItemMin(vector<Item>& items, MinHeap& minHeap) {
    string name, category;
    int price;
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter item category: ";
    cin >> category;
    cout << "Enter item price: ";
    cin >> price;
    Item newItem(name, category, price);
    items.push_back(newItem);
    minHeap.insertelement(newItem);
//    maxHeap.insertelement(newItem);
}
void addItemMax(vector<Item>& items, MaxHeap& maxHeap) {
    string name, category;
    int price;
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter item category: ";
    cin >> category;
    cout << "Enter item price: ";
    cin >> price;
    Item newItem(name, category, price);
    items.push_back(newItem);
//    minHeap.insertelement(newItem);
    maxHeap.insertelement(newItem);
}



void removeItemMin(MinHeap& minHeap,vector<Item>& items,int ch) {
    if(ch==1) namesort=false;
    else namesort=true;

    Item del;
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
void removeItemMax(MaxHeap& maxHeap,vector<Item>&items, int ch) {
    if(ch==1) namesort=false;
    else namesort=true;

    Item del;
//    del=minHeap.removeelement();
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
void priceornames(){
    cout << "\nRemove type:\n";
    cout << "1- delete root by price \n";
    cout << "2- delete root by name \n";
    cout << "3- Quit\n";
}

void displayItems(const vector<Item>& items) {
    for (const auto& item : items) {
        item.print();
    }
}
int main() {
    vector<Item> items;
    MinHeap minHeap(100);
    MaxHeap maxHeap(100);

    int choice;
    cout << "\nHeap Type:\n";
    cout << "1- MinHeap ( when deleting the root , we delete the biggest element )\n";
    cout << "2- MaxHeap ( when deleting the root , we delete the smallest element )\n";
    cout << "3- Quit\n";

    cin>>choice;
    if(choice==3) return -1;

    if(choice==1){
        do {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1:
                    addItemMin(items, minHeap);
                    break;
                case 2:
                    if(true) {
                        priceornames();
                        int ch;
                        while(cin>>ch){
                            if(ch==3) return -1;
                            else if(ch!=1 && ch!=2) continue;
                            else break;
                        }
                        removeItemMin(minHeap, items,ch);
                        break;
                    }
                    break;
                case 3:
                    displayItems(items);
                    break;
                case 4:
                    namesort=true;
                    minHeap.minHeapSort();
                    minHeap.printArrayOpposite(); // ascending
                    break;

                case 5:
                    namesort=true;
                    minHeap.minHeapSort();
                    minHeap.printArray();
                    break;
                case 6:
                    namesort=false;
                    minHeap.minHeapSort();
                    minHeap.printArrayOpposite();// ascending
                    break;

                case 7:
                    namesort=false;
                    minHeap.minHeapSort();
                    minHeap.printArray(); //descinfing
                    break;
                case 8:
                    cout << "Exiting program.\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 8);
    }
    else if(choice==2){
        do {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1:
                    addItemMax(items, maxHeap);
                    break;
                case 2:
                    if(true) {
                        priceornames();
                        int ch;
                        while(cin>>ch){
                            if(ch==3) return -1;
                            else if(ch!=1 && ch!=2) continue;
                            else break;
                        }
                        removeItemMax(maxHeap, items,ch);
                    }
                    break;
                case 3:
                    displayItems(items);
                    break;
                case 4: //by name
                    namesort=true;
                    maxHeap.maxHeapSort();
                    maxHeap.printArray(); //ascending
                    break;

                case 5:
                    namesort=true;
                    maxHeap.maxHeapSort();
                    maxHeap.printArrayOpposite(); //descninding
                    break;
                case 6:
                    namesort=false; //price
                    maxHeap.maxHeapSort();
                    maxHeap.printArray();   //ascending
                case 7:
                    namesort=false; //price
                    maxHeap.maxHeapSort();
                    maxHeap.printArrayOpposite();   //ascending
                    break;
                case 8:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 8);
    }



    return 0;
}