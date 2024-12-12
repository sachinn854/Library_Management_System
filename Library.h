#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Forward declaration of the Library class
class Library;

// Class to represent a Member
class Member {
public:
    string name;
    string id; // Keep id as string
    string email;
    string role;
    vector<string> borrowedBooks;

    Member() : name(""), id(""), email(""), role("") {}
    Member(string name, string id, string email, string role) 
        : name(name), id(id), email(email), role(role) {}

    void inputMemberData(const string& role, const vector<Member>& members);
    void display() const;
    void borrowBook(const string& bookName);
    void returnBook(const string& bookName);
};

// Class to represent a Book
class Book {
public:
    string title;
    string author;
    bool isAvailable;

    Book(string t, string a, bool available = true) 
        : title(t), author(a), isAvailable(available) {}

    void display() const;
};

// Class to represent a Library
class Library {
public:
    vector<Member> members;
    vector<Book> books;

    void registerUser(Member& member);
    bool loginAsMember(const string& id, const string& email);
    bool loginAsLibrarian(const string& id, const string& email);
    void addBook(const string& title, const string& author);
    void displayBooks() const;
    bool issueBook(Member& member, const string& bookTitle);
    bool returnBook(Member& member, const string& bookTitle);
    void recommendBooks(Member& member);
    void loadBooks();
    void loadMembers();
    void loadLibrarians();
    void saveBooks();
    void saveMembers();
    void saveLibrarians();
    void saveBorrowedBooks();
};

// Function to check if the ID is alphanumeric and unique
bool isValidID(const string& id, const vector<Member>& members);
bool isValidEmail(const string& email);


#endif // LIBRARY_H