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
    int newCart[14], * oldCart = accountDatabase.getCart(email); //add
    Account user(email); //modify
    user.setCart(newCart); //modify

   
    int foodCode = -1; //modify
    int quantity = newCart[foodCode]; //modify

    //showing Cart
    user.displayCart();

   
    if (oldCart != nullptr) //add
    {
        for (int i = 1; i < 14; i++) { //add
            newCart[i] = (oldCart[i] >= 0 ? oldCart[i] : 0); //add
        }
    }
    do { //add
        cout << "\nEnter foods code  (0 to end): ";

    } while ((foodCode = inputAnInteger(0, 13)) == -1); //modify
    
        if (foodCode == 0)
            return;
    //unsure

    cout << "\nEnter quantity: ";
    cin >> quantity;
    cin.ignore(); //add

    bool backToTop = false; 
    while (!backToTop) 
   {
        cout << "\n1. Continue Shopping\n"
            << "2. Save your Shopping Cart\n"
            << "3. Abandon\n";

        int choice;
        do cout << "Enter your choice: (1~3): ";
        while ((choice = inputAnInteger(1, 3)) == -1);

        user.setCart(newCart); //add

        switch (choice)
        {
        case 1:
            accountDatabase.modifyCart(user); //add
            run();
            backToTop = true; //add
            break;
        case 2:
            accountDatabase.modifyCart(user); //modify
            // call function to save shopping cart
            backToTop = true; 
            break; 
        case 3:
            backToTop = true; // this session should end 
            break; //add
        }
   }


  //  accountDatabase.displayOrders(email); //delete




}