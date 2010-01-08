//////////////////////////////////////////////////////////////////////////

#ifndef _PRIMESWING_H_
#include "primeswing.h"
#endif

//////////////////////////////////////////////////////////////////////////

#include <cmath>

//////////////////////////////////////////////////////////////////////////


const int smallOddSwing[] = {
1, 1, 1, 3, 3, 15, 5, 35, 35, 315, 63, 693, 231, 3003, 429,
6435, 6435, 109395, 12155, 230945, 46189, 969969, 88179,
2028117, 676039, 16900975, 1300075, 35102025, 5014575,
145422675, 9694845, 300540195, 300540195 };


//////////////////////////////////////////////////////////////////////////


mpz_class PrimeSwing::Factorial( int _number )
{
    mpz_class result;

    // For very small n the 'NaiveFactorial' is OK.
    if (_number < 20)
    {
        mpz_fac_ui(result.get_mpz_t(), _number);
        return result;
    }

    PrimeSieve sieve(_number);
    RecFactorial(result, _number, sieve);
    result <<= ( _number - UtilityFunctions::BitCount(_number) );

    return result;
}


//////////////////////////////////////////////////////////////////////////


void PrimeSwing::RecFactorial( mpz_class& _result, int _number, PrimeSieve& _sieve )
{
    // Stop recursion here
    if (_number < 2)
    {
        _result = 1;
        return;
    }

    // Continue calculating recursively
    RecFactorial(_result, _number / 2, _sieve);
    _result *= _result;
    _result *= Swing(_number, _sieve);
}


//////////////////////////////////////////////////////////////////////////


mpz_class PrimeSwing::Swing( int _number, PrimeSieve& _sieve )
{
    // Small precalculated values
    if (_number < 33)
        return smallOddSwing[_number];

    // Fetch multiplies
    IntVec multiplies = GetMultiplies(_number, _sieve);

    // Return multiplies of primorials
    return _sieve.Primorial(_number / 2, _number) *
           UtilityFunctions::SequenceProduct( multiplies.begin(), multiplies.end() );
}


//////////////////////////////////////////////////////////////////////////


IntVec PrimeSwing::GetMultiplies( int _number, PrimeSieve& _sieve )
{
    IntVec multiplies;
    int sqrtN = static_cast<int>( sqrt( static_cast<double>(_number) ) );

    int maxIdx = _sieve.GetPrimeIndex( sqrtN, 2, _sieve.GetNumberOfPrimes() );
    for ( int i = 1; i < maxIdx; ++i )
    {
        int prime = _sieve.GetPrime(i);

        int q = _number, p = 1;

        while ((q /= prime) > 0)
            if ((q & 1) == 1)
                p *= prime;

        if (p > 1)
            multiplies.push_back(p);
    }

    int minIdx = maxIdx;
    maxIdx = _sieve.GetPrimeIndex( _number / 3, minIdx, _sieve.GetNumberOfPrimes() );

    for (int i = minIdx; i < maxIdx; ++i)
    {
        int prime = _sieve.GetPrime(i);

        if (((_number / prime) & 1) == 1)
            multiplies.push_back(prime);
    }

    return multiplies;
}


//////////////////////////////////////////////////////////////////////////
