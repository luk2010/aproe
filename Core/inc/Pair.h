/** @file Pair.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the Pair class.
 *
**/
#ifndef APROPAIR_H
#define APROPAIR_H

#include "Map.h"

namespace APro
{
    template <typename T1, typename T2>
    class Pair : public Map<T1, T2>::Pair
    {
    public:

        typedef typename Map<T1, T2>::Pair pair_t;

    public:

        Pair()
            : pair_t()
        {

        }

        Pair(const Pair<T1, T2>& other)
            : pair_t(other)
        {

        }

        Pair(const T1& t1, const T2& t2)
            : pair_t(t1, t2)
        {

        }

        Pair(const pair_t& p)
            : pair_t(p)
        {

        }

        ~Pair()
        {

        }
    };
}

#endif
