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
void InsertionSort(T *A[], int n,int & cnt, bool compare(const T& a, const T& b)) {
    for (int i = 1; i < n; ++i) {
        T* value = A[i];
        int k = i - 1;
        while (k >= 0 && compare(*value, *A[k])) {
            A[k + 1] = A[k];
            --k;
        }
        A[k + 1] = value;
    }
}

int main() {
    ifstream inputFile("students.txt"); // Open file for reading

    if (!inputFile) {
        cerr << "Error: Unable to open file" << std::endl;
        return 1;
    }

    int numStudents;
    inputFile >> numStudents; // Read number of students from the file
    Student *students[numStudents];
    string firstName, lastName, id;
    double gpa;

    // Read student information for each student
    for (int i = 0; i < numStudents; ++i) {
        inputFile >> firstName;

        // Check if there's additional input for last name
        if (inputFile.peek() != '\n' && inputFile.peek() != '\r' && inputFile.peek() != EOF) {
            inputFile >> lastName;
        } else {
            lastName = ""; // Last name not provided
        }

        // Read ID and GPA
        inputFile >> id >> gpa;

        // Concatenate first name and last name (if provided) with a space
        string fullName = (lastName.empty()) ? firstName : firstName + " " + lastName;

        // Create a Student object and add it to the array
        students[i] = new Student(fullName, id, gpa);
    }

    inputFile.close(); // Close the file after reading

    // Sort students by Name (in ascending) and GPA (in descending) using QuickSort
    int cnt = 0;
    InsertionSort(students, numStudents, cnt, compareByGPA); // Then sort by Name

    // Write sorted students by Name
    ofstream outputFile1("SortedByGPA.txt");
    if (!outputFile1) {
        cerr << "Error: Unable to create SortedByGPA.txt" << std::endl;
        return 1;
    }

    for (int i = 0; i < numStudents; ++i) {
        outputFile1 << students[i]->getName() << " " << students[i]->getId() << " " << students[i]->getGpa() << std::endl;
//        delete students[i]; // Clean up dynamically allocated memory
    }

    outputFile1.close(); // Close the output file

    InsertionSort(students, numStudents, cnt, compareByName); // Then sort by Name

    // Write sorted students by Name
    ofstream outputFile("SortedByName.txt");
    if (!outputFile) {
        cerr << "Error: Unable to create SortedByName.txt" << std::endl;
        return 1;
    }

    for (int i = 0; i < numStudents; ++i) {
        outputFile << students[i]->getName() << " " << students[i]->getId() << " " << students[i]->getGpa() << std::endl;
        delete students[i]; // Clean up dynamically allocated memory
    }

    outputFile.close(); // Close the output file

    cout << "Sorting and file writing completed successfully." << std::endl;

    return 0;
}
