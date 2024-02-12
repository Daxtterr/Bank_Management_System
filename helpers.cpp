/*
 * Created by Emmanuel Aimuel on 2024-02-08.
 * This module contains all the helper functions to be used in this program.
 * This file contains classes and a fucntion used to run the operation of the bank
 */


/* Include header file */
#include "headers.h"


/* Class Declaration */

/*
 * Date
 *
 * Purpose: Structure the date of each transaction
 *
 * \Data fields: int day which specifies the day as an integer
 *               int month which specifies the month as an integer
 *               int year which specifies the year as an integer
 * 
 * \Methods: None
 *
 */

class Date {
    //Public Data fields
    public:
    int day;
    int month;
    int year;
  
    //Constructor
    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }
    
};



/*
 * current_date
 *
 * Purpose:get the current date
 *
 * \param None
 * \return current date as Date data type
 *
 * Side effect: None
 */

Date current_date() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1; 
    int year = localTime->tm_year + 1900;

    return Date(day, month, year);
    }


/*
 * Customer

 * Purpose: Structure the data of each customer that will perform a transaction
 *
 * \Data fields: int age which specifies the age of the customer as an integer
 *               int telephone_number which specifies the phone number of the customer as an integer
 *               string name which specifies the name of the customer as a string
 *               string address which specifies the address of the customer as a string
 *               string customer which specifies the customer type as a string
 * 
 * \Methods: Accessors :string get_name() returns name of a specific customer
 *                      string get_address() returns address of a specific customer
 *                      int get_age) returns age of a specific customer
 *                      string get_address() returns address of a specific customer
 *                      string get_customer_type() returns customer_type of a specific customer
 * 
 * 
 *          Modifiers :void set_name() changes the name of a specific customer to the parameter passed
 *                     void set_address() changes the address of a specific customer to the parameter passed
 *                     void set_age() changes the age of a specific customer to the parameter passed
 *                     void set_address() changes the address of a specific customer to the parameter passed
 *                     void set_customer_type() changes the customer_type of a specific customer to the parameter passed
 */

class Customer {
//Data fields
public:
    string name;
    string address;
    int age;
    int telephone_number;
    string customer_type;
    

   //Cnstructor
    Customer(string n, string addr, int a, int tel,string cust_type)
        : name(n), address(addr), age(a), telephone_number(tel),customer_type(cust_type){}


      

   // Accessors
    string get_name() const {
        return name;
    }

    string get_address() const {
        return address;
    }

    int get_age() const {
        return age;
    }

    int get_telephone_number() const {
        return telephone_number;
    }

    string get_customer_type() const{
        return customer_type;
    }

    


    // Modifiers
    void set_name(string new_name) {
        name = new_name;
    }

    void set_address(string new_address) {
        address = new_address;
    }

    void set_age(int new_age) {
        age = new_age;
    }

    void set_telephone_number(int new_telephone) {
        telephone_number = new_telephone;
    }


    void set_customer_type(string new_customer_type) {
         customer_type = new_customer_type;
    }

    
};

/*
 * Transaction
 *
 *
 * Purpose: Creates and updates the transaction performed in an account with an array
 *
 * \Data fields: string transaction_type specifies the type of transaction as a string
 *               double amount specifies the amount of money in that transaction as a double
 *               double balance specifies the balance of money in the account where transaction just occured
 *               Date date specifies the date in which a specific transaction took place using the Date class as it's data type
 * 
 * \Methods: to_string() :returns the array elements of transactions of a specific account in a string format
 *
 */
class Transaction{
    //Data Fields
    public:
    string transaction_type;
    double amount;
    double balance;
    Date date;

    //  Constructors
    Transaction() : amount(0.0), balance(0.0), date(0,0,0),transaction_type("transact") {}
    Transaction(double amt, double bal, Date d,string transact_type) : amount(amt), balance(bal), date(d),transaction_type(transact_type) {}



