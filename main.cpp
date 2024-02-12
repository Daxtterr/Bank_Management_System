/* 
 * This module contains the main function of this program.
 *
 * This file calls the header file as well as the file containing
 * the helper functions and demonstrates Object-Oriented Programming
 */

/* Include header files */
#include "headers.h"
#include "helpers.cpp"

/*
 * Module: main
 * Author: Aimuel Emmanuel
 * Date: 2024-02-08
 *
 * Purpose: Point of execution in this program
 * Parameter: None
 * Precondition: None
 * \return 0 if no errors, otherwise 1
 * Side effect: None
 */

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
            //Create account
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
            //Make a deposit
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
                //Make a Withdrawal
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
                //Display account details and information
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