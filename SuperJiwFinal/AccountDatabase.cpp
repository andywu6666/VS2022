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





}

Account* AccountDatabase::getAccount( string email )
{





}
