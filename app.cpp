#include <iostream>
using namespace std;

struct Book {
    static inline int ID = 100;
    static inline int numBooks = 0;
    int bookId;
    string name;
    int quantity;
    int numberBorrowed = 0;
    string borrowedByUserNames[50];

    Book() {}

    Book(string _name, int _quantity) {
        bookId = ++ID;
        name = _name;
        quantity = _quantity;
    }

    void printBook() {
        cout << "ID = " << bookId << " Name = " << name 
             << " totalQuantity: " << quantity 
             << " totalBorrowed: " << numberBorrowed << endl;
    }
};

struct User {
    static inline int numberOfstudents = 0;
    int studentId;
    string name;
    string email;
    int numberBorrowedBooks = 0;
    string BorrowedBooksNames[50];

    User() {}

    User(string _name, int _studentId) {
        studentId = _studentId;
        name = _name;
    }
};

void print_by(Book books[]) {
    for (int i = 0; i < Book::numBooks; i++) {
        books[i].printBook();
    }
}

void search_for_book(string prefix, Book books[]) {
    int count = 0;

    for (int i = 0; i < Book::numBooks; i++) {
        if (prefix.size() > books[i].name.size())
            continue;

        bool isFound = true;
        for (int j = 0; j < prefix.size(); j++) {
            if (prefix[j] != books[i].name[j]) {
                isFound = false;
                break;
            }
        }
        if (isFound) {
            cout << books[i].name << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "No books with such prefix\n";
}

void print_by_name(Book books[]) {
    for (int i = 0; i < Book::numBooks; i++) {
        int lowestIndex = i;
        Book temp = books[i];
        for (int j = i + 1; j < Book::numBooks; j++) {
            if (temp.name > books[j].name) {
                temp = books[j];
                lowestIndex = j;
            }
        }
        books[lowestIndex] = books[i];
        books[i] = temp;
    }
    print_by(books);
}

void print_by_id(Book books[]) {
    for (int i = 0; i < Book::numBooks; i++) {
        int lowestIndex = i;
        Book temp = books[i];
        for (int j = i + 1; j < Book::numBooks; j++) {
            if (temp.bookId > books[j].bookId) {
                temp = books[j];
                lowestIndex = j;
            }
        }
        books[lowestIndex] = books[i];
        books[i] = temp;
    }
    print_by(books);
}

bool user_borrow_books(User users[], Book books[], string studentName, string bookName) {
    for (int i = 0; i < User::numberOfstudents; i++) {
        if (studentName == users[i].name) {
            for (int j = 0; j < Book::numBooks; j++) {
                if (bookName == books[j].name) {
                    if (books[j].numberBorrowed < books[j].quantity) {
                        books[j].borrowedByUserNames[books[j].numberBorrowed] = studentName;
                        books[j].numberBorrowed++;
                        users[i].BorrowedBooksNames[users[i].numberBorrowedBooks] = bookName;
                        users[i].numberBorrowedBooks++;
                        return true;
                    } else {
                        cout << "The book isn't available right now\n";
                        return false;
                    }
                }
            }
            cout << "There is no such book name\n";
            return false;
        }
    }
    cout << "There is no such student name\n";
    return false;
}

void print_who_borrowed_book_by_name(Book books[], string bookName) {
    for (int i = 0; i < Book::numBooks; i++) {
        if (bookName == books[i].name) {
            if (books[i].numberBorrowed == 0) {
                cout << "No one borrowed this book yet\n";
                return;
            }
            for (int j = 0; j < books[i].numberBorrowed; j++) {
                cout << books[i].borrowedByUserNames[j] << endl;
            }
            return;
        }
    }
    cout << "Invalid book name\n";
}

void remove_element_from_arr(string arr[], int pos, int len) {
    for (int i = pos + 1; i < len; i++) {
        arr[i - 1] = arr[i];
    }
}

int findIndex(string arr[], string target, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

bool user_return_books(User users[], Book books[], string studentName, string bookName) {
    for (int i = 0; i < User::numberOfstudents; i++) {
        if (studentName == users[i].name) {
            for (int j = 0; j < Book::numBooks; j++) {
                if (bookName == books[j].name) {
                    int posb = findIndex(books[j].borrowedByUserNames, studentName, books[j].numberBorrowed);
                    int poss = findIndex(users[i].BorrowedBooksNames, bookName, users[i].numberBorrowedBooks);
                    if (posb == -1 || poss == -1) {
                        cout << "This student did not borrow this book\n";
                        return false;
                    }
                    remove_element_from_arr(books[j].borrowedByUserNames, posb, books[j].numberBorrowed);
                    books[j].numberBorrowed--;

                    remove_element_from_arr(users[i].BorrowedBooksNames, poss, users[i].numberBorrowedBooks);
                    users[i].numberBorrowedBooks--;
                    return true;
                }
            }
            cout << "There is no such book name\n";
            return false;
        }
    }
    cout << "There is no such student name\n";
    return false;
}

void print_users(User users[]) {
    for (int i = 0; i < User::numberOfstudents; i++) {
        cout << "user: " << users[i].name << " id: " << users[i].studentId << " borrowed books: ";
        for (int j = 0; j < users[i].numberBorrowedBooks; j++) {
            cout << users[i].BorrowedBooksNames[j] << " ";
        }
        cout << endl;
    }
}

int getChoice() {
    cout << "\nLibrary Menu;\n"
         << "1) add_book\n"
         << "2) search_books_by_prefix\n"
         << "3) print_who_borrowed_book_by_name\n"
         << "4) print_library_by_id\n"
         << "5) print_library_by_name\n"
         << "6) add_user\n"
         << "7) user_borrow_book\n"
         << "8) user_return_book\n"
         << "9) print_users\n"
         << "10) Exit\n";

    int choice;
    do {
        cout << "Enter your menu choice [1 - 10]: ";
        cin >> choice;
    } while (!(choice >= 1 && choice <= 10));
    return choice;
}

void mainMenu() {
    Book books[100];
    User users[100];

    while (true) {
        int choice = getChoice();

        switch (choice) {
            case 1: {
                string bookName;
                int quantity;
                cout << "Enter book info (name & total quantity): ";
                cin >> bookName >> quantity;
                books[Book::numBooks++] = Book(bookName, quantity);
                break;
            }
            case 2: {
                string prefix;
                cout << "Enter book name prefix: ";
                cin >> prefix;
                search_for_book(prefix, books);
                break;
            }
            case 3: {
                string bookName;
                cout << "Enter book name: ";
                cin >> bookName;
                print_who_borrowed_book_by_name(books, bookName);
                break;
            }
            case 4: {
                print_by_id(books);
                break;
            }
            case 5: {
                print_by_name(books);
                break;
            }
            case 6: {
                string userName;
                int userId;
                cout << "Enter user name & national id: ";
                cin >> userName >> userId;
                users[User::numberOfstudents++] = User(userName, userId);
                break;
            }
            case 7: {
                string userName, bookName;
                cout << "Enter user name and book name: ";
                cin >> userName >> bookName;
                user_borrow_books(users, books, userName, bookName);
                break;
            }
            case 8: {
                string userName, bookName;
                cout << "Enter user name and book name: ";
                cin >> userName >> bookName;
                user_return_books(users, books, userName, bookName);
                break;
            }
            case 9: {
                print_users(users);
                break;
            }
            case 10: {
                return;
            }
        }
    }
}

int main() {
    mainMenu();
    return 0;
}