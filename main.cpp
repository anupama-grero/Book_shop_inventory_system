#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <sstream>

using namespace std;

// --- Struct Definition ---
struct Item 
{
    int id;
    string description;
    double selling_price;
    double purchase_price;
    int quantity;
    double profit;
};

void printSeparator() 
{
    cout << "+----------+----------------------+---------------+---------------+----------+----------+" << endl;
}

void fileSeparator(ofstream &f) 
{
    f << "+----------+----------------------+---------------+---------------+----------+----------+" << endl;
}

// --- Function Prototypes ---
void login();
void menu();
void dashboard();
void owner();
void cashier();
void inventory_Save();   
void inventory_Report(); 
void inventory_Update(); 

int main() 
{
    system("Color F0"); 
    cout << "----------------- Minsara Book Shop -----------------" << endl << endl;
    login();
    return 0;
}

// --- Login System ---
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

// --- Menu Design ---
void menu() 
{
    cout << "\n---------------------Minsara Book Shop---------------------\n" << endl;
    cout << "1. Owner Dashboard(O)" << endl;
    cout << "2. Cashier Billing System(C)" << endl;
    cout << "3. Inventory Management(I)" << endl;
    cout << "4. Exit(E)" << endl;
    cout << "\n------------------------------------------------------------\n" << endl;
}

void dashboard() 
{
    char letter;
    while (true) 
    {
        menu();
        cout << "Enter your logging letter: ";
        cin >> letter;

        letter = toupper(letter);

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
                inventory_Save(); 
                break;

            case 'E': 
                exit(0);

            default: 
                cout << "Invalid Selection." << endl;
        }
    }
}

// --- 1. SAVE: Creating visual tables in text.txt ---
void inventory_Save() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    // Check if file is empty to write header
    ifstream checkFile("text.txt");
    bool isEmpty = (checkFile.peek() == ifstream::traits_type::eof());
    checkFile.close();

    ofstream outputFile("text.txt", ios::app);

    if (outputFile.is_open()) 
    {
        if (isEmpty) 
        {
            fileSeparator(outputFile);

            outputFile << "| " << left << setw(8) << "ID" 
                       << "| " << setw(20) << "Description" 
                       << "| " << setw(13) << "Selling(Rs)" 
                       << "| " << setw(13) << "Purchase(Rs)" 
                       << "| " << setw(8) << "Qty" 
                       << "| " << setw(8) << "Profit" << " |" << endl;
            fileSeparator(outputFile);
        }

        for (int i = 0; i < n; i++) 
        {
            Item itm;
            cout << "\n--- Item " << i + 1 << " ---" << endl;
            cout << "Item ID: "; 
            cin >> itm.id;

            cout << "Description: "; 
            cin.ignore(); 
            getline(cin, itm.description);

            cout << "Selling Price: "; 
            cin >> itm.selling_price;

            cout << "Purchase Price: "; 
            cin >> itm.purchase_price;

            cout << "Quantity: "; 
            cin >> itm.quantity;
            
            itm.profit = itm.selling_price - itm.purchase_price;

            outputFile << "| " << left << setw(8) << itm.id 
                       << "| " << setw(20) << (itm.description.substr(0, 20)) 
                       << "| " << setw(13) << fixed << setprecision(2) << itm.selling_price 
                       << "| " << setw(13) << itm.purchase_price 
                       << "| " << setw(8) << itm.quantity 
                       << "| " << setw(8) << itm.profit << " |" << endl;
            fileSeparator(outputFile);
        }
        outputFile.close();

        cout << "\nData saved successfully with borders.\n";
    }
}

// --- 2. GET: Reading data from the visual table ---
void inventory_Report() 
{
    ifstream inputFile("text.txt");
    string line;
    if (!inputFile) 
    {
        cout << "No inventory records found." << endl;
        return;
    }
    cout << "\n--- Inventory Report ---\n";
    while (getline(inputFile, line)) 
    {
        cout << line << endl;
    }
    inputFile.close();
}

