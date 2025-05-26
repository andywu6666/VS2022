// AccountDatabase.cpp
// Member-function definitions for class AccountDatabase.
#include <iostream>
#include <fstream>
#include "AccountDatabase.h" // AccountDatabase class definition

AccountDatabase::AccountDatabase()
{
   loadAccountDetails();
}

AccountDatabase::~AccountDatabase()
{
   saveAccountDetails();
}

void AccountDatabase::loadAccountDetails()
{
    ifstream inFile("Accounts.dat", ios::in | ios::binary);
    if (!inFile)
    {
        cout << "There are no accounts registered yet! (or not correctly opened...)" << endl;
        return;
    }

    Account infor;
    while (inFile.read(reinterpret_cast<char*>(&infor), sizeof(Account)))
    {
        accounts.push_back(infor);
    }

    inFile.close();
}

// determine whether user-specified email address and password match
// those of an account in the database
bool AccountDatabase::existAccount( string userEmail )
{
   // attempt to retrieve the account with the email address
   Account * const userAccountPtr = getAccount( userEmail );

   if( userAccountPtr == nullptr )
      return false;
   else // account found
      return true;
} // end function authenticateUser

// determine whether user-specified email address and password match
// those of an account in the database
bool AccountDatabase::authenticateUser( string email, string password )
{
   // attempt to retrieve the account with the email address
   Account * const userAccountPtr = getAccount( email );

   // if account exists, return result of Account function validatePassword
   if ( userAccountPtr == nullptr )
      return false;
   else
      return userAccountPtr->validatePassword( password );
} // end function authenticateUser

void AccountDatabase::pushBack( Account &newAccount )
{
   accounts.push_back( newAccount );
}

string AccountDatabase::getName( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return string( "" );
   else
      return accountPtr->getName();
}

string AccountDatabase::getAddress( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return string( "" );
   else
      return accountPtr->getAddress();
}

int* AccountDatabase::getCart( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return nullptr;
   else
      return accountPtr->getCart();
}

void AccountDatabase::modifyCart( Account &account )
{
   Account *ptr = getAccount( account.getEmail() );
   ptr->setCart( account.getCart() );
}

void AccountDatabase::resetCart( string email )
{
   Account *ptr = getAccount( email );
   ptr->resetCart();
}

bool AccountDatabase::emptyCart( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return true;
   else
      return accountPtr->emptyCart();
}

void AccountDatabase::displayOrders( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr != nullptr )
      return accountPtr->displayOrders();
}

void AccountDatabase::saveAccountDetails()
{
    ofstream outFile("Accounts.dat", ios::out | ios::binary);

    if (!outFile)
    {
        cout << "The file Account.dat can't be written!" << endl;
        system("pause");
        exit(1);
    }

    
    for (size_t i = 0; i < accounts.size(); i++)
    {
        outFile.write(reinterpret_cast<const char*>(&accounts[i]), sizeof(Account));
    }
    outFile.close();


}

Account* AccountDatabase::getAccount( string email ) // finding where this email address located? //something wrong
{

   /* Account* accountPtr = getAccount(email);
    if (accountPtr->getEmail() == email)
    return accountPtr;
    
    
    return nullptr;*/
    vector<Account>::iterator ptr = accounts.begin();
    for (;ptr < accounts.end() ; ptr++)
    {
        if (email == ptr->getEmail())
        return &*ptr;
    }

    return nullptr;

}
