#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Student class to store student details
class Student {
public:
    int id;
    string name;
    int age;
    string grade;

    // Constructor
    Student(int i = 0, string n = "", int a = 0, string g = "") 
        : id(i), name(n), age(a), grade(g) {}

    // Display student details
    void display() const {
        cout << left << setw(10) << id << setw(20) << name << setw(10) << age << setw(10) << grade << endl;
    }
};

// Student Management System class
class StudentManagementSystem {
private:
    vector<Student> students;
    const string filename = "students.txt";

    // Load students from file
    void loadFromFile() {
        ifstream file(filename);
        students.clear();
        int id, age;
        string name, grade;
        
        while (file >> id) {
            file.ignore(); // Ignore newline after id
            getline(file, name);
            file >> age;
            file.ignore();
            getline(file, grade);
            students.push_back(Student(id, name, age, grade));
        }
        file.close();
    }

    // Save students to file
    void saveToFile() const {
        ofstream file(filename);
        for (const auto& student : students) {
            file << student.id << endl;
            file << student.name << endl;
            file << student.age << endl;
            file << student.grade << endl;
        }
        file.close();
    }

public:
    StudentManagementSystem() {
        loadFromFile(); // Load data on startup
    }

    // Add a new student
    void addStudent() {
        int id, age;
        string name, grade;

        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Student Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Student Grade: ";
        getline(cin, grade);

        // Check for duplicate ID
        for (const auto& student : students) {
            if (student.id == id) {
                cout << "Student ID already exists!\n";
                return;
            }
        }

        students.push_back(Student(id, name, age, grade));
        saveToFile();
        cout << "Student added successfully!\n";
    }

    // View all students
    void viewStudents() const {
        if (students.empty()) {
            cout << "\nNo students found!\n";
            return;
        }

        cout << "\nStudent List:\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Age" << setw(10) << "Grade" << endl;
        cout << string(50, '-') << endl;
        for (const auto& student : students) {
            student.display();
        }
    }

    // Delete a student by ID
    void deleteStudent() {
        int id;
        cout << "\nEnter Student ID to delete: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                saveToFile();
                cout << "Student deleted successfully!\n";
                return;
            }
        }
        cout << "Student ID not found!\n";
    }

    // Search student by ID
    void searchStudent() const {
        int id;
        cout << "\nEnter Student ID to search: ";
        cin >> id;

        for (const auto& student : students) {
            if (student.id == id) {
                cout << "\nStudent Found:\n";
                cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Age" << setw(10) << "Grade" << endl;
                cout << string(50, '-') << endl;
                student.display();
                return;
            }
        }
        cout << "Student ID not found!\n";
    }
};

// Menu-driven UI
void displayMenu() {
    cout << "\nStudent Management System\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Delete Student\n";
    cout << "4. Search Student by ID\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentManagementSystem sms;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                sms.addStudent();
                break;
            case 2:
                sms.viewStudents();
                break;
            case 3:
                sms.deleteStudent();
                break;
            case 4:
                sms.searchStudent();
                break;
            case 5:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}