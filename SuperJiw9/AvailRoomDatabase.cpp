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
    ifstream inFile("Available Rooms 2025-5-5.dat", ios::in | ios::binary);

    if (!inFile)
    {
        cout << "File could not be opened " << endl;
        return;
    }
    AvailRoom room;
    
    while (inFile.read(reinterpret_cast<char*>(&room), sizeof(AvailRoom))) {
       
            availRooms.push_back(room);
    }
    inFile.close();


}

void AvailRoomDatabase::initAvailRooms()
{
    Date currentDate = computeCurrentDate();
    Date tempDate = currentDate;
    AvailRoom currentAvailRoom;

    // Create available rooms information for 180 days (approximately 6 months)
    for (int i = 0; i < 180; ++i)
    {
        currentAvailRoom.setDate(tempDate.getYear(), tempDate.getMonth(), tempDate.getDay());
        currentAvailRoom.initAvailRooms(); // Initializes availRooms[i] to totalNumRooms[i]
        availRooms.push_back(currentAvailRoom);

        // Increment date
        int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (leapYear(tempDate.getYear()))
        {
            daysInMonth[2] = 29;
        }

        int day = tempDate.getDay() + 1;
        int month = tempDate.getMonth();
        int year = tempDate.getYear();

        if (day > daysInMonth[month])
        {
            day = 1;
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }
        tempDate.setDay(day);
        tempDate.setMonth(month);
        tempDate.setYear(year);
    }


}

void AvailRoomDatabase::appendAvailRooms()
{
    if (availRooms.empty()) // Should not happen if initAvailRooms was called correctly
    {
        initAvailRooms();
        return;
    }

    Date lastDateInVector = availRooms.back().getDate();
    Date currentDate = computeCurrentDate();
    Date sixMonthsLater = currentDate;

    // Calculate date six months from current date
    int month = sixMonthsLater.getMonth() + 6;
    int year = sixMonthsLater.getYear();
    while (month > 12) {
        month -= 12;
        year++;
    }
    sixMonthsLater.setMonth(month);
    sixMonthsLater.setYear(year);
    // Adjust day if it exceeds days in new month (e.g. March 31 + 1 month = April 30)
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (leapYear(sixMonthsLater.getYear())) {
        daysInMonth[2] = 29;
    }
    if (sixMonthsLater.getDay() > daysInMonth[sixMonthsLater.getMonth()]) {
        sixMonthsLater.setDay(daysInMonth[sixMonthsLater.getMonth()]);
    }


    Date dateToAppend = lastDateInVector;
    // Increment lastDateInVector by one day to start appending from the next day
    int daysInMonthLast[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (leapYear(dateToAppend.getYear())) {
        daysInMonthLast[2] = 29;
    }
    int day = dateToAppend.getDay() + 1;
    int m = dateToAppend.getMonth();
    int y = dateToAppend.getYear();
    if (day > daysInMonthLast[m]) {
        day = 1;
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }
    dateToAppend.setDay(day);
    dateToAppend.setMonth(m);
    dateToAppend.setYear(y);


    AvailRoom newAvailRoom;
    while (dateToAppend <= sixMonthsLater)
    {
        newAvailRoom.setDate(dateToAppend.getYear(), dateToAppend.getMonth(), dateToAppend.getDay());
        newAvailRoom.initAvailRooms();
        availRooms.push_back(newAvailRoom);

        // Increment dateToAppend
        int daysInMonthCurrent[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (leapYear(dateToAppend.getYear()))
        {
            daysInMonthCurrent[2] = 29;
        }
        int d = dateToAppend.getDay() + 1;
        int mo = dateToAppend.getMonth();
        int ye = dateToAppend.getYear();
        if (d > daysInMonthCurrent[mo])
        {
            d = 1;
            mo++;
            if (mo > 12)
            {
                mo = 1;
                ye++;
            }
        }
        dateToAppend.setDay(d);
        dateToAppend.setMonth(mo);
        dateToAppend.setYear(ye);
    }


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
    if (roomType < 1 || roomType > 5) // Assuming room types are 1-5
    {
        return 0; // Invalid room type
    }

    vector< AvailRoom >::iterator checkInIter;
    vector< AvailRoom >::iterator checkOutIter;

    findIterators(checkInDate, checkOutDate, checkInIter, checkOutIter);

    if (checkInIter == availRooms.end() || checkOutIter == availRooms.end() || checkInIter == checkOutIter)
    {
        return 0; // Dates not found or invalid range
    }

    int minNumRooms = -1; // Initialize with a value that will be overwritten or indicates error

    for (vector< AvailRoom >::iterator it = checkInIter; it < checkOutIter; ++it)
    {
        if (minNumRooms == -1 || it->getAvailRoom(roomType) < minNumRooms)
        {
            minNumRooms = it->getAvailRoom(roomType);
        }
    }
    return (minNumRooms == -1) ? 0 : minNumRooms; // return 0 if no rooms found in range


}

void AvailRoomDatabase::decreaseAvailRooms( int roomType, int numRooms,
                        const Date &checkInDate, const Date &checkOutDate )
{
   

    vector< AvailRoom >::iterator checkInIter;
    vector< AvailRoom >::iterator checkOutIter;

    findIterators(checkInDate, checkOutDate, checkInIter, checkOutIter);

    if (checkInIter == availRooms.end() || checkOutIter == availRooms.end() || checkInIter == checkOutIter)
    {
        cout << "Dates not found or invalid range" << endl;
        return; // Dates not found or invalid range
    }

    for (vector< AvailRoom >::iterator it = checkInIter; it < checkOutIter; ++it)
    {
        it->decreaseAvailRooms(roomType, numRooms);
    }


}

void AvailRoomDatabase::saveAvailableRooms()
{
    ofstream outFile("Available Rooms blank.dat", ios::out | ios::binary);

    if (!outFile)
    {
        cout << "File could not be opened!";
        system("pause");
        exit(1);
    }
    
    for (size_t i = 0; i < availRooms.size(); i++)
    {
        outFile.write(reinterpret_cast<const char*>(&availRooms[i] ), sizeof(AvailRoom));
    }
    outFile.close();


}

void AvailRoomDatabase::findIterators( const Date &checkInDate, const Date &checkOutDate,
                                       vector< AvailRoom >::iterator &checkInIterator,
                                       vector< AvailRoom >::iterator &checkOutIterator )
{
    checkInIterator = availRooms.end();
    checkOutIterator = availRooms.end();

    for (vector< AvailRoom > ::iterator it = availRooms.begin(); it != availRooms.end(); it++)
    {
        if (it->getDate() == checkInDate)
        {
            checkInIterator = it;
        }
        if (it->getDate() == checkOutDate)
        {
            checkOutIterator = it;
        }
    }


}