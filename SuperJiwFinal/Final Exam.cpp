#include <iostream>
#include <ctime>
using namespace std;

#include "Login.h"
#include "Date.h"

const char foods[ 14 ][ 60 ] = { "", "Pork XiaoLongBao (12)",
                                     "Steamed Vegetable and Ground Pork Dumplings (8)",
                                     "Steamed Shrimp and Pork Dumplings (8)",
                                     "Steamed Vegetarian Mushroom Dumplings (8)",
                                     "Pork Buns (5)",
                                     "Vegetable and Ground Pork Buns (5)",
                                     "Vegetarian Mushroom Buns (5)",
                                     "Red Bean Buns (5)",
                                     "Sesame Buns (5)",
                                     "Taro Buns (5)",
                                     "Golden Lava Buns (5)",
                                     "House Special Spicy Shrimp and Pork Wontons (8)",
                                     "House Special Spicy Vegetable and Ground Pork Wontons (8)" };

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end = INT_MAX );

Date computeCurrentDate(); // return the current date

// if the year is a leap year, return true; otherwise, return false
bool leapYear( int year );

void registration( AccountDatabase &accountDatabase );

int main()
{
   cout << "Welcome to DintaiFung Shopping Mall!\n";

   bool userExited = false; // user has not chosen to exit

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      AccountDatabase accountDatabase;
      OrderDatabase orderDatabase;

      Login login( accountDatabase, orderDatabase );

      cout << "\n1. Login\n"
           << "2. Registration\n"
           << "3. End\n\n";

      int mainMenuSelection;
      do cout << "Enter your choice: (1~3): ";
      while( ( mainMenuSelection = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( mainMenuSelection )
      {
      case 1:
         login.run();
         break;
      case 2:
         registration( accountDatabase );
         break;
      case 3: // user chose to terminate session
         cout << "\nExiting the system...\n\n";
         userExited = true; // this session should end
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

Date computeCurrentDate()
{
   tm structuredTime;
//   time_t rawTime = time( 0 ) + 5 * 24 * 60 * 60;
   time_t rawTime = time( 0 );
   localtime_s( &structuredTime, &rawTime );

   int year = structuredTime.tm_year + 1900;
   int month = structuredTime.tm_mon + 1;
   int day = structuredTime.tm_mday;

   Date currentDate;
   currentDate.setYear( year );
   currentDate.setMonth( month );
   currentDate.setDay( day );

   return currentDate;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

void registration( AccountDatabase &accountDatabase )
{
   string email;







   cout << "\nEnter your password: ";
   string password;
   cin >> password;

   cout << "\nEnter your name: ";
   string name;
   cin >> name;

   cout << "\nEnter your physical address: ";
   string address;
   cin >> address;
   cin.ignore();

   Account newAccount( email, password, name, address );

   int cart[ 14 ] = {};
   newAccount.setCart( cart );

   accountDatabase.pushBack( newAccount );

   cout << "\nRegistration Successfully!\n";
}