   // returns the array elements of transactions of a specific account in a string format
    string to_string() const {
        string type; 
         if (transaction_type == "DEPOSIT"){
            type = "DEPOSIT";
        }else if (transaction_type == "WITHDRAWAL"){
            type="WITHDRAWAL";
        }else if (transaction_type == "INTEREST"){
            type="INTEREST";
        }else if (transaction_type == "CHECK_CHARGE"){
            type="CHECK_CHARGE";
        }
        return "Type: " + type + ", Amount: " + std::to_string(amount) +
               ", Balance: " + std::to_string(balance) +
               ", Date: " + std::to_string(date.day) + "/" +
               std::to_string(date.month) + "/" + std::to_string(date.year);
    }


};


/*
 * Account
 *
 *
 * Purpose: Structure the bank account of each customer
 *
 * \Data fields: Customer customer specifies the details of the customer that owns a specific account
 *               double balance specifies the balance of money in the account 
 *               int year which specifies the year as an integer
 *               int MAX_TRANSACTIONS specifies the maxmimum amount of transactions per account
 *               Transaction* transactions the array of transactions in a specific account with data type of the Transaction class
 *               int numTransactions specifies the current number of transactions an account has done 
 * 
 * 
 * \Methods: string get_account_number() returns the account_number of a specific customer
 *           double get_balance() returns the account balance of a specific customer's account
 *           Customer get_customer() returns a customer that owns a specific account
 *           string get_transactions() returns the array of transactions of a particular account
 *           void add_transaction() adds a transaction to the array of transactions of a particular account
 *           string to_string() returns the details of a particular account
 *           void set_customer() modifies the details of an existing customer
 *           void set_balance() modifies the balance of a customer's account
 *           void create_account() collects details and creates an account for a customer
 *
 */
class Account {
//Data Fields
public:
    Customer customer;
    double balance;
    int accountNumber;
    Transaction* transactions;
    int numTransactions;
    int MAX_TRANSACTIONS=100;

    virtual ~Account() {}
    //Constructor
   Account(const Customer& cus, double bal, int accNum, Transaction* tran)
    : customer(cus), balance(bal), accountNumber(accNum), numTransactions(0) {
    transactions = new Transaction[MAX_TRANSACTIONS];
    
    // Copy transactions from transaction array
    for (int i = 0; i < MAX_TRANSACTIONS; ++i) {
        if (i < numTransactions) {
            transactions[i] = tran[i];
        } else {
            break; // Stop copying if we reach the end of the transaction array
        }
    }
}

  

    int get_account_number() const {
        return accountNumber;
    }

    double get_balance() const {
        return balance;
    }

    Customer get_customer() const {
        return customer;
    }

    string get_transaction() const {
        std::string transactionsStr;
        for (int i = 0; i < numTransactions; ++i) {
            transactionsStr += transactions[i].to_string() + "\n"; // Assuming each transaction has a to_string() method
        }
        return transactionsStr;
    }

    // adds a transaction to the array of transactions of a particular account
    void add_transaction(const Transaction& transaction) {
        // Check if there is enough space in the transactions array
        if (numTransactions < MAX_TRANSACTIONS) {
            // Add the transaction to the array
            transactions[numTransactions] = transaction;
            // Increment the number of transactions
            numTransactions++;
        } else {
            // Handle the case where the transaction array is full
            cout << "Maximum number of transactions reached. Transaction not added." << endl;
        }
    }



    //Modifiers
    void set_customer(Customer cus) {
        customer = cus;
    }

    void set_balance(double bal) {
        balance = bal;
    }

    //returns the details of a particular account
    string to_string() const {
        return "Account Number: " + std::to_string(accountNumber) +
               "\nCustomer: " + customer.name +
               "\nBalance: $" + std::to_string(balance);
    }


    //collects details and creates an account for a customer
    void create_account() {
        // Get input from the user for the new account
        string name, address,customer_type;
        int age, telephone;
        double startingBalance;

        cout << "Enter customer name: ";
        cin >> name;

        cout << "Enter customer address: ";
        cin >> address;

        cout << "Enter customer age: ";
        cin >> age;

        cout << "Enter customer telephone number: ";
        cin >> telephone;

        cout << "Enter customer type: ";
        cin >> customer_type;

        //create the customer
        Customer customer(name, address, age, telephone,customer_type);

        //create the account for the customer
        Account newAccount(customer, 0, accountNumber, 0);              
    }
};



