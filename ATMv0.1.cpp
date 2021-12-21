// ATMv0.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h> 
#include <sqlite3.h>
//#include "DatabaseManager.h"

using namespace std;

void splashScreen();
void selectLoginOrRegister();
void loginUser();
void registerUser();
void mainMenu(string phoneNumber);
void accSettings(string);
void changePin(string);
void verification(string);


int createDB(const char* s);
int createTable(const char* s);

bool insertData(const char* s, string, string, string, string, string, string , string ,string ,string, string);
void selectData(const char* s, string, int);

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
static int callbackOtherAccount(void* NotUsed, int argc, char** argv, char** azColName);
static int callbackPassword(void* NotUsed, int argc, char** argv, char** azColName);

int updateData(const char* s);
void updatePIN(const char* s, string phonenumher, string newPIN);
void updateStatus(const char* s, string phonenumher, string newStatus);
int deleteData(const char* s);

void checkBalance(string);
void withdraw(string);
void deposit(string);
void transfer(string);
void transferSameBank(string);
void transferOtherBank(string);


struct Accountdata {
    int id;
    string fname;
    string mname;
    string lastname;
    string completebday;
    string address;
    string typeofID;
    string numberID;
    string accStatus;
    int balance;
    string pinorpass;
    string phoneNumber;
};

struct OtherAccountdata {
    int id;
    string fname;
    string lname;
    int balance;
    string phoneNumber;
};

const char* dir = "newdatabase.db";
//const char* dir = "C:\\Users\\angel\\Desktop\\ONLINE CLASS 2nd SEM\\c111\\FINAL PROJ\\ATMv0.1\\database\\database.db";
sqlite3* DB;

Accountdata account;
OtherAccountdata otheraccount;

int main()
{
    createDB(dir);
  
}

void splashScreen()
{

    std::cout << R"(
+======================================================================================================================+
|                                                                                                                      |
|                                                                                                                      |
|                             /$$   /$$ /$$     /$$ /$$$$$$$  /$$$$$$$  /$$$$$$ /$$$$$$$                               |
|                            | $$  | $$|  $$   /$$/| $$__  $$| $$__  $$|_  $$_/| $$__  $$                              |
|                            | $$  | $$ \  $$ /$$/ | $$  \ $$| $$  \ $$  | $$  | $$  \ $$                              |
|                            | $$$$$$$$  \  $$$$/  | $$$$$$$ | $$$$$$$/  | $$  | $$  | $$                              |
|                            | $$__  $$   \  $$/   | $$__  $$| $$__  $$  | $$  | $$  | $$                              |
|                            | $$  | $$    | $$    | $$  \ $$| $$  \ $$  | $$  | $$  | $$                              |
|                            | $$  | $$    | $$    | $$$$$$$/| $$  | $$ /$$$$$$| $$$$$$$/                              |
|                            |__/  |__/    |__/    |_______/ |__/  |__/|______/|_______/                               |
|                                                                                                                      |
|                                                                                                                      |
|                                           /$$$$$$  /$$$$$$$$ /$$      /$$                                            |
|                                          /$$__  $$|__  $$__/| $$$    /$$$                                            |
|                                         | $$  \ $$   | $$   | $$$$  /$$$$                                            |
|                                         | $$$$$$$$   | $$   | $$ $$/$$ $$                                            |
|                                         | $$__  $$   | $$   | $$  $$$| $$                                            |
|                                         | $$  | $$   | $$   | $$\  $ | $$                                            |
|                                         | $$  | $$   | $$   | $$ \/  | $$                                            |
|                                         |__/  |__/   |__/   |__/     |__/                                            |
|                                                                                                                      |
|                                                                                                                      |)" ;
    cout << "|                                               By: Dionisio & Plata                                                   |"<< endl;
    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;
    //cout << "Press Any Key to Continue" << endl; // blinking
    system("pause");

    system("CLS");
    selectLoginOrRegister();
}

void selectLoginOrRegister() {
    char typeOfAction;
    bool isValid = false;
    
    while (isValid == false) {

        std::cout << R"(
+======================================================================================================================+
                                 $$$$$$\                                          $$\              
                                 \_$$  _|                                         $$ |             
                                   $$ |  $$$$$$$\   $$$$$$$\  $$$$$$\   $$$$$$\ $$$$$$\            
                                   $$ |  $$  __$$\ $$  _____|$$  __$$\ $$  __$$\\_$$  _|           
                                   $$ |  $$ |  $$ |\$$$$$$\  $$$$$$$$ |$$ |  \__| $$ |             
                                   $$ |  $$ |  $$ | \____$$\ $$   ____|$$ |       $$ |$$\          
                                 $$$$$$\ $$ |  $$ |$$$$$$$  |\$$$$$$$\ $$ |       \$$$$  |         
                                 \______|\__|  \__|\_______/  \_______|\__|        \____/          
                     $$$$$$\ $$$$$$$$\ $$\      $$\        $$$$$$\                            $$\ 
                   $$  __$$\\__$$  __|$$$\    $$$ |      $$  __$$\                           $$ |
                   $$ /  $$ |  $$ |   $$$$\  $$$$ |      $$ /  \__| $$$$$$\   $$$$$$\   $$$$$$$ |
                   $$$$$$$$ |  $$ |   $$\$$\$$ $$ |      $$ |       \____$$\ $$  __$$\ $$  __$$ |
                   $$  __$$ |  $$ |   $$ \$$$  $$ |      $$ |       $$$$$$$ |$$ |  \__|$$ /  $$ |
                   $$ |  $$ |  $$ |   $$ |\$  /$$ |      $$ |  $$\ $$  __$$ |$$ |      $$ |  $$ |
                   $$ |  $$ |  $$ |   $$ | \_/ $$ |      \$$$$$$  |\$$$$$$$ |$$ |      \$$$$$$$ |
                   \__|  \__|  \__|   \__|     \__|       \______/  \_______|\__|       \_______|
)";
      
        cout << "+======================================================================================================================+";
        cout << endl;
        cout << endl;
        cout << "--OR--" << endl;
        cout << endl;
        cout << "(L)Login" << endl;
        cout << "(R)Register" << endl;
        cout << "(X)Cancel" << endl;
        cout << endl;
        cout << "Your choice: ";
        cin >> typeOfAction;


        switch (typeOfAction)
        {
            case 'L': {
                system("CLS");
                //cout << "Login Selected" << endl;
                isValid = true;
                loginUser();
                break;
            }

            case 'R': {
                system("CLS");
                //cout << "Register Selected" << endl;
                isValid = true;
                registerUser();
                break;
            }

            case 'X': {
                cout << "Transaction Cancelled" << endl;
                system("CLS");
                isValid = true;
                splashScreen();
                break;
            }

            default: {
                cout << "Invalid input... Please Try Again" << endl; 
                system("pause");
                system("CLS");
                //LOOP
                break;
            }
        }
    }
    
}

