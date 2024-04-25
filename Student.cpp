#include <bits/stdc++.h>

using namespace std;

bool nameSort = false;
int num;
long long counter = 0;

class Student {
    string name, id;
    double gpa;
public:
    Student() {}

    Student(const string &name, const string &id, const double gpa) : name(name), id(id), gpa(gpa) {

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

    friend ostream &operator<<(ostream &out, Student &st) {
        out << st.name << '\n' << st.id << '\n' << st.gpa;
        return out;
    }

};

template<typename T>
void Selection(T arr[]) {
    for (int i = 0; i < num; ++i) {
        counter++;
        int minPos = i;
        for (int j = i + 1; j < num; ++j) {
            counter++;
            if (arr[j] < arr[minPos]){
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
    T *leftArray = new Student[n1], *rightArray = new Student[n2];
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
        counter+=2;
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
            if (arr[j + 1] < arr[j]){
                counter++;
                swap(arr[j + 1], arr[j]);
    
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
                counter+=2;
                arr[k] = arr[k - i];
            }

            arr[k] = var;
        }
    }
}


int main() {
    string str = "Student.txt";
    //cin >> str;
    ifstream ifile;
    ifile.open(str);
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
    Student arr[num];
    ifile.ignore();
    string name, id;
    double gpa;
    for (int i = 0; i < num; ++i) {
        getline(ifile, name);
        getline(ifile, id);
        ifile >> gpa;
        ifile.ignore(1, '\n');// Ignore one newline after "gpa".
        arr[i] = Student(name, id, gpa);
    }
    //Selection(arr);
    //mergeSort(arr, 0, num - 1);
    //bubbleSort(arr);
    shellSort(arr, num);
    for (int i = 0; i < num; ++i) {
        cout << arr[i] << '\n';
    }

}
