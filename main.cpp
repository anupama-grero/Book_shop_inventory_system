#include <iostream>

#include <fstream>

#include <string>

#include <ctime>

#include <vector>

#include <iomanip>

#include <windows.h>

using namespace std;

void dashboard();
void menu();
void inventory_Report();

void owner()
{
    int number;
    cout << "\n------------------------Minsara Book Shop------------------------" << endl << endl;
    cout << "1. Inventory Management" << endl;
    cout << "2. Exit" << endl;
    cout << "\n-----------------------------------------------------------------" << endl << endl;
    cout << "Enter the number you want log: ";
    cin >> number;
    switch (number)
    {
    case 1:
        cout << "-------------------------Sales Report-------------------------" << endl << endl;
        inventory_Report();
        break;

    case 2:
        break;
    }
}

void cashier()
{
    int invo_num;
    string user_name;
    cout << "                            INVOICE                              \n" << endl;
    cout << "------------------------Minsara Book Shop------------------------\n" << endl;
    cout << "                       #134, Colombo Road                        " << endl;
    cout << "                            Negombo                              " << endl;
    cout << "                         Tel: 0317362833                         " << endl;
    time_t tt;
    struct tm * ti;
    time(&tt);
    ti = localtime(&tt);
    cout << "Date and Time: \t" << asctime(ti) << endl;
    cout << "Invoice No: ";
    cin >> invo_num;
    cout << "User: ";
    cin >> user_name;
    cout << endl << endl;

    ifstream inventoryFile("item_data.txt");

    if (!inventoryFile.is_open())
    {
        cerr << "Error: Unable to open file for reading.\n";
        return;
    }

    string description;
    int quantity, item_id;
    double price, total_amount = 0.0, cash_received, balance;

    while (true)
    {
        cout << "Enter item id (or '0' to finish): ";
        cin >> item_id;

        if (item_id == 0)
        {
            break;
        }

        bool item_found = false;
        inventoryFile.clear();
        inventoryFile.seekg(0);

        string line;
        while (getline(inventoryFile, line))
        {
            stringstream lineStream(line);
            int id;
            string tempDescription;
            double tempPrice;

            lineStream >> id >> tempDescription >> tempPrice;

            if (id == item_id)
            {
                item_found = true;
                description = tempDescription;
                price = tempPrice;

                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "\n";
                cout << "----------------------------------------\n\n";
                cout << "Item: " << setw(30) << left << description << endl;
                cout << "Quantity: " << setw(20) << right << quantity << endl;
                cout << "Price/Unit: " << setw(20) << right << fixed << setprecision(2) << price << endl;

                double item_total = quantity * price;
                total_amount += item_total;

                cout << "Total: " << setw(25) << right << fixed << setprecision(2) << item_total << endl;
                cout << "----------------------------------------\n\n";

                break;
            }
        }

        if (!item_found)
        {
            cout << "Item not found in inventory." << endl;
        }
    }

    inventoryFile.close();

    cout << endl;
    cout << "\t Total Amount: " << fixed << setprecision(2) << " Rs. " << total_amount << endl << endl;

    cout << "Enter cash received: Rs. ";
    cin >> cash_received;
    balance = cash_received - total_amount;

    cout << endl;
    cout << "Cash Received: " << fixed << setprecision(2) << " Rs. " << cash_received << endl << endl;
    cout << "Balance: " << fixed << setprecision(2) <<  " Rs. " << balance << endl << endl;

    cout << "Thank You! Have a nice day!" << endl << endl;

    menu();

    dashboard();
}

struct Item
{
    int id;
    int quantity;
    string description;
    double selling_price;
    double purchase_price;
    double profit;
    int Quantity;
};

void inventory()
{
    int n;

    cout << "Enter the number of items: ";
    cin >> n;
    cout << endl;

    vector<Item> items(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter details for item " << i + 1 << ": \n";
        cout << "Item ID: ";
        cin >> items[i].id;

        cout << "Description: ";
        cin.ignore();
        getline(cin, items[i].description);

        cout << "Selling Price (Rs.): ";
        cin >> items[i].selling_price;

        cout << "Purchase Price (Rs.): ";
        cin >> items[i].purchase_price;

        cout << "Quantity: ";
        cin >> items[i].quantity;

        items[i].profit = items[i].selling_price - items[i].purchase_price;

        cout << "\n";
    }

    ofstream outputFile("item_data.txt");

    if (outputFile.is_open())
    {
        outputFile << left
        << setw(10) << "Item ID"
        << setw(20) << "Description"
        << setw(20) << "Selling Price(Rs.)"
        << setw(20) << "Purchase Price(Rs.)"
        << setw(20) << "Quantity"
        << setw(20) << "Profit(Rs.)" << endl;

        for (int i = 0; i < n; i++)
        {
            outputFile << left
            << setw(10) << items[i].id
            << setw(20) << items[i].description
            << setw(20) << items[i].selling_price
            << setw(20) << items[i].purchase_price
            << setw(20) << items[i].quantity
            << setw(20) << items[i].profit << endl;
        }

        outputFile.close();

        cout << "Item data written to item_data.txt\n";
    }
    else
    {
        cerr << "File Was not Found.\n";
    }
}

