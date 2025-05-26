// MakingOrder.h
// MakingOrder class definition.
#ifndef MAKING_ORDER_H
#define MAKING_ORDER_H

#include "AccountDatabase.h" // AccountDatabase class definition

class MakingOrder
{
public:
   MakingOrder( string theEmail, AccountDatabase &theAccountDatabase );
   void run(); // perform the MakingOrder
private:
   string email; // used as the account number
   AccountDatabase &accountDatabase; // account database
};

#endif // MAKING_ORDER_H