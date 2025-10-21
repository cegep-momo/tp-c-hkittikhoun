#include <iostream>
#include <algorithm>

#include "library.h"

using namespace std;

// Constructor
Library::Library() {}

// Add book to library
void Library::addBook(const Book& book) {
    books.push_back(make_unique<Book>(book));
}

// Remove book from library
bool Library::removeBook(const string& isbn) {
    Book* book = findBookByISBN(isbn);
    if (!book) {
        return false;
    }

    // Show book details and ask for confirmation
    if (!confirmBookDeletion(book->toString())) {
        cout << "Suppression annulée.\n";
        return false;
    }
    
    auto it = find_if(books.begin(), books.end(),
        [&isbn](const unique_ptr<Book>& book) {
            return book->getISBN() == isbn;
        });
    
    if (it != books.end()) {
        books.erase(it);
        return true;
    }
    return false;
}

// Find book by ISBN
Book* Library::findBookByISBN(const string& isbn) {
    auto it = find_if(books.begin(), books.end(),
        [&isbn](const unique_ptr<Book>& book) {
            return book->getISBN() == isbn;
        });
    
    return (it != books.end()) ? it->get() : nullptr;
}

// Search books by title (case-insensitive partial match)
vector<Book*> Library::searchBooksByTitle(const string& title) {
    vector<Book*> results;
    string lowerTitle = title;
    transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
    
    for (auto& book : books) {
        string bookTitle = book->getTitle();
        transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);
        
        if (bookTitle.find(lowerTitle) != string::npos) {
            results.push_back(book.get());
        }
    }
    return results;
}

// Search books by author (case-insensitive partial match)
vector<Book*> Library::searchBooksByAuthor(const string& author) {
    vector<Book*> results;
    string lowerAuthor = author;
    transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
    
    for (auto& book : books) {
        string bookAuthor = book->getAuthor();
        transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);
        
        if (bookAuthor.find(lowerAuthor) != string::npos) {
            results.push_back(book.get());
        }
    }
    return results;
}

// Get all available books
vector<Book*> Library::getAvailableBooks() {
    vector<Book*> available;
    for (auto& book : books) {
        if (book->getAvailability()) {
            available.push_back(book.get());
        }
    }
    return available;
}

// Get all books
vector<Book*> Library::getAllBooks() {
    vector<Book*> allBooks;
    for (auto& book : books) {
        allBooks.push_back(book.get());
    }
    return allBooks;
}

// Add user to library
void Library::addUser(const User& user) {
    users.push_back(make_unique<User>(user));
}

// Find user by ID
User* Library::findUserById(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [&userId](const unique_ptr<User>& user) {
            return user->getUserId() == userId;
        });
    
    return (it != users.end()) ? it->get() : nullptr;
}

// Get all users
vector<User*> Library::getAllUsers() {
    vector<User*> allUsers;
    for (auto& user : users) {
        allUsers.push_back(user.get());
    }
    return allUsers;
}

// Check out book
bool Library::checkOutBook(const string& isbn, const string& userId) {
    Book* book = findBookByISBN(isbn);
    User* user = findUserById(userId);
    
    if (book && user && book->getAvailability()) {
        book->checkOut(user->getName());
        user->borrowBook(isbn);
        return true;
    }
    return false;
}

// Return book
bool Library::returnBook(const string& isbn) {
    Book* book = findBookByISBN(isbn);
    
    if (book && !book->getAvailability()) {
        // Find the user who borrowed this book
        for (auto& user : users) {
            if (user->hasBorrowedBook(isbn)) {
                user->returnBook(isbn);
                break;
            }
        }
        book->returnBook();
        return true;
    }
    return false;
}

// Display all books
void Library::displayAllBooks() {
    if (books.empty()) {
        cout << "Aucun livre dans la bibliothèque.\n";
        return;
    }
    
    cout << "\n=== TOUS LES LIVRES ===\n";
    for (size_t i = 0; i < books.size(); ++i) {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << books[i]->toString() << "\n";
        cout << "-------------------------\n";
    }
}