/*
 * Senior
 *
 *
 * Purpose: Deines constants for the Senior customer account
 *
 * \Data fields: static constexpr double SAVINGS_INTEREST specifies the savings interest for a senior savings account
 *               static constexpr double CHECKING_INTEREST specifies the checking interest for a senior checkings account
 *               static constexpr double CHECK_CHARGE specifies the checking charge for a senior account
 *               static constexpr double OVERDRAFT_PENALTY specifies the overdraft penalty for a senior account
 * 
 * 
 * \Methods: None
 *
 */
class Senior : public Customer {
public:
    // Constants for Senior
     static constexpr double SAVINGS_INTEREST=0.04;
     static constexpr double CHECKING_INTEREST = 0.01;
     static constexpr double CHECK_CHARGE = 0.01;
     static constexpr double OVERDRAFT_PENALTY = 25.0;

}; 



/*
 * Adult
 *
 *
 * Purpose: Deines constants for the Adult customer account
 *
 * \Data fields: static constexpr double SAVINGS_INTEREST specifies the savings interest for an Adult savings account
 *               static constexpr double CHECKING_INTEREST specifies the checking interest for an Adult checkings account
 *               static constexpr double CHECK_CHARGE specifies the checking charge for an Adult account
 *               static constexpr double OVERDRAFT_PENALTY specifies the overdraft penalty for an Adult account
 * 
 * 
 * \Methods: None
 *
 */
class Adult : public Customer {
public:
    // Constants for Account
    static constexpr double SAVINGS_INTEREST = 0.03;
    static constexpr double CHECKING_INTEREST = 0.01;
    static constexpr double CHECK_CHARGE = 0.03;
    static constexpr double OVERDRAFT_PENALTY = 25.0;
};



/*
 * Student
 *
 *
 * Purpose: Deines constants for the Student customer account
 *
 * \Data fields: static constexpr double SAVINGS_INTEREST specifies the savings interest for a student's savings account
 *               static constexpr double CHECKING_INTEREST specifies the checking interest for a student's checkings account
 *               static constexpr double CHECK_CHARGE specifies the checking charge for a student's account
 *               static constexpr double OVERDRAFT_PENALTY specifies the overdraft penalty for a student's account
 * 
 * 
 * \Methods: None
 *
 */

class Student : public Customer {
public: 
    // Constants for Student Account
    static constexpr double SAVINGS_INTEREST = 0.04;
    static constexpr double CHECKING_INTEREST = 0.01;
    static constexpr double CHECK_CHARGE = 0.02;
    static constexpr double OVERDRAFT_PENALTY = 25.0;

};






/*
 * Savings_Account
 *
 *
 * Purpose: Structure the data of a customer's savings account
 *
 * \Data fields: int SAVINGS_INTEREST set a customer's saving interest based on the customer's account_type
 * 
 * 
 * \Methods: void deposit() handles deposit into a customer's savings account
 *           void withdrwawal() handles withdrawal into a customer's savings account
 *           void add_interest() adds interest into a customer's savings account
 *
 */

class Savings_Account: public Account {
//Data fields
public:
    int SAVINGS_INTEREST;
    
    //Constructor
    Savings_Account(Customer cus, double bal, int accNum, Transaction* tran)
    : Account(cus, bal, accNum, tran) {}


    //Set SAVINGS_INTEREST depending on the customer type
    int set_SAVINGS_INTEREST(string account_type){
        if (account_type == "Senior") {
           SAVINGS_INTEREST = Senior::SAVINGS_INTEREST;
        } else if (account_type == "Adult") {
            SAVINGS_INTEREST = Adult::SAVINGS_INTEREST;
        }else if (account_type== "Student") {
            SAVINGS_INTEREST = Student::SAVINGS_INTEREST;
        }

        return SAVINGS_INTEREST;
    };


    //handles deposit into a customer's savings account
    void deposit(int amount,int day ,int month,int year){
        balance += amount;
        Date date(day,month,year);
        Transaction transaction(amount,balance,date,"DEPOSIT");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }

    // handles withdrawal into a customer's savings account
    void withdrawal(int amount,int day ,int month,int year){
        balance -= amount;
        Date date(day,month,year);
        Transaction transaction(amount,balance,date,"WITHDRAWAL");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }

