// Account.h
// Account class definition.
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

extern const char foods[ 14 ][ 60 ];

class Account
{
public:
   Account( string theEmail = "", string thePassword = "", string theName = "",
            string theAddress = "" );

   // determines whether a user-specified password matches password in Account
   bool validatePassword( string userPassword ) const;

   void setEmail( string theEmail );
   string getEmail() const;

   void setPassword( string thePassword );
   string getPassword() const;

   void setName( string theName );
   string getName() const;

   void setAddress( string theAddress );
   string getAddress() const;

   void setCart( int *theCart );

   int *getCart();

   void modifyCart( int code, int amount ); // cart[ code ] is modified to amount

   void resetCart();

   bool emptyCart() const;

   // Code, Item and Quantity of each foods in the shopping cart
   void displayCart() const;

   void displayOrders() const;
private:
   char email[ 40 ]; // used as the account number
   char password[ 20 ];
   char name[ 8 ];
   char address[ 80 ];
   int cart[ 14 ]; // cart[ i ] is the quantity of food #i in the shopping cart
                   // cart[ 0 ] is not used
}; // end class Account

#endif // ACCOUNT_H