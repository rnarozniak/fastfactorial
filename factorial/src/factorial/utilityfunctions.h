//////////////////////////////////////////////////////////////////////////

#ifndef _UTILITYFUNCTIONS_H_
#define _UTILITYFUNCTIONS_H_

//////////////////////////////////////////////////////////////////////////

#ifndef _UTILITYTYPES_H_
#include "utilitytypes.h"
#endif

//////////////////////////////////////////////////////////////////////////


/** Utility functions
* 
*   @author Roman Pasechnik
*   @since    Dec 22, 2009
*   @updated  Jan 02, 2010
*/
class UtilityFunctions
{
//////////////////////////////////////////////////////////////////////////

public:

//////////////////////////////////////////////////////////////////////////


    template<typename T>
    static T log2( T _n )
    {
        return log(_n) * 1.4426950408889634;
    }


//////////////////////////////////////////////////////////////////////////


    /* Returns the number of one-bits in the two's complement binary
     * representation of the specified value.  This function is
     * sometimes referred to as the population count. */
    static int BitCount( int _n )
    {
        _n = _n - ( unsigned(_n >> 1) & 0x55555555);
        _n = (_n & 0x33333333) + ( unsigned(_n >> 2) & 0x33333333);
        _n = ( _n + unsigned(_n >> 4) ) & 0x0f0f0f0f;
        _n = _n + unsigned(_n >> 8);
        _n = _n + unsigned(_n >> 16);
        return _n & 0x3f;
    }


//////////////////////////////////////////////////////////////////////////


    /* Sorting numbers keeps the resulting products more nearly equal in size
     * than would the simpler approach. 
     * Nearly equal products are more efficient for the current multiply implementation.
     * Such sorting is more efficient than repeated N?1 multiplies since it forms big multiplies,
     * allowing Karatsuba and higher algorithms to be used. And even below the Karatsuba threshold
     * a big block of work can be more efficient for the base case algorithm. */
    template<typename _InputIterator>
    static mpz_class SequenceProduct( const _InputIterator& _begin,
                                      const _InputIterator& _end )
    {
        // First copy collection to sorted container
        MpzSet sorted;
        for (_InputIterator it = _begin; it != _end; ++it)
            sorted.insert(*it);

        // Start from smaller numbers
        // Get first and second smallest numbers
        MpzSet::iterator itFirst = sorted.begin();
        if ( itFirst == sorted.end() )
            return 0;

        MpzSet::iterator itSecond = itFirst;
        ++itSecond;

        while( itSecond != sorted.end() )
        {
            // Multiply them
            mpz_class prod = (*itFirst) * (*itSecond);

            // Remove them from container
            sorted.erase(itFirst);
            sorted.erase(itSecond);

            // Put their product in container
            sorted.insert(prod);

            // And repeat all this stuff
            itFirst = sorted.begin();
            itSecond = itFirst;
            ++itSecond;
        }

        // After all of this we have single element in sorted
        // container -- product of all elements of sequence.
        return *itFirst;


        // This implementation may be optimized further, I guess.
        // Maybe using of std::set is not a best choice.
    }


//////////////////////////////////////////////////////////////////////////
};


//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
