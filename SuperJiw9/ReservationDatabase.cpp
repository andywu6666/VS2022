// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

ReservationDatabase::ReservationDatabase()
{
	loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
	saveToReservationFile();
}

void ReservationDatabase::loadReservations()
{
	ifstream inFile("Reservations.dat", ios::in | ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened (this is normal for first run)" << endl;
		return;
	}
	Date currentDate = computeCurrentDate();
	Reservation reservation;

	while (inFile.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation) ) ){
		if (reservation.getCheckInDate() >= currentDate)
			pushBack(reservation);
	}
	inFile.close();
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

int ReservationDatabase::numReservations( string idNumber )
{
	int count = 0;
	vector<Reservation>::iterator it;
	for (it = reservations.begin(); it != reservations.end(); it++)
	{
		if (it->equalID(idNumber, it->getIDNumber()))
			count++;

	}
	return count;


}

void ReservationDatabase::displayReservations( string idNumber )
{
	cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";

   for( vector< Reservation >::iterator it = reservations.begin(); it < reservations.end(); it++ )
      if( it->equalID( idNumber, it->getIDNumber() ) )
         it->displayReservation();
}

void ReservationDatabase::saveToReservationFile()
{
	ofstream outFile("Reservations.dat", ios::out | ios::binary);

	if (!outFile)
	{
		cout << "File could not be opened!";
		system("pause");
		exit(1);
	}
	vector<Reservation>::iterator it;
		for (it = reservations.begin(); it != reservations.end(); it++)
		{
			outFile.write(reinterpret_cast<const char*>(&(*it)), sizeof(Reservation));
		}
		outFile.close();
	


}