/** @file Variant.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the Variant class.
 *
**/
#ifndef APROVARIANT_H
#define APROVARIANT_H

#include "Platform.h"
#include "Allocator.h"
#include "SString.h"
#include "Singleton.h"
#include <typeinfo>


namespace APro
{
    class Variant
    {
    protected:

        class holder
        {
        public:

            virtual ~holder()
            {

            }

        public:

            virtual const std::type_info& type()const = 0;
            virtual holder* clone()const = 0;
        };

        template <typename ValueType>
        class RHolder : public holder
        {
        public:

            RHolder()
            {

            }

            RHolder(const ValueType & mvalue)
            : value(mvalue)
            {

            }

            virtual const std::type_info & type() const
            {
                return typeid(ValueType);
            }

            virtual holder* clone() const
            {
                return AProNew(1, RHolder<ValueType>) (value);
            }

        public:

            ValueType value;
        };

    protected:

        holder* content;

    public:

        Variant() : content(nullptr)
        {

        }

        template <typename ValueType>
        explicit Variant(const ValueType & value) : content(AProNew(1, RHolder<ValueType>) (value))
        {

        }

        Variant(const Variant& other) : content(other.content ? other.content->clone() : nullptr)
        {

        }

        virtual ~Variant()
        {
            clear();
        }

    public:

        Variant& swap(Variant & other)
        {
            holder* tmp = content;
            content = other.content;
            other.content = tmp;
            return *this;
        }

        template <typename ValueType>
        Variant& operator = (const ValueType& other)
        {
            set<ValueType>(other);
            return *this;
        }

        Variant& operator = (const Variant& other)
        {
            set(other);
            return *this;
        }

    public:

        bool isEmpty() const
        {
            return !content;
        }

        const std::type_info & getType() const
        {
            return content ? content->type() : typeid(void);
        }

        template<typename ValueType>
        void set(const ValueType& obj)
        {
            if(content)
                clear();

            content = AProNew(1, RHolder<ValueType>) (obj);
        }

        void set(const Variant& other)
        {
            if(content)
                clear();

            if(!other.isEmpty())
                content = other.content->clone();
        }

        void clear()
        {
            AProDelete(content);
            content = nullptr;
        }

    public:

        template<typename ValueType>
        ValueType* toPtr()
        {
            if(!content)
            {
#if APRO_EXCEPTION == APRO_ON
                String str;
                str << "Bad Cast from type " << getType().name() << " to type " << typeid(ValueType).name() << "." << "\nType of void is : " << typeid(void).name() << ".";
                APRO_THROW("BadCast", str.toCstChar(), "Variant");
#endif
            }

            if(getType() == typeid(ValueType))
            {
                return &(static_cast<Variant::RHolder<ValueType> *>(content)->value);
            }
            else
            {
                return nullptr;
            }
        }

        template<typename ValueType>
        const ValueType* toCstPtr() const
        {
            if(!content)
            {
#if APRO_EXCEPTION == APRO_ON
                String str;
                str << "Bad Cast from type " << getType().name() << " to type " << typeid(ValueType).name() << "." << "\nType of void is : " << typeid(void).name() << ".";
                APRO_THROW("BadCast", str.toCstChar(), "Variant");
#endif
            }

            if(getType() == typeid(ValueType))
            {
                return &(static_cast<Variant::RHolder<ValueType> *>(content)->value);
            }
            else
            {
                return nullptr;
            }
        }

        template<typename ValueType>
        ValueType& to()
        {
            ValueType* ptr = toPtr<ValueType>();
            if(ptr == nullptr)
            {
#if APRO_EXCEPTION == APRO_ON
                String str;
                str << "Bad Cast from type " << getType().name() << " to type " << typeid(ValueType).name() << "." << "\nType of void is : " << typeid(void).name() << ".";
                APRO_THROW("BadCast", str.toCstChar(), "Variant");
#endif
            }

            return *ptr;
        }

        template<typename ValueType>
        const ValueType& to() const
        {
            const ValueType* ptr = toCstPtr<ValueType>();
            if(ptr == nullptr)
            {
#if APRO_EXCEPTION == APRO_ON
                String str;
                str << "Bad Cast from type " << getType().name() << " to type " << typeid(ValueType).name() << "." << "\nType of void is : " << typeid(void).name() << ".";
                APRO_THROW("BadCast", str.toCstChar(), "Variant");
#endif
            }

            return *ptr;
        }

        template<typename ValueType>
        bool isCastable() const
        {
            return getType() == typeid(ValueType);
        }
    };
}

#endif