void inventory_Report()
{
    ifstream inputFile("item_data.txt");

    if (!inputFile.is_open())
    {
        cerr << "File Was not Found.\n";
        return;
    }

    cout << "* Inventory Report *" << endl;

    string line;

    while (getline(inputFile, line))
    {
        cout << line << endl;
    }

    inputFile.close();
    menu();
    dashboard();
}

void report()
{
    fstream outputFile;
    outputFile.open("item_data.txt", ios::in);

    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for reading.\n";
        return;
    }

    cout << "Displaying contents of 'item_data.txt':\n";
    string line;

    while (getline(outputFile, line))
    {
        cout << line << endl;
    }

    outputFile.close();
}



void dashboard()
{
    char letter;
    cout << "Enter your logging letter: ";
    cin >> letter;
    cout << "\n----------------------------------------------------------" << endl;
    switch (letter)
    {
    case 'O':
        owner();
        break;

    case 'C':
        cashier();
        break;

    case 'I':
        inventory();
        break;

    case 'E':
        break;
    }
}

void menu()
{
    cout << "\n---------------------Minsara Book Shop---------------------\n" << endl;
    cout << "1. Owner Dashboard(O)" << endl;
    cout << "2. Cashier Billing System(C)" << endl;
    cout << "3. Inventory Management(I)" << endl;
    cout << "4. Exit(E)" << endl;
    cout << "\n------------------------------------------------------------\n" << endl;
}

void login()
{
    string username = "admin", password = "temp@123", uname1, pswrd1, ans, pswrd2, pswrd3;
    for(int i = 0; i < 1; i++)
    {
        cout << "Enter the Username: ";
        cin >> uname1;
        cout << "Enter the Password: ";
        cin >> pswrd1;
        if (username == uname1 and password == pswrd1)
        {
            cout << "--------------------------Welcome!--------------------------\n" << endl;

            menu();
            dashboard();

            break;
        }
        else
        {
            cout << "Invalid Username or Password. Try again!" << endl;
            for(int i = 0; i < 2; i++)
            {
                cout << "Enter the Username: ";
                cin >> uname1;
                cout << "Enter the Password: ";
                cin >> pswrd1;
                break;
            }
            if (username == uname1 and password == pswrd1)
            {
                cout << "--------------------------Welcome!--------------------------\n" << endl;

                menu();
                dashboard();

                break;
            }
            else
            {
                 cout << "Invalid Username or Password. Try again!" << endl;

            for(int i = 0; i < 2; i++)
            {
                cout << "Enter the Username: ";
                cin >> uname1;
                cout << "Enter the Password: ";
                cin >> pswrd1;
                break;
            }
            if (username == uname1 and password == pswrd1)
            {
                cout << "--------------------------Welcome!--------------------------\n" << endl;

                menu();
                dashboard();

                break;
            }
            else
            {
                cout << "Forget your Password? " << endl;
                cout << "Enter \"Yes\" or \"No\": ";
                cin >> ans;
                if(ans == "Yes")
                {
                    cout << "Enter your Username: ";
                    cin >> uname1;
                    if(uname1 == username)
                    {
                        cout << "Enter your New Password: ";
                        cin >> pswrd2;
                        cout << "Confirm your Password: ";
                        cin >> pswrd3;
                        if(pswrd2 == pswrd3)
                        {
                            cout << "Password changed successfully!\n" << endl;
                            cout << "---------------------------------------------\n" << endl;
                            menu();
                            dashboard();
                            break;
                        }
                        else
                        {
                            cout << "Password doesn't matched! " << endl;
                            break;
                        }
                    }
                    else
                    {
                        cout << "ERROR!" << endl;
                        cout << "You cannot logging to the system!" << endl;
                        break;
                    }
                }
                else
                {
                    cout << "You cannot logging because you\'ve failed 3 times. Please contact owner of the shop!" << endl;
                }
            }
            }
        }
    }
}

int main()
{
    //Welcome

    system("Color F0"); //Background color

    cout << "-----------------Minsara Book Shop-----------------" << endl << endl;

    login();
    return 0;
}
