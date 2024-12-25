#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Product structure
struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

// Admin and User Credentials
const string adminUsername = "admin";
const string adminPassword = "password";
const string userUsername = "user";
const string userPassword = "1234";

// Global product list
vector<Product> products;

// Function prototypes
void adminPanel();
void userPanel();
void addProduct();
void viewProducts();
void editProduct();
void deleteProduct();
void generateBill();
void generateReport();
void loadProducts();
void saveProducts();

int main() {
    int choice;
    loadProducts(); // Load products from file

    do {
        cout << "\n===== Billing System =====\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, password;
                cout << "\nAdmin Login\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (username == adminUsername && password == adminPassword) {
                    adminPanel();
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "\nUser Login\n";
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (username == userUsername && password == userPassword) {
                    userPanel();
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }
            case 3:
                cout << "Exiting...\n";
                saveProducts(); // Save products to file
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}

// Admin panel
void adminPanel() {
    int choice;
    do {
        cout << "\n===== Admin Panel =====\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Edit Product\n";
        cout << "4. Delete Product\n";
        cout << "5. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                editProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

// User panel
void userPanel() {
    int choice;
    do {
        cout << "\n===== User Panel =====\n";
        cout << "1. View Products\n";
        cout << "2. Generate Bill\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                generateBill();
                break;
            case 3:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

// Add a new product
void addProduct() {
    Product p;
    cout << "Enter Product ID: ";
    cin >> p.id;
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Product Price: ";
    cin >> p.price;
    cout << "Enter Product Quantity: ";
    cin >> p.quantity;

    products.push_back(p);
    cout << "Product added successfully!\n";
}

// View all products
void viewProducts() {
    cout << "\n===== Product List =====\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << "Quantity\n";
    cout << "------------------------------------------\n";
    for (const auto& p : products) {
        cout << left << setw(10) << p.id << setw(20) << p.name << setw(10) << p.price << p.quantity << endl;
    }
}

// Edit a product
void editProduct() {
    int id;
    cout << "Enter Product ID to edit: ";
    cin >> id;

    for (auto& p : products) {
        if (p.id == id) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, p.name);
            cout << "Enter new price: ";
            cin >> p.price;
            cout << "Enter new quantity: ";
            cin >> p.quantity;
            cout << "Product updated successfully!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// Delete a product
void deleteProduct() {
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == id) {
            products.erase(it);
            cout << "Product deleted successfully!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// Generate a bill
void generateBill() {
    int id, qty;
    double total = 0;
    vector<pair<string, double>> bill;

    cout << "\nEnter products to purchase (0 to stop):\n";
    while (true) {
        cout << "Product ID: ";
        cin >> id;
        if (id == 0) break;

        cout << "Quantity: ";
        cin >> qty;

        for (auto& p : products) {
            if (p.id == id) {
                if (qty > p.quantity) {
                    cout << "Insufficient stock!\n";
                } else {
                    double cost = p.price * qty;
                    total += cost;
                    bill.push_back({p.name, cost});
                    p.quantity -= qty;
                }
                break;
            }
        }
    }

    // Display bill
    cout << "\n===== Bill =====\n";
    for (const auto& item : bill) {
        cout << left << setw(20) << item.first << "Rs. " << item.second << endl;
    }
    cout << "Total: Rs. " << total << endl;
}

// Save products to file
void saveProducts() {
    ofstream file("products.txt");
    for (const auto& p : products) {
        file << p.id << "|" << p.name << "|" << p.price << "|" << p.quantity << endl;
    }
    file.close();
}

// Load products from file
void loadProducts() {
    ifstream file("products.txt");
    if (!file.is_open()) return;

    Product p;
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        pos = line.find('|');
        p.id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        p.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        p.price = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        p.quantity = stoi(line);
        products.push_back(p);
    }
    file.close();
}

