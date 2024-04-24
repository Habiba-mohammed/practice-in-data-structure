//
// Created by Abdelaziz Ali on 4/23/2024.
//

#include "Student.h"
#include <bits/stdc++.h>

template<typename T>
void QuickSort(T *A[], int start, int end, int& cnt, bool compare (const T& a, const T& b));

template<typename T>
int Partition(T *A[], int start, int end, int& cnt, bool compare(const T& a, const T& b));

// Comparison functions
bool compareByGPA(const Student& a, const Student& b) {
    return a.getGpa() <= b.getGpa(); // Sort by GPA in ascending order
}

bool compareByName(const Student& a, const Student& b) {
    return a <= b ;// Sort by name in ascending order ( we already overloaded that tho :D )
}

template<typename T>
void QuickSort(T *A[], int start, int end, int& cnt, bool compare (const T& a, const T& b)) { // function compare as a parameter !!
    if (start >= end) return;
    int pindex = Partition(A, start, end, cnt, compare);
    QuickSort(A, start, pindex - 1, cnt, compare);
    QuickSort(A, pindex + 1, end, cnt, compare);
}

template<typename T>
int Partition(T *A[], int start, int end, int& cnt, bool compare (const T& a, const T& b) )
{ // function compare as a parameter !// !
    // Generate a random number in between
    // start - end
    int random = (start-1) + rand() % ( (end-1) - (start-1));
    // Swap A[random] with A[high]
    swap(A[random], A[end-1]);
    T* pivot = A[end - 1];
    int pindex = start - 1;

    for (int i = start-1; i < end - 1; i++) {
        if (compare(*A[i], *pivot)) {
            swap(A[i], A[pindex]);
            pindex++;

            cnt++;
        }
    }
    swap(A[pindex], A[end - 1]);
    return pindex + 1;
}

int main() {
    srand(time(NULL));

    ifstream inputFile("students.txt"); 

    if (!inputFile) {
        cerr << "Error: Unable to open file" << std::endl;
        return 1;
    }

    int numStudents;
    inputFile >> numStudents; 
    Student *students[numStudents];
    string firstName, lastName, id;
    double gpa;

    for (int i = 0; i < numStudents; ++i) {
        inputFile >> firstName;

        if (inputFile.peek() != '\n' && inputFile.peek() != '\r' && inputFile.peek() != EOF) {
            inputFile >> lastName;
        } else {
            lastName = ""; 
        }

        inputFile >> id >> gpa;

        string fullName = (lastName.empty()) ? firstName : firstName + " " + lastName;

        students[i] = new Student(fullName, id, gpa);
    }

    inputFile.close(); 

    int cnt = 0;
    QuickSort(students, 1, numStudents, cnt, compareByGPA); 

    ofstream outputFile1("SortedByGPA.txt");
    if (!outputFile1) {
        cerr << "Error: Unable to create SortedByGPA.txt" << std::endl;
        return 1;
    }

    for (int i = 0; i < numStudents; ++i) {
        outputFile1 << students[i]->getName() << " " << students[i]->getId() << " " << students[i]->getGpa() << std::endl;
//        delete students[i]; 
    }

    outputFile1.close(); 

    QuickSort(students, 1, numStudents, cnt, compareByName);

    ofstream outputFile("SortedByName.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create SortedByName.txt" << std::endl;
        return 1;
    }

    for (int i = 0; i < numStudents; ++i) {
        outputFile << students[i]->getName() << " " << students[i]->getId() << " " << students[i]->getGpa() << std::endl;
        delete students[i]; 
    }

    outputFile.close(); 

    cout << "Sorting and file writing completed successfully." << std::endl;

    return 0;
}