void loginUser() 
{
    //system("CLS");

    int retrycount = 0;
    string phoneNumber;
    string pin;
    bool isValid = false;
    bool isAccValid = false;
start:
    std::cout << R"(
+======================================================================================================================+


                                 ooooo                              o8o              
                                 `888'                              `"'              
                                  888          .ooooo.   .oooooooo oooo  ooo. .oo.   
                                  888         d88' `88b 888' `88b  `888  `888P"Y88b  
                                  888         888   888 888   888   888   888   888  
                                  888       o 888   888 `88bod8P'   888   888   888  
                                 o888ooooood8 `Y8bod8P' `8oooooo.  o888o o888o o888o 
                                                        d"     YD                    
                                                        "Y88888P'                                                                                         

)";

    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;
    cout << "Please enter the following details:" << endl;
    
    if (retrycount >= 3) {
        //cooldown
        main();
    }
    

    // check if account number is valid and in the database
    do {
        cout << endl;
        cout << "Phone Number: ";
        cin >> phoneNumber;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Phone number. Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } 	while (isValid == false);

    cout << "Enter your pin or password:";
    cin >> pin;

    selectData(dir, phoneNumber, 1);

   
    while (isAccValid == false)
    {
        if (phoneNumber == phoneNumber && pin == account.pinorpass) {
            cout << endl;
            cout << "Login Successfull." << endl;
            system("pause");
            isAccValid = true;
            selectData(dir, phoneNumber, 2);
            mainMenu(phoneNumber);

        }
        else {
            cout << "The Account Number and PIN does not Match." << endl;
            retrycount++;
            if (retrycount <= 3) {
                cout << "Please Try Again Later" << endl;
                system("pause");
                system("CLS");
                //system("CLS");
                goto start;
            }
            else {
                cout << "Please Try Again" << endl;
                goto start;
            }
         
        }
    }
    
}

