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


void FastCheck();
void TestNumber( int _number );


//////////////////////////////////////////////////////////////////////////


int main()
{
    // Perform a fast check
    FastCheck();

    // It takes approx 25 seconds to calculate 10000000 factorial on
    // Athlon Dual Core Processor 4050e 2.10 GHz, 2 GB RAM
    TestNumber(10000000);

    // Exit
    return 0;
}


//////////////////////////////////////////////////////////////////////////


void FastCheck()
{
    for (int i = 1000; i < 10000; i += 500)
        TestNumber(i);
}


//////////////////////////////////////////////////////////////////////////


void TestNumber( int _number )
{
    // Number for calculating factorial
    mpz_class primeSwingResult;
    mpz_class parallelPrimeSwingResultresult;

    std::cout << "Testing number: " << _number << std::endl;

    // Calculate factorial using prime swing algorithm
    std::cout << "Prime Swing: ";
    {
        PrimeSwing calculator;
        ScopeTimePrinter printer;
        primeSwingResult = calculator.Factorial(_number);
    }
    std::cout << std::endl;

    // Calculate factorial using parallel prime swing algorithm
    std::cout << "Parallel Prime Swing: ";
    {
        ParallelPrimeSwing calculator;
        ScopeTimePrinter printer;
        parallelPrimeSwingResultresult = calculator.Factorial(_number);
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
    if (check == primeSwingResult && check == parallelPrimeSwingResultresult)
        std::cout << "      OK";
    else
        std::cout << "      FAIL";

    std::cout << std::endl << "===================="
        << std::endl << std::endl;
}


//////////////////////////////////////////////////////////////////////////
