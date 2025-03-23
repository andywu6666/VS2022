#include <iostream>
using namespace std;

int main()
{
   char s1[ 20 ];
   char s2[] = "happy new year";

   cout << "Enter the string \"merry christmas\": ";
   cin >> s1; // reads "merry"

   cout << "s1 is: " << '\'' << s1 << '\'' << "\ns2 is: " << '"' << s2 << '"';

   cout << "\n\ns1 with spaces between characters is:\n";
   for ( int i = 0; s1[ i ] != '\0'; i++ )
      cout << s1[ i ] << ' ';
   cout << '\n';

   cin >> s1; // reads "christmas"
   cout << "\ns1 is: " << '\'' << s1 << '\'' << '\n';
}