//////////////////////////////////////////////////////////////////////////

#ifndef _PARALLELPRIMESWING_H_
#include "parallelprimeswing.h"
#endif

//////////////////////////////////////////////////////////////////////////


void ParallelPrimeSwing::RecFactorial( mpz_class& _result, int _number, PrimeSieve& _sieve )
{
    // Stop recursion here
    if (_number < 2)
    {
        _result = 1;
        return;
    }

    // Prepare result for swing
    mpz_class swing;

    // Calculate it in a new thread
    boost::thread swingThread( boost::bind( &ParallelPrimeSwing::SwingThreadProc, this, &swing, _number, &_sieve ) );

    // Continue calculating recursively
    RecFactorial(_result, _number / 2, _sieve);
    _result *= _result;

    // Wait until swing is calculated
    swingThread.join();
    _result *= swing;
}


//////////////////////////////////////////////////////////////////////////


void ParallelPrimeSwing::SwingThreadProc( mpz_class* _result, int _number, PrimeSieve* _sieve )
{
    *_result = Swing(_number, *_sieve);
}


//////////////////////////////////////////////////////////////////////////
