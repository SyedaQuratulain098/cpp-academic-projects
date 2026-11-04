#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

// Maximum limits
const int STUDENT_LIMIT = 20;
const int BOOK_LIMIT = 15;
const int NAME_SIZE = 50;

// Global data
int totalStudents = 0;
int totalBooks = 0;

int rollNumbers[STUDENT_LIMIT];
double balances[STUDENT_LIMIT];
char names[STUDENT_LIMIT][NAME_SIZE];

char titles[BOOK_LIMIT][NAME_SIZE];
char authors[BOOK_LIMIT][NAME_SIZE];
int ISBN[BOOK_LIMIT];
bool availability[BOOK_LIMIT];

// Function declarations
void registerStudent();
void showStudent(int roll);
void addMoney(int roll, double amount);
void borrowBook(int roll);
void sortStudents();
int searchStudent(int roll);
int searchBook(int isbn);
void insertBook();
void updateBook();
void showBooks();

int main()
{
    // Initial library records
    const char* initialTitles[BOOK_LIMIT] = {
        "The Alchemist",
        "Harry Potter",
        "Atomic Habits",
        "Rich Dad Poor Dad",
        "The Hobbit",
        "Ikigai",
        "Deep Work",
        "Think and Grow Rich",
        "The Psychology of Money",
        "The Great Gatsby",
        "1984",
        "Pride and Prejudice",
        "The Power of Habit",
        "Clean Code",
        "Introduction to Algorithms"
    };

    const char* initialAuthors[BOOK_LIMIT] = {
        "Paulo Coelho",
        "J.K. Rowling",
        "James Clear",
        "Robert Kiyosaki",
        "J.R.R. Tolkien",
        "Hector Garcia",
        "Cal Newport",
        "Napoleon Hill",
        "Morgan Housel",
        "F. Scott Fitzgerald",
        "George Orwell",
        "Jane Austen",
        "Charles Duhigg",
        "Robert Martin",
        "Thomas Cormen"
    };

    for (int i = 0; i < BOOK_LIMIT; i++)
    {
        strcpy(titles[i], initialTitles[i]);
        strcpy(authors[i], initialAuthors[i]);
        ISBN[i] = 2000 + i;
        availability[i] = true;
    }

    totalBooks = BOOK_LIMIT;

    int choice;
    int userType;
    string password;

    do
    {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Administrator Login\n";
        cout << "2. Student Login\n";
        cout << "0. Exit Program\n";
        cout << "Select option: ";
        cin >> userType;

        if (userType == 0)
            break;

        if (userType != 1 && userType != 2)
        {
            cout << "Invalid selection!\n";
            continue;
        }

        cout << "Enter login password: ";
        cin >> password;

        if (password != "password")
        {
            cout << "Access denied! Incorrect password.\n";
            continue;
        }

        if (userType == 1)
        {
            cout << "\n----------- ADMIN PANEL -----------\n";
            cout << "1. Register New Book\n";
            cout << "2. Modify Book Information\n";
            cout << "3. Display Library Collection\n";
            cout << "4. Display Student Records\n";
            cout << "5. Check Student Account\n";
            cout << "Select option: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    insertBook();
                    break;

                case 2:
                    updateBook();
                    break;

                case 3:
                    showBooks();
                    break;

                case 4:
                    sortStudents();
                    break;

                case 5:
                {
                    int roll;
                    cout << "Enter student roll number: ";
                    cin >> roll;
                    showStudent(roll);
                    break;
                }

                default:
                    cout << "Invalid admin option.\n";
            }
        }
        else
        {
            int roll;
            cout << "\nEnter your roll number: ";
            cin >> roll;

            int position = searchStudent(roll);

            if (position == -1)
            {
                cout << "No account found for this student.\n";
                cout << "Create a new account?\n1. Yes\n2. No\n";
                cin >> choice;

                if (choice == 1)
                    registerStudent();
            }
            else
            {
                cout << "\n----------- STUDENT PANEL -----------\n";
                cout << "1. View Account Details\n";
                cout << "2. Deposit Money\n";
                cout << "3. Borrow a Book\n";
                cout << "Select option: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:
                        showStudent(roll);
                        break;

                    case 2:
                    {
                        double amount;
                        cout << "Enter deposit amount: $";
                        cin >> amount;
                        addMoney(roll, amount);
                        break;
                    }

                    case 3:
                        borrowBook(roll);
                        break;

                    default:
                        cout << "Invalid student option.\n";
                }
            }
        }

    } while (true);

    cout << "\nThank you for using the Library Management System!\n";

    return 0;
}

// Create student account
void registerStudent()
{
    if (totalStudents >= STUDENT_LIMIT)
    {
        cout << "Student registration limit reached.\n";
        return;
    }

    int roll;
    cout << "Enter roll number: ";
    cin >> roll;

    if (searchStudent(roll) != -1)
    {
        cout << "This roll number is already registered.\n";
        return;
    }

    rollNumbers[totalStudents] = roll;

    cout << "Enter student full name: ";
    cin.ignore();
    cin.getline(names[totalStudents], NAME_SIZE);

    double deposit;
    cout << "Enter initial deposit (minimum $50): ";
    cin >> deposit;

    if (deposit < 50)
    {
        cout << "Minimum deposit requirement not fulfilled.\n";
        return;
    }

    balances[totalStudents] = deposit - 50;
    totalStudents++;

    cout << "Student account created successfully!\n";
}

