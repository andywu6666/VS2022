// OrderDatabase.cpp
// Member-function definitions for class OrderDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "OrderDatabase.h" // OrderDatabase class definition

extern Date computeCurrentDate();
extern bool leapYear( int year );

// OrderDatabase default constructor initializes orders
OrderDatabase::OrderDatabase()
{
   loadOrderDetails();
}

// OrderDatabase destructor
OrderDatabase::~OrderDatabase()
{
   saveOrderDetails();
}

void OrderDatabase::loadOrderDetails()
{
    ifstream inFile("Orders.dat", ios::in | ios::binary);
    if (!inFile)
    {
        cout << "There are no orders yet! (or not correctly opened...)" << endl;
        return;
    }

    Order infor;
    while (inFile.read(reinterpret_cast<char*>(&infor), sizeof(Order)))
    {
        if (infor.getDeliveryDate() < computeCurrentDate()) //add
            continue;//add
        
            continue;
        orders.push_back(infor);
    }

    inFile.close();




}

string OrderDatabase::generateOrderNumber() const
{
   srand( static_cast< unsigned int >( time( nullptr ) ) );

   string orderNumber;
   do
   {
      orderNumber.push_back( rand() % 26 + 'A' );
      for( int i = 1; i <= 9; i++ )
         orderNumber.push_back( rand() % 10 + '0' );
   } while( existOrder( orderNumber ) );

   return orderNumber;
}

void OrderDatabase::pushBack( Order &newOrder )
{
   orders.push_back( newOrder );
}

bool OrderDatabase::existOrders( string email ) const
{
   for( size_t i = 0; i < orders.size(); i++ )
      if( orders[ i ].getEmail() == email )
         return true;
   return false;
}

void OrderDatabase::displayOrders( string email, string name ) const
{
   cout << "\nYour order details:";
   for( size_t i = 0; i < orders.size(); i++ )
      if( orders[ i ].getEmail() == email )
      {
         cout << endl << setw( 9 ) << "Item Code" << setw( 60 ) << "Item" << setw(7) << "Price"
              << setw( 10 ) << "Quantity" << setw( 10 ) << "Subtotal" << endl;
         orders[ i ].displayOrderDetails();
      }
}

void OrderDatabase::saveOrderDetails()
{
    ofstream outFile("Orders.dat", ios::out | ios::binary);

    if (!outFile)
    {
        cout << "The file Orders.dat can't be written!" << endl;
        system("pause");
        exit(1);
    }


    for (size_t i = 0; i < orders.size(); i++)
    {
        outFile.write(reinterpret_cast<const char*>(&orders[i]), sizeof(Order));
    }
    outFile.close();




}

bool OrderDatabase::existOrder( string orderNumber ) const
{
   for( size_t i = 0; i < orders.size(); i++ )
      if( orders[ i ].getOrderNumber() == orderNumber )
         return true;
   return false;
}