// --- 3. UPDATE: Updating data within the table ---
void inventory_Update() 
{
    int targetId;
    cout << "Enter Item ID to edit: ";
    cin >> targetId;

    ifstream inputFile("text.txt");
    if (!inputFile) 
    { 
        cout << "Error opening file!"; 
        return; 
    }

    vector<string> fileLines;
    string line;
    bool found = false;

    while (getline(inputFile, line)) 
    {
        // Look for the ID inside the table row (ignoring separator lines)
        if (line[0] == '|') 
        {
            stringstream ss(line.substr(1, 10)); // Extract ID section
            int currentId;
            if (ss >> currentId && currentId == targetId) 
            {
                found = true;
                Item itm;
                itm.id = currentId;

                cout << "Record Found! Enter New Details:" << endl;

                cout << "New Description: "; 
                cin.ignore(); 
                getline(cin, itm.description);

                cout << "New Selling Price: "; 
                cin >> itm.selling_price;

                cout << "New Purchase Price: "; 
                cin >> itm.purchase_price;

                cout << "New Quantity: "; 
                cin >> itm.quantity;

                itm.profit = itm.selling_price - itm.purchase_price;

                // Re-construct the specific row string
                stringstream updatedLine;
                updatedLine << "| " << left << setw(8) << itm.id 
                            << "| " << setw(20) << (itm.description.substr(0, 20)) 
                            << "| " << setw(13) << fixed << setprecision(2) << itm.selling_price 
                            << "| " << setw(13) << itm.purchase_price 
                            << "| " << setw(8) << itm.quantity 
                            << "| " << setw(8) << itm.profit << " |";
                fileLines.push_back(updatedLine.str());
                continue;
            }
        }
        fileLines.push_back(line);
    }
    inputFile.close();

    if (found) 
    {
        ofstream outputFile("text.txt");
        for (const string& l : fileLines) outputFile << l << endl;
        outputFile.close();
        cout << "Item ID " << targetId << " has been edited successfully." << endl;
    } 
    else 
    {
        cout << "Item ID not found." << endl;
    }
}

void owner() 
{
    int num;
    cout << "\n1. Inventory Report\n2. Update Item\n3. Back\nChoice: ";
    cin >> num;
    if (num == 1) inventory_Report();
    else if (num == 2) inventory_Update();
}

void cashier()
{
    int invo_num;
    string user_name;
    cout << "                            INVOICE                               \n" << endl;
    cout << "------------------------Minsara Book Shop------------------------\n" << endl;
    cout << "                       #134, Colombo Road                         " << endl;
    cout << "                            Negombo                               " << endl;
    cout << "                         Tel: 0317362833                          " << endl;
    
    time_t tt;
    struct tm * ti;
    time(&tt);
    ti = localtime(&tt);
    cout << "Date and Time: \t" << asctime(ti); // asctime adds a newline
    
    cout << "Invoice No: ";
    cin >> invo_num;
    cout << "User: ";
    cin >> user_name;
    cout << endl;

    double total_amount = 0.0;

    while (true)
    {
        int search_id;
        cout << "Enter item id (or '0' to finish): ";
        cin >> search_id;

        if (search_id == 0) break;

        ifstream inventoryFile("text.txt");
        if (!inventoryFile.is_open()) 
        {
            cerr << "Error: Unable to open inventory file.\n";
            return;
        }

        string line;
        bool item_found = false;

        while (getline(inventoryFile, line))
        {
            // Only process lines that look like table data rows
            if (line.length() > 10 && line[0] == '|') 
            {
                // Extract the ID part (first column)
                stringstream ssId(line.substr(2, 8)); 
                int currentId;
                
                if (ssId >> currentId && currentId == search_id)
                {
                    item_found = true;
                    
                    // Extract Description (Column 2) and Price (Column 3)
                    // Based on your setw() in inventory_Save:
                    // ID starts at 2, Desc starts at 12, Price starts at 34
                    string description = line.substr(12, 20);
                    // Trim trailing spaces from description
                    description.erase(description.find_last_not_of(" \n\r\t")+1);

                    stringstream ssPrice(line.substr(34, 13));
                    double price;
                    ssPrice >> price;

                    int quantity;
                    cout << "Item: " << description << " (Rs. " << fixed << setprecision(2) << price << ")" << endl;
                    cout << "Enter quantity: ";
                    cin >> quantity;

                    double item_total = quantity * price;
                    total_amount += item_total;

                    cout << "\n----------------------------------------\n";
                    cout << left << setw(20) << "Item" << ": " << description << endl;
                    cout << left << setw(20) << "Qty" << ": " << quantity << endl;
                    cout << left << setw(20) << "Total" << ": Rs. " << item_total << endl;
                    cout << "----------------------------------------\n\n";
                    break; 
                }
            }
        }
        inventoryFile.close();

        if (!item_found)
        {
            cout << "Item [" << search_id << "] not found in inventory.\n" << endl;
        }
    }

    // Final calculations
    cout << "\n" << string(40, '=') << endl;
    cout << "TOTAL AMOUNT: Rs. " << fixed << setprecision(2) << total_amount << endl;
    cout << string(40, '=') << endl;

    if (total_amount > 0) {
        double cash_received;
        cout << "Enter cash received: Rs. ";
        cin >> cash_received;
        cout << "Balance: Rs. " << (cash_received - total_amount) << endl;
    }

    cout << "\nThank You! Have a nice day!\n" << endl;
}