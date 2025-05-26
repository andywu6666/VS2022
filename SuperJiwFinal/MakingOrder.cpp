#include <iostream>
#include <iomanip>
#include "MakingOrder.h" // MakingOrder class definition

extern int inputAnInteger( int begin, int end = INT_MAX );

MakingOrder::MakingOrder( string theEmail, AccountDatabase &theAccountDatabase )
   : email( theEmail ),
     accountDatabase( theAccountDatabase )
{
}

void MakingOrder::run()
{





}