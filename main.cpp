#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

const string ClientsFileName = "ClientsFile.txt";

enum enChoice 
{
    enShowClientList = 1, 
    enAddNewClient, 
    enDeleteClient, 
    enUpdateClientInfo, 
    enFindClient,
    enTransactions, 
    enExit
};

enum enTChoice 
{
    enDeposit = 1, 
    enWithdraw, 
    enTotalBalances, 
    enMainMenu,
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

void MainMenuScreen(vector <stClient> &vClients);
void TransactionsMenuScreen(vector <stClient> &vClients);

string ReadStr(string Message = "Enter a string: ")
{
    string S;
    cout << Message;
    getline(cin >> ws, S);
    return S;
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

stClient ConvertLineToRecord(string ClientLine, string seperator = "#//#")
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

bool FindClientByAccountNumber(vector <stClient> &vClients, string AccountNumber)
{
    for (stClient &C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            return true;
        }
    }

    return false;
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

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;
    cin.ignore(1, '\n');

    return Client;
}

string ConvertRecordToLine(stClient Client, string seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + seperator;
    stClientRecord += Client.PinCode + seperator;
    stClientRecord += Client.Name + seperator;
    stClientRecord += Client.Phone + seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
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

void PrintClientRecord(stClient Client)
{
    cout << "The extracted Client Record: \n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "PinCode        : " << Client.PinCode << endl;
    cout << "Account Name   : " << Client.Name << endl;
    cout << "Phone Number   : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
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

stClient ChangeClientDetails(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name: ";
    //cin.ignore(1, '\n');
    getline(cin, Client.Name);

    cout << "Enter Phone Number: ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;
    cin.ignore(1, '\n');

    return Client;
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
                        cout << "Enter Deposit Amount? ";
                        cin >> DepositAmount;
                        cin.ignore(1, '\n');
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
                        cout << "Enter Withdraw Amount? ";
                        cin >> WithdrawAmount;
                        cin.ignore(1, '\n');
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

void ChooseTransactinosOption(vector <stClient> &vClients)
{
    short Choice;
    do
    {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> Choice;
        cin.ignore(1, '\n');
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
        MainMenuScreen(vClients);
        break;
    default:
        break;
    }

    cout << "\n\nEnter any key to back to transaction menu...";
    system("pause>0");
    TransactionsMenuScreen(vClients);
}

void TransactionsMenuScreen(vector <stClient> &vClients)
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
    ChooseTransactinosOption(vClients);
}

void ChooseOption(vector <stClient> &vClients)
{
    short Choice;
    do
    {
        cout << "Choose what do you want to do? [1 to 7]? ";
        cin >> Choice;
        cin.ignore(1, '\n');
    } while (Choice < 1 || Choice > 7);

    system("cls");
    switch (Choice)
    {
    case enChoice::enShowClientList:
        PrintAllClientsData(vClients);
        break;
    case enChoice::enAddNewClient:
        AddClients(vClients);
        break;
    case enChoice::enDeleteClient:
        DeleteClientByAccountNumber(vClients);
        break;
    case enChoice::enUpdateClientInfo:
        UpdateClientByAccountNumber(vClients);
        break;
    case enChoice::enFindClient:
        PrintFindClientsByAccountNumber(vClients);
        break;
    case enChoice::enTransactions:
        TransactionsMenuScreen(vClients);
        break;
    case enChoice::enExit:
        cout << "============================================" << endl;
        cout << "            End Of Program" << endl;
        cout << "============================================" << endl;
        system("pause>0");
        exit(0);
    default:
        break;
    }

    cout << "\n\nEnter any key to back to menu...";
    system("pause>0");
    MainMenuScreen(vClients);
}

void MainMenuScreen(vector <stClient> &vClients)
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
    cout << "[7]         Exit.\n";
    cout << "============================================" << endl;
    ChooseOption(vClients);
}

int main(void)
{
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    MainMenuScreen(vClients);

    system("pause>0");
    return 0;
}