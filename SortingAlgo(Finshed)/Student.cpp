#include <bits/stdc++.h>

using namespace std::chrono;
using namespace std;

ifstream ifile;
ofstream ofile1, ofile2;
bool nameSort = true;
int num;
long long counter = 0;

class Student {
    string name, id;
    double gpa;
public:
    Student() {}

    Student(const string &name, const string &id, const double gpa) : name(name), id(id), gpa(gpa) {

    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Student::name = name;
    }

    const string &getId() const {
        return id;
    }

    void setId(const string &id) {
        Student::id = id;
    }

    double getGpa() const {
        return gpa;
    }

    void setGpa(double gpa) {
        Student::gpa = gpa;
    }

    bool operator<(const Student &st) const {
        if (nameSort)
            return this->name < st.name;
        return this->gpa < st.gpa;

    }

    bool operator>(const Student &st) const {
        if (nameSort)
            return this->name > st.name;
        return this->gpa > st.gpa;

    }

    bool operator<=(const Student &st) const {
        if (nameSort)
            return this->name <= st.name;
        return this->gpa <= st.gpa;

    }

    bool operator>=(const Student &st) const {
        if (nameSort)
            return this->name >= st.name;
        return this->gpa >= st.gpa;

    }

    friend ostream &operator<<(ostream &out, Student &st) {
        out << st.name << '\n' << st.id << '\n' << st.gpa;
        return out;
    }

};


template<typename T>
void insertionSort(T arr[]) {
    for (int i = 1; i < num; i++) {

        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }

}


template<typename T>
void selectionSort(T arr[]) {
    for (int i = 0; i < num; ++i) {
        counter++;
        int minPos = i;
        for (int j = i + 1; j < num; ++j) {
            counter++;
            if (arr[j] < arr[minPos]) {
                minPos = j;
                counter++;
            }

        }
        swap(arr[minPos], arr[i]);
    }

}

template<typename T>
void Merge(T arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    T *leftArray = new T[n1], *rightArray = new T[n2];
    for (int i = 0; i < n1; ++i) {
        counter++;
        leftArray[i] = arr[l + i];
    }
    for (int i = 0; i < n2; ++i) {
        rightArray[i] = arr[m + i + 1];
        counter++;
    }
    int k = l, pos1, pos2;
    pos1 = pos2 = 0;
    while (pos1 < n1 && pos2 < n2) {
        counter += 2;
        if (leftArray[pos1] < rightArray[pos2]) {
            counter++;
            arr[k] = leftArray[pos1];
            pos1++;
        } else {
            arr[k] = rightArray[pos2];
            pos2++;
        }
        k++;
    }
    while (pos1 < n1) {
        counter++;
        arr[k] = leftArray[pos1];
        pos1++;
        k++;
    }
    while (pos2 < n2) {
        counter++;
        arr[k] = rightArray[pos2];
        pos2++;
        k++;
    }
    delete[]leftArray;
    delete[]rightArray;

}

template<typename T>
void mergeSort(T arr[], int l, int r) {
    if (l < r) {
        counter++;
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }

}

template<typename T>
void bubbleSort(T arr[]) {
    for (int i = 0; i < num; ++i) {
        counter++;
        for (int j = 0; j < num - 1; ++j) {
            counter++;
            if (arr[j + 1] < arr[j]) {
                counter++;
                swap(arr[j + 1], arr[j]);
                counter++;
            }

        }
    }
}

template<typename T>
void shellSort(T arr[], int size) {
    for (int i = size / 2; i > 0; i /= 2) {
        counter++;
        for (int j = i; j < size; ++j) {
            counter++;
            T var = arr[j];
            int k;
            for (k = j; k >= i && arr[k - i] > var; k -= i) {
                counter += 2;
                arr[k] = arr[k - i];
            }

            arr[k] = var;
        }
    }
}


void readInputFileName(string &str) {
    cin >> str;
    int Size = str.size();
    if (Size > 4)
        str += (str.substr(Size - 4, 4) == ".txt") ? "" : ".txt";
    else
        str += ".txt";
    ifile.open(str);
}

template<typename T>
int partition(T arr[], int start, int end) {
    int i = start;
    int j = end;
    int pivLoc = i;
    while (true) {
        while (arr[pivLoc] <= arr[j] && pivLoc != j) {
            j--;
        }
        if (pivLoc == j)
            break;
        swap(arr[j], arr[pivLoc]);
        pivLoc = j;

        while (arr[pivLoc] >= arr[i] && pivLoc != i) {
            i++;
        }
        if (pivLoc == i)
            break;
        swap(arr[i], arr[pivLoc]);
        pivLoc = i;

    }
    return pivLoc;
}

template<typename T>
void quickSort(T arr[], int l, int h) {

    if (l < h) {
        int piv = partition(arr, l, h);
        quickSort(arr, l, piv - 1);
        quickSort(arr, piv + 1, h);
    }

}


