/** @file Number.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/02/2013
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the Number class.
 *
**/
#ifndef APRO_NUMBER_H
#define APRO_NUMBER_H

#include "Variant.h"

namespace APro
{
    class Number : public Variant
    {
    protected:

        class NumHolder : public Variant::holder
        {
            public:
                ~NumHolder()
                {

                }

                virtual holder* add(holder* h) = 0;
                virtual holder* substract(holder* h) = 0;
                virtual holder* multiply(holder* h) = 0;
                virtual holder* multiply(double h) = 0;
                virtual holder* divide(holder* h) = 0;
        };

        template<typename ValueType>
        class NumRHolder : public NumHolder
        {
        public:

            ValueType held;

        public:

            NumRHolder(const ValueType& v) : held(v)
            {

            }

            virtual const std::type_info & getType() const
            {
                return typeid(ValueType);
            }

            virtual holder* clone() const
            {
                return AProNew(1, NumRHolder) (held);
            }

            virtual holder* add(holder* h)
            {
                return AProNew(1, NumRHolder) (held + static_cast<NumRHolder*>(h)->held);
            }

            virtual holder* substract(holder* h)
            {
                return AProNew(1, NumRHolder) (held - static_cast<NumRHolder*>(h)->held);
            }

            virtual holder* multiply(holder* h)
            {
                return AProNew(1, NumRHolder) (held * static_cast<NumRHolder*>(h)->held);
            }

            virtual holder* multiply(double h)
            {
                return AProNew(1, NumRHolder) (held * h);
            }

            virtual holder* divide(holder* h)
            {
                return AProNew(1, NumRHolder) (held / static_cast<NumRHolder*>(h)->held);
            }
        };

    public:

        Number() : Variant()
        {

        }

        template <typename ValueType> explicit Number(const ValueType& v)
        {
            content = AProNew(1, NumRHolder<ValueType>) (v);
        }

        Number(const Number& other)
            : Variant()
        {
            content = other.content ? other.content->clone() : 0;
        }

        Number(Variant::holder* pholder)
        {
            content = pholder;
        }

    public:

        Number& operator = (const Number& other)
        {
            Number(other).swap(*this);
            return *this;
        }

        Number operator + (const Number& other) const
        {
            return Number(static_cast<NumHolder*>(content)->add(other.content));
        }

        Number operator - (const Number& other) const
        {
            return Number(static_cast<NumHolder*>(content)->substract(other.content));
        }

        Number operator * (const Number& other) const
        {
            return Number(static_cast<NumHolder*>(content)->multiply(other.content));
        }

        Number operator * (double other) const
        {
            return Number(static_cast<NumHolder*>(content)->multiply(other));
        }

        Number operator / (const Number& other) const
        {
            return Number(static_cast<NumHolder*>(content)->divide(other.content));
        }

        Number& operator += (const Number& other)
        {
            *this = Number(static_cast<NumHolder*>(content)->add(other.content));
            return *this;
        }

        Number& operator -= (const Number& other)
        {
            *this = Number(static_cast<NumHolder*>(content)->substract(other.content));
            return *this;
        }

        Number& operator *= (const Number& other)
        {
            *this = Number(static_cast<NumHolder*>(content)->multiply(other.content));
            return *this;
        }

        Number& operator /= (const Number& other)
        {
            *this = Number(static_cast<NumHolder*>(content)->divide(other.content));
            return *this;
        }

        Number& operator *= (double other)
        {
            *this = Number(static_cast<NumHolder*>(content)->multiply(other));
            return *this;
        }

    public:

        double toReal() const
        {
            return to<double>();
        }

        int toInt() const
        {
            return to<int>();
        }

        float toFloat() const
        {
            return to<float>();
        }
    };
}

#endif // APRO_NUMBER_H