void registerUser() 
{


   
    string fname, mname, lastname ,address, numberID, pinorpass, pinorpass2, completebday, typeofID, phoneNumber;
    int birthday, birthmonth, birthyear;
    bool isValid = false;
    string accStatus = "Unverified"; // unverified

    registerStart:

    std::cout << R"(
+======================================================================================================================+


                       _______  _______  _______ _________ _______ _________ _______  _______             
                      (  ____ )(  ____ \(  ____ \\__   __/(  ____ \\__   __/(  ____ \(  ____ )            
                      | (    )|| (    \/| (    \/   ) (   | (    \/   ) (   | (    \/| (    )|            
                      | (____)|| (__    | |         | |   | (_____    | |   | (__    | (____)|            
                      |     __)|  __)   | | ____    | |   (_____  )   | |   |  __)   |     __)            
                      | (\ (   | (      | | \_  )   | |         ) |   | |   | (      | (\ (               
                      | ) \ \__| (____/\| (___) |___) (___/\____) |   | |   | (____/\| ) \ \__            
                      |/   \__/(_______/(_______)\_______/\_______)   )_(   (_______/|/   \__/            
                                                                                              
                                                                 

)";

    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;

    cin.clear();

    cout << "Please fill the information needed below" << endl;
    cout << endl;
    cout << "Enter First Name:";
    cin.ignore();
    getline(cin, fname);
    //error proofing: required dapat hindi dapat blanko

    cout << "Enter Middle Name:";
    getline(cin, mname);
    //error proofing: required dapat hindi dapat blanko

    cout << "Enter Last Name:";
    getline(cin, lastname);
    //error proofing: required dapat hindi dapat blanko

    do {
        cout << "Enter your Birthday (Day) DD: ";
        cin >> birthday;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid date. Please try again" << endl;
        }
        else if(birthday <= 0 && birthday >= 31){
            cout << "Invalid date. Please try again" << endl;
        }
        else {
            isValid = true;
        }
    }     
    while (isValid == false);

    isValid = false;
    do {
        cout << "Enter your Birthmonth (Month) MM: ";
        cin >> birthmonth;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid month. Please try again" << endl;
        }
        else if (birthmonth <= 0 && birthmonth > 12) {
            cout << "Invalid month. Please try again" << endl;
        }
        else {
            isValid = true;
        }
    }     while (isValid == false);

    isValid = false;
    do {
        cout << "Enter your Birthyear (Year) YYYY :";
        cin >> birthyear;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid year. Please try again" << endl;
        }
        else if (birthyear <= 999 && birthyear >= 10000) {
            cout << "Invalid year. Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } while (isValid == false);

    completebday = to_string(birthday) + "/" + to_string(birthmonth) + "/" + to_string(birthyear);

    cout << "Enter Permanent Home Address: ";
    cin.ignore();
    getline(cin, address);
    //error proofing: required dapat hindi dapat blanko

    cout << "Type of ID you want to attach:" << endl;
    cout << endl;
    cout << "(1)Passport" << endl;
    cout << "(2)Driver's license" << endl;
    cout << "(3)Professional Regulation Commission(PRC) ID" << endl;
    cout << "(4)Postal ID" << endl;
    cout << "(5)Voter’s ID" << endl;
    cout << "(6)Taxpayer Identification Number(TIN)" << endl;
    cout << "(7)Government Service Insurance System(GSIS)" << endl;
    cout << "(8)Social Security System(SSS) card" << endl;
    cout << "(9)Senior Citizen card" << endl;
    cout << "(10)Overseas Workers Welfare Administration(OWWA) ID" << endl;
    cout << "(11) Overseas Filipino Worker(OFW) ID" << endl;
    cout << "(12)Government office and Government - owned and Controlled Corporation(GOCC) ID:" << endl;
    cout << "(13)ID issued by the National Council on Disability Affairs" << endl;
    cout << "(14)Integrated Bar of the Philippines(IBP) ID" << endl;
    cout << "(15)Company IDs" << endl;
    cout << "(16)PhilHealth Health Insurance Card ng Bayan" << endl;
    cout << "(17)National Bureau of Investigation(NBI) Clearance" << endl;
    cout << "(18)Police Clearance" << endl;
    cout << "(19)Baranggay Certification" << endl;
    cout << "(10)Seaman’s Book" << endl;
    cout << "(11)Alien Certificate of Registration / Immigrant Certificate of Registration" << endl;
    cout << "(12)Department of Social Welfare and Development(DSWD) Certification" << endl;
    cout << "(13)Professional ID cards issued by Maritime Industry Authority(MARINA)" << endl;
    cout << endl;

    cout << "Your Choice: ";
    cin >> typeofID;
    // error proofing: wala sa pag pipilian

    cout << "Enter id's number: ";
    cin >> numberID;
    //error proofing: required dapat hindi dapat blanko
    //upgrade: show type of id number you have to enter

    isValid = false;
    do{
        cout << "Enter your pin or password: ";
        cin >> pinorpass;
        //error proofing: required dapat hindi dapat blanko

        cout << "Enter your pin or password again: ";
        cin >> pinorpass2;
        //error proofing : required dapat hindi dapat blanko

        if (pinorpass != pinorpass2) {
            cout << "The pin or password you enter does not match. Please Try Again ";
        }
        else
            isValid = true;
        
    }
    while (isValid == false);

   
    do {
        cin.ignore();
        cout << "Please Enter Your Phone Number: ";
        cin >> phoneNumber;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Phone number. Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } while (isValid == false);


    system("CLS");

    std::cout << R"(
+======================================================================================================================+


                       _______  _______  _______ _________ _______ _________ _______  _______             
                      (  ____ )(  ____ \(  ____ \\__   __/(  ____ \\__   __/(  ____ \(  ____ )            
                      | (    )|| (    \/| (    \/   ) (   | (    \/   ) (   | (    \/| (    )|            
                      | (____)|| (__    | |         | |   | (_____    | |   | (__    | (____)|            
                      |     __)|  __)   | | ____    | |   (_____  )   | |   |  __)   |     __)            
                      | (\ (   | (      | | \_  )   | |         ) |   | |   | (      | (\ (               
                      | ) \ \__| (____/\| (___) |___) (___/\____) |   | |   | (____/\| ) \ \__            
                      |/   \__/(_______/(_______)\_______/\_______)   )_(   (_______/|/   \__/            
                                                                                              
                                                                 

)";

    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;

    cout << "By confirming below, you accepts the terms and condition of Hybrid ATM System" << endl;
    cout << "Please Confirm the Information you Entered: " << endl;
    cout << endl;
    cout << "First Name: " << fname << endl;
    cout << "Middle Name: " << mname << endl;
    cout << "Last Name: " << lastname << endl;
    cout << "Birthday(dd/mm/yyyy): " << birthday << "/" << birthmonth << "/" << birthyear << endl;
    cout << "Address: " << address << endl;
    cout << "Type of ID: " << typeofID << endl;
    // UPRADE: show correct type of id
    cout << "ID number: " << numberID << endl;
    cout << "Phone number: " << phoneNumber << endl;

    //UPGRADE Accept terms and conditions privacy act
    
    cin.ignore();
   
    isValid = false;
    do {
        char yesorno;
        cout << endl;
        cout << "Is the information entered correctly?(Y)es/(N)o/(C)ancel: ";
        cin >> yesorno;
        //error proofing: required dapat hindi dapat blanko

        if (yesorno == 'y' || yesorno == 'Y') {
            cout << "Your Information will be stored on database..." << endl;
            isValid = insertData(dir, fname, mname, lastname, completebday, address, typeofID, numberID, accStatus, pinorpass, phoneNumber);
            
            if (isValid == true) {
                system("Pause");
                selectData(dir, phoneNumber, 2);
                mainMenu(phoneNumber);
            }

            //DATABASE SAVE
            //mainMenu(generated ID)
        }
        else if (yesorno == 'n' || yesorno == 'N') {
            cout << "Please re enter your information" << endl;
            goto registerStart;
            isValid = true;
        }
        else if (yesorno == 'c' || yesorno == 'C') {
            cout << "Register cancelled" << endl;
            system("CLS");
            selectLoginOrRegister();
            isValid = true;
        }

    }     while (isValid == false);  
}

void mainMenu(string phoneNumber){
    selectData(dir, phoneNumber, 2);

    system("CLS");
    string fname;
    bool accStatus = false;
    char transaction;
    bool isValid = false;
    //get data
    std::cout << R"(
+======================================================================================================================+
 Hybrid ATM: By Dionisio & Plata                                                        Hybrid ATM: By Dionisio & Plata
                                      $$\      $$\                                                                   
                                      $$$\    $$$ |                                                                  
                                      $$$$\  $$$$ | $$$$$$\  $$$$$$$\  $$\   $$\                                     
                                      $$\$$\$$ $$ |$$  __$$\ $$  __$$\ $$ |  $$ |                                    
                                      $$ \$$$  $$ |$$$$$$$$ |$$ |  $$ |$$ |  $$ |                                    
                                      $$ |\$  /$$ |$$   ____|$$ |  $$ |$$ |  $$ |                                    
                                      $$ | \_/ $$ |\$$$$$$$\ $$ |  $$ |\$$$$$$  |                                    
                                      \__|     \__| \_______|\__|  \__| \______/                                     
 Hybrid ATM: By Dionisio & Plata                                                        Hybrid ATM: By Dionisio & Plata )";

    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;
    cout << "Hello " << account.fname << "! " << endl;
    cout << "Status: " << account.accStatus << endl;
    cout << endl;

    cout << "Select your transaction: " << endl;
    cout << "(A)Check Balance" << endl;
    cout << "(B)Withdraw" << endl;
    cout << "(C)Deposit" << endl;
    cout << "(D)Transfer" << endl;
    cout << "(S)Account Settings" << endl;
    cout << "(X)Logout" << endl;
    cout << endl;

    while (isValid == false) {
        cout << "Your Choice: ";
        cin >> transaction;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Choice. Please try again" << endl;
            system("pause");
        }
        else {

            switch (transaction) {
            case 'A': {
                cout << "Check balance selected" << endl;
                checkBalance(phoneNumber);
                isValid = true;
                break;
            }
            case 'B': {
                system("CLS");
                //cout << "Withdraw selected" << endl;
                withdraw(phoneNumber);
                isValid = true;
                break;
            }
            case 'C': {
                system("CLS");
                //cout << "Deposit selected" << endl;
                deposit(phoneNumber);
                isValid = true;
                break;
            }
            case 'D': {
                system("CLS");
                cout << "Transfer selected" << endl;
                transfer(phoneNumber);
                isValid = true;
                break;
            }
            case 'S': {
                system("CLS");
                cout << "Account Settings selected" << endl;
                accSettings(phoneNumber);
                isValid = true;
                break;
            }
            case 'X': {
                cout << "Logout selected" << endl;
                system("pause");
                system("CLS");
                splashScreen();
                isValid = true;
                break;
            }
            default:
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Choice. Please try again" << endl;
                system("pause");
                break;
            }

            
        }
    }
    

    
}

int createDB(const char* s)
{
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);

    cout << "DB CREATE SUCCESS" << endl;

    createTable(dir);
    return 0;
}

int createTable(const char* s)
{
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS 'ACCOUNT'("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "FNAME TEXT NOT NULL, "
        "MNAME TEXT NOT NULL, "
        "LNAME TEXT NOT NULL, "
        "BIRTHDAY TEXT NOT NULL, "
        "ADDRESS TEXT NOT NULL, "
        "TYPEOFID TEXT NOT NULL, "
        "IDNUMBER TEXT NOT NULL, "
        "ACCOUNTSTATUS TEXT NOT NULL, "
        "BALANCE INTEGER DEFAULT 0, "
        "PINNUMBER TEXT NOT NULL, "
        "PHONENUMBER TEXT NOT NULL UNIQUE );";

    try {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        char* messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK) {
            cerr << "Error Create Table" << endl;

            cout << messaggeError << endl;
            cout << sql << endl;
            sqlite3_free(messaggeError);
        }
        else
            cout << "Table created successfully" << endl;
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    system("CLS");
    splashScreen();

    return 0;
}

bool insertData(const char* s, string fname, string mname, string lname, string birthday, string address, string typeofid, string idnumber, string accountstatus, string pinnumber, string phonenumber)
{

    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    string sql = ("INSERT INTO ACCOUNT(FNAME, MNAME, LNAME, BIRTHDAY, ADDRESS, TYPEOFID, IDNUMBER, ACCOUNTSTATUS, PINNUMBER, PHONENUMBER ) VALUES( '" + fname + "', '" + mname + "',  '" + lname + "', '" + birthday + "', '" + address + "', '" + typeofid + "','" + idnumber + "', '" + accountstatus + "', '" + pinnumber + "', '" + phonenumber + "');");
      
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert Data on Database" << endl;
        cout << messageError << endl; 
        cout << sql << endl;
        sqlite3_free(messageError);
        
        return false;
    }
    else
        cout << "REcords created successfully!" << endl;

    return true;
}

void selectData(const char* s, string phoneNumber, int action)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);
    string sql = "SELECT * FROM ACCOUNT WHERE PHONENUMBER = '" + phoneNumber +"';";
    char* messaggeError;
    switch (action) {
        case 1: { // return only password 
            sqlite3_exec(DB, sql.c_str(), callbackPassword, NULL, NULL);
            break;
        }
        case 2: { // all data
            sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
            break;
        }
        case 3: {
            //cout << "executeing sql "<< phoneNumber << endl;
            exit = sqlite3_exec(DB, sql.c_str(), callbackOtherAccount, NULL, &messaggeError);
            if (exit != SQLITE_OK) {
                cerr << "Error Reading Table" << endl;

                cout << messaggeError << endl;
                cout << sql << endl;
                sqlite3_free(messaggeError);
            }
            break;
        }
              
    }

    /* aN OPEN DATABSE , SQL TO BE evaluated, callback function, 1st argument to callback, error meg will be written here*/
    //sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return;
}

// retrieve the contents of the database used by selectdata()
/* argc: holds the number of results, azcolname: hold each column returned in array,argv: hols each value in array */
int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    /*
    for (int i = 0; i < argc; i++) {
        //column name and value 
        std::cout << azColName[i] << ": " << argv[i] << endl;
    }
    */

    //(int)account.id = argv[0];
    account.fname = argv[1];
   // account.mname = argv[2];
    account.accStatus = argv[8];
    account.balance = std::stoi(argv[9]);
    account.pinorpass = argv[10];

    return 0;

}

int callbackOtherAccount(void* NotUsed, int argc, char** argv, char** azColName)
{
    /*
    try {
        for (int i = 0; i < argc; i++) {
            //column name and value
            std::cout << azColName[i] << ": " << argv[i] << endl;
        }
    }
    catch (const std::exception& e) {
        cout << e.what();
    }
   
    */

    //(int)account.id = argv[0];
    otheraccount.fname = argv[1];
    otheraccount.lname = argv[3];
   // account.accStatus = argv[8];
    otheraccount.balance = std::stoi(argv[10]);

    return 0;

}

int callbackPassword(void* NotUsed, int argc, char** argv, char** azColName)
{
   
    account.pinorpass = argv[10];
    //std::cout << azColName[10] << ": " << argv[10] << endl;
    //cout << endl;
    return 0;


}

int updateData(const char* s)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open(s, &DB);

    string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error Update" << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "REcords updated successfully!" << endl;

    return 0;
}

void updateBalance(const char* s, string phonenumher, int newBalance)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open(s, &DB);

    string sql = "UPDATE ACCOUNT SET BALANCE = '"+ to_string(newBalance) +"' WHERE PHONENUMBER = '"+ phonenumher +"'";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error Update: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Records updated successfully!" << endl;

    return;
}

void updatePIN(const char* s, string phonenumher, string newPIN)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open(s, &DB);

    string sql = "UPDATE ACCOUNT SET PINNUMBER = '" + newPIN + "' WHERE PHONENUMBER = '" + phonenumher + "'";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error Update: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Records updated successfully!" << endl;

    return;
}

void updateStatus(const char* s, string phonenumher, string newStatus)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open(s, &DB);

    string sql = "UPDATE ACCOUNT SET ACCOUNTSTATUS = '" + newStatus + "' WHERE PHONENUMBER = '" + phonenumher + "'";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error Update: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Records updated successfully!" << endl;

    return;
}



int deleteData(const char* s)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);
    string sql = "DELETE FROM GRADES;";
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return 0;
}

void checkBalance(string phoneNumber)
{
    string pinorpass;
    bool isAccValid = false;
    int retrycount= 0;

    start:

    cout << "Enter Pin or Password: ";
    cin >> pinorpass;

    while (isAccValid == false)
    {
        if (pinorpass == account.pinorpass) {
            cout << "Successfull." << endl;
            isAccValid = true;

        }
        else {
            cout << "PIN does not Match." << endl;
            retrycount++;
            if (retrycount <= 3) {
                cout << "Please Try Again Later" << endl;
                system("pause");
                system("CLS");
                goto start;
            }
            else {
                cout << "Please Try Again" << endl;
                goto start;
            }

        }
    }

    cout << "Your current balance is: " << account.balance << endl;

    system("pause");
    system("CLS");

    mainMenu(phoneNumber);


}

void withdraw(string phoneNumber)
{
    string pinorpass;
    int retrycount = 0;
    bool isValid = false; 
    int money;


start:
    std::cout << R"(
+======================================================================================================================+
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
|:::::::::::::::'##:::::'##:'####:'########:'##::::'##:'########::'########:::::'###::::'##:::::'##::::::::::::::::::::|
|::::::::::::::: ##:'##: ##:. ##::... ##..:: ##:::: ##: ##.... ##: ##.... ##:::'## ##::: ##:'##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: ##:::: ##: ##:::: ##: ##:::: ##::'##:. ##:: ##: ##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: #########: ##:::: ##: ########::'##:::. ##: ##: ##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: ##.... ##: ##:::: ##: ##.. ##::: #########: ##: ##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: ##:::: ##: ##:::: ##: ##::. ##:: ##.... ##: ##: ##: ##::::::::::::::::::::|
|:::::::::::::::. ###. ###::'####:::: ##:::: ##:::: ##: ########:: ##:::. ##: ##:::: ##:. ###. ###:::::::::::::::::::::|
|::::::::::::::::...::...:::....:::::..:::::..:::::..::........:::..:::::..::..:::::..:::...::...::::::::::::::::::::::|
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|)";
    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;
    cout << "Enter Pin or Password: ";
    cin >> pinorpass;

    while (isValid == false)
    {
        if (pinorpass == account.pinorpass) {
            cout << "Successfull." << endl;
            system("pause");
            system("CLS");
            isValid = true;
        }
        else {
            cout << "PIN does not Match." << endl;
            retrycount++;
            if (retrycount <= 3) {
                cout << "Please Try Again Later" << endl;
                system("pause");
                system("CLS");
                goto start;
            }
            else {
                cout << "Please Try Again" << endl;
                goto start;
            }
        }
    }

    std::cout << R"(
+======================================================================================================================+
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
|:::::::::::::::'##:::::'##:'####:'########:'##::::'##:'########::'########:::::'###::::'##:::::'##::::::::::::::::::::|
|::::::::::::::: ##:'##: ##:. ##::... ##..:: ##:::: ##: ##.... ##: ##.... ##:::'## ##::: ##:'##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: ##:::: ##: ##:::: ##: ##:::: ##::'##:. ##:: ##: ##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: #########: ##:::: ##: ########::'##:::. ##: ##: ##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: ##.... ##: ##:::: ##: ##.. ##::: #########: ##: ##: ##::::::::::::::::::::|
|::::::::::::::: ##: ##: ##:: ##::::: ##:::: ##:::: ##: ##:::: ##: ##::. ##:: ##.... ##: ##: ##: ##::::::::::::::::::::|
|:::::::::::::::. ###. ###::'####:::: ##:::: ##:::: ##: ########:: ##:::. ##: ##:::: ##:. ###. ###:::::::::::::::::::::|
|::::::::::::::::...::...:::....:::::..:::::..:::::..::........:::..:::::..::..:::::..:::...::...::::::::::::::::::::::|
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|)";
    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;

    cout << "Notice: The minumum ammount of withdraw is 500 php" << endl;
    cout << endl;
    isValid = false;
    do {
        cout << "Enter the amount of cash you want to withdraw: " ;
        cin >> money;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid amount. Please try again" << endl;
        }
        else if (money <= 500) {
            cout << "The minumum amount of withdraw is 500 php" << endl;
            cout << "Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } while (isValid == false);
    
    cout << "Processing..." << endl;
    
    
    if (account.balance < money) {
        cout << "You have unsufficient ammount of balance in your account" << endl;
        system("pause");
        system("CLS");
        mainMenu(phoneNumber);
    }
    else {
        int newbalance = account.balance - money;
        updateBalance(dir, phoneNumber, newbalance);
        selectData(dir, phoneNumber, 2);
        cout << "Please get your cash" << endl;
        system("pause");
        system("CLS");
        mainMenu(phoneNumber);
    }

}

void deposit(string phoneNumber)
{
    int money = 0, lastmoney = 0;
    bool isValid = false;
    char choice;

    std::cout << R"(
+======================================================================================================================+
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
|:::::::::::::::::::::::'########::'########:'########:::'#######:::'######::'####:'########:::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##.... ##: ##.....:: ##.... ##:'##.... ##:'##... ##:. ##::... ##..::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##::::::: ##:::: ##: ##:::: ##: ##:::..::: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ######::: ########:: ##:::: ##:. ######::: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##...:::: ##.....::: ##:::: ##::..... ##:: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##::::::: ##:::::::: ##:::: ##:'##::: ##:: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ########:: ########: ##::::::::. #######::. ######::'####:::: ##::::::::::::::::::::::::::::::|
|:::::::::::::::::::::::........:::........::..::::::::::.......::::......:::....:::::..:::::::::::::::::::::::::::::::|
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|)";
    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;

    cout << "Do not deposit more than 200 notes" << endl;
    cout << "You can Deposit up to 49999 php only" << endl;
    cout << endl;
    system("pause");

    start:
    system("CLS");

    std::cout << R"(
+======================================================================================================================+
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
|:::::::::::::::::::::::'########::'########:'########:::'#######:::'######::'####:'########:::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##.... ##: ##.....:: ##.... ##:'##.... ##:'##... ##:. ##::... ##..::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##::::::: ##:::: ##: ##:::: ##: ##:::..::: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ######::: ########:: ##:::: ##:. ######::: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##...:::: ##.....::: ##:::: ##::..... ##:: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##::::::: ##:::::::: ##:::: ##:'##::: ##:: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ########:: ########: ##::::::::. #######::. ######::'####:::: ##::::::::::::::::::::::::::::::|
|:::::::::::::::::::::::........:::........::..::::::::::.......::::......:::....:::::..:::::::::::::::::::::::::::::::|
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|)";
    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;

    while (isValid == false) {
        cout << "Please insert your Cash in Deposit Machine...." << endl;
        cout << endl;

              
        system("pause");
      
        cout << "Please put the amount you deposited in the machine: ";
        cin >> money;

        if (money >= 50000) {
            cout << "You deposited excess amount of cash" << endl;
            cout << "Please remove the excess amount of cash" << endl;
            system("pause");
            goto start;
        }
        else if (money <= 0) {
            cout << "You deposited zero amount of cash" << endl;
            system("pause");
            goto start;
        }
        else {
            cout << "Please wait..." << endl;
            cout << "Validating the cash... "<< endl;
            system("pause");
            isValid == true;
            break;
        }

    }
    system("CLS");

    std::cout << R"(
+======================================================================================================================+
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
|:::::::::::::::::::::::'########::'########:'########:::'#######:::'######::'####:'########:::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##.... ##: ##.....:: ##.... ##:'##.... ##:'##... ##:. ##::... ##..::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##::::::: ##:::: ##: ##:::: ##: ##:::..::: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ######::: ########:: ##:::: ##:. ######::: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##...:::: ##.....::: ##:::: ##::..... ##:: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ##:::: ##: ##::::::: ##:::::::: ##:::: ##:'##::: ##:: ##::::: ##::::::::::::::::::::::::::::::|
|::::::::::::::::::::::: ########:: ########: ##::::::::. #######::. ######::'####:::: ##::::::::::::::::::::::::::::::|
|:::::::::::::::::::::::........:::........::..::::::::::.......::::......:::....:::::..:::::::::::::::::::::::::::::::|
|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|)";
    cout << "+======================================================================================================================+";
    cout << endl;
    cout << endl;

    cout << "Summary" << endl;
    cout << endl;
    cout << "The total cash you will deposit is: " << endl;
    cout << money + lastmoney << endl;
    cout << "Select your action" << endl;
    cout << "(C)Confirm" << endl;
    cout << "(A)Add more Cash" << endl;
    cout << "(X)Cancel " << endl;
   

    isValid = false;
    while (isValid == false) {

        cout << "Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 'C': {
                cout << "Confirmed" << endl;
                money = lastmoney + account.balance + money;
                updateBalance(dir, phoneNumber, money);
                selectData(dir, phoneNumber, 2);
                system("Pause");
                mainMenu(phoneNumber);
                isValid = true;
            break;
            }

            case 'A': {
                cout << "Add more cash selected" << endl;
                lastmoney = money;
                goto start;
                isValid = true;
            break;
            }

            case 'X' :{
                cout << "Cancelled Selected" << endl;
                cout << "Please get your cash in the deposit machine" << endl;
                system("Pause");
                mainMenu(phoneNumber);
                isValid == true;
                break;

            }

            default: {
                cout << "Invalid choice." << endl;
                system("Pause");
                break;
            }
        }

    }
        


   

   
}

void transfer(string phoneNumber)
{

    string pinorpass;
    int retrycount = 0;
    bool isValid = false;
    int money;
    char choice;

start:

    cout << "Enter Pin or Password: ";
    cin >> pinorpass;

    while (isValid == false)
    {
        if (pinorpass == account.pinorpass) {
            cout << "Successfull." << endl;
            isValid = true;
        }
        else {
            cout << "PIN does not Match." << endl;
            retrycount++;
            if (retrycount <= 3) {
                cout << "Please Try Again Later" << endl;
                system("pause");
                system("CLS");
                goto start;
            }
            else {
                cout << "Please Try Again" << endl;
                goto start;
            }
        }
    }

    isValid = false;
    while (isValid == false) {
        cout << "Select Banks" << endl;
        cout << "(A)Same Bank" << endl;
        cout << "(B)Other Bank" << endl;
        cout << "(X)Cancel" << endl;
        cout << "Your choice: ";
        cin >> choice;
        switch (choice) {
            case 'A': {
                system("CLS");
                cout << "Same bank selected" << endl;
                transferSameBank(phoneNumber);
                isValid = true;
                break;
            }
            case 'B': {
                system("CLS");
                cout << "Other bank selected" << endl;
                transferOtherBank(phoneNumber);
                isValid = true;
                break;
            }
            case 'X': {

                cout << "Operation Cancelled" << endl;
                system("pause");
                system("CLS");
                mainMenu(phoneNumber);
                isValid = true;
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
                break;
            }
        }
    }
    
}

void transferSameBank(string phoneNumber)
{
    string receivername, receiverphoneNumber;
    int amountToTransfer;
    bool isValid = false;
    int transfer;
    
start: 
    cin.ignore();
    //cin.clear();
    cout << "Enter the Name of the Receiver:";
    getline(cin, receivername);

    while (isValid == false) {
        cin.clear();
        //cin.ignore();
        cout << "Enter the Phone Number of the Receiver: ";
        cin >> receiverphoneNumber;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Phone number. Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } 

    cout << "Checking if it is existing account..." << endl;
    selectData(dir, receiverphoneNumber, 3);

    bool isEmpty = otheraccount.fname.empty();
    if (isEmpty) {
        cout << "The account does not exist..." << endl;
        cout << "Please check the phone number account" << endl;
        system("pause");
        system("CLS");
        goto start;
    }
    else {
        confirm:
        char choice;
        cout << "Is the receiver is: " << otheraccount.fname + " " + otheraccount.lname <<"?(Y/N):" ;
        cin >> choice;
        if (choice == 'N') {
            cout << "Please check the phone number account" << endl;
            cout << "Please re-enter your information" << endl;
            system("pause");
            system("CLS");
            goto start;
        }
        else if (choice == 'Y') {
            
        }
        else {
            cout << "Invalid choice... Please Try Again" << endl;
            system("pause");
            goto confirm;
        } 
    }
    isValid = false;
    do {
        cout << "Enter the amount of cash you will transfer:";
        cin >> transfer;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid amount. Please try again" << endl;
        }
        else if (transfer > account.balance) {
            cout << "You have insufficient balance to transfer this amount of cash" << endl;
            cout << "Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } while (isValid == false);

    system("CLS");
    cout << "Please confirm the name and the phone number or account number" << endl;
    cout << "Name: " << receivername << endl;
    cout << "Phone Number or Account Number: " << receiverphoneNumber << endl;
    cout << "The Ammount you will transfer: " << transfer << endl;

    char choice;
confirm2:
    cout << "Is this the correct information?(Y)es/(N)o/(C)ancel:";
    cin >> choice;
    if (choice == 'N') {
        cout << "Please re-enter your information" << endl;
        system("pause");
        system("CLS");
        goto start;
    }
    else if (choice == 'Y') {

    }
    else if (choice == 'C') {
        cout << "Transfer cancelled..." << endl;
        system("pause");
        system("CLS");
        mainMenu(phoneNumber);
    }
    else {
        cout << "Invalid choice... Please Try Again" << endl;
        system("pause");
        goto confirm2;
    }

    cout << "Processing..." << endl;
    int newbalance = account.balance - transfer;
    updateBalance(dir, phoneNumber, newbalance);
    int newbalanceotheracc = otheraccount.balance + transfer;
    updateBalance(dir, receiverphoneNumber, transfer);
    selectData(dir, phoneNumber, 2);
    cout << "Money transfer sucessfull" << endl;
    system("pause");
    system("CLS");
    mainMenu(phoneNumber);

}

void transferOtherBank(string phoneNumber)
{
    string receivername, receiverphoneNumber;
    int amountToTransfer;
    bool isValid = false;
    int transfer;

start:
    cin.ignore();
    //cin.clear();
    cout << "Enter the Full Name of the Receiver:";
    getline(cin, receivername);

    while (isValid == false) {
        
        cin.clear();
        //cin.ignore();
        cout << "Enter the Phone Number or Account Number of the Receiver: ";
        cin >> receiverphoneNumber;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Phone number or Account Number. Please try again" << endl;
            system("pause");
        }
        else {
            isValid = true;
        }
    }

    
    isValid = false;
    do {
        cout << "Enter the amount of cash you will transfer:";
        cin >> transfer;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid amount. Please try again" << endl;
        }
        else if (transfer > account.balance) {
            cout << "You have insufficient balance to transfer this amount of cash" << endl;
            cout << "Please try again" << endl;
        }
        else {
            isValid = true;
        }
    } while (isValid == false);

    system("CLS");
    cout << "Please confirm the name and the phone number or account number" << endl;
    cout << "Name: " << receivername << endl;
    cout << "Phone Number or Account Number: " << receiverphoneNumber << endl;
    cout << "The Ammount you will transfer: " << transfer << endl;

    char choice;
confirm:
    cout << "Is this the correct information?(Y)es/(N)o/(C)ancel:";
    cin >> choice;
    if (choice == 'N') {
        cout << "Please re-enter your information" << endl;
        system("pause");
        system("CLS");
        goto start;
    }
    else if (choice == 'Y') {

    }
    else if (choice == 'C') {
        cout << "Transfer cancelled..." << endl;
        system("pause");
        system("CLS");
        mainMenu(phoneNumber);
    }
    else {
        cout << "Invalid choice... Please Try Again" << endl;
        system("pause");
        goto confirm;
    }

    cout << "Processing..." << endl;
    int newbalance = account.balance - transfer;
    updateBalance(dir, phoneNumber, newbalance);
    //int newbalanceotheracc = otheraccount.balance + transfer;
    //updateBalance(dir, receiverphoneNumber, transfer);
    selectData(dir, phoneNumber, 2);
    cout << "Money transfer sucessfull" << endl;
    system("pause");
    system("CLS");
    mainMenu(phoneNumber);

}

