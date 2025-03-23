// This program reads a binary file,
// updates grades previously written to the file,
// adds new grades in the file,
// and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

struct StudentData
{
   char studentId[ 8 ];
   char lastName[ 12 ];
   char firstName[ 12 ];
   int grade;
};

enum class Choices{ PRINT = 1, UPDATE, NEW, DELETE, END };

// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile( fstream &readFromFile );

// update grade in record
void updateRecord( fstream &updateFile );

// add a new grade in record
void newRecord( fstream &insertInFile );

// delete an existing record
void deleteRecord( fstream &deleteFromFile );

// obtain student ID from user
void getID( const char * const prompt, char studentId[] );

int main()
{
   // open file for reading and writing
   fstream inOutGrade( "grades.dat", ios::in | ios::out | ios::binary );

   // exit program if fstream cannot open file
   if( !inOutGrade )
   {
      cout << "File could not be opened." << endl;
      exit( 1 );
   }

   Choices choice; // store user choice

   // enable user to specify action
   while( ( choice = enterChoice() ) != Choices::END )
   {
      switch( choice )
      {
      case Choices::PRINT:
         createTextFile( inOutGrade ); // create text file from binary file
         break;
      case Choices::UPDATE:
         updateRecord( inOutGrade ); // update grade
         break;
      case Choices::NEW:
         newRecord( inOutGrade ); // add a new grade
         break;
      case Choices::DELETE:
         deleteRecord( inOutGrade ); // delete existing record
         break;
      default:
         cout << "Incorrect choice" << endl;
         break;
      }

      cout << endl;
      inOutGrade.clear(); // set the state of inOutGrade to good
      inOutGrade.seekg( 0 );
   }

   inOutGrade.close();
}

// enable user to input menu choice
Choices enterChoice()
{
   // display available options
   cout << "Enter your choice" << endl
      << "1 - store all students' information into grades.txt for printing\n"
      << "2 - update a student's grade" << endl
      << "3 - add a student's grade" << endl
      << "4 - delete a student's information" << endl
      << "5 - end program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return static_cast< Choices >( menuChoice );
}

// create text file for printing
void createTextFile( fstream &readFromFile )
{
   // create text file
   ofstream outPrintFile( "grades.txt", ios::out );

   // exit program if ofstream cannot create file
   if( !outPrintFile )
   {
      cout << "File could not be created." << endl;
      exit( 1 );
   }

   outPrintFile << "ID       " << left
               << setw( 12 ) << "Last Name"
               << setw( 13 ) << "First Name"
               << setw( 5 ) << "Grade" << endl;

   cout << "\nID       " << left
        << setw( 12 ) << "Last Name"
        << setw( 13 ) << "First Name"
        << setw( 5 ) << "Grade" << endl;

   StudentData student;
   // copy all records from record file into text file
   while( readFromFile.read( reinterpret_cast< char * >( &student ), sizeof( StudentData ) ) )
   {
      // write single record to text file
      if( strcmp( student.studentId, "" ) != 0 ) // skip empty records
      {
         outPrintFile << setw( 9 ) << left << student.studentId
                     << setw( 12 ) << student.lastName
                     << setw( 13 ) << student.firstName
                     << setw( 5 ) << right << student.grade << endl;

         cout << setw( 9 ) << left << student.studentId
              << setw( 12 ) << student.lastName
              << setw( 13 ) << student.firstName
              << setw( 5 ) << right << student.grade << endl;
      }
   }

   outPrintFile.close();
}

