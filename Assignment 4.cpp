#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include "SourceLine.h" // SourceLine class definition

// reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< SourceLine > &program );

// stores all non-keyword strings in the vector identifiers into a text file
void save( vector< Identifier > &identifiers );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< Identifier > &identifiers, size_t pos );

int main()
{
   vector< SourceLine > program;

   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );

   vector< Identifier > identifiers;

   for( size_t i = 0; i < program.size(); i++ )
   {
      program[ i ].delComments(); // deletes the comment beginning with "//" in program[ i ]
      program[ i ].delStrConst(); // deletes all string constants in program[ i ]
      program[ i ].delCharConst(); // deletes all character constants in program[ i ]
      program[ i ].extractIdentifiers( identifiers );
      // extracts all identifiers from program[ i ], and put them into the vector identifiers
   }

   save( identifiers );

   system( "pause" );
}

void load( vector< SourceLine > &program )
{
   char filename[ 12 ];
   cout << "Input the name of a cpp file: ";
   cin >> filename;
   ifstream inFile( filename, ios::in );

   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   SourceLine sourceLine;
   char source[ 200 ];
   while( inFile.getline( source, sizeof( source ), '\n' ) )
      if( strlen( source ) > 0 )
      {
         sourceLine = source;
         program.push_back( sourceLine );
      }

   inFile.close();
}

void save( vector< Identifier > &identifiers )
{
   char filename[ 20 ];
   cout << "Input the name of a txt file: ";
   cin >> filename;
   ofstream outFile( filename, ios::out );

   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( size_t i = 0; i < identifiers.size(); i++ )
      if( !identifiers[ i ].keyword() && !duplicate( identifiers, i ) )
         outFile << identifiers[ i ] << endl;

   outFile.close();
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< Identifier > &identifiers, size_t pos )
{
   for( size_t i = 0; i < pos; ++i )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}