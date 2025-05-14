// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition


extern bool leapYear( int year );
extern Date computeCurrentDate();
extern int inputAnInteger(int begin, int end); // input an integer in the range [ begin, end ]

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
                                  AvailRoomDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomDatabase( theAvailableRoomsDatabase )
{
}

void MakeReservation::execute()
{
   Date currentDate = computeCurrentDate();

   /*cout << "Current Date: " << currentDate.getYear() << "-"
       << setw(2) << setfill('0') << currentDate.getMonth() << "-"
       << setw(2) << setfill('0') << currentDate.getDay() << endl;*/

   Date availableMonths[ 7 ]; //6 is enough , adding 1 for assurance

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

   // Check if any rooms are available for the period before displaying the table
   bool anyPossiblyAvailableRooms = false;
   for (int roomType = 1; roomType <= 5; roomType++)
   {
       if (availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate) > 0)
       {
           anyPossiblyAvailableRooms = true;
           break;
       }
   }
   if (!anyPossiblyAvailableRooms)
   {
       cout << "\nThere are no rooms available!" << endl;
       return;
    }



   availableRoomDatabase.displayAvailableRooms( checkInDate, checkOutDate );

   const char roomTypeName[ 6 ][ 20 ] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
                                              "Superior Suite", "Deluxe Suite" };

   vector<int> availType;
   vector<int> numAvailType;

   showAvailType:
   cout << "\nSelect Room Type:\n";
   for (int i = 1; i <= 5; i++)
   {
       int roomsForThisType = availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate);
       if (roomsForThisType > 0)
       {
           cout << i << ". " << roomTypeName[i] << "\n";
           availType.push_back(i);
           numAvailType.push_back(roomsForThisType);

       }
   }

   if (availType.size() == 0)
   {
       cout << "\nThere are no rooms available for the selected period!" << endl;
       return;
   }

   cout << 6 << ". Give up\n";
   cout << "? ";

   int choice = 0;
   int roomType = 0;
   int maxRoomsForChosenType = 0;


   while (true)
   {
       
        choice = inputAnInteger(1, 6);
       if (choice == -1) {
           cout << "Invalid input. Please enter a number: ";
           goto showAvailType;
       }

       if (choice == 6)
       {
           cout << "\nReservation process canceled." << endl;
           return;
       }

       // User choice is 1-5, representing an attempt to select an actual room type
       roomType = choice;
       bool isValidChoice = false;
       for (size_t k = 0; k < availType.size(); ++k) {
           if (availType[k] == roomType) {
               maxRoomsForChosenType = numAvailType[k];
               isValidChoice = true;
               break;
           }
       }

       if (isValidChoice) {
           break; // Valid room type selected
       }
       else {
           goto showAvailType;
           
       }
   }

    int numRooms = 0;

   cout << "\nNumber of rooms ( " << maxRoomsForChosenType << " rooms available ): ";
   numRooms = inputAnInteger(1, maxRoomsForChosenType);
   while (numRooms == -1 || numRooms == 0 || numRooms > maxRoomsForChosenType)
   {
       cout << "Invalid input. Please enter a number between 1 and " << maxRoomsForChosenType << ": ";
       numRooms = inputAnInteger(1, maxRoomsForChosenType);
   }

   // Check availability again (though somewhat redundant if maxRoomsForChosenType is accurate)
   int minRoomsAvailable = availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate);

   if (numRooms <= minRoomsAvailable)
   {
       availableRoomDatabase.decreaseAvailRooms(roomType, numRooms, checkInDate, checkOutDate);

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

       newReservation.setReservation(roomType, numRooms, checkInDate, checkOutDate, idNumber, name, mobile);

       cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
       newReservation.displayReservation();

       reservationDatabase.pushBack(newReservation);

       cout << "\nReservation successfully!" << endl;

   }
   else // This case should ideally not be reached if selection logic is correct
   {
       cout << "\nSorry! The number of rooms you requested (" << numRooms
           << ") is not available for the selected period for " << roomTypeName[roomType] << ".\n"
           << "Maximum available is " << minRoomsAvailable << ".\n";
   }
}

void MakeReservation::computeAvailableMonths( Date currentDate, Date availableMonths[] )
{
    availableMonths[0].setYear(currentDate.getYear());
    availableMonths[0].setMonth(currentDate.getMonth());
    availableMonths[0].setDay(1);

    for (int i = 1; i < 6; ++i)
    {
        int month = availableMonths[i - 1].getMonth() + 1;
        int year = availableMonths[i - 1].getYear();

        if (month > 12)
        {
            month = 1;
            year++;
        }
        availableMonths[i].setYear(year);
        availableMonths[i].setMonth(month);
        availableMonths[i].setDay(1);
    }


}

