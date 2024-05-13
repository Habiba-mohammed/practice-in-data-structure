#include <bits/stdc++.h>
using namespace std;

bool namesort=true;

class item
{
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
        else return price<other.price;
    }

    bool operator>(const item& other) const {
        if(namesort)
            return itemname > other.itemname;
        else return price>other.price;
    }

    bool operator<=(const item& other) const {
        if(namesort)
            return itemname <= other.itemname;
        else return price<=other.price;
    }

    bool operator>=(const item& other) const {
        if(namesort)
            return itemname >= other.itemname;
        else return price>=other.price;      }

    bool operator==(const item& other) const {
        if(namesort)
            return itemname == other.itemname;
        else return price==other.price;
    }

    void print() {
        cout << "Name: " << itemname << ", Category: " << category << ", Price: " << price << endl;
    }
    friend ostream& operator<<(ostream& os,  item& itm){
        itm.print();
        return os;
    }

};




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
        root = NULL;
    }

    bool is_empty() { return root == NULL; }

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
        if (curr == NULL) {
            node *newnode=new node;
            newnode->info = data;
            newnode->left = NULL;
            newnode->right = NULL;
            return newnode;
        } else if (data > curr->info)
            curr->right = insertHelper(curr->right, data);
        else
            curr->left = insertHelper(curr->left, data);
        return curr;
    }

    bool searchHelper(node *curr, item data) {
        if (curr == NULL) return false;
        if (curr->info == data) return true;
        if (curr->info < data) return searchHelper(curr->right, data);
        return searchHelper(curr->left, data);
    }

    void printascHelper(node *curr) {
        if (curr == NULL) return;
        printascHelper(curr->left);
        cout << curr->info << " ";
        printascHelper(curr->right);
    }
    void printdesHelper(node *curr) {
        if (curr == NULL) return;
        printdesHelper(curr->right);
        cout << curr->info << " ";
        printdesHelper(curr->left);
    }

    node *removeHelper(node *curr, item data) {
        if (curr == NULL) return curr;
        else if (data < curr->info) curr->left = removeHelper(curr->left, data);
        else if (data > curr->info) curr->right = removeHelper(curr->right, data);
        else { // found the element !! 3 cases
            // Case 1: No child
            if (curr->right == NULL && curr->left == NULL) {
                delete curr;
                curr = NULL;
            }
                // Case 2: One child
            else if (curr->left == NULL) {
                node *temp = curr;
                curr = curr->right;
                delete temp;
            } else if (curr->right == NULL) {
                node *temp = curr;
                curr = curr->left;
                delete temp;
            }
                // Case 3: 2 children
            else {
                node *maxLeftSub = curr->left; // guranteed to exist and not be null cuz 2 children exist for curr !!
                while (maxLeftSub->right != NULL) {
                    maxLeftSub = maxLeftSub->right;
                }
                curr->info = maxLeftSub->info;
                curr->left = removeHelper(curr->left, curr->info);
            }
        }
        return curr;
    }



};

void delitem(vector<item>&items,BST &prices,BST &names){
    string name,category; int price;
    cout<<"Please enter the item's data :-\n";
    cout<<"Name: "; cin>>name; cout<<"\n";
    cout<<"Category: "; cin>>category; cout<<"\n";
    cout<<"Price: "; cin>>price; cout<<"\n";

    for(auto it = items.begin(); it != items.end(); ) {
        if(it->getItemName() == name && it->getPrice() == price && it->getCategory() == category)
        {
            it = items.erase(it);
            break;
        }
        else ++it;

    }
    item i= item(name,category,price);
    names.remove(i);
    namesort=false;
    prices.remove(i);
    namesort=true;
}

void additem(vector<item>&items,BST &prices,BST &names){
    string name,category; int price;
    cout<<"Please enter the item's data :-\n";
    cout<<"Name: "; cin>>name;
    cout<<"Category: "; cin>>category;
    cout<<"Price: "; cin>>price;

    item i= item(name,category,price);
    items.push_back(i);
    names.insert(i);
    namesort=false;
    prices.insert(i);
    namesort=true;
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
    BST prices;
    BST names;
    vector<item> items;

    displayMenu();
    int choice; cin>>choice;
    while(choice!=8){
        switch (choice) {
            case 1:
                additem(items,prices,names);
                break;
            case 2:
                delitem(items, prices, names);
                break;
            case 3:
                for(auto item: items) item.print();
                break;
            case 4:
                names.printasc();
                break;
            case 5:
                names.printdes();
                break;
            case 6:
                prices.printasc();
                break;
            case 7:
                prices.printdes();
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        displayMenu();
        cin>>choice;
    }
    return 0;
}
