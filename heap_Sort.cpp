#include <iostream>
#include <string>
#include <stdexcept>

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

    virtual void insertelement(const Item& k) = 0;
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
    }

    void removeelement() {
        if (heap_size <= 0) {
            cout << "\nUnderflow: No element to remove\n";
            return;
        }

        if (heap_size == 1) {
            heap_size--;
            return;
        }

        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);
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
   }

    void removeelement() {
        if (heap_size <= 0) {
            cout << "\nUnderflow: No element to remove\n";
            return;
        }

        if (heap_size == 1) {
            heap_size--;
            return;
        }

        harr[0] = harr[heap_size - 1];
        heap_size--;
        MaxHeapify(0);
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

int main() {
    // Create some items
    namesort=false;
    Item item7("Eglant", "Vegetable", 777);
    Item item9("Eant", "Vegetable", 4);
    Item item1("Apple", "Fruit", 50);
    Item item2("Banana", "Fruit", 30);
    Item item3("Carrot", "Vegetable", 20);
    Item item4("Dates", "DryFruit", 70);
    Item item5("Eggplant", "Vegetable", 40);

    // Create a MinHeap
    MinHeap minHeap(10);

    // Insert items into MinHeap
    minHeap.insertelement(item1);
    minHeap.insertelement(item2);
    minHeap.insertelement(item3);
    minHeap.insertelement(item4);
    minHeap.insertelement(item5);

    // Print MinHeap
    cout << "MinHeap:" << endl;
   minHeap.printArray();

//    // Sort MinHeap
    minHeap.minHeapSort();
    cout << "Sorted MinHeap:" << endl;
    minHeap.printArray();
//
/////////////////////////////////////////////////////////////////////////////
   //  Create a MaxHeap
    MaxHeap maxHeap(10);

    // Insert items into MaxHeap
    maxHeap.insertelement(item1);
    maxHeap.insertelement(item2);
    maxHeap.insertelement(item3);
    maxHeap.insertelement(item4);
    maxHeap.insertelement(item5);
    maxHeap.insertelement(item7);
    maxHeap.insertelement(item9);



    // Print MaxHeap
    cout << "MaxHeap:" << endl;
    maxHeap.printArray();
    maxHeap.maxHeapSort();
    maxHeap.printArray();

}
