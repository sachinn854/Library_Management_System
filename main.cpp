#include "Library.h"

int main() {
    Library library;
    Member currentMember;
    int choice;

    // Load existing data from files
    library.loadBooks();
    library.loadMembers();
    library.loadLibrarians();

    while (true) {
        cout << "-------- Main Menu --------" << endl;
        cout << "1. Register as a new Member" << endl;
        cout << "2. Register as a new Librarian" << endl;
        cout << "3. Login as a Member" << endl;
        cout << "4. Login as a Librarian" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Register as a new Member
            cout << "Registering as a Member..." << endl;
            currentMember.inputMemberData("Member");
            library.registerUser(currentMember);
            break;
        }
        case 2: {
            // Register as a new Librarian
            cout << "Registering as a Librarian..." << endl;
            currentMember.inputMemberData("Librarian");
            library.registerUser(currentMember);
            break;
        }
        case 3: {
            // Login as a Member
            int memberID;
            string memberEmail;
            cout << "Enter Member ID: ";
            cin >> memberID;
            cout << "Enter Member Email: ";
            cin >> memberEmail;

            if (library.loginAsMember(memberID, memberEmail)) {
                // Show Member Menu after login
                int memberChoice;
                while (true) {
                    cout << "\n--- Member Menu ---\n";
                    cout << "1. View all Books" << endl;
                    cout << "2. Borrow a Book" << endl;
                    cout << "3. Return a Book" << endl;
                    cout << "4. View Borrowed Books" << endl;
                    cout << "5. Recommend Books" << endl;
                    cout << "6. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> memberChoice;

                    switch (memberChoice) {
                    case 1:
                        // View all books
                        library.displayBooks();
                        break;
                    case 2: {
                        // Borrow a book
                        string bookTitle;
                        cout << "Enter the book title to borrow: ";
                        cin.ignore();  // Clear input buffer
                        getline(cin, bookTitle);
                        library.issueBook(currentMember, bookTitle);
                        break;
                    }
                    case 3: {
                        // Return a book
                        string bookTitle;
                        cout << "Enter the book title to return: ";
                        cin.ignore();  // Clear input buffer
                        getline(cin, bookTitle);
                        library.returnBook(currentMember, bookTitle);
                        break;
                    }
                    case 4:
                        // View borrowed books
                        currentMember.display();
                        break;
                    case 5:
                        // Recommend books
                        library.recommendBooks(currentMember);
                        break;
                    case 6:
                        // Logout
                        cout << "Logging out as Member..." << endl;
                        return 0;  // Exit the program or go back to main menu
                    default:
                        cout << "Invalid choice. Try again." << endl;
                    }
                }
            } else {
                cout << "Invalid Member credentials!" << endl;
            }
            break;
        }
        case 4: {
            // Login as a Librarian
            int librarianID;
            string librarianEmail;
            cout << "Enter Librarian ID: ";
            cin >> librarianID;
            cout << "Enter Librarian Email: ";
            cin >> librarianEmail;

            if (library.loginAsLibrarian(librarianID, librarianEmail)) {
                // Show Librarian Menu after login
                int librarianChoice;
                while (true) {
                    cout << "\n--- Librarian Menu ---\n";
                    cout << "1. View all Books" << endl;
                    cout << "2. Add a Book" << endl;
                    cout << "3. View Members" << endl;
                    cout << "4. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> librarianChoice;

                    switch (librarianChoice) {
                    case 1:
                        // View all books
                        library.displayBooks();
                        break;
                    case 2: {
                        // Add a book
                        string bookTitle, bookAuthor;
                        cout << "Enter the book title: ";
                        cin.ignore();  // Clear input buffer
                        getline(cin, bookTitle);
                        cout << "Enter the book author: ";
                        getline(cin, bookAuthor);
                        library.addBook(bookTitle, bookAuthor);
                        break;
                    }
                    case 3:
                        // View Members (just print all member data for now)
                        for (const auto& member : library.members) {
                            member.display();
                        }
                        break;
                    case 4:
                        // Logout
                        cout << "Logging out as Librarian..." << endl;
                        return 0;  // Exit the program or go back to main menu
                    default:
                        cout << "Invalid choice. Try again." << endl;
                    }
                }
            } else {
                cout << "Invalid Librarian credentials!" << endl;
            }
            break;
        }
        case 5:
            // Exit the program
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}