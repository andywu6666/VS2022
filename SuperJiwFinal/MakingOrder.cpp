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
    Account user;
    user.setCart(0);
    int foodCode = 0;
    int quantity = 0;

    //showing Cart
    user.displayCart();

    cout << "\nEnter foods code  (0 to end): ";
    
    while ((foodCode = inputAnInteger(0, 13)) == -1)
    {
        if (foodCode == 0)
            return;
    }//unsure

    cout << "\nEnter quantity: ";
    cin >> quantity;

    bool backToTop = false;
    while (!backToTop)
    {
        cout << "\n1. Continue Shopping\n"
            << "2. Save your Shopping Cart\n"
            << "3. Abandon\n";

        int choice;
        do cout << "Enter your choice: (1~3): ";
        while ((choice = inputAnInteger(1, 3)) == -1);

        switch (choice)
        {
        case 1:
            run();
            break;
        case 2:
            user.modifyCart(foodCode, quantity);
            // call function to save shopping cart
            backToTop = true;
            break;
        case 3:
            backToTop = true; // this session should end
        }
    }


    accountDatabase.displayOrders(email);




}