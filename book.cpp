#include <sstream>
#include "book.h"

using namespace std;

// Default constructor
Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerName("") {}

// Parameterized constructor
Book::Book(const string& title, const string& author, const string& isbn) 
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerName("") {}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
bool Book::getAvailability() const { return isAvailable; }
string Book::getBorrowerName() const { return borrowerName; }

// Setters
void Book::setTitle(const string& title) { this->title = title; }
void Book::setAuthor(const string& author) { this->author = author; }
void Book::setISBN(const string& isbn) { this->isbn = isbn; }
void Book::setAvailability(bool available) { this->isAvailable = available; }
void Book::setBorrowerName(const string& name) { this->borrowerName = name; }

// Check out book
void Book::checkOut(const string& borrower) {
    if (isAvailable) {
        isAvailable = false;
        borrowerName = borrower;
    }
}

// Return book
void Book::returnBook() {
    isAvailable = true;
    borrowerName = "";
}

// Display book information
string Book::toString() const {
    string result = "Titre: " + title + "\nAuteur: " + author + "\nISBN: " + isbn + 
                   "\nDisponible: " + (isAvailable ? "Oui" : "Non");
    
    if (!isAvailable && !borrowerName.empty()) {
        result += "\nEmprunté par: " + borrowerName;
    }
    
    return result;
}

// Format for file storage
string Book::toFileFormat() const {
    string result = title + "|" + author + "|" + isbn + "|" + (isAvailable ? "1" : "0") + "|";
    if (!isAvailable) {
        result += borrowerName;
    }
    return result;
}

// Parse from file format
void Book::fromFileFormat(const string& line) {
    stringstream ss(line);
    string token;
    
    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');
    
    string availableStr;
    getline(ss, availableStr, '|');
    isAvailable = (availableStr == "1");
    
    getline(ss, borrowerName, '|');
    if (isAvailable) {
        borrowerName = "";
    }
}