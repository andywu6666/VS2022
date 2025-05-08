// AvailRoomDatabase.cpp
// Member-function definitions for class AvailRoomDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

extern bool leapYear( int year );
extern Date computeCurrentDate();
//char availFileName[] = "Available Rooms 2024-11-6.dat";
//char availFileName[] = "Available Rooms 2025-2-4.dat";
char availFileName[] = "Available Rooms 2025-5-5.dat";
//char availFileName[] = "Available Rooms blank.dat";

AvailRoomDatabase::AvailRoomDatabase()
{
   loadAvailableRooms();

   if( availRooms.size() == 0 )
      initAvailRooms(); // create available rooms information for 6 months
   else
      appendAvailRooms(); // append new available rooms information
}

AvailRoomDatabase::~AvailRoomDatabase()
{
   saveAvailableRooms();
}

void AvailRoomDatabase::loadAvailableRooms()
{



}

void AvailRoomDatabase::initAvailRooms()
{



}

void AvailRoomDatabase::appendAvailRooms()
{



}

void AvailRoomDatabase::displayAvailableRooms( Date checkInDate, Date checkOutDate )
{
   cout << "\nThe number of available rooms of each room type:\n\n";
   cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

   vector< AvailRoom >::iterator checkInIterator;
   vector< AvailRoom >::iterator checkOutIterator;

   findIterators( checkInDate, checkOutDate, checkInIterator, checkOutIterator );

   for( vector< AvailRoom >::iterator it = checkInIterator; it < checkOutIterator; ++it )
      cout << it->getDate().getYear() << "-"
           << setw( 2 ) << setfill( '0' ) << it->getDate().getMonth() << "-"
           << setw( 2 ) << it->getDate().getDay()
           << setw( 16 ) << setfill( ' ' ) << it->getAvailRoom( 1 )
           << setw( 14 ) << it->getAvailRoom( 2 )
           << setw( 19 ) << it->getAvailRoom( 3 )
           << setw( 17 ) << it->getAvailRoom( 4 )
           << setw( 15 ) << it->getAvailRoom( 5 ) << "\n";
}

int AvailRoomDatabase::compMinNumRooms( int roomType,
                       const Date &checkInDate, const Date &checkOutDate )
{



}

void AvailRoomDatabase::decreaseAvailRooms( int roomType, int numRooms,
                        const Date &checkInDate, const Date &checkOutDate )
{



}

void AvailRoomDatabase::saveAvailableRooms()
{



}

void AvailRoomDatabase::findIterators( const Date &checkInDate, const Date &checkOutDate,
                                       vector< AvailRoom >::iterator &checkInIterator,
                                       vector< AvailRoom >::iterator &checkOutIterator )
{



}