    //adds interest into a customer's savings account and adds the transaction to the transaction array
    void add_interest(int SAVINGS_INTEREST){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentDay = ltm->tm_mday;
        int currentMonth = 1 + ltm->tm_mon;
        int currentYear = 1900 + ltm->tm_year;
        int interest = currentDay - balance * SAVINGS_INTEREST;
        balance += interest ;
        Date date(current_date().day, current_date().month, current_date().year);
        Transaction transaction(SAVINGS_INTEREST,balance,date,"INTEREST");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }

    
};


/*
 * Checking_Account
 *
 *
 * Purpose: Structure the data of a customer's checking account
 *
 * \Data fields: int CHECKING_INTEREST set a customer's CHECKING interest based on the customer's account_type
 * 
 * 
 * \Methods: void deposit() handles deposit into a customer's checking account
 *           void withdrwawal() handles withdrawal into a customer's checking account
 *           void add_interest() adds interest into a customer's checking account
 *
 */

class Checking_Account : public Account {
//Data fields
public:
    int CHECKING_INTEREST;


    //Constructor
    Checking_Account(Customer cus, double bal, int accNum, Transaction* tran)
        : Account(cus, bal, accNum, tran) {}

    //Set CHECK_INTEREST depending on the customer type
    int set_CHECK_INTEREST(string customer_type){
        if (customer_type == "Senior") {
           CHECKING_INTEREST = Senior::CHECKING_INTEREST;
        } else if (customer_type == "Adult") {
            CHECKING_INTEREST = Adult::CHECKING_INTEREST;
        }else if (customer_type== "Student") {
            CHECKING_INTEREST = Student::CHECKING_INTEREST;
        }
        return CHECKING_INTEREST;
    };
    
     //handles deposit into a customer's checking account
    void deposit(int amount,int day ,int month,int year){
        balance += amount;
        Date date(day,month,year);
        Transaction transaction(amount,balance,date,"DEPOSIT");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }

    //handles withdrawal into a customer's checking account
    void withdrawal(int amount,int day ,int month,int year){
        balance -= amount;
        Date date( day , month, year);
        Transaction transaction(amount,balance,date,"WITHDRAWAL");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


    //adds interest into a customer's checking account and adds the transaction to the transaction array
    void add_interest(int CHECKING_INTEREST){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentDay = ltm->tm_mday;
        int currentMonth = 1 + ltm->tm_mon;
        int currentYear = 1900 + ltm->tm_year;       
        int interest = currentDay - balance * CHECKING_INTEREST;
        balance += interest ;
        Date date(current_date().day, current_date().month, current_date().year);
        Transaction transaction(interest,balance,date,"INTEREST");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


   
};


/*
 * Bank
 *
 *
 * Purpose: Structure the Operations ofa bank uses all the classes above
 *
 * \Data fields: private Account** accounts 
 * 
 *               public: int MAX_TRANSACTIONS specifies the maxmimum amount of transactions per account
 *               int numTransactions specifies the current number of transactions an account has done 
 * 
 * 
 * 
 * 
 * \Methods: void add_account()creates an account for a customer
 *           void make_deposit() handles deposit into a customer's account
 *           void make_withdrawal() handles withdrawal from a customer's account
 *           void checkAccount() displays details of a customer's account
 *
 */
class Bank {
//Private data fields
private:Account** accounts;


//Public data fields
public:
    int num_accounts; 
    int MAX_ACCOUNTS=20;

    Bank() {
        accounts = new Account*[MAX_ACCOUNTS];
        num_accounts=0;

    }

    //creates an account for a customer
    void add_account(Customer cus, double bal, int accNum, string acc_type, Transaction* tran) {       
        if (num_accounts < MAX_ACCOUNTS) {
            if (acc_type == "Savings") {
                accounts[num_accounts] = new Savings_Account(cus, bal, accNum, tran);  
            } else if (acc_type == "Checking") {
                accounts[num_accounts] = new Checking_Account(cus, bal, accNum, tran);
            } else {
                cout << "Invalid account type.\n";
                return;
            }
            cout << "Account : "<<accNum << " Added Successfully!" << endl;
            num_accounts++; // Increment the number of accounts
        } else {
            cout << "Maximum number of accounts reached.\n";
        }
    }


    // handles deposit into a customer's account
    void make_deposit(int accNum, double amount, int day,int month, int year) {
    bool found = false;
    for (int i = 0; i < num_accounts; ++i) {
        if (accounts[i]->get_account_number() == accNum) {
            // Check the type of account
            if (dynamic_cast<Savings_Account*>(accounts[i]) != nullptr) {
                // It's a Savings Account
                Savings_Account* savingsAccount = dynamic_cast<Savings_Account*>(accounts[i]);
                savingsAccount->deposit(amount, day, month,  year);
                cout << "Deposit in savings account " << accNum << ": " << amount << " on " <<day << "/" << month << "/" << year
                     << " new balance: " << savingsAccount->get_balance() << endl;
            } else if (dynamic_cast<Checking_Account*>(accounts[i]) != nullptr) {
                // It's a Checking Account
                Checking_Account* checkingAccount = dynamic_cast<Checking_Account*>(accounts[i]);
                //Date date(day, month,  year);
                checkingAccount->deposit(amount, day, month,  year);
                cout << "Deposit in checking account " << accNum << ": " << amount << " on " << day << "/" << month << "/" << year
                << " new balance: " << checkingAccount->get_balance() << endl;
            } else {
                cout << "Unknown account type. Deposit failed." << endl;
                return;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Account not found. Deposit failed." << endl;
    }
}

   
    //handles withdrawal from a customer's account
    void make_withdrawal(int accNum, double amount, int day,int month, int year) {
    bool found = false;
    for (int i = 0; i < num_accounts; ++i) {
        if (accounts[i]->get_account_number() == accNum) {
            // Check the type of account
            if (dynamic_cast<Savings_Account*>(accounts[i]) != nullptr) {
                // if it's a Savings Account
                Savings_Account* savingsAccount = dynamic_cast<Savings_Account*>(accounts[i]);
                savingsAccount->withdrawal(amount, day, month,  year);
                cout << "Withdrawal from savings account " << accNum << ": " << amount << " on " << day << "/" << month << "/" << year
                     << " new balance: " << savingsAccount->get_balance() << endl;
            } else if (dynamic_cast<Checking_Account*>(accounts[i]) != nullptr) {
                // if it's a Checking Account
                Checking_Account* checkingAccount = dynamic_cast<Checking_Account*>(accounts[i]);
                checkingAccount->withdrawal(amount,day, month,  year);
                cout << "Withdrawal from checking account " << accNum << ": " << amount << " on " << day << "/" << month << "/" << year
                     << " new balance: " << checkingAccount->get_balance() << endl;
            } else {
                cout << "Unknown account type. Withdrawal failed." << endl;
                return;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Account not found. Withdrawal failed." << endl;
    }
}



    /*isplays details of a customer's account,I assumed the check charge is meant to bill the customer
    each time they check their account*/
    void checkAccount(int accNum,string customer_type) {
    for (int i = 0; i < num_accounts; ++i) {
            double charge;
            if (customer_type == "Senior") {
            charge = Senior::CHECK_CHARGE;
            } else if (customer_type == "Adult") {
                charge = Adult::CHECK_CHARGE;
            }else if (customer_type== "Student") {
                charge = Student::CHECK_CHARGE;
            }
            accounts[i]->set_balance(accounts[i]-> balance -= charge);
            Date date(current_date().day, current_date().month, current_date().year);
            Transaction transaction(charge,accounts[i]->get_balance() ,date,"CHECK_CHARGE");
            accounts[i]->add_transaction(transaction); // Add the transaction to the account

            //numTransactions++; // Increment the number of transactions       
            cout << "Account found!" << endl;
            cout << "Account Number: " << accounts[i]->get_account_number() << endl;
            cout << "Account Owner: " << accounts[i]->get_customer().get_name() << endl;
            cout << "Type of Customer: " << accounts[i]->get_customer().customer_type << endl;
            cout << "Balance: " << accounts[i]->get_balance() << endl;
            cout << "Transactions Breakdown: " << endl << accounts[i]->get_transaction() << endl;


            return;
        
    }
    std::cout << "Account not found." << std::endl;
}


};