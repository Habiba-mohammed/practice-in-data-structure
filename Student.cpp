#include <bits/stdc++.h>

using namespace std;

bool nameSort = true;
int num;

class Student {
    string name, id;
    double gpa;
public:
    Student() {}

    Student(const string& name, const string& id, const double gpa) : name(name), id(id), gpa(gpa) {

    }

    bool operator<(const Student &st) const {
        if (nameSort)
            return this->name < st.name;
        return this->gpa < st.gpa;

    }

    friend ostream & operator << (ostream &out, Student & st){
        out << st.name << '\n' << st.id << '\n' << st.gpa;
        return out;
    }

};


void Selection(Student arr[]) {
    for (int i = 0; i < num; ++i) {
        int minPos = i;
        for (int j = i + 1; j < num; ++j) {
            if (arr[j] < arr[minPos])
                minPos = j;
        }
        swap(arr[minPos], arr[i]);
    }

}

void mergeSort(Student arr[], int l, int r){

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
    Selection(arr);
    //mergeSort(arr, 0, num - 1);
    for (int i = 0; i < num; ++i) {
        cout << arr[i] << '\n';
    }

}