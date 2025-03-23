#include <iostream>
using namespace std;

int main()
{
   char s1[ 20 ];
   char s2[] = "string literal";

   cin >> s1;

   cout << "aa\"b\'ccc\"dd\"\": " << '\"' << s1 << '"'
      << "\"\"\'\"" << s2 << "\'" << '"' << "\"\"\'\"";
}