// Order.h
// Order class definition.
#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

#include "Date.h"

const int price[ 14 ] = {   0, 280, 232, 256, 240, 275, 275,
                          300, 250, 250, 275, 275, 230, 200 };

class Order
{
public:
   Order( string theOrderNumber = "", string theEmail = "" );
   void setOrderNumber( string theOrderNumber );
   string getOrderNumber() const;
   void setEmail( string theEmail );
   string getEmail() const;
   void setDeliveryDate( Date date );
   Date getDeliveryDate();
   void setOrderDetails( int theOrderDetails[] );
   void displayOrderDetails() const;
private:
   char orderNumber[ 12 ]; // each order has a unique orderNumber
   char email[ 40 ];
   Date deliveryDate;  // delivery date
   int quantity[ 14 ]; // quantity[ i ] is the quantity of food #i in the order
                       // quantity[ 0 ] is not used
}; // end class Order

#endif // ORDER_H