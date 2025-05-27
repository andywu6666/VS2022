#include <iostream>
#include <iomanip>
#include "Login.h" // Registration class definition
#include "OrderDatabase.h" // OrderDatabase class definition
#include "MakingOrder.h" // MakingOrder class definition


extern int inputAnInteger( int begin, int end = INT_MAX );
extern Date computeCurrentDate();

Login::Login( AccountDatabase &theAccountDatabase, OrderDatabase &theOrderDatabase )
   : accountDatabase( theAccountDatabase ),
     orderDatabase( theOrderDatabase )
{
}

void Login::run()
{
   string email;
   string password;

   authenticateUser( email, password );

   if( email == "0" )
      return;

   MakingOrder makingOrder( email, accountDatabase );

   bool backToTop = false;
   while( !backToTop )
   {
      cout << "\n1. Making order\n"
           << "2. Display Cart\n"
           << "3. Proceed to Checkout\n"
           << "4. Order history\n"
           << "5. Back to top\n\n";

      int choice;
      do cout << "Enter your choice: (1~5): ";
      while( ( choice = inputAnInteger( 1, 5 ) ) == -1 );

      switch( choice )
      {
      case 1:
         makingOrder.run();
         break;
      case 2:
         displayCart( email );
         break;
      case 3:
         checkout( email );
         break;
      case 4:
         displayOrderHistory( email );
         break;
      case 5:
         backToTop = true; // this session should end
      }
   }
}

void Login::authenticateUser( string &email, string &password )
{
    inputEmail:
    cout << "\nEmail (Account number) (0 to end): ";
    cin >> email;
    cin.ignore(); //add
     if (email == "0") return;
     if (!accountDatabase.existAccount(email)) {
         cout << "\nNo account exists with the e-mail!\n"; goto inputEmail;
     }
    inputPassword:
    cout << "\nPassword: ";
    cin >> password;
    cin.ignore(); //add
    if (password == "0") return;
    if (!accountDatabase.authenticateUser(email, password)) { //modify
        cout << "Invalid password. Please try again.\n"; goto inputPassword;
    }


    
    



}

void Login::displayCart( string email )
{
   Account currentAccount( email );

   currentAccount.setCart( accountDatabase.getCart( email ) );

   currentAccount.displayCart();
}

void Login::checkout( string email )
{
    string orderNumber = orderDatabase.generateOrderNumber(); //add
    if (!accountDatabase.emptyCart(email)) { // modify
        cout << "\nOrder Number: " << orderNumber << endl; //modify
        cout << "\nFull Name: " << accountDatabase.getName(email) << endl; //modify
        cout << "\nShipping Address: " << accountDatabase.getAddress(email) << endl;  //modify
        cout << "\nBank account: 合作金庫 0062013162077139" << endl;
        
        Order newOrder(orderNumber, email); //add
        newOrder.setOrderDetails(accountDatabase.getCart(email)); //add
        
        cout << endl << setw(9) << "Item Code" << setw(60) << "Item" << setw(7) << "Price" << setw(10) << "Quantity" << setw(10) << "Subtotal" << endl; //add
        int total = 0; //add
        for (int i = 1; i < 14; i++) //add
        {
            if (accountDatabase.getCart(email)[i] > 0) //add
            {
                cout << setw(9) << i << setw(60) << foods[i] << setw(7) << price[i] //add
                    << setw(10) << accountDatabase.getCart(email)[i]
                    << setw(10) << price[i] * accountDatabase.getCart(email)[i] << endl;

                total += accountDatabase.getCart(email)[i] * price[i]; //add
            }
        }
        cout << "\nTotal: " << total << endl; //add
        newOrder.setDeliveryDate(deliveryDate()); //modify
        orderDatabase.pushBack(newOrder); //modify
        accountDatabase.resetCart(email); //add
       // cout << endl; //delete
       
    }
    else
    {
        cout << "\nYou shopping cart is empty!\n";
        return; //add;
    }
}

void Login::displayOrderHistory( string email )
{
   if( !orderDatabase.existOrders( email ) )
   {
      cout << "\nYou have no order history!\n";
      return;
   }

   string name = accountDatabase.getName( email );

   orderDatabase.displayOrders( email, name );
}

Date Login::deliveryDate()
{
   Date date = computeCurrentDate() + 4;
   cout << "\nChoose a delivery date\n";
   for( int i = 1; i <= 28; i++ )
   {
      cout << setw( 2 ) << i << ". " << date + i;
      if( i % 4 == 0 )
         cout << endl;
      else
         cout << "  ";
   }

   int dateCode;
   do cout << "? ";
   while( ( dateCode = inputAnInteger( 1, 28 ) ) == -1 );

   return date + dateCode;
}