// update grade in record
void updateRecord( fstream &updateFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to update", studentId );

   int inClassId = 10 * ( studentId[ 5 ] - '0' ) + ( studentId[ 6 ] - '0' );

   // move file-position pointer to correct record in file
   updateFile.seekg( ( inClassId - 1 ) * sizeof( StudentData ) );

   // read first record from file
   StudentData student;
   updateFile.read( reinterpret_cast< char * >( &student ), sizeof( StudentData ) );

   // update record
   if( strcmp( student.studentId, "" ) != 0 )
      if( student.grade >= 0 )
      {
         cout << endl << setw( 9 ) << left << student.studentId
            << setw( 12 ) << student.lastName
            << setw( 13 ) << student.firstName
            << setw( 5 ) << right << student.grade << endl;

         // request user to specify grade
         cout << "\nEnter grade: ";
         cin >> student.grade;

         cout << endl << setw( 9 ) << left << student.studentId
            << setw( 12 ) << student.lastName
            << setw( 13 ) << student.firstName
            << setw( 5 ) << right << student.grade << endl;

         // move file-position pointer to correct record in file
         updateFile.seekp( ( inClassId - 1 ) * sizeof( StudentData ) );

         // write updated record over old record in file
         updateFile.write( reinterpret_cast< const char * >( &student ), sizeof( StudentData ) );
      }
      else // display error if student's grade does not exist
         cout << "\nStudent ID " << studentId << " has no grade." << endl;
   else
      cout << "\nStudent ID " << studentId << " is empty.\n"; // display error if record does not exist
}

// add a new grade in record
void newRecord( fstream &insertInFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to add", studentId );

   int inClassId = 10 * ( studentId[ 5 ] - '0' ) + ( studentId[ 6 ] - '0' );

   // move file-position pointer to correct record in file
   insertInFile.seekg( ( inClassId - 1 ) * sizeof( StudentData ) );

   // read record from file
   StudentData student;
   insertInFile.read( reinterpret_cast< char * >( &student ), sizeof( StudentData ) );

   // create record, if record does not previously exist
   if( strcmp( student.studentId, "" ) != 0 )
      if( student.grade == -1 )
      {
         // user enters last name, first name and grade
         cout << "\nEnter grade: ";
         cin >> student.grade;

         cout << endl << setw( 9 ) << left << student.studentId
            << setw( 12 ) << student.lastName
            << setw( 13 ) << student.firstName
            << setw( 5 ) << right << student.grade << endl;

         // move file-position pointer to correct record in file
         insertInFile.seekp( ( inClassId - 1 ) * sizeof( StudentData ) );

         // insert record in file                       
         insertInFile.write( reinterpret_cast< const char * >( &student ), sizeof( StudentData ) );
      }
      else // display error if student information already exists
         cout << "\nStudent ID " << studentId << " already contains information." << endl;
   else
      cout << "\nStudent ID " << studentId << " is empty.\n"; // display error if record does not exist
}

// delete an existing record
void deleteRecord( fstream &deleteFromFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to delete", studentId );

   int inClassId = 10 * ( studentId[ 5 ] - '0' ) + ( studentId[ 6 ] - '0' );

   // move file-position pointer to correct record in file
   deleteFromFile.seekg( ( inClassId - 1 ) * sizeof( StudentData ) );

   // read record from file
   StudentData student;
   deleteFromFile.read( reinterpret_cast< char * >( &student ), sizeof( StudentData ) );

   // delete record, if record exists in file
   if( strcmp( student.studentId, "" ) != 0 )
   {
      StudentData blankRecord = { "", "", "", -1 }; // create blank record

      // move file-position pointer to correct record in file
      deleteFromFile.seekp( ( inClassId - 1 ) * sizeof( StudentData ) );

      // replace existing record with blank record
      deleteFromFile.write(
         reinterpret_cast< const char * >( &blankRecord ), sizeof( StudentData ) );

      cout << "\nStudent ID " << studentId << " deleted.\n";
   }
   else
      cout << "\nStudent ID " << studentId << " is empty.\n"; // display error if record does not exist
}

// obtain student ID from user
void getID( const char * const prompt, char studentId[] )
{
   do
   {
      cout << prompt << " ( 1121401 - 1121450 ): ";
      cin >> studentId;
   } while( strcmp( studentId, "1121401" ) == -1 || strcmp( studentId, "1121450" ) == 1 );
}