// AccountDatabase.h
// AccountDatabase class definition.
#ifndef ACCOUNT_DATABASE_H
#define ACCOUNT_DATABASE_H

#include <vector>
#include "Account.h" // Account class definition

class AccountDatabase
{
public:
   AccountDatabase();
   ~AccountDatabase();

   // there exists an account containing specified email address
   bool existAccount( string userEmail );

   // determine whether email address and password match those of an Account
   bool authenticateUser( string email, string password );

   void pushBack( Account &newAccount ); // add newAccount at the end of accounts

   // return name of the unique Account object in accounts, containing specified email address
   string getName( string email );

   // return address of the unique Account object in accounts, containing specified email address
   string getAddress( string email );

   // return cart of the unique Account object in accounts, containing specified email address
   int* getCart( string email );

   void modifyCart( Account &account );

   void resetCart( string email );

   bool emptyCart( string email );

   void displayOrders( string email );

private:
   vector< Account > accounts; // vector of the customer's accounts

   void loadAccountDetails(); // loads accounts from Accounts.dat
   void saveAccountDetails(); // saves accounts into Accounts.dat

   // return a pointer to the unique Account object in accounts,
   // containing specified email address
   // if no Account object in accounts contains specified email address, return nullptr
   Account* getAccount( string email );
}; // end class AccountDatabase

#endif // ACCOUNT_DATABASE_H