#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
	
string username, password;

struct MenuItem {
    string name;
    double price;
};

vector<MenuItem> menu;

// Function to sign up a new user
void SignUp() {
    cout << "Enter a username: ";
    cin >> username;

    cout << "Enter a password: ";
    cin >> password;

    // Open the file in append mode
    ofstream outfile("users.txt", ios::app);

    if (outfile.is_open()) {
        outfile << username << " " << password << endl;
        cout << "User signed up successfully!" << endl;
        outfile.close();
    }
    else {
        cerr << "Error: Unable to open the file." << endl;
    }
}

// Function for customer login
bool CustomerLogin() {
    bool customerLoggedIn = false; // Flag to check if the customer is logged in

    string enteredUsername, enteredPassword;

    cout << "Enter your username: ";
    cin >> enteredUsername;

    cout << "Enter your password: ";
    cin >> enteredPassword;

    // Open the file in read mode
    ifstream infile("users.txt");

    if (infile.is_open()) {
        bool found = false;
        string storedUsername, storedPassword;

        while (infile >> storedUsername >> storedPassword) {
            if (storedUsername == enteredUsername && storedPassword == enteredPassword) {
                found = true;
                break;
            }
        }

        infile.close();

        if (found) {
            cout << "Customer login successful!" << endl;
            customerLoggedIn = true; // Set the flag to true
            // Add your customer-specific functionality here
        } else {
            cout << "Customer login failed!! Please enter a valid username and password." << endl;
        }
    }
    else {
        cerr << "Error: Unable to open the file." << endl;
    }

    return customerLoggedIn;
}

// Function for admin login
bool AdminLogin() {
    string adminUsername = "admin";
    string adminPassword = "admin123";

    string enteredUsername, enteredPassword;

    cout << "Enter admin username: ";
    cin >> enteredUsername;

    cout << "Enter admin password: ";
    cin >> enteredPassword;

    if (enteredUsername == adminUsername && enteredPassword == adminPassword) {
        cout << "Admin login successful!" << endl;
        // Add your admin-specific functionality here
        return true;
    } else {
        cout << "Admin login failed!! Please enter a valid username and password." << endl;
        return false;
    }
}

// Function to add a new item to the menu
void AddMenuItem() {
    string itemName;
    double itemPrice;

    cout << "Enter the name of the new item: ";
    cin.ignore(); // Ignore any newline characters left in the input buffer
    getline(cin, itemName); // Use getline to read the whole line, including spaces

    cout << "Enter the price of the new item: ";
    cin >> itemPrice;

    MenuItem newItem;
    newItem.name = itemName;
    newItem.price = itemPrice;

    menu.push_back(newItem);

    cout << "Item added to the menu successfully!" << endl;
}

// Function to delete an item from the menu
void DeleteMenuItem() {
    int itemNumber;

    cout << "Enter the number of the item to delete: ";
    cin >> itemNumber;

    if (itemNumber >= 1 && itemNumber <= menu.size()) {
        cout << "Item '" << menu[itemNumber - 1].name << "' deleted from the menu." << endl;
        menu.erase(menu.begin() + itemNumber - 1);
    } else {
        cout << "Invalid item number." << endl;
    }
}

// Function for customer logout
void CustomerLogout(bool& customerLoggedIn) {
    cout << "you're logging out!!" << endl;
    customerLoggedIn = false; // Set the flag to false
}

// Function to display the menu
void DisplayMenu(bool customerLoggedIn, bool adminLoggedIn) {
    if (!customerLoggedIn && !adminLoggedIn) {
        cout << "Please login first." << endl;
        return;
    }

    if (customerLoggedIn) {
        // Display the menu for customers
        int order, no_deals;
        double totalBill = 0.0;

        cout << "|*---------------------------MENU-----------------------------*|" << endl;
        cout << endl;

        for (int i = 0; i < menu.size(); ++i) {
            cout << "(" << i + 1 << ")    " << menu[i].name << "    Rs" << menu[i].price << endl;
        }

        cout << endl;

        while (true) {
            cout << "Please select the item number (0 to finish, 7 to logout): ";
            cin >> order;

            if (order == 0) {
                break;  // Finish ordering
            }
            else if (order == 7) {
                CustomerLogout(customerLoggedIn); // Logout the customer
                break;
            }

            if (order > 0 && order <= menu.size()) {
                cout << "Please enter the number of items: ";
                cin >> no_deals;

                if (no_deals > 0) {
                    cout << "Order : " << menu[order - 1].name << endl;
                    cout << "Number of items : " << no_deals << endl;
                    cout << "Price of each item: Rs" << menu[order - 1].price << " only." << endl;
                    totalBill += menu[order - 1].price * no_deals;
                } else {
                    cout << "Invalid number of items. Please enter a positive number." << endl;
                }
            } else {
                cout << "Invalid item number. Please select a valid item." << endl;
            }
        }

        cout << "Total bill: Rs" << totalBill << " only." << endl;
        cout << "Thank you for your order!" << endl;
        
    }

    if (adminLoggedIn) {
        // Display the menu for admins
        int adminChoice;

        cout << "Admin Menu:" << endl;
        cout << "1. Add Item to Menu" << endl;
        cout << "2. Delete Item from Menu" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice) {
            case 1:
                AddMenuItem();
                break;
            case 2:
                DeleteMenuItem();
                break;
            case 3:
                // Do nothing, return to the main menu
                break;
            case 4:
                cout << "you're logging out!!'" << endl;
                adminLoggedIn = false; // Logout the admin
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
// Function to display the login options
void Login(bool& customerLoggedIn, bool& adminLoggedIn) {
    int choice;
    cout << "1. Admin Login" << endl;
    cout << "2. Customer Login" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            adminLoggedIn = AdminLogin();
            break;

        case 2:
            customerLoggedIn = CustomerLogin();
            break;

        case 3:
            // Do nothing, return to the main menu
            break;

        default:
            cout << "Please select one from the above options." << endl;
    }
}
void Help() {
	cout<<"Contact buntalks@gmail.com for any help."<<endl;
}
// Function to display the main menu
void MainMenu() {
    bool customerLoggedIn = false;
    bool adminLoggedIn = false;

    int choice;

    do {
        cout << "1. Signup\n2. Login\n3. Exit\n4. Help\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                SignUp();
                break;
            case 2:
                Login(customerLoggedIn, adminLoggedIn);
                break;
            case 3:
                cout << "Goodbye!" << endl;
            case 4:
            	cout<<"Contact buntalks@gmail.com for any help."<<endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (customerLoggedIn || adminLoggedIn) {
            // If either a customer or admin is logged in, show the menu
            DisplayMenu(customerLoggedIn, adminLoggedIn);
        }
    } while (choice != 3);
}

int main() {
	
	cout<<"___________________WELCOME TO BUN TALKS_________________________"<<endl;
    // Initialize the menu with some default items
    MenuItem item1 = {"Rotti", 50};
    MenuItem item2 = {"Pancake", 120};
    MenuItem item3 = {"Mixed Vegetable Curry", 350};
    MenuItem item4 = {"Bread with Sambol and Dhal Curry", 400};
    MenuItem item5 = {"Kiribath (Two Pieces) with Katta Sambol", 750};
    MenuItem item6 = {"Red Rice with Potato Curry or Dhal Curry and Fish Ambulthiyal", 850};

    menu.push_back(item1);
    menu.push_back(item2);
    menu.push_back(item3);
    menu.push_back(item4);
    menu.push_back(item5);
    menu.push_back(item6);

    MainMenu();  // Display the main menu
    return 0;
    
    
}