// Display available books
void Library::displayAvailableBooks() {
    auto available = getAvailableBooks();
    
    if (available.empty()) {
        cout << "Aucun livre disponible pour emprunt.\n";
        return;
    }
    
    cout << "\n=== LIVRES DISPONIBLES ===\n";
    for (size_t i = 0; i < available.size(); ++i) {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << available[i]->toString() << "\n";
        cout << "---------------------------\n";
    }
}

// Display all users
void Library::displayAllUsers() {
    if (users.empty()) {
        cout << "Aucun utilisateur enregistré.\n";
        return;
    }
    
    cout << "\n=== TOUS LES UTILISATEURS ===\n";
    for (size_t i = 0; i < users.size(); ++i) {
        cout << "\nUtilisateur " << (i + 1) << " :\n";
        cout << users[i]->toString() << "\n";
        cout << "------------------------------\n";
    }
}

// Statistics
int Library::getTotalBooks() const { return books.size(); }
int Library::getAvailableBookCount() const {
    return count_if(books.begin(), books.end(),
        [](const unique_ptr<Book>& book) {
            return book->getAvailability();
        });
}
int Library::getCheckedOutBookCount() const { return getTotalBooks() - getAvailableBookCount(); }

// Confirmation before deletion of a book
bool Library::confirmBookDeletion(const string& bookInfo) {
    cout << "\n=== CONFIRMATION DE SUPPRESSION DE LIVRE ===\n";
    cout << "Vous êtes sur le point de supprimer ce livre :\n";
    cout << bookInfo << "\n";
    cout << "Cette action est irréversible.\n";
    cout << "Confirmez-vous la suppression ? (oui/non) : ";

    string response;
    getline(cin, response);

    // Convert response to lowercase for comparison
    transform(response.begin(), response.end(), response.begin(), ::tolower);

    return (response == "oui" || response == "o" || response == "yes" || response == "y");
}

// Get all books sorted by title
vector<Book*> Library::getAllBooksSortedByTitle() {
    auto allBooks = getAllBooks();
    sort(allBooks.begin(), allBooks.end(),
        [](Book* a, Book* b) {
            return a->getTitle() < b->getTitle();
        });
    return allBooks;
}

// Get all books sorted by author
vector<Book*> Library::getAllBooksSortedByAuthor() {
    auto allBooks = getAllBooks();
    sort(allBooks.begin(), allBooks.end(),
        [](Book* a, Book* b) {
            return a->getAuthor() < b->getAuthor();
        });
    return allBooks;
}

// Get available books sorted by title
vector<Book*> Library::getAvailableBooksSortedByTitle() {
    auto availableBooks = getAvailableBooks();
    sort(availableBooks.begin(), availableBooks.end(),
        [](Book* a, Book* b) {
            return a->getTitle() < b->getTitle();
        });
    return availableBooks;
}

// Get available books sorted by author
vector<Book*> Library::getAvailableBooksSortedByAuthor() {
    auto availableBooks = getAvailableBooks();
    sort(availableBooks.begin(), availableBooks.end(),
        [](Book* a, Book* b) {
            return a->getAuthor() < b->getAuthor();
        });
    return availableBooks;
}

// Display all books sorted
void Library::displayAllBooksSorted(bool byTitle) {
    auto books = byTitle ? getAllBooksSortedByTitle() : getAllBooksSortedByAuthor();
    
    if (books.empty()) {
        cout << "Aucun livre dans la bibliothèque.\n";
        return;
    }
    
    cout << "\n=== TOUS LES LIVRES (Triés par " << (byTitle ? "Titre" : "Auteur") << ") ===\n";
    for (size_t i = 0; i < books.size(); ++i) {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << books[i]->toString() << "\n";
        cout << "-------------------------\n";
    }
}

// Display available books sorted
void Library::displayAvailableBooksSorted(bool byTitle) {
    auto books = byTitle ? getAvailableBooksSortedByTitle() : getAvailableBooksSortedByAuthor();
    
    if (books.empty()) {
        cout << "Aucun livre disponible pour emprunt.\n";
        return;
    }
    
    cout << "\n=== LIVRES DISPONIBLES (Triés par " << (byTitle ? "Titre" : "Auteur") << ") ===\n";
    for (size_t i = 0; i < books.size(); ++i) {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << books[i]->toString() << "\n";
        cout << "---------------------------\n";
    }
}