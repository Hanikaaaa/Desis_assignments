#include <bits/stdc++.h>
using namespace std;
class Book {
public:
    string title, author;
    double price, cost;
    int stock;
    Book(string t, string a, double p, double c, int s) 
        : title(t), author(a), price(p), cost(c), stock(s) {}
    void display() {
        cout << "Title: " << title << endl
             << "Author: " << author << endl
             << "Price: Rs" << price << endl
             << "Stock: " << stock << endl;
    }
};
class Magazine {
public:
    string title, issue;
    double price, cost;
    int stock;

    Magazine(string t, string i, double p, double c, int s) 
        : title(t), issue(i), price(p), cost(c), stock(s) {}

    void display() {
        cout << "Title: " << title << endl
             << "Issue: " << issue << endl
             << "Price: Rs" << price << endl
             << "Stock: " << stock << endl;
    }
};

class Inventory {
public:
    vector<Book> books;
    vector<Magazine> magazines;

    void addBook(const Book &b) { books.push_back(b); }
    void addMagazine(const Magazine &m) { magazines.push_back(m); }

    void displayAll() {
        cout << "Books available:" << endl;
        for (auto &b : books) b.display();
        cout << endl << "Magazines available:" << endl;
        for (auto &m : magazines) m.display();
        cout << endl;
    }

    bool sellBook(string title, int quantity) {
        for (auto &b : books) {
            if (b.title == title) {
                if (b.stock >= quantity) {
                    b.stock -= quantity;
                    cout << "Sold " << quantity << " copies of " << title << endl;
                    return true;
                } else {
                    cout << "Insufficient stock for " << title << endl;
                    return false;
                }
            }
        }
        cout << "Book " << title << " not found" << endl;
        return false;
    }

    bool sellMagazine(string title, int quantity) {
        for (auto &m : magazines) {
            if (m.title == title) {
                if (m.stock >= quantity) {
                    m.stock -= quantity;
                    cout << "Sold " << quantity << " copies of " << title << endl;
                    return true;
                } else {
                    cout << "Insufficient stock" << endl;
                    return false;
                }
            }
        }
        cout << "Magazine " << title << " not found" << endl;
        return false;
    }

    void restockBook(string title, int quantity) {
        for (auto &b : books) {
            if (b.title == title) {
                b.stock += quantity;
                cout << "Restocked " << quantity << " copies of '" << title << "'." << endl;
                return;
            }
        }
        cout << "Book '" << title << "' not available" << endl;
    }
};

class Customer {
public:
    string name;
    Customer(string n) : name(n) {}

    void buyBook(Inventory &inv, string bookname, int quantity) {
        cout << name << " is buying " << quantity << " copies of '" << bookname << "'." << endl;
        inv.sellBook(bookname, quantity);
    }
};

class Cashier {
public:
    string name;
    Cashier(string n) : name(n) {}
    void processSale(Inventory &inv, string bookname, int quantity) {
        cout << "Cashier: " << name << endl
             << "BOOKNAME: " << bookname << endl
             << "Number of copies: " << quantity << endl;
        inv.sellBook(bookname, quantity);
    }
};

class Manager {
public:
    string name;
    Manager(string n) : name(n) {}

    void restockInventory(Inventory &inv, string bookname, int quantity) {
        cout << "Manager: " << name << endl
             << "BOOKNAME: " << bookname << endl
             << "Number of copies: " << quantity << endl;
        inv.restockBook(bookname, quantity);
    }
};

int main() {
    Inventory inv;
    inv.addBook(Book("aanimuthyalu", "pandith", 159, 80, 10));
    inv.addMagazine(Magazine("Tech Weekly", "Issue 45", 69.9, 30.0, 20));
    inv.displayAll();
    cout << "--- Customer and Cashier Transactions ---" << endl;
    Cashier cashier("Bob");
    cashier.processSale(inv, "aanimuthyalu", 3);
    inv.displayAll();

    cout << "--- Manager Restocking Inventory ---" << endl;
    Manager mgr("Carol");
    mgr.restockInventory(inv, "aanimuthyalu", 10);
    inv.displayAll();

    return 0;
}
