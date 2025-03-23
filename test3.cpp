// Grade inquiry program.
#include <iostream>
#include <fstream>  
#include <iomanip>
#include <string>
using namespace std;
 
enum class RequestType { PASSED = 1, FAILED, END };

RequestType getRequest();

int main()
{
   ifstream inFile( "grades.txt", ios::in );

   if ( !inFile ) 
   {
      cout << "File could not be opened" << endl;
      exit( 1 );
   }

   RequestType request; // request type: passing or failing grade
   string id;   // student's id
   string name; // student's name
   int grade;   // student's grade

   // get user's request (e.g., passing or failing grade)
   request = getRequest();

   while( request != RequestType::END )
   {
      switch( request )
      {
      case RequestType::PASSED:
         cout << "\nStudents with passing grades:\n";
         while( inFile >> id >> name >> grade )
            if( grade >= 60 )
               cout << left << setw( 9 ) << id << setw( 8 ) << name
                   << right << setw( 5 ) << grade << endl;
         break;
      case RequestType::FAILED:
         cout << "\nStudents with failing grades:\n";
         while( inFile >> id >> name >> grade )
            if( grade < 60 )
               cout << left << setw( 9 ) << id << setw( 8 ) << name
                   << right << setw( 5 ) << grade << endl;
         break;
      }
      
      cout << endl;
      inFile.clear();        // reset eof for next input          
      inFile.seekg( 0 );      // reposition to beginning of file
      request = getRequest(); // get additional request from user
   }

   cout << "\nEnd of run.\n\n";
}

// obtain request from user
RequestType getRequest()
{
   RequestType request;

   cout << "Enter request" << endl
      << "1 - List students with passing grades" << endl
      << "2 - List students with failing grades" << endl
      << "3 - End of run";

   int temp;
   do
   {
      cout << "\n? ";
      cin >> temp;
      request = static_cast< RequestType >( temp );
   } while( request < RequestType::PASSED && request > RequestType::END );

   return request;
}