void MakeReservation::inputCheckInDates( Date &checkInDate, Date currentDate,
     Date availableMonths[], int &checkInYMCode, int &firstDay, int &lastDay )
{
    showCheckInOption:
    cout << "\nPlease Input Check In Date\n"; // Adjusted prompt
    cout << "\nMonth:\n"; // Adjusted prompt
    for (int i = 0; i < 6; ++i)
    {
        cout << i + 1 << ". " << availableMonths[i].getYear() << "-"
            << setw(2) << setfill('0') << availableMonths[i].getMonth() << endl;
    }

    cout << "? "; // Adjusted prompt
    int monthChoice = inputAnInteger(1, 6);
    while (monthChoice == -1) {
        goto showCheckInOption;
    }
    checkInYMCode = monthChoice - 1;

    int chosenYear = availableMonths[checkInYMCode].getYear();
    int chosenMonth = availableMonths[checkInYMCode].getMonth();

    if (chosenYear == currentDate.getYear() && chosenMonth == currentDate.getMonth())
    {
        firstDay = currentDate.getDay();
    }
    else
    {
        firstDay = 1;
    }

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (leapYear(chosenYear))
    {
        daysInMonth[2] = 29;
    }
        lastDay = daysInMonth[chosenMonth];
    
        if (checkInYMCode == 5)
            if (lastDay == 31)
                lastDay--;

    inputDays:
    cout << "\nDay (" << firstDay << " ~ " << lastDay << "): "; // Adjusted prompt
    int chosenDay = inputAnInteger(firstDay, lastDay);
    while (chosenDay == -1) {
        goto inputDays;
    }

    checkInDate.setYear(chosenYear);
    checkInDate.setMonth(chosenMonth);
    checkInDate.setDay(chosenDay);


}

void MakeReservation::inputCheckOutDates( Date &checkOutDate, Date checkInDate,
     Date availableMonths[], int checkInYMCode, int firstDay, int lastDay )
{
    int chosenYear = 0, chosenMonth = 0;
    int firstDayForCheckout = 0, lastDayForCheckout = 0;
    bool validMonthSelected = false; // Renamed from validMonthSelectedLoop for clarity

    while (!validMonthSelected) {
        cout << "\nPlease Input Check Out Date\n"; // Adjusted prompt
        cout << "\nMonth:\n"; // Adjusted prompt
        int displayOptionNumber = 1;
        for (int i = checkInYMCode; i < 6; ++i)
        {
            cout << displayOptionNumber++ << ". " << availableMonths[i].getYear() << "-"
                << setw(2) << setfill('0') << availableMonths[i].getMonth() << endl;
        }

        cout << "? "; // Adjusted prompt
        int monthChoiceRelative = inputAnInteger(1, 6 - checkInYMCode);
        while (monthChoiceRelative == -1) {
            cout << "Invalid choice. Please enter a number between 1 and " << 6 - checkInYMCode << ": ";
            monthChoiceRelative = inputAnInteger(1, 6 - checkInYMCode);
        }
        int checkoutYMCode = checkInYMCode + monthChoiceRelative - 1;

        chosenYear = availableMonths[checkoutYMCode].getYear();
        chosenMonth = availableMonths[checkoutYMCode].getMonth();

        int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (leapYear(chosenYear))
        {
            daysInMonth[2] = 29;
        }
        lastDayForCheckout = daysInMonth[chosenMonth];


        if (chosenYear == checkInDate.getYear() && chosenMonth == checkInDate.getMonth())
        {
            if (checkInDate.getDay() == lastDayForCheckout) {
                cout << "Check-in is on the last day of this month (" << checkInDate.getYear() << "-" << checkInDate.getMonth() << "-" << checkInDate.getDay()
                    << "). Please select a later month for check-out." << endl;
                // validMonthSelected remains false, loop will continue
                continue; // Restart month selection
            }
            firstDayForCheckout = checkInDate.getDay() + 1;
        }
        else
        {
            firstDayForCheckout = 1;
        }

        if (firstDayForCheckout > lastDayForCheckout) {

            cout << "No valid checkout days in the selected month (" << chosenYear << "-" << chosenMonth
                << ") after your check-in date. Please select a later month." << endl;
            continue;
        }
        validMonthSelected = true;
    }

    cout << "\nDay (" << firstDayForCheckout << " ~ " << lastDayForCheckout << "): "; // Adjusted prompt
    int chosenDay;
    do {
        chosenDay = inputAnInteger(firstDayForCheckout, lastDayForCheckout);
        if (chosenDay == -1) {
            cout << "Invalid day. Please enter a day between " << firstDayForCheckout << " and " << lastDayForCheckout << ": ";
            continue;
        }
        checkOutDate.setYear(chosenYear);
        checkOutDate.setMonth(chosenMonth);
        checkOutDate.setDay(chosenDay);
        if (checkOutDate <= checkInDate) {
            cout << "Check-out date must be after check-in date. Please re-enter." << endl;
            cout << "\nDay (" << firstDayForCheckout << " ~ " << lastDayForCheckout << "): ";
            chosenDay = -1;
        }
    } while (chosenDay == -1 || checkOutDate <= checkInDate);


}