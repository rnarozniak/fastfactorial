//////////////////////////////////////////////////////////////////////////

#ifndef _PRIMESIEVE_H_
#define _PRIMESIEVE_H_

//////////////////////////////////////////////////////////////////////////

#ifndef _UTILITYFUNCTIONS_H_
#include "utilityfunctions.h"
#endif

//////////////////////////////////////////////////////////////////////////



/** Prime number sieve -- collection of prime numbers
* 
*   @author Roman Pasechnik
*   @since  Dec 05, 2009
*   @since  Jan 08, 2009
*/
class PrimeSieve
{
//////////////////////////////////////////////////////////////////////////

public:

//////////////////////////////////////////////////////////////////////////


    /** Constructor.
    Constructs a prime sieve for the integer range [1,n]. */
    PrimeSieve( int _i );


//////////////////////////////////////////////////////////////////////////


    /** Get prime by index */
    int GetPrime( int _index ) const { return m_Primes[_index]; }


    /** Returns prime index in collection */
    int GetPrimeIndex( int _number, int _lowerBound, int _upperBound ) const;


    /** Get number of prime numbers in sieve */
    const int GetNumberOfPrimes() const { return m_NumberOfPrimes; }


    /** Gives the product of primes in range [_low, _high] */
    mpz_class Primorial( int _low, int _high);


//////////////////////////////////////////////////////////////////////////

private:

//////////////////////////////////////////////////////////////////////////


    /** Get a high bound for pi(n), the number of primes less or equal n. */
    static int GetPiHighBound( double _n );


//////////////////////////////////////////////////////////////////////////


    /** Prime number sieve, Eratosthenes (276-194 b. t.) This implementation
    considers only multiples of primes greater than 3, so the smallest value
    has to be mapped to 5.

    Note: There is no multiplication operation in this function.

    After execution of the function this boolean array includes
    all composite numbers in [5,n] disregarding multiples of 2 and 3. */
    static void SieveOfEratosthenes( BoolVec& _composite );


//////////////////////////////////////////////////////////////////////////


    /** Transforms the sieve of Eratosthenes
    into the sequence of prime numbers. */
    void MakePrimeList( int _n );


//////////////////////////////////////////////////////////////////////////


    /** Prime numbers */
    IntVec m_Primes;


    /** Number of primes in collection */
    int m_NumberOfPrimes;


//////////////////////////////////////////////////////////////////////////
};


//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