void accSettings(string phoneNumber)
{
    system("CLS");
    char transaction;
    bool isValid = false;

    cout << "Select account settings: " << endl;
    cout << "(A)Change PIN" << endl;
    cout << "(B)Make me verified(ADMIN)" << endl;
   // cout << "(C)Delete Account(ADMIN)" << endl;
    cout << "(X)EXIT" << endl;
    cout << endl;

    while (isValid == false) {
        cout << "Your Choice: ";
        cin >> transaction;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid Choice. Please try again" << endl;
            system("pause");
        }
        else {

            switch (transaction) {
            case 'A': {
                system("CLS");
                cout << "Change PIN selected" << endl;
                changePin(phoneNumber);
                isValid = true;
                break;
            }
            case 'B': {
                system("CLS");
                cout << "Make me verified selected" << endl;
                verification(phoneNumber);
                isValid = true;
                break;
            }
                    /*
            case 'C': {
                system("CLS");
                cout << "Delete Account(ADMIN) selected" << endl;
                //deposit(phoneNumber);
                isValid = true;
                break;
            }
            */
            case 'X': {
                cout << "Exit selected" << endl;
                system("pause");
                system("CLS");
                mainMenu(phoneNumber);
                isValid = true;
                break;
            }
            default:
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Choice. Please try again" << endl;
                system("pause");
                break;
            }


        }
    }
}