template<typename T>
void outputArrayAfterSorting(T arr[], T arr2[], map<int, string> &mp, auto duration, int &chooseNum) {
    ofile1.open("SortedByName.txt");
    ofile1 << "Algorithm: " << mp[chooseNum] << '\n';
    ofile1 << "Running Time: " << duration << '\n';
    ofile1 << "Number of comparisons: " << counter << '\n';
    for (int i = 0; i < num; ++i) {
        ofile1 << arr[i] << '\n';
    }


    ofile2.open("SortedByGPA.txt");
    ofile2 << "Algorithm: " << mp[chooseNum] << '\n';
    ofile2 << "Running Time: " << duration << '\n';
    ofile2 << "Number of comparisons: " << counter << '\n';
    for (int i = 0; i < num; ++i) {
        ofile2 << arr2[i] << '\n';
    }
    ofile1.close();
    ofile2.close();

}

int main() {
    cout << "Enter Student file name: ";
    string str = "Hello";
    readInputFileName(str);
    while (!ifile.is_open()) {
        cerr << "Error: Student Input file name isn't found ^_^\n"
                "Enter valid Input file name!";
        readInputFileName(str);
    }
    while (true) {
        bool check = nameSort = true;
        counter = 0;
        ifile >> num;
        /*
    When reading an integer from a file, the reading operation typically stops at a whitespace or newline.
    After ifile >> num, the next character in the input stream could be a newline (\n), space, tab, or another character.
    In most text-based file formats, it's common to have a newline after reading a line containing a number.
    Using ignore() After Reading an Integer:
    When you call ifile.ignore(), it skips one character. If the last operation left a newline in the input stream (which is common), this call to ignore() will skip over that newline.
    Ensuring Correct Transition to std::getline:
    If you don't ignore the newline after reading the integer, the subsequent call to std::getline(ifile, str) might read an empty line, because it consumes the newline left in the stream.
    By ignoring the newline with ifile.ignore(), you're ensuring that std::getline reads the intended content.
    Therefore, in your example, the first character ignored by ifile.ignore() is most likely the newline (\n) left in the input stream after reading the integer with ifile >> num.
         In this example, calling ifile.ignore() skips and ignores the newline (\n) left after reading the integer (ifile >> num).
         */
        Student arr[num], arr2[num];
        ifile.ignore();
        string name, id;
        double gpa;
        for (int i = 0; i < num; ++i) {
            getline(ifile, name);
            getline(ifile, id);
            ifile >> gpa;
            ifile.ignore(1, '\n');// Ignore one newline after "gpa".
            arr[i] = arr2[i] = Student(name, id, gpa);
        }
        // Record the start time
        auto start = high_resolution_clock::now();

        // Record the end time
        auto end = high_resolution_clock::now();
        int chooseNum;
        map<int, string> mp = {{1, "Insertion Sort"},
                               {2, "Selection Sort"},
                               {3, "Bubble Sort"},
                               {4, "Shell Sort"},
                               {5, "Merge Sort"},
                               {6, "Quick Sort"},
                               {7, "Exit"}};
        cout << "Choose The Sorting Algo that you want to sort with:\n";
        for (auto &ele: mp) {
            cout << ele.first << ')' << ele.second << '\n';
        }

        cin >> chooseNum;
        switch (chooseNum) {
            case 1:
                start = high_resolution_clock::now();
                insertionSort(arr);
                nameSort = false;
                insertionSort(arr2);
                end = high_resolution_clock::now();
                break;
            case 2:
                start = high_resolution_clock::now();
                selectionSort(arr);
                nameSort = false;
                selectionSort(arr2);
                end = high_resolution_clock::now();
                break;
            case 3:
                start = high_resolution_clock::now();
                bubbleSort(arr);
                nameSort = false;
                bubbleSort(arr2);
                end = high_resolution_clock::now();
                break;
            case 4:
                start = high_resolution_clock::now();
                shellSort(arr, num);
                nameSort = false;
                shellSort(arr2, num);
                end = high_resolution_clock::now();
                break;
            case 5:
                start = high_resolution_clock::now();
                mergeSort(arr, 0, num - 1);
                nameSort = false;
                mergeSort(arr2, 0, num - 1);
                end = high_resolution_clock::now();
                break;
            case 6:
                start = high_resolution_clock::now();
                quickSort(arr, 0, num - 1);
                nameSort = false;
                quickSort(arr2, 0, num - 1);
                end = high_resolution_clock::now();
                break;
            case 7:
                ifile.close();
                return 0;
            default:
                check = false;
                cout << "Invalid Number";
                break;

        }

        // Calculate the duration in milliseconds
        auto duration = duration_cast<nanoseconds>(end - start);

        if (check) {
            outputArrayAfterSorting(arr, arr2, mp, duration, chooseNum);
            cout << "Sorting is completed check your files Now!!!\n";
        }

    }

}