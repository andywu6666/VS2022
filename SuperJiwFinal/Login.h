// Login.h
// Login class definition.
#ifndef LOGIN_H
#define LOGIN_H

#include "AccountDatabase.h" // AccountDatabase class definition
#include "OrderDatabase.h" // OrderDatabase class definition

class Login
{
public:
   Login( AccountDatabase &theAccountDatabase, OrderDatabase &theOrderDatabase );
   void run();
private:
   AccountDatabase &accountDatabase; // account database
   OrderDatabase &orderDatabase; // order database

   void authenticateUser( string &email, string &password );
   void displayCart( string email );
   void checkout( string email ); // creates an order, and push it into orderDatabase
   void displayOrderHistory( string email );
   Date deliveryDate(); // returns the delivery date
}; // end class Login

#endif