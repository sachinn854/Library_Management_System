#include "Library.h"
#include <algorithm>
#include <fstream>
#include <regex>
using namespace std;

// Implementation of isValidID (if not defined elsewhere)
bool isValidID(const string& id, const vector<Member>& members) {
    // Check if the ID is alphanumeric
    if (id.empty() || !all_of(id.begin(), id.end(), [](char c) { return isalnum(c); })) {
        cout << "ID must be alphanumeric!" << endl;
        return false;
    }

    // Check for uniqueness
    for (const auto& member : members) {
        if (member.id == id) { // Compare strings
            cout << "This ID already exists!" << endl;
            return false;
        }
    }

    return true;
}


bool isValidEmail(const string& email) {
    // Regular expression for validating an Email
    const regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");

    if (regex_match(email, pattern)) {
        return true;
    } else {
        cout << "Invalid email format!" << endl;
        return false;
    }
}

// Method to input Member or Librarian details
void Member::inputMemberData(const string& role, const vector<Member>& members) {
    this->role = role; // Set the role

    cout << "Enter Name: ";
    cin.ignore();  // Clear the newline left by previous input
    getline(cin, name);

    // Loop until a valid and unique ID is entered
    while (true) {
        cout << "Enter ID: ";
        cin >> id;

        if (isValidID(id, members)) {
            break; // Exit the loop if ID is valid and unique
        }
    }

    while (true) {
        cout << "Enter Email: ";
        cin.ignore();  // Clear the newline left by previous input
        getline(cin, email);

        if (isValidEmail(email)) {
            break; // Exit the loop if email is valid
        }
    }

}



// Method to display Member details
void Member::display() const {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Email: " << email << endl;
    cout << "Role: " << role << endl;
    cout << "Borrowed Books: ";
    for (const auto& book : borrowedBooks) {
        cout << book << ", ";
    }
    cout << endl;
}

// Method to load members from the file
void Library::loadMembers() {
    ifstream memberFile("members.txt");
    string name, email, id; // Change id to string

    while (getline(memberFile, name, ',') && getline(memberFile, id, ',') && getline(memberFile, email)) {
        members.push_back(Member{name, id, email, "Member"});
    }
    memberFile.close();
}

// Method to load librarians from the file
void Library::loadLibrarians() {
    ifstream librarianFile("librarians.txt");
    string name, email, id; // Change id to string

    while (getline(librarianFile, name, ',') && getline(librarianFile, id, ',') && getline(librarianFile, email)) {
        members.push_back(Member{name, id, email, "Librarian"});
    }
    librarianFile.close();
}

// Function to check if the ID is alphanumeric and unique
// Method to display Book details
void Book::display() const {
    cout << "Title: " << title << ", Author: " << author;
    if (isAvailable) {
        cout << " - Available" << endl;
    } else {
        cout << " - Not Available" << endl;
    }
}

// Method to borrow a book
void Member::borrowBook(const string& bookName) {
    borrowedBooks.push_back(bookName);
}

// Method to return a book
void Member::returnBook(const string& bookName) {
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookName);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    } else {
        cout << "Book not found in borrowed list!" << endl;
    }
}



// Method to register a new Member or Librarian
void Library::registerUser(Member& member) {
    if (member.role == "Member") {
        ofstream memberFile("members.txt", ios::app); // Append to file
        if (memberFile.is_open()) {
            memberFile << member.name << "," << member.id << "," << member.email << endl;
            memberFile.close();
            cout << "Member registered successfully!" << endl;
        } else {
            cout << "Error: Could not open members.txt file!" << endl;
        }
    } else if (member.role == "Librarian") {
        ofstream librarianFile("librarians.txt", ios::app); // Append to file
        if (librarianFile.is_open()) {
            librarianFile << member.name << "," << member.id << "," << member.email << endl;
            librarianFile.close();
            cout << "Librarian registered successfully!" << endl;
        } else {
            cout << "Error: Could not open librarians.txt file!" << endl;
        }
    }
}

// Method to login as a Member
bool Library::loginAsMember(const string& id, const string& email) { // Change id to string
    for (auto& member : members) {
        if (member.id == id && member.email == email) {
            cout << "Logged in as Member: " << member.name << endl;
            return true;
        }
    }
    return false;
}

// Method to login as a Librarian
bool Library::loginAsLibrarian(const string& id, const string& email) { // Change id to string
    for (auto& member : members) {
        if (member.id == id && member.email == email) {
            cout << "Logged in as Librarian: " << member.name << endl;
            return true;
        }
    }
    return false;
}

// Method to add a book
void Library::addBook(const string& title, const string& author) {
    Book newBook(title, author);
    books.push_back(newBook);
    saveBooks(); // Save the books data after adding a new one
    cout << "Book added successfully!" << endl;
}

// Method to display all books
void Library::displayBooks() const {
    cout << "Available Books:" << endl;
    for (const auto& book : books) {
        book.display();
    }
}

// Method to issue a book to a member
bool Library::issueBook(Member& member, const string& bookTitle) {
    for (auto& book : books) {
        if (book.title == bookTitle && book.isAvailable) {
            book.isAvailable = false;
            member.borrowBook(bookTitle);
            saveBooks(); // Save the books data after issuing
            saveBorrowedBooks(); // Save borrowed books after issuing
            cout << "Book issued to " << member.name << endl;
            return true;
        }
    }
    cout << "Book not available!" << endl;
    return false;
}

// Method to return a book to the library
bool Library::returnBook(Member& member, const string& bookTitle) {
    for (auto& book : books) {
        if (book.title == bookTitle && !book.isAvailable) {
            book.isAvailable = true;
            member.returnBook(bookTitle);
            saveBooks(); // Save the books data after returning
            saveBorrowedBooks(); // Save borrowed books after returning
            cout << "Book returned by " << member.name << endl;
            return true;
        }
    }
    cout << "Invalid return request!" << endl;
    return false;
}

// Method to recommend books based on borrowing trends
void Library::recommendBooks(Member& member) {
    cout << "Recommendations based on your borrowing history:" << endl;
    for (const auto& book : member.borrowedBooks) {
        cout << "You borrowed: " << book << endl;
    }
    cout << "You might also like more books from these authors!" << endl;
}

// Helper methods to load data from files
void Library::loadBooks() {
    ifstream bookFile("books.txt");
    string title, author;
    while (getline(bookFile, title, ',') && getline(bookFile, author)) {
        books.push_back(Book(title, author));
    }
    bookFile.close();
}

// Helper methods to save data to files
void Library::saveBooks() {
    ofstream bookFile("books.txt");
    for (const auto& book : books) {
        bookFile << book.title << "," << book.author << endl;
    }
    bookFile.close();
}

void Library::saveMembers() {
    ofstream memberFile("members.txt");
    for (const auto& member : members) {
        memberFile << member.name << "," << member.id << "," << member.email << endl;
    }
    memberFile.close();
}

void Library::saveLibrarians() {
    ofstream librarianFile("librarians.txt");
    for (const auto& member : members) {
        if (member.role == "Librarian") {
            librarianFile << member.name << "," << member.id << "," << member.email << endl;
        }
    }
    librarianFile.close();
}

void Library::saveBorrowedBooks() {
    ofstream borrowedBooksFile("borrowed_books.txt");
    for (const auto& member : members) {
        for (const auto& book : member.borrowedBooks) {
            borrowedBooksFile << member.id << "," << book << endl;
        }
    }
    borrowedBooksFile.close();
}