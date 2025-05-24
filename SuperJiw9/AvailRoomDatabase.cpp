// AvailRoomDatabase.cpp
// Member-function definitions for class AvailRoomDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition
#include "AvailRoom.h"         // Added for AvailRoom usage
#include "Date.h"              // Added for Date usage

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
    availRooms.clear();
    ifstream inFile(availFileName, ios::in | ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }
    AvailRoom room;
    while (inFile.read(reinterpret_cast<char*>(&room), sizeof(AvailRoom)))
    {
        availRooms.push_back(room);
    }

    inFile.close();
}

void AvailRoomDatabase::initAvailRooms()
{
    Date currentDate = computeCurrentDate();
    Date tempDate = currentDate;
    AvailRoom currentAvailRoom;

    for (int i = 0;i < 180; i++)
    {
        currentAvailRoom.setDate( tempDate.getYear(), tempDate.getMonth(), tempDate.getDay());
        currentAvailRoom.initAvailRooms();
        availRooms.push_back(currentAvailRoom);

        int day = tempDate.getDay() + 1;
        int month = tempDate.getMonth();
        int year = tempDate.getYear();

        int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (leapYear(year))
        {
            daysInMonth[2] = 29;
        }

        if (day > daysInMonth[month])
        {
            day = 1;
            month++;
            if (month > 12) {
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
    if (availRooms.empty()) 
    {
        initAvailRooms();
        return;
    }

    Date dateToAppend = availRooms.back().getDate();
    int year = dateToAppend.getYear();
    int month = dateToAppend.getMonth();
    int day = dateToAppend.getDay();

    int dayMonth1[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(year))
    {
        dayMonth1[2] = 29;
    }
    day++;
    if (day > dayMonth1[month])
    {
        day = 1;
        month++;
    }
    if (month > 12)
    {
        month = 1;
        year++;
    }
    dateToAppend.setYear(year);
    dateToAppend.setMonth(month);
    dateToAppend.setDay(day);

    Date sixMonthLater = computeCurrentDate();
    int sYear = sixMonthLater.getYear();
    int sMonth = sixMonthLater.getMonth() + 6;

    int dayMonth2[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (leapYear(sYear))
    {
        dayMonth2[2] = 29;
    }
    if (sMonth > 12)
    {
        sMonth = 1;
        sYear++;
    }

    sixMonthLater.setYear(sYear);
    sixMonthLater.setMonth(sMonth);

    AvailRoom newEntry;
    while (dateToAppend <= sixMonthLater)
    {
        newEntry.setDate(dateToAppend.getYear(), dateToAppend.getMonth(), dateToAppend.getDay());
        newEntry.initAvailRooms();
        availRooms.push_back(newEntry);

        if (leapYear(year))
        {
            dayMonth1[2] = 29;
        }
        day++;
        if (day > dayMonth1[month])
        {
            day = 1;
            month++;
        }
        if (month > 12)
        {
            month = 1;
            year++;
        }
        dateToAppend.setYear(year);
        dateToAppend.setMonth(month);
        dateToAppend.setDay(day);
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
    vector<AvailRoom>::iterator checkInIter;
    vector<AvailRoom>::iterator checkOutIter;

    findIterators(checkInDate, checkOutDate, checkInIter, checkOutIter);

    int minNumRooms = -1;
    for (vector<AvailRoom>::iterator it = checkInIter; it < checkOutIter; it++)
    {
        if (minNumRooms == -1 || it->getAvailRoom(roomType) < minNumRooms)
        minNumRooms = it->getAvailRoom(roomType);
    }

    return (minNumRooms == -1) ? 0 : minNumRooms;
}

void AvailRoomDatabase::decreaseAvailRooms( int roomType, int numRooms,
                        const Date &checkInDate, const Date &checkOutDate )
{

    vector<AvailRoom>::iterator checkInIter;
    vector<AvailRoom>::iterator checkOutIter;

    findIterators(checkInDate, checkOutDate, checkInIter, checkOutIter);

    for (vector<AvailRoom>::iterator it = checkInIter; it != checkOutIter; it++)
    {
        it->decreaseAvailRooms(roomType, numRooms);
    }


}

void AvailRoomDatabase::saveAvailableRooms()
{
    ofstream outFile(availFileName, ios::out | ios::binary);

    if (!outFile)
    {
        cout << "File could not be saved!" << endl;
        system("pause");
        exit(1);
    }

    for (size_t i = 0; i < availRooms.size(); i++)
        outFile.write(reinterpret_cast<const char*>(&availRooms[i]), sizeof(AvailRoom));

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
            checkInIterator = it;

        if (it->getDate() == checkOutDate)
            checkOutIterator = it;
    }

}