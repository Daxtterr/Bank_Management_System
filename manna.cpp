#include <iostream>
#include <string>
#include <ctime>
using namespace std;



class Date {
    public:
    int day;
    int month;
    int year;
  

    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }
    
};

Date current_date() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1; 
    int year = localTime->tm_year + 1900;

    return Date(day, month, year);
    }

class Transaction{
    public:
    string transaction_type;
    double amount;
    double balance;
    Date date;

    Transaction() : amount(0.0), balance(0.0), date(0,0,0),transaction_type("transact") {}

    Transaction(double amt, double bal, Date d,string transact_type) : amount(amt), balance(bal), date(d),transaction_type(transact_type) {}



    
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


class Customer {
public:
    string name;
    string address;
    int age;
    int telephone_number;
    string customer_type;
    

   
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



class Account {


public:
    Customer customer;
    double balance;
    int accountNumber;
    Transaction* transactions;
    int numTransactions;
    int MAX_TRANSACTIONS=100;

    virtual ~Account() {}

   Account(const Customer& cus, double bal, int accNum, Transaction* tran)
    : customer(cus), balance(bal), accountNumber(accNum), numTransactions(0) {
    transactions = new Transaction[MAX_TRANSACTIONS];
    
    // Copy transactions from tran array
    for (int i = 0; i < MAX_TRANSACTIONS; ++i) {
        if (i < numTransactions) {
            transactions[i] = tran[i];
        } else {
            break; // Stop copying if we reach the end of the tran array
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


    string to_string() const {
        return "Account Number: " + std::to_string(accountNumber) +
               "\nCustomer: " + customer.name +
               "\nBalance: $" + std::to_string(balance);
    }

    void set_customer(Customer cus) {
        customer = cus;
    }

    void set_balance(double bal) {
        balance = bal;
    }

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


        Customer customer(name, address, age, telephone,customer_type);

        Account newAccount(customer, 0, accountNumber, 0);              
    }
};




class Senior : public Customer {
public:
    // Constants for Senior
     static constexpr double SAVINGS_INTEREST=0.04;
     static constexpr double CHECKING_INTEREST = 0.01;
     static constexpr double CHECK_CHARGE = 0.01;
     static constexpr double OVERDRAFT_PENALTY = 25.0;

}; 

class Adult : public Customer {
public:
    // Constants for Account
    static constexpr double SAVINGS_INTEREST = 0.03;
    static constexpr double CHECKING_INTEREST = 0.01;
    static constexpr double CHECK_CHARGE = 0.03;
    static constexpr double OVERDRAFT_PENALTY = 25.0;
};



class Student : public Customer {
public: 
    // Constants for Student Account
    static constexpr double SAVINGS_INTEREST = 0.04;
    static constexpr double CHECKING_INTEREST = 0.01;
    static constexpr double CHECK_CHARGE = 0.02;
    static constexpr double OVERDRAFT_PENALTY = 25.0;

};




class Savings_Account: public Account {
public:
    int SAVINGS_INTEREST;
    

    Savings_Account(Customer cus, double bal, int accNum, Transaction* tran)
    : Account(cus, bal, accNum, tran) {}

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



    void deposit(int amount,int day ,int month,int year){
        balance += amount;
        Date date(day,month,year);
        Transaction transaction(amount,balance,date,"DEPOSIT");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


    void withdrawal(int amount,int day ,int month,int year){
        balance -= amount;
        Date date(day,month,year);
        Transaction transaction(amount,balance,date,"WITHDRAWAL");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


    void add_interest(int SAVINGS_INTEREST){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentDay = ltm->tm_mday;
        int currentMonth = 1 + ltm->tm_mon;
        int currentYear = 1900 + ltm->tm_year;

        // Assuming date is stored in the format day/month/year
        int interest = currentDay - balance * SAVINGS_INTEREST;
        balance += interest ;
        Date date(current_date().day, current_date().month, current_date().year);
        Transaction transaction(SAVINGS_INTEREST,balance,date,"INTEREST");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }

    
};


class Checking_Account : public Account {
public:
    int CHECKING_INTEREST;



    Checking_Account(Customer cus, double bal, int accNum, Transaction* tran)
        : Account(cus, bal, accNum, tran) {}

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
    

    void deposit(int amount,int day ,int month,int year){
        balance += amount;
        Date date(day,month,year);
        Transaction transaction(amount,balance,date,"DEPOSIT");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


    void withdrawal(int amount,int day ,int month,int year){
        balance -= amount;
        Date date( day , month, year);
        Transaction transaction(amount,balance,date,"WITHDRAWAL");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


    void add_interest(int CHECKING_INTEREST){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentDay = ltm->tm_mday;
        int currentMonth = 1 + ltm->tm_mon;
        int currentYear = 1900 + ltm->tm_year;

        // Assuming date is stored in the format day/month/year
        int interest = currentDay - balance * CHECKING_INTEREST;
        balance += interest ;
        Date date(current_date().day, current_date().month, current_date().year);
        Transaction transaction(interest,balance,date,"INTEREST");
        transactions[numTransactions] = transaction;
        numTransactions++; // Increment the number of transactions
    }


   
};

class Bank {
private:Account** accounts;

public:
    int num_accounts; 
    int MAX_ACCOUNTS=20;

    Bank() {
        accounts = new Account*[MAX_ACCOUNTS];
        num_accounts=0;

    }


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

   

    void make_withdrawal(int accNum, double amount, int day,int month, int year) {
    bool found = false;
    for (int i = 0; i < num_accounts; ++i) {
        if (accounts[i]->get_account_number() == accNum) {
            // Check the type of account
            if (dynamic_cast<Savings_Account*>(accounts[i]) != nullptr) {
                // It's a Savings Account
                Savings_Account* savingsAccount = dynamic_cast<Savings_Account*>(accounts[i]);
                savingsAccount->withdrawal(amount, day, month,  year);
                cout << "Withdrawal from savings account " << accNum << ": " << amount << " on " << day << "/" << month << "/" << year
                     << " new balance: " << savingsAccount->get_balance() << endl;
            } else if (dynamic_cast<Checking_Account*>(accounts[i]) != nullptr) {
                // It's a Checking Account
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
            // Assuming customer_type is a member of Customer class
            cout << "Type of Customer: " << accounts[i]->get_customer().customer_type << endl;
            cout << "Balance: " << accounts[i]->get_balance() << endl;
            cout << "Transactions Breakdown: " << endl << accounts[i]->get_transaction() << endl;


            return;
        
    }
    std::cout << "Account not found." << std::endl;
}


};


int main() {   
    Bank bank;
    while (true) {
        // Display menu
        cout << "Select:" << endl;
        cout << "0: Add Account" << endl;
        cout << "1: Make Deposit" << endl;
        cout << "2: Make Withdrawal" << endl;
        cout << "3: Check Account" << endl;
        cout << "4: Exit" << endl;

        // Get user input
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {

            case 0: {
                string name;
                string address;
                int age;
                int telephone_number;
                int accNum ;
                int user_choice;
                int userr_choice;
                string customer_type;
                string acc_type;

                cout << "Enter Customer Name :";
                cin >> name;
                cout << "Enter Customer Address :";
                cin >> address;
                cout << "Enter Customer Age :";
                cin >> age;
                cout << "Enter Customer Phone Number :";
                cin >> telephone_number;

                cout << "Select Customer Type:" << endl;
                cout << "0: Senior" << endl;
                cout << "1: Adult" << endl;
                cout << "2: Student" << endl;
                cout << "Enter your choice: ";
                cin >>user_choice;
                if (user_choice == 0) {
                    customer_type = "Senior";
                } else if (user_choice == 1) {
                    customer_type = "Adult";
                } else if (user_choice == 2) {
                    customer_type = "Student";
                } else {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    return 1;  
                }
                cout << "Select Account Type:" << endl;
                cout << "0: Checking" << endl;
                cout << "1: Savings" << endl;
                cout << "Enter your choice:";
                cin >>userr_choice;
                if (userr_choice == 0) {
                    acc_type = "Checking";
                } else if (userr_choice == 1) {
                    acc_type = "Savings";
                } else {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    return 1;  // Exit with an error code
                }

                Customer newCustomer(name,address,age,telephone_number,customer_type);
                bank.add_account(newCustomer,0,0,acc_type,0);



                break;
            }

            case 1: {
                int accNum;
                double amount;
                int day, month, year;
                
                

                cout << "Enter Account Number :" << endl;
                cin >> accNum;
                cout << "Enter the amount  :" << endl;
                cin >> amount;
                cout << "Enter the date yyyy-mm-dd :" << endl;
                cin >> year >> month >> day;
                bank.make_deposit(accNum,amount,day,month,year);
                break;
        
            }
            case 2: {
                int accNum;
                double amount;
                int day, month, year;;

                cout << "Enter Account Number :" << endl;
                cin >> accNum;
                cout << "Enter the amount  :" << endl;
                cin >> amount;
                cout << "Enter the date yyyy-mm-dd :" << endl;
                cin >> year >> month >> day;
                bank.make_withdrawal(accNum,amount,day,month,year);
                break;
            }
            case 3: {
                int accNum;
                string customer;
                cout << "Enter Account Number :" << endl;
                cin >> accNum;
                cout << "Type of Customer :" << endl;
                cin >> customer;
                bank.checkAccount(accNum,customer);
                
                break;
            }
             case 4: {
                std::cout << "Exiting the program. Thank you!" << std::endl;
                return 0;
            }
            default: {
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            }
        
        }
        
    }
        }    