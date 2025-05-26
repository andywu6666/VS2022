// OrderDatabase.h
// OrderDatabase class definition. Represents the order's database.
#ifndef ORDER_DATABASE_H
#define ORDER_DATABASE_H

#include <vector>
#include "Order.h" // Order class definition

class OrderDatabase
{
public:
   OrderDatabase();
   ~OrderDatabase();
   string generateOrderNumber() const; // generate a unique order number
   void pushBack( Order &newOrder ); // add newOrder at the end of orders

   // there exists an order containing specified email address
   bool existOrders( string email ) const;

   void displayOrders( string email, string name ) const;
private:
   vector< Order > orders; // vector of the customer's orders

   // loads orders from Orders.dat; outdated orders are deleted
   void loadOrderDetails();
   void saveOrderDetails(); // saves orders into Orders.dat

   // there exists an order containing specified orderNumber
   bool existOrder( string orderNumber ) const;
}; // end class OrderDatabase

#endif // ORDER_DATABASE_H