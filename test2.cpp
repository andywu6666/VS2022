#include <iostream>
#include <string>
using namespace std;

int main()
{
   string s1( "merry" ); // string object s1 initialized to "merry"
   string s2( " christmas" ); // s2 initialized to " christmas"
   string s3; // s3 is empty
   string s4; // s4 is empty

   cout << "Enter a string: ";
   cin >> s4; // read a string into s4

   // display each string's contents
   cout << "\ns1 is \"" << s1 << '"' << "; s2 is " << '"' << s2 << '"'
      << "; s3 is " << '"' << s3 << "\"; s4 is " << '"' << s4 << '"' << "\n\n";

   // determine the length of each string
   cout << "s1 length " << s1.length() << "; s2 length " << s2.length()
      << "; s3 length " << s3.length() << "; s4 length " << s4.length();

   // test equality and relational operators
   cout << "\n\nThe results of comparing s2 and s1:"
      << "\ns2 == s1 yields " << ( s2 == s1 ? "true" : "false" )
      << "\ns2 != s1 yields " << ( s2 != s1 ? "true" : "false" )
      << "\ns2 >  s1 yields " << ( s2 > s1 ? "true" : "false" ) 
      << "\ns2 <  s1 yields " << ( s2 < s1 ? "true" : "false" )
      << "\ns2 >= s1 yields " << ( s2 >= s1 ? "true" : "false" )
      << "\ns2 <= s1 yields " << ( s2 <= s1 ? "true" : "false" );
      
   // test string member function empty 
   cout << "\n\nTesting s3.empty():\n";

   if ( s3.empty() )
   {
      cout << "s3 is empty; assigning s1 to s3;\n";
      s3 = s1; // assign s1 to s3
      cout << "s3 is \"" << s3 << '"';
   }

   // test string concatenation operator
   cout << "\n\nAfter s1 += s2, ";
   s1 += s2; // concatenate s2 to the end of s1
   cout << "s1 is " << '"' << s1 << "\"";

   // test string concatenation operator with string literal
   cout << "\n\ns1 += \" to you\" yields\n";
   s1 += " to you";  
   cout << "s1 is \"" << s1 << "\"\n\n";

   // making a copy of a string
   string s5( s1 ); // creates s5 as a copy of s1
   cout << "s5 is " << '"' << s5 << '"';

   // test the subscript operator to create lvalues
   s1[ 0 ] = 'M'; // replaces m with M  
   s1[ 6 ] = 'C'; // replaces c with C
//   cout << "\n\ns1 after s1[0] = 'M' and s1[6] = 'C' is: " << s1;
   cout << "\n\ns1 after s1[ 0 ] = " << "'" << 'M' << '\''
      << " and s1[ 6 ] = " << '\'' << 'C' << "'" << " is: " << '"' << s1 << '"' << "\n\n";
}