/** @file Functor.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Functor system.
 *
**/
#ifndef APRO_FUNCTOR_H
#define APRO_FUNCTOR_H

#include "Platform.h"
#include "List.h"
#include "Variant.h"

namespace APro
{
/*
    class Functor
    {
    public:

        typedef List<Variant> Arguements;

    public:

        Functor()
        {

        }

        virtual ~Functor()
        {

        }

    public:

        virtual void Call(Arguements& args) = 0;
    };

    template <typename F>
    class FunctorWithoutArg : public Functor
    {
    public:

        FunctorWithoutArg(F func)
            : m_func(func)
        {

        }

        virtual ~FunctorWithoutArg()
        {

        }

    public:

        virtual void Call(Functor::Arguements& args)
        {
            m_func();
        }

    protected:

        F m_func;
    };

    template <typename F>
    class FunctorWithArg : public FunctorWithoutArg<F>
    {
    public:

        FunctorWithArg(F func)
            : FunctorWithoutArg<F>(func)
        {

        }

        ~FunctorWithArg()
        {

        }

    public:

        virtual void Call(Functor::Arguements& args)
        {
            _unpackArgsAndCall<args.size()>(FunctorWithoutArg<F>::m_func, args);
        }

    protected:

        template <int N>
        void _unpackArgsAndCall(F func, Functor::Arguements& args)
        {
            if(N == 1)
            {
                func(args[0]);
            }
            else if(N == 2)
            {
                func(args[0], args[1]);
            }
            else if(N == 3)
            {
                func(args[0], args[1], args[2]);
            }
            else if(N == 4)
            {
                func(args[0], args[1], args[2], args[3]);
            }
            else if(N == 5)
            {
                func(args[0], args[1], args[2], args[3], args[4]);
            }
            else if(N == 6)
            {
                func(args[0], args[1], args[2], args[3], args[4], args[5]);
            }
            else if(N == 7)
            {
                func(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            }
        }
    };
    */
}

#endif // APRO_FUNCTOR_H
