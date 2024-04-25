//
// Created by Abdelaziz Ali on 4/23/2024.
//

#ifndef DESKTOP_STUDENT_H
#define DESKTOP_STUDENT_H


#include <iostream>
#include <string>

using namespace std;



class Student {
private:
    string name;
    string id;
    double gpa;

public:
    // Constructor to initialize name, id, and gpa
    Student(const string& studentName, const string& studentId, double studentGpa) {
        name = studentName;
        id = studentId;
        gpa = studentGpa;
    }

    // Getter method for name
    string getName() const {
        return name;
    }

    // Getter method for id
    string getId() const {
        return id;
    }

    // Getter method for gpa
    double getGpa() const {
        return gpa;
    }

    // Setter method for name
    void setName(const string& studentName) {
        name = studentName;
    }

    // Setter method for id
    void setId(const string& studentId) {
        id = studentId;
    }

    // Setter method for gpa
    void setGpa(double studentGpa) {
        gpa = studentGpa;
    }

    // Overload < operator to compare Student objects based on name
    bool operator<=(const Student& other) const {
        return name <= other.name;
    }


};




#endif //DESKTOP_STUDENT_H