// Display student details
void showStudent(int roll)
{
    int position = searchStudent(roll);

    if (position == -1)
    {
        cout << "Student record does not exist.\n";
        return;
    }

    cout << "\nStudent Information\n";
    cout << "Roll Number: " << rollNumbers[position] << endl;
    cout << "Student Name: " << names[position] << endl;
    cout << "Account Balance: $" << fixed << setprecision(2)
         << balances[position] << endl;
}

// Deposit money
void addMoney(int roll, double amount)
{
    int position = searchStudent(roll);

    if (position == -1)
    {
        cout << "Student account not found.\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Please enter a valid deposit amount.\n";
        return;
    }

    balances[position] += amount;

    cout << "Deposit completed successfully!\n";
    cout << "Updated Balance: $" << fixed << setprecision(2)
         << balances[position] << endl;
}

// Borrow a book
void borrowBook(int roll)
{
    int position = searchStudent(roll);

    if (position == -1)
    {
        cout << "Student account not found.\n";
        return;
    }

    cout << "\nAvailable Books\n";

    bool found = false;

    for (int i = 0; i < totalBooks; i++)
    {
        if (availability[i])
        {
            cout << i + 1 << ". " << titles[i]
                 << " | Author: " << authors[i]
                 << " | ISBN: " << ISBN[i] << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No books are currently available.\n";
        return;
    }

    int choice;
    cout << "Enter book number to borrow (0 to cancel): ";
    cin >> choice;

    if (choice == 0)
        return;

    if (choice < 1 || choice > totalBooks)
    {
        cout << "Invalid book selection.\n";
        return;
    }

    int bookIndex = choice - 1;

    if (availability[bookIndex] && balances[position] >= 2)
    {
        availability[bookIndex] = false;
        balances[position] -= 2;

        cout << "Book borrowed successfully!\n";
        cout << "Remaining Balance: $" << fixed << setprecision(2)
             << balances[position] << endl;
    }
    else
    {
        cout << "Book unavailable or insufficient account balance.\n";
    }
}

// Sort and display students
void sortStudents()
{
    for (int i = 0; i < totalStudents - 1; i++)
    {
        for (int j = i + 1; j < totalStudents; j++)
        {
            if (rollNumbers[i] > rollNumbers[j])
            {
                swap(rollNumbers[i], rollNumbers[j]);
                swap(balances[i], balances[j]);

                char temp[NAME_SIZE];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }

    cout << "\nRegistered Student Records\n";

    if (totalStudents == 0)
    {
        cout << "No students registered yet.\n";
        return;
    }

    for (int i = 0; i < totalStudents; i++)
    {
        cout << rollNumbers[i] << " | "
             << names[i] << " | Balance: $"
             << fixed << setprecision(2)
             << balances[i] << endl;
    }
}

// Search student by roll number
int searchStudent(int roll)
{
    for (int i = 0; i < totalStudents; i++)
    {
        if (rollNumbers[i] == roll)
            return i;
    }

    return -1;
}

// Search book by ISBN
int searchBook(int isbn)
{
    for (int i = 0; i < totalBooks; i++)
    {
        if (ISBN[i] == isbn)
            return i;
    }

    return -1;
}

// Add a new book
void insertBook()
{
    if (totalBooks >= BOOK_LIMIT)
    {
        cout << "Library storage is full.\n";
        return;
    }

    cin.ignore();

    cout << "Enter book title: ";
    cin.getline(titles[totalBooks], NAME_SIZE);

    cout << "Enter author name: ";
    cin.getline(authors[totalBooks], NAME_SIZE);

    int isbn;
    cout << "Enter ISBN number: ";
    cin >> isbn;

    if (searchBook(isbn) != -1)
    {
        cout << "This ISBN is already registered.\n";
        return;
    }

    ISBN[totalBooks] = isbn;
    availability[totalBooks] = true;
    totalBooks++;

    cout << "New book added to the library!\n";
}

// Edit existing book
void updateBook()
{
    int isbn;
    cout << "Enter ISBN of the book: ";
    cin >> isbn;

    int position = searchBook(isbn);

    if (position == -1)
    {
        cout << "Book record not found.\n";
        return;
    }

    cin.ignore();

    cout << "Current Title: " << titles[position] << endl;
    cout << "Enter updated title: ";
    cin.getline(titles[position], NAME_SIZE);

    cout << "Current Author: " << authors[position] << endl;
    cout << "Enter updated author: ";
    cin.getline(authors[position], NAME_SIZE);

    cout << "Book information updated successfully!\n";
}

// Display all books
void showBooks()
{
    cout << "\n========== LIBRARY BOOKS ==========\n";

    if (totalBooks == 0)
    {
        cout << "No books available in the library.\n";
        return;
    }

    for (int i = 0; i < totalBooks; i++)
    {
        cout << "\nBook " << i + 1 << endl;
        cout << "Title: " << titles[i] << endl;
        cout << "Author: " << authors[i] << endl;
        cout << "ISBN: " << ISBN[i] << endl;
        cout << "Status: "
             << (availability[i] ? "Available" : "Issued")
             << endl;
    }
}