void changePin(string phoneNumber)
{

    string newpin1, newpin2, oldpin;
    char choice;

    start:
    cout << "Please enter your current PIN: ";
    cin >> oldpin;

    if (oldpin != account.pinorpass) {
        cout << "The pin you entered does not match into the system "<< endl;
        cout << "Please try Again" << endl;
        system("pause");
        system("CLS");
        goto start;
    }

    start2:
    cout << "Enter the new pin: ";
    cin >> newpin1;
    cout << "Re-Enter the new pin: ";
    cin >> newpin2;

    if (newpin1 != newpin2) {
        cout << "The new pin you entered does not match" << endl;
        cout << "Please try Again" << endl;
        system("pause");
        goto start2;
    }

    start3:
    cout << "Please confirm: " << endl;
    cout << "Do you want to change your pin?(Y/N): ";
    cin >> choice;

    if (choice == 'N') {
        cout << "Canceled Selected... " << endl;
        system("pause");
        system("CLS");
        accSettings(phoneNumber);
    }
    else if (choice == 'Y') {
        cout << "Processing... " << endl;
        updatePIN(dir, phoneNumber, newpin1);
        cout << "Success" << endl;
        system("pause");
        system("CLS");
        accSettings(phoneNumber);
    }
    else {
        cout << "Invalid choice... " << endl;
        cout << "Please try Again" << endl;
        system("pause");
        goto start3;
    }
}

void verification(string phoneNumber)
{
    system("CLS");
    char transaction;
    bool isValid = false;

    cout << "Changing account status to verified" << endl;
    updateStatus(dir, phoneNumber, "Verified(ADMIN)");
    cout << "Sucesss...." << endl;

    system("pause");
    system("CLS");
    accSettings(phoneNumber);

}
