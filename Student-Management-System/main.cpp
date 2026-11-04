#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;

    Student(int id, string name, int age) {
        this->id = id;
        this->name = name;
        this->age = age;
    }
};

class StudentDatabase {
private:
    vector<Student> students;

public:
    void addStudent(int id, string name, int age) {
        students.push_back(Student(id, name, age));
        cout << "Student added successfully!" << endl;
    }

    void searchStudent(int id) {
        bool found = false;
        for (auto& student : students) {
            if (student.id == id) {
                cout << "Student Found: " << endl;
                cout << "ID: " << student.id << ", Name: " << student.name << ", Age: " << student.age << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void deleteStudent(int id) {
        bool found = false;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                cout << "Student with ID " << id << " deleted successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found to delete." << endl;
        }
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students to display." << endl;
            return;
        }
        for (auto& student : students) {
            cout << "ID: " << student.id << ", Name: " << student.name << ", Age: " << student.age << endl;
        }
    }
};

int main() {
    StudentDatabase db;
    int choice, id, age;
    string name;

    do {
        cout << "\nStudent Database Menu:" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter student ID: ";
                cin >> id;
                cout << "Enter student Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter student Age: ";
                cin >> age;
                db.addStudent(id, name, age);
                break;

            case 2:
                cout << "Enter student ID to search: ";
                cin >> id;
                db.searchStudent(id);
                break;

            case 3:
                cout << "Enter student ID to delete: ";
                cin >> id;
                db.deleteStudent(id);
                break;

            case 4:
                db.displayAllStudents();
                break;

            case 5:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
