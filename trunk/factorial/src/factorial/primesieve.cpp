//////////////////////////////////////////////////////////////////////////

#ifndef _PRIMESIEVE_H_
#include "primesieve.h"
#endif

//////////////////////////////////////////////////////////////////////////

#include <cmath>

//////////////////////////////////////////////////////////////////////////


PrimeSieve::PrimeSieve( int _n )
: m_Primes( GetPiHighBound(_n) )
{
    MakePrimeList(_n);
}


//////////////////////////////////////////////////////////////////////////


int PrimeSieve::GetPiHighBound( double _n )
{
    if (_n < 17)
        return 6;
    return static_cast<int>( _n / (log(_n) - 1.5) );
}


//////////////////////////////////////////////////////////////////////////


void PrimeSieve::SieveOfEratosthenes( BoolVec& _composite )
{
    int d1 = 8;
    int d2 = 8;
    int p1 = 3;
    int p2 = 7;
    int s1 = 7;
    int s2 = 3;
    int n = 0;
    int len = _composite.size();
    bool toggle = false;

    while (s1 < len) // -- scan sieve
    {
        if (!_composite[n++]) // -- if a prime is found
        { // -- cancel its multiples
            int inc = p1 + p2;

            for (int k = s1; k < len; k += inc)
                _composite[k] = true;

            for (int k = s1 + s2; k < len; k += inc)
                _composite[k] = true;
        }

        if (toggle = !toggle) // Never mind, it's ok.
        {
            s1 += d2;
            d1 += 16;
            p1 += 2;
            p2 += 2;
            s2 = p2;
        }
        else
        {
            s1 += d1;
            d2 += 8;
            p1 += 2;
            p2 += 6;
            s2 = p1;
        }
    }
}


//////////////////////////////////////////////////////////////////////////


void PrimeSieve::MakePrimeList( int _n )
{
    // Fetch two first primes manually
    m_Primes[0] = 2;
    m_Primes[1] = 3;

    // Fetch vector representing composite numbers
    // [index] -- number
    // [value] -- is number composite or prime
    BoolVec composite(_n / 3);
    SieveOfEratosthenes(composite);
    bool toggle = false;

    // Fetch prime numbers
    int p = 5, i = 0, j = 2;
    while (p <= _n)
    {
        if (!composite[i++])
        {
            m_Primes[j] = p;
            ++j;
        }
    
        // -- never mind, it's ok.
        p += (toggle = !toggle) ? 2 : 4;
    }

    // Number of primes
    m_NumberOfPrimes = j;
}


//////////////////////////////////////////////////////////////////////////


mpz_class PrimeSieve::Primorial( int _low, int _high )
{
    int minIdx = GetPrimeIndex(_low, 3, m_NumberOfPrimes);
    int maxIdx = GetPrimeIndex(_high, minIdx, m_NumberOfPrimes);

    return UtilityFunctions::SequenceProduct( &m_Primes[minIdx],
                                              &m_Primes[maxIdx] );
}


//////////////////////////////////////////////////////////////////////////


int PrimeSieve::GetPrimeIndex( int _number, int _lowerBound, int _upperBound ) const
{
    // Binary search

    while (_lowerBound < _upperBound)
    {
        int mid = ( static_cast<unsigned int>(_lowerBound + _upperBound) ) >> 1;

        if (m_Primes[mid] < _number)
            _lowerBound = mid + 1;
        else
            _upperBound = mid;
    }

    if ( _lowerBound >= static_cast<int>( m_Primes.size() ) )
        return _lowerBound;

    if (m_Primes[_lowerBound] == _number)
        _lowerBound++;

    return _lowerBound;
}


//////////////////////////////////////////////////////////////////////////
