// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition

extern bool leapYear( int year );
extern Date computeCurrentDate();

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
                                  AvailRoomDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomDatabase( theAvailableRoomsDatabase )
{
}

void MakeReservation::execute()
{
   Date currentDate = computeCurrentDate();

   Date availableMonths[ 7 ];

   computeAvailableMonths( currentDate, availableMonths );

   int checkInYMCode;
   int firstDay;
   int lastDay;

   Date checkInDate;
   Date checkOutDate;

   inputCheckInDates( checkInDate, currentDate, availableMonths, checkInYMCode, firstDay, lastDay );
   inputCheckOutDates( checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay );

   cout << "\nCheck in date: " << checkInDate.getYear() << '-'
        << setw( 2 ) << setfill( '0' ) << checkInDate.getMonth() << '-'
        << setw( 2 ) << checkInDate.getDay() << endl;

   cout << "Check out date: " << checkOutDate.getYear() << '-'
        << setw( 2 ) << checkOutDate.getMonth() << '-'
        << setw( 2 ) << checkOutDate.getDay() << endl;





   availableRoomDatabase.displayAvailableRooms( checkInDate, checkOutDate );

   const char roomTypeName[ 6 ][ 20 ] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
                                              "Superior Suite", "Deluxe Suite" };





   availableRoomDatabase.decreaseAvailRooms( roomType, numRooms, checkInDate, checkOutDate );

   cout << "\nID Number: ";
   string idNumber;
   cin >> idNumber;

   cout << "\nName: ";
   string name;
   cin >> name;

   cout << "\nMobile Phone: ";
   string mobile;
   cin >> mobile;
   cin.ignore();

   newReservation.setReservation( roomType, numRooms, checkInDate, checkOutDate, idNumber, name, mobile );

   cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
   newReservation.displayReservation();

   reservationDatabase.pushBack( newReservation );

   cout << "\nReservation successfully!" << endl;
}

void MakeReservation::computeAvailableMonths( Date currentDate, Date availableMonths[] )
{



}

void MakeReservation::inputCheckInDates( Date &checkInDate, Date currentDate,
     Date availableMonths[], int &checkInYMCode, int &firstDay, int &lastDay )
{



}

void MakeReservation::inputCheckOutDates( Date &checkOutDate, Date checkInDate,
     Date availableMonths[], int checkInYMCode, int firstDay, int lastDay )
{



}