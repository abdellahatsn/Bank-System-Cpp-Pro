#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

const string ClientsFileName = "ClientsFile.txt";
const string UsersFileName = "UsersFile.txt";
const string Seperator = "#//#";

enum enChoice 
{
    enShowClientList = 1, 
    enAddNewClient, 
    enDeleteClient, 
    enUpdateClientInfo, 
    enFindClient,
    enTransactions, 
    enManageUsers,
    enLogout
};

enum enTChoice 
{
    enDeposit = 1, 
    enWithdraw, 
    enTotalBalances, 
    enMainMenu,
};

enum enUserChoice 
{
    enUShowUserList = 1, 
    enUAddNewUser, 
    enUDeleteUser, 
    enUUpdateUserInfo, 
    enUFindUser,
    enUMainMenu,
};

enum enUserPermissions
{
    enPShowClientList = 1, 
    enPAddNewClient = 2, 
    enPDeleteClient = 4, 
    enPUpdateClientInfo = 8, 
    enPFindClient = 16,
    enPTransactions = 32, 
    enPManageUsers = 64,
};

struct stClient
{
  string AccountNumber;
  string PinCode;
  string Name;
  string Phone;
  double AccountBalance;  
  bool MarkForDelete = false;

};

struct stUser
{
  string UserName;
  string Password; 
  int Permissions;
  bool MarkForDelete = false;

};

void MainMenuScreen(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients);
void TransactionsMenuScreen(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients);
void Login(vector <stClient> &vClients, vector <stUser> &vUsers);
void ShowManageScreen(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients);

int ReadInt(string Message)
{
    int Number = 0;
    cout << Message;
    while (!(cin >> Number)) 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Number, Enter again: ";
    }
    return Number;
}

double ReadDouble(string Message)
{
    double Number = 0;
    cout << Message;
    while (!(cin >> Number)) 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Number, Enter again: ";
    }
    return Number;
}

string ReadStr(string Message = "Enter a string: ")
{
    string S;
    cout << Message;
    getline(cin >> ws, S);
    return S;
}

char ReadChar(string Message = "Enter a string: ")
{
    char c;
    cout << Message;
    cin >> c;
    cin.ignore(1, '\n');
    return c;
}

vector <string> split(string text, string delm)
{
    string word;
    vector <string> vWords;
    short pos;

    while((pos = text.find(delm)) != std::string::npos)
    {
        word = text.substr(0, pos);

        if(word != "")
        {
            vWords.push_back(word);
        }

        text.erase(0, pos + delm.length());
    }

    if(text != "")
    {
        vWords.push_back(text);
    }
    return vWords;
}

stClient ConvertLineToRecord(string ClientLine, string seperator = Seperator)
{
    vector <string> vClientRecord = split(ClientLine, seperator);
    stClient stClientRecord;

    stClientRecord.AccountNumber = vClientRecord[0];
    stClientRecord.PinCode = vClientRecord[1];
    stClientRecord.Name = vClientRecord[2];
    stClientRecord.Phone = vClientRecord[3];
    stClientRecord.AccountBalance = stod(vClientRecord[4]);

    return stClientRecord;
}

stUser ConvertLineToUserRecord(string UserLine, string seperator = Seperator)
{
    vector <string> vUserRecord = split(UserLine, seperator);
    stUser stUserRecord;

    stUserRecord.UserName = vUserRecord[0];
    stUserRecord.Password = vUserRecord[1];
    stUserRecord.Permissions = stoi(vUserRecord[2]);

    return stUserRecord;
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
    vector <stUser> stUsers;

    fstream UsersFile;
    UsersFile.open(FileName, ios::in);

    if (UsersFile.is_open())
    {
        string Line;
        stUser User;

        while(getline(UsersFile, Line))
        {
            User = ConvertLineToUserRecord(Line);
            stUsers.push_back(User);
        }

        UsersFile.close();
    }
    return stUsers;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
    vector <stClient> stClients;

    fstream ClientsFile;
    ClientsFile.open(FileName, ios::in);

    if (ClientsFile.is_open())
    {
        string Line;
        stClient Client;

        while(getline(ClientsFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            stClients.push_back(Client);
        }

        ClientsFile.close();
    }
    return stClients;
}

void PrintClientData(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintAllClientsData(vector <stClient> &vClients)
{
    cout << "\n\t\t\t\t    Client List (" << vClients.size() << ") Client(s)." << endl;
    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;

    for (stClient &Client : vClients)
    {
        PrintClientData(Client);
        cout << endl;
    }

    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;

}

void PrintUserData(stUser User)
{
    cout << "| " << left << setw(40) << User.UserName;
    cout << "| " << left << setw(12) << "********";
    cout << "| " << left << setw(12) << User.Permissions;
}

void PrintAllUsersData(vector <stUser> &vUsers)
{
    cout << "\n\t\t\t\t    User List (" << vUsers.size() << ") User(s)." << endl;
    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;
    cout << "| " << left << setw(40) << "Username";
    cout << "| " << left << setw(12) << "Password";
    cout << "| " << left << setw(12) << "Permissions";
    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;

    for (stUser &User : vUsers)
    {
        PrintUserData(User);
        cout << endl;
    }

    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;

}

void PrintClientMinData(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintAllClientsMinData(vector <stClient> &vClients)
{
    cout << "\n\t\t\t\t    Client List (" << vClients.size() << ") Client(s)." << endl;
    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;

    for (stClient &Client : vClients)
    {
        PrintClientMinData(Client);
        cout << endl;
    }

    cout << "\n---------------------------------------------------------------------";
    cout << "------------------------------\n" << endl;

}

bool FindClientByAccountNumber(vector <stClient> &vClients, string AccountNumber, stClient &Client)
{
    for (stClient &C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

bool FindUserByUserName(vector <stUser> &vUsers, string UserName, stUser &User)
{
    for (stUser &U : vUsers)
    {
        if(U.UserName == UserName)
        {
            User = U;
            return true;
        }
    }

    return false;
}

bool FindClientByAccountNumber(vector <stClient> &vClients, string AccountNumber)
{
    stClient Client;
    return FindClientByAccountNumber(vClients, AccountNumber, Client);
}

bool FindUserByUserName(vector <stUser> &vUsers, string UserName)
{
    stUser User;
    return FindUserByUserName(vUsers, UserName, User);
}

stClient ReadNewClient(vector <stClient> &vClients)
{
    stClient Client;

    cout << "Enter Account Number: ";
    getline(cin >> ws, Client.AccountNumber);

    while (FindClientByAccountNumber(vClients, Client.AccountNumber))
    {
        cout << "\nClient with [" << Client.AccountNumber 
        << "] already exists, Enter another Account Number: ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.Name);

    cout << "Enter Phone Number: ";
    getline(cin, Client.Phone);

    Client.AccountBalance = ReadDouble("Enter Account Balance: ");

    return Client;
}

string ConvertRecordToLine(stClient Client, string seperator = Seperator)
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + seperator;
    stClientRecord += Client.PinCode + seperator;
    stClientRecord += Client.Name + seperator;
    stClientRecord += Client.Phone + seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

string ConvertUserRecordToLine(stUser User, string seperator = Seperator)
{
    string stUserRecord = "";

    stUserRecord += User.UserName + seperator;
    stUserRecord += User.Password + seperator;
    stUserRecord += to_string(User.Permissions);

    return stUserRecord;
}

void AddDataLineToFile(string FileName, string DataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << DataLine << endl;
        MyFile.close();
    }
}

void AddNewClient(vector <stClient> &vClients)
{
    stClient Client = ReadNewClient(vClients);
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
    vClients.push_back(Client);
}

stUser ReadNewUser(vector <stUser> &vUsers)
{
    stUser User;
    User.Permissions = 0;

    cout << "Enter Username: ";
    getline(cin >> ws, User.UserName);

    while (FindUserByUserName(vUsers, User.UserName))
    {
        cout << "\nUsername [" << User.UserName 
        << "] already exists, Enter another Username: ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter Password: ";
    getline(cin >> ws, User.Password);

    if(tolower(ReadChar("All Permissions? (y/n)")) == 'y')
    {
        User.Permissions = -1;
        return User;
    }

    if(tolower(ReadChar("Show Client List Permission? (y/n)")) == 'y') User.Permissions++;
    if(tolower(ReadChar("Add New Client Permission? (y/n)")) == 'y') User.Permissions += 2;
    if(tolower(ReadChar("Delete Client Permission? (y/n)")) == 'y') User.Permissions += 4;
    if(tolower(ReadChar("Update Client Info Permission? (y/n)")) == 'y') User.Permissions += 8;
    if(tolower(ReadChar("Find Client Permission? (y/n)")) == 'y') User.Permissions += 16;
    if(tolower(ReadChar("Transactions Permission? (y/n)")) == 'y') User.Permissions += 32;
    if(tolower(ReadChar("Manage Users Permission? (y/n)")) == 'y') User.Permissions += 64;

    return User;
}

void AddNewUser(vector <stUser> &vUsers)
{
    stUser User = ReadNewUser(vUsers);
    AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
    vUsers.push_back(User);
}

void AddClients(vector <stClient> &vClients)
{
    char a = 'y';

    do
    {
        system("cls");
        cout << "Adding New Client\n" << endl;

        AddNewClient(vClients);
        cout << "Client Added successfully, do you want to add more clients ??\n";
        cin >> a;
        cin.ignore(1, '\n');
    } while(tolower(a) == 'y');

}

void AddUsers(vector <stUser> &vUsers)
{
    char a = 'y';

    do
    {
        system("cls");
        cout << "Adding New User\n" << endl;

        AddNewUser(vUsers);
        cout << "User Added successfully, do you want to add more users ??\n";
        cin >> a;
        cin.ignore(1, '\n');
    } while(tolower(a) == 'y');

}

void PrintClientRecord(stClient Client)
{
    cout << "The extracted Client Record: \n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "PinCode        : " << Client.PinCode << endl;
    cout << "Account Name   : " << Client.Name << endl;
    cout << "Phone Number   : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

void PrintUserRecord(stUser User)
{
    cout << "\nThe extracted User Record: \n";
    cout << "Username   : " << User.UserName << endl;
    cout << "Password   : " << "********" << endl;
    cout << "Permissions: " << User.Permissions << endl;
}

bool MakeClientForDeleteByAccountNumber(string AccountNumber, vector <stClient> &vClients)
{
    for (stClient &Client : vClients)
    {
        if(Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool MakeUserForDeleteByUserName(string UserName, vector <stUser> &vUsers)
{
    for (stUser &User : vUsers)
    {
        if(User.UserName == UserName)
        {
            User.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void SaveClientsDataToFile(string FileName, vector <stClient> &vClients)
{
    fstream ClientsFile;
    ClientsFile.open(FileName, ios::out);

    if(ClientsFile.is_open())
    {
        string DataLine;
        for (stClient &C : vClients)
        {
            if(!C.MarkForDelete)
            {
                DataLine = ConvertRecordToLine(C);
                ClientsFile << DataLine << endl;
            }
        }
        ClientsFile.close();
    }
}

void SaveUsersDataToFile(string FileName, vector <stUser> &vUsers)
{
    fstream UsersFile;
    UsersFile.open(FileName, ios::out);

    if(UsersFile.is_open())
    {
        string DataLine;
        for (stUser &U : vUsers)
        {
            if(!U.MarkForDelete)
            {
                DataLine = ConvertUserRecordToLine(U);
                UsersFile << DataLine << endl;
            }
        }
        UsersFile.close();
    }
}

bool DeleteClientByAccountNumber(vector <stClient> &vClients)
{
    string AccountNumber = ReadStr("Enter Account Number: ");
    stClient Client;
    char Answer = 'n';

    if(FindClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClientRecord(Client);
        
        cout << "Are you sure you wanna delete this client? ";
        cin >> Answer;
        cin.ignore(1,'\n');
        if(Answer == 'y' || Answer == 'Y')
        {
            MakeClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "Clients Deleted succefully" << endl;
            return true;
        }

    }
    else
    {
        cout << "Not Founded" << endl;
        return false;
    }
    return false;
}

bool DeleteUserByUserName(stUser Me, vector <stUser> &vUsers)
{
    string Username = ReadStr("Enter Username: ");

    while(Username == "Admin" || Username == Me.UserName)
    {
        cout << "You can't delete this user" << endl;
        Username = ReadStr("Enter Username: ");
    }

    stUser User;
    char Answer = 'n';

    if(FindUserByUserName(vUsers, Username, User))
    {
        PrintUserRecord(User);
        
        cout << "Are you sure you wanna delete this user? ";
        cin >> Answer;
        cin.ignore(1,'\n');
        if(Answer == 'y' || Answer == 'Y')
        {
            MakeUserForDeleteByUserName(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);

            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "User Deleted succefully" << endl;
            return true;
        }

    }
    else
    {
        cout << "Not Founded" << endl;
        return false;
    }
    return false;
}

stClient ChangeClientDetails(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.Name);

    cout << "Enter Phone Number: ";
    getline(cin, Client.Phone);

    Client.AccountBalance = ReadDouble("Enter Account Balance: ");

    return Client;
}

stUser ChangeUserDetails(string Username)
{
    stUser User;

    User.UserName = Username;

    cout << "Enter Password: ";
    getline(cin >> ws, User.Password);

    if(tolower(ReadChar("All Permissions? (y/n)")) == 'y')
    {
        User.Permissions = -1;
        return User;
    }

    if(tolower(ReadChar("Show Client List Permission? (y/n)")) == 'y') User.Permissions++;
    if(tolower(ReadChar("Add New Client Permission? (y/n)")) == 'y') User.Permissions += 2;
    if(tolower(ReadChar("Delete Client Permission? (y/n)")) == 'y') User.Permissions += 4;
    if(tolower(ReadChar("Update Client Info Permission? (y/n)")) == 'y') User.Permissions += 8;
    if(tolower(ReadChar("Find Client Permission? (y/n)")) == 'y') User.Permissions += 16;
    if(tolower(ReadChar("Transactions Permission? (y/n)")) == 'y') User.Permissions += 32;
    if(tolower(ReadChar("Manage Users Permission? (y/n)")) == 'y') User.Permissions += 64;

    return User;
}

bool UpdateClientByAccountNumber(vector <stClient> &vClients)
{
    string AccountNumber = ReadStr("Enter Account Number: ");
    stClient Client;
    char Answer = 'n';

    if(FindClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClientRecord(Client);
        
        cout << "Are you sure you wanna update this client? ";
        cin >> Answer;
        cin.ignore(1, '\n');
        if(Answer == 'y' || Answer == 'Y')
        {
            for (stClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientDetails(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "Clients Updated succefully" << endl;
            return true;
        }

    }
    else
    {
        cout << "Not Founded" << endl;
        return false;
    }
    return false;
}

bool UpdateUserByUserName(stUser Me, vector <stUser> &vUsers)
{
    string Username = ReadStr("Enter UserName: ");
    while(Username == "Admin" && Me.UserName != "Admin")
    {
        cout << "You can't update this user" << endl;
        Username = ReadStr("Enter UserName: ");
    }
    stUser User;
    char Answer = 'n';

    if(FindUserByUserName(vUsers, Username, User))
    {
        PrintUserRecord(User);
        
        cout << "Are you sure you wanna update this client? ";
        cin >> Answer;
        cin.ignore(1, '\n');
        if(Answer == 'y' || Answer == 'Y')
        {
            for (stUser &U : vUsers)
            {
                if (U.UserName == Username)
                {
                    U = ChangeUserDetails(Username);
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);

            cout << "User Updated succefully" << endl;
            return true;
        }

    }
    else
    {
        cout << "Not Founded" << endl;
        return false;
    }
    return false;
}

void PrintFindClientsByAccountNumber(vector <stClient> &vClients)
{
    stClient Client;
    string AccountNumber = ReadStr("Enter Account Number: ");

    if(FindClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClientRecord(Client);
    }
    else
    {
        cout << "Not Founded" << endl;
    }
}

void PrintFindUsersByUserName(vector <stUser> &vUser)
{
    stUser User;
    string Username = ReadStr("Enter Username: ");

    if(FindUserByUserName(vUser, Username, User))
    {
        PrintUserRecord(User);
    }
    else
    {
        cout << "Not Founded" << endl;
    }
}

bool Deposit(vector <stClient> &vClients)
{
    string AccountNumber = ReadStr("Enter Account Number: ");
    stClient Client;
    char Answer = 'n';
    double DepositAmount = 0;

    if(FindClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClientRecord(Client);
        
        cout << "Are you sure you wanna deposit? ";
        cin >> Answer;
        cin.ignore(1, '\n');

        if(Answer == 'y' || Answer == 'Y')
        {
            for (stClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    do
                    {
                        DepositAmount = ReadDouble("Enter Deposit Amount? ");
                    } while(DepositAmount < 0); 

                    C.AccountBalance += DepositAmount;
                    cout << "New Amount is: " << C.AccountBalance << endl;
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);
            return true;
        }

    }
    else
    {
        cout << "Not Founded" << endl;
        return false;
    }
    return false;
}

bool Withdraw(vector <stClient> &vClients)
{
    string AccountNumber = ReadStr("Enter Account Number: ");
    stClient Client;
    char Answer = 'n';
    double WithdrawAmount = 0;

    if(FindClientByAccountNumber(vClients, AccountNumber, Client))
    {
        PrintClientRecord(Client);
        
        cout << "Are you sure you wanna withdraw? ";
        cin >> Answer;
        cin.ignore(1, '\n');

        if(Answer == 'y' || Answer == 'Y')
        {
            for (stClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    do
                    {
                        WithdrawAmount = ReadDouble("Enter Withdraw Amount? ");
                    } while(WithdrawAmount < 0 || WithdrawAmount > C.AccountBalance); 

                    C.AccountBalance -= WithdrawAmount;
                    cout << "New Amount is: " << C.AccountBalance << endl;
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);
            return true;
        }

    }
    else
    {
        cout << "Not Founded" << endl;
        return false;
    }
    return false;
}

double TotalBalance(vector <stClient> &vClients)
{
    double Total = 0;
    for(stClient &C : vClients)
    {
        Total += C.AccountBalance;
    }
    return Total;
}

void PrintTotalBalance(vector <stClient> &vClients)
{
    PrintAllClientsMinData(vClients);
    cout << "\t\t\t\tTotal Balance is : " << TotalBalance(vClients) << endl;
}

void ChooseTransactinosOption(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients)
{
    short Choice;
    do
    {
        Choice = ReadInt("Choose what do you want to do? [1 to 4]? ");
    } while (Choice < 1 || Choice > 4);

    system("cls");
    switch (Choice)
    {
    case enTChoice::enDeposit:
        Deposit(vClients);
        break;
    case enTChoice::enWithdraw:
        Withdraw(vClients);
        break;
    case enTChoice::enTotalBalances:
        PrintTotalBalance(vClients);
        break;
    case enTChoice::enMainMenu:
        MainMenuScreen(User, vUsers, vClients);
        break;
    default:
        break;
    }

    cout << "\n\nEnter any key to back to transaction menu...";
    system("pause>0");
    TransactionsMenuScreen(User, vUsers, vClients);
}

void TransactionsMenuScreen(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients)
{
    system("cls");
    cout << "\n\n============================================" << endl;
    cout << "            Transactions Menu Screen" << endl;
    cout << "============================================" << endl;
    cout << "[1]         Deposit.\n";
    cout << "[2]         Withdraw.\n";
    cout << "[3]         Total Balances.\n";
    cout << "[4]         Main Menu.\n";
    cout << "============================================" << endl;
    ChooseTransactinosOption(User, vUsers, vClients);
}

void ChooseUserOption(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients)
{
    short Choice;
    do
    {
        Choice = ReadInt("Choose what do you want to do? [1 to 6]? ");
    } while (Choice < 1 || Choice > 6);

    system("cls");
    switch (Choice)
    {
    case enUserChoice::enUShowUserList:
        PrintAllUsersData(vUsers);
        break;
    case enUserChoice::enUAddNewUser:
        AddUsers(vUsers);
        break;
    case enUserChoice::enUDeleteUser:
        DeleteUserByUserName(User, vUsers);
        break;
    case enUserChoice::enUUpdateUserInfo:
        UpdateUserByUserName(User, vUsers);
        break;
    case enUserChoice::enUFindUser:
        PrintFindUsersByUserName(vUsers);
        break;
    case enUserChoice::enUMainMenu:
        MainMenuScreen(User, vUsers, vClients);
        break;
    default:
        break;
    }

    cout << "\n\nEnter any key to back to Manage Users Menu...";
    system("pause>0");
    ShowManageScreen(User, vUsers, vClients);
}

void ShowManageScreen(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients)
{
    system("cls");
    cout << "\n\n============================================" << endl;
    cout << "            Manage Users Menu Screen" << endl;
    cout << "============================================" << endl;
    cout << "[1]         List Users.\n";
    cout << "[2]         Add New User.\n";
    cout << "[3]         Delete User.\n";
    cout << "[4]         Update User.\n";
    cout << "[5]         Find User.\n";
    cout << "[6]         Main Menu.\n";
    cout << "============================================" << endl;
    ChooseUserOption(User, vUsers, vClients);
}

bool HasPermission(stUser &User, enUserPermissions UserPermission)
{
    return (((UserPermission & User.Permissions) == UserPermission) || User.Permissions == -1);
}

void PrintAccessDenied()
{
    system("cls");
    cout << "You don't have permission\n";
}

void ChooseOption(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients)
{
    short Choice;
    do
    {
        Choice = ReadInt("Choose what do you want to do? [1 to 8]? ");
    } while (Choice < 1 || Choice > 8);

    system("cls");
    switch (Choice)
    {
    case enChoice::enShowClientList:
        if(HasPermission(User, enUserPermissions::enPShowClientList))
            PrintAllClientsData(vClients);
        else PrintAccessDenied();
        break;
    case enChoice::enAddNewClient:
        if(HasPermission(User, enUserPermissions::enPAddNewClient))
            AddClients(vClients);
        else PrintAccessDenied();
        break;
    case enChoice::enDeleteClient:
        if(HasPermission(User, enUserPermissions::enPDeleteClient))
            DeleteClientByAccountNumber(vClients);
        else PrintAccessDenied();
        break;
    case enChoice::enUpdateClientInfo:
        if(HasPermission(User, enUserPermissions::enPUpdateClientInfo))
            UpdateClientByAccountNumber(vClients);
        else PrintAccessDenied();
        break;
    case enChoice::enFindClient:
        if(HasPermission(User, enUserPermissions::enPFindClient))
            PrintFindClientsByAccountNumber(vClients);
        else PrintAccessDenied();
        break;
    case enChoice::enTransactions:
        if(HasPermission(User, enUserPermissions::enPTransactions))
            TransactionsMenuScreen(User, vUsers, vClients);
        else PrintAccessDenied();
        break;
    case enChoice::enManageUsers:
        if(HasPermission(User, enUserPermissions::enPManageUsers))
            ShowManageScreen(User, vUsers, vClients);
        else PrintAccessDenied();
        break; 
    case enChoice::enLogout:
        Login(vClients, vUsers);
    default:
        break;
    }

    cout << "\n\nEnter any key to back to menu...";
    system("pause>0");
    MainMenuScreen(User, vUsers, vClients);
}

void MainMenuScreen(stUser &User, vector <stUser> &vUsers, vector <stClient> &vClients)
{
    system("cls");
    cout << "\n\n============================================" << endl;
    cout << "            Main Menu Screen" << endl;
    cout << "============================================" << endl;
    cout << "[1]         Show Client List.\n";
    cout << "[2]         Add New Client.\n";
    cout << "[3]         Delete Client.\n";
    cout << "[4]         Update Client Info.\n";
    cout << "[5]         Find Client.\n";
    cout << "[6]         Transactions.\n";
    cout << "[7]         Manage Users.\n";
    cout << "[8]         Logout.\n";
    cout << "============================================" << endl;
    ChooseOption(User, vUsers, vClients);
}

bool FindLoginUser(stUser &User, vector <stUser> &vUsers)
{
    for (stUser &U : vUsers)
    {
        if(U.UserName == User.UserName && U.Password == User.Password)
        {
            User.Permissions = U.Permissions;
            return true;
        }
    }

    return false;
}

void Login(vector <stClient> &vClients, vector <stUser> &vUsers)
{
    system("cls");
    cout << "============================================" << endl;
    cout << "            Login Screen" << endl;
    cout << "============================================" << endl;

    stUser User;
    User.UserName = ReadStr("Username? ");
    User.Password = ReadStr("Password? ");

    while (!FindLoginUser(User, vUsers))
    {
        system("cls");
        cout << "Invalid Username/Password" << endl;
        User.UserName = ReadStr("Username? ");
        User.Password = ReadStr("Password? ");
    }
    
    MainMenuScreen(User, vUsers, vClients);

}

int main()
{
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    Login(vClients, vUsers);

    system("pause>0");
    return 0;
}