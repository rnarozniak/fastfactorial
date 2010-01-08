//////////////////////////////////////////////////////////////////////////

#ifndef _PRIMESWING_H_
#include "primeswing.h"
#endif

#ifndef _PARALLELPRIMESWING_H_
#include "parallelprimeswing.h"
#endif

#ifndef _SCOPETIMEPRINTER_H_
#include "scopetimeprinter.h"
#endif

#include <iostream>

//////////////////////////////////////////////////////////////////////////


template<typename _FactorialCalculator>
void FastCheck();


template<typename _FactorialCalculator>
void TestNumber( int _number );


//////////////////////////////////////////////////////////////////////////


int main()
{
    // Perform a fast check
    FastCheck<ParallelPrimeSwing>();

    // It takes approx 25 seconds to calculate 10000000 factorial on
    // Athlon Dual Core Processor 4050e 2.10 GHz, 2 GB RAM
    TestNumber<ParallelPrimeSwing>(10000000);

    // Exit
    return 0;
}


//////////////////////////////////////////////////////////////////////////


template<typename _FactorialCalculator>
void FastCheck()
{
    for (int i = 1000; i < 10000; i += 500)
        TestNumber<_FactorialCalculator>(i);
}


//////////////////////////////////////////////////////////////////////////


template<typename _FactorialCalculator>
void TestNumber( int _number )
{
    // Number for calculating factorial
    _FactorialCalculator calculator;
    mpz_class result;

    std::cout << "Testing number: " << _number << std::endl;

    // Calculate factorial using prime swing algorithm
    std::cout << "Prime Swing: ";
    {
        ScopeTimePrinter printer;
        result = calculator.Factorial(_number);
    }
    std::cout << std::endl;

    // Calculate factorial using built in binary split algorithm
    mpz_class check;
    std::cout << "Binary split: ";
    {
        ScopeTimePrinter printer;
        mpz_fac_ui(check.get_mpz_t(), _number);
    }

    // Check them for equality
    if (check == result)
        std::cout << "      OK";
    else
        std::cout << "      FAIL";

    std::cout << std::endl << "===================="
        << std::endl << std::endl;
}


//////////////////////////////////////////////////////////////////////////
