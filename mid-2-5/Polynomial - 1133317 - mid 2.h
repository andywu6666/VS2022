#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include <vector>
using std::vector;

#include "list - 1133317 - mid 2-5.h"

// Represents a term of a polynomial
template< typename T >
struct Term
{
   Term( T c = T(), T e = T() )
      : coef( c ),
        expon( e )
   {
   }

   Term( const Term &right )
      : coef( right.coef ),
        expon( right.expon )
   {
   }

   bool operator==( const Term &right ) const
   {
      return coef == right.coef && expon == right.expon;
   }

   bool operator!=( const Term &right ) const
   {
      return !( *this == right );
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
      for( int i = 0; i < numTerms; ++i )
         polynomial.push_back( Term< T2 >( coefficient[ i ], exponent[ i ] ) );
   }

   // addition assignment operator; Polynomial += Polynomial
   void operator+=( Polynomial &op2 )
   {
      Polynomial sum;
      Polynomial addend(polynomial.size());
      
      T2 coefficient;
      T2 exponenet;
      typename T1::iterator it1 = addend.polynomial.begin();
      typename T1::iterator it2 = op2.adder.polynomial.begin();


      for (; it1 != polynomial.end(); it1++, it2++)
      {
         // sum += *it1 + *it2;
          sum.polynomial.coef = it1->coef + it2->coef;
          
          sum.attach(coefficient, exponenet);
      }
      while (it1 != polynomial.end())
      {
          //sum += *it1;


          sum.attach(coefficient, exponenet);
      }
      while (it2 != op2.polynomial.end())
      {
          //sum += *it2;

          sum.attach(coefficient, exponenet);
      }
      while (polynomial.size() > 1 && polynomial.end() - 1 == 0)
      {
          polynomial.erase(polynomial.end() - 1 );
      }


      *this = sum;
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
      typename T1::iterator it2;
      int carry = 0;

      


      while (polynomial.size() > 1 && polynomial.end() - 1 == 0)
      {
          polynomial.erase(polynomial.end() - 1 );
      }

      return product;
   }

   // computes the square root of the current polynomial
   Polynomial compSquareRoot()
   {
      Polynomial monomial( 1 );
      Polynomial squareRoot;
      Polynomial divisor;
      Polynomial buffer;
      Polynomial remainder( *this );


      monomial.attach(sqrt(remainder.polynomial.coef), remainder.polynomial.expon / 2);
      squareRoot.attach(monomial.polynomial.coef, monomial.polynomial.expon);
      divisor.attach(monomial.polynomial.coef, monomial.polynomial.expon);

      buffer.attach( remainder.polynomial.coef * divisor.polynomial.coef, remainder.polynomial.expon + divisor.polynomial.expon);
      remainder.polynomial -= buffer.polynomial;

      for (int i = 0; i < polynomial.size();i ++) {
          divisor.polynomial[divisor.polynomial.size() - 1].coef *= 2;
          monomial.attach(remainder / divisor);
          squareRoot.attach(monomial);
          buffer.attach(remainder.polynomial.coef * divisor.polynomial.coef, remainder.polynomial.expon + divisor.polynomial.expon);
          remainder.polynomial -= buffer.polynomial;


      }

      while( !remainder.zero() )
      {





      }

      return squareRoot;
   }

private:
   T1 polynomial; // a polynomial

   // Attaches a new term to the polynomial
   void attach( T2 coefficient, T2 exponent )
   {
      Term< T2 > tempTerm( coefficient, exponent );
      polynomial.push_back( tempTerm );
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