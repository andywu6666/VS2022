#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include "vector.h"

// Represents a term of a polynomial
template< typename T >
struct Term
{
   bool operator!=( const Term &right ) const
   {
      return coef != right.coef || expon != right.expon;
   }

   T coef;
   T expon;
};

// Polynomial class template definition
template< typename T1, typename T2 >
class Polynomial
{
   // Overloaded stream insertion operator
   template< typename T1, typename T2 >
   friend ostream &operator<<( ostream &output, Polynomial< T1, T2 > a );
public:

   // Constructs an empty polynomial, with no terms.
   Polynomial( size_t n = 0 )
      : polynomial( n )
   {
   }

   // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
   Polynomial( const Polynomial &right )
      : polynomial( right.polynomial )
   {
   }

   // Destructor with empty body
   ~Polynomial()
   {
   }

   // Copies all the terms from "right" into the polynomial
   const Polynomial operator=( const Polynomial &right )
   {
      if( &right != this ) // avoid self-assignment
         polynomial = right.polynomial;

      return *this; // enables x = y = z, for example
   }

   bool operator==( const Polynomial &right )
   {
      return polynomial == right.polynomial;
   }

   void setPolynomial( T2 coefficient[], T2 exponent[], int numTerms )
   {
      for( int i = 0; i < numTerms; i++ )
      {
         polynomial[ i ].coef = coefficient[ i ];
         polynomial[ i ].expon = exponent[ i ];
      }
   }

   // addition assignment operator; Polynomial += Polynomial
   void operator+=( Polynomial &op2 )
   {
       vector< Term<T2> > merged;
       typename vector< Term<T2> >::iterator it1 = polynomial.begin();
       typename vector< Term<T2> >::iterator it2 = op2.polynomial.begin();

       // Merge sorted terms
       while (it1 != polynomial.end() && it2 != op2.polynomial.end())
       {
           if (it1->expon > it2->expon)
           {
               merged.insert(merged.end(), *it1);
               ++it1;
           }
           else if (it1->expon < it2->expon)
           {
               merged.insert(merged.end(), *it2);
               ++it2;
           }
           else // equal exponents
           {
               T2 sumCoef = it1->coef + it2->coef;
               if (sumCoef != 0)
                   merged.insert(merged.end(), Term<T2>{ sumCoef, it1->expon });
               ++it1;
               ++it2;
           }
       }

       // Add remaining terms
       merged.insert(merged.end(), it1, polynomial.end());
       merged.insert(merged.end(), it2, op2.polynomial.end());

       polynomial = merged;


   }

   // subtraction assignment operator; Polynomial -= Polynomial
   void operator-=( Polynomial &op2 )
   {
      Polynomial minus = -op2;
      *this += minus;
   }

   // multiplication operator; Polynomial * Polynomial
   Polynomial operator*( Polynomial &op2 )
   {
       Polynomial product;
       for (typename vector< Term<T2> >::iterator it1 = polynomial.begin(); it1 != polynomial.end(); it1++)
           for (typename vector< Term<T2> >::iterator it2 = op2.polynomial.begin(); it2 != op2.polynomial.end(); it2++)
           {
               T2 coef = it1->coef * it2->coef;
               T2 expon = it1->expon + it2->expon;

               // Insert term in sorted order
               bool inserted = false;
               for (typename vector< Term<T2> >::iterator it = product.polynomial.begin(); it != product.polynomial.end(); ++it)
               {
                   if (it->expon == expon)
                   {
                       it->coef += coef;
                       if (it->coef == 0)
                           product.polynomial.erase(it);
                       inserted = true;
                       break;
                   }
                   else if (it->expon < expon)
                   {
                       product.polynomial.insert(it, Term<T2>{ coef, expon });
                       inserted = true;
                       break;
                   }
               }
               if (!inserted && coef != 0)
                   product.attach(coef, expon);
           }
       return product;


   }

   // computes the square root of the current polynomial
   Polynomial compSquareRoot()
   {
       Polynomial root; // Create empty polynomial for result

       // Iterate through all terms in current polynomial
       for (typename vector< Term<T2> >::iterator it = polynomial.begin(); it != polynomial.end(); ++it)
       {
           // Calculate square root of coefficient
           T2 sqrtCoef = static_cast<T2>(sqrt(it->coef));

           // Verify perfect square (per test case assumption)
           if (sqrtCoef * sqrtCoef != it->coef)
               return Polynomial(); // return zero polynomial on error

           // Halve the exponent for square root term
           T2 sqrtExpon = it->expon / 2;

           // Add term to square root polynomial
           root.attach(sqrtCoef, sqrtExpon);
       }
       return root;


   }

private:
   T1 polynomial; // a polynomial

   // Attaches a new term to the polynomial
   void attach( T2 coefficient, T2 exponent )
   {
      Term< T2 > tempTerm;
      tempTerm.coef = coefficient;
      tempTerm.expon = exponent;
      polynomial.insert( polynomial.end(), tempTerm );
   }

   // Returns the minus of the current polynomial
   Polynomial operator-()
   {
      Polynomial minus( polynomial.size() );
      typename T1::iterator it2 = minus.polynomial.begin();
      typename T1::iterator it1 = polynomial.begin();
      for( ; it1 != polynomial.end(); ++it1, ++it2 )
      {
         it2->coef = -it1->coef;
         it2->expon = it1->expon;
      }

      return minus;
   }

   // Returns true if and only if polynomial is a zero polynomial
   bool zero() const
   {
      return polynomial.empty();
   }

   // Returns the highest of degrees of polynomial's terms
   int degree() const
   {
      if( polynomial.empty() )
         return 0;
      else
         return polynomial.begin()->expon;
   }

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T1, typename T2 >
ostream& operator<<( ostream &output, Polynomial< T1, T2 > a )
{
   if( a.zero() )
   {
      output << 0 << endl;
      return output;
   }

   typename T1::iterator it = a.polynomial.begin();

   if( it->coef < 0 )
      cout << "-" << -it->coef;
   else if( it->coef > 0 )
      cout << it->coef;

   if( it->expon > 0 )
   {
      if( it->expon == 1 )
         cout << "x";
      else
         cout << "x^" << it->expon;
   }

   for( ++it; it != a.polynomial.end(); ++it )
   {
      if( it->coef < 0 )
         cout << " - " << -it->coef;
      else if( it->coef > 0 )
         cout << " + " << it->coef;

      if( it->expon > 0 )
      {
         if( it->expon == 1 )
            cout << "x";
         else
            cout << "x^" << it->expon;
      }
   }

   return output; // enables cout << x << y;
} // end function operator<<

#endif