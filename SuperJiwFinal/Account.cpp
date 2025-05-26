// Account.cpp
// Member-function definitions for class Account.
#include <iostream>
#include <iomanip>
#include "Account.h" // Account class definition

const int price[ 14 ] = {   0, 280, 232, 256, 240, 275, 275,
                          300, 250, 250, 275, 275, 230, 200 };

Account::Account( string theEmail, string thePassword, string theName, string theAddress )
{
   setEmail( theEmail );
   setPassword( thePassword );
   setName( theName );
   setAddress( theAddress );

   int cart[ 14 ] = {};
   setCart( cart );
}

// determines whether a user-specified password matches password in Account
bool Account::validatePassword( string userPassword ) const
{ 
   return ( userPassword.compare( password ) == 0 );
}
   
void Account::setEmail( string theEmail )
{
   unsigned int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( unsigned int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

string Account::getEmail() const
{
   return email;
}

void Account::setPassword( string thePassword )
{
   unsigned int length = thePassword.size();
   length = ( length < 20 ? length : 19 );
   for( unsigned int i = 0; i < length; i++ )
      password[ i ] = thePassword[ i ];
   password[ length ] = '\0';
}

string Account::getPassword() const
{
   return password;
}

void Account::setName( string theName )
{
   unsigned int length = theName.size();
   length = ( length < 8 ? length : 7 );
   for( unsigned int i = 0; i < length; i++ )
      name[ i ] = theName[ i ];
   name[ length ] = '\0';
}

string Account::getName() const
{
   return name;
}

void Account::setAddress( string theAddress )
{
   unsigned int length = theAddress.size();
   length = ( length < 80 ? length : 79 );
   for( unsigned int i = 0; i < length; i++ )
      address[ i ] = theAddress[ i ];
   address[ length ] = '\0';
}

string Account::getAddress() const
{
   return address;
}

// set cart content
void Account::setCart( int *theCart )
{
   if( theCart != nullptr )
      for( int i = 1; i < 14; i++ )
         cart[ i ] = ( theCart[ i ] >= 0 ? theCart[ i ] : 0 );
}

int * Account::getCart()
{
   return cart;
}

void Account::resetCart()
{
   for( int i = 0; i < 14; i++ )
      cart[ i ] = 0;
}

bool Account::emptyCart() const
{
   for( int i = 1; i < 14; i++ )
      if( cart[ i ] != 0 )
         return false;
   return true;
}

void Account::modifyCart( int code, int amount )
{
   if( code > 0 && code < 14 && amount >= 0 )
      cart[ code ] = amount;
}

void Account::displayCart() const
{
   cout << "\nYour shopping cart:\n";
   cout << setw( 4 ) << "Code" << setw( 60 ) << "Item" << setw( 10 ) << "Quantity" << endl;

   for( int i = 1; i < 14; i++ )
      cout << setw( 4 ) << i << setw( 60 ) << foods[ i ] << setw( 10 ) << cart[ i ] << endl;
}

void Account::displayOrders() const
{
   int total = 0;
   for( int i = 1; i < 14; i++ )
      if( cart[ i ] > 0 )
      {
         cout << setw( 9 ) << i << setw( 60 ) << foods[ i ] << setw( 7 ) << price[ i ]
              << setw( 10 ) << cart[ i ]
              << setw( 10 ) << cart[ i ] * price[ i ] << endl;
         total += cart[ i ] * price[ i ];
      }

   cout << "\nTotal: " << total << endl;
}