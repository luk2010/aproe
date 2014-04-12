////////////////////////////////////////////////////////////
/** @file Variant.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/01/2014 - 10/04/2014
 *
 *  Defines the Variant class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROVARIANT_H
#define APROVARIANT_H

#include "Platform.h"
#include "SString.h"

namespace APro
{
    // Following code based on cdiggins::any
    namespace VariantPolicy
    {
        /// An exception for bad casting.
        class BadVariantCast : public Exception
        {
            APRO_MAKE_EXCEPTION(BadVariantCast)
            const char* what() const throw() { return "Bad Variant Cast Exception."; }
        };

        /// A structure that describe an empty variant.
        struct empty_variant {};

        /// @brief A structure describing the base variant policy.
        ///
        /// Variant has 2 policies : one for small types, one for big or
        /// unknown types. Small types are holded in the data object,
        /// and data pointes directly to the object.
        /// Big types are pointer to pointer. We hold only a pointer to the
        /// data.
        struct base_variant_policy
        {
            /// Delete an object
            virtual void static_delete(void** x) = 0;

            /// Copy an object
            virtual void copy_from_value(const void* src, void** dest) = 0;

            /// Clone an object
            virtual void clone(const void** src, void** dest) = 0;

            /// Move an object (destruct the old and replace it be new one)
            virtual void move(const void** src, void** dest) = 0;

            /// Return the value.
            virtual void* get_value(void** src) = 0;

            /// Return the size of the data.
            virtual size_t get_size() = 0;
        };

        template<typename T>
        struct typed_variant_policy : public base_variant_policy
        {
            virtual size_t get_size() { return sizeof(T); }
        };


        template<typename T>
        struct small_variant_policy : public typed_variant_policy<T>
        {
            virtual void static_delete(void** x) {}

            virtual void copy_from_value(const void* src, void** dest)
            { AProConstructedCopy(dest, *reinterpret_cast<const T*>(src), T); }

            virtual void clone(const void** src, void** dest)
            { *dest = *src; }

            virtual void move(const void** src, void** dest)
            { *dest = *src; }

            virtual void* get_value(void** src)
            { return reinterpret_cast<void*>(src); }
        };

        template<typename T>
        struct big_variant_policy : public typed_variant_policy<T>
        {
            virtual void static_delete(void** x)
            {
                if(*x)
                {
                    AProDelete(*reinterpret_cast<T**>(x));
                    *x = nullptr;
                }
            }

            virtual void copy_from_value(const void* src, void** dest)
            {
                *dest = AProNew(T, *reinterpret_cast<const T*>(src));
            }

            virtual void clone(const void** src, void** dest)
            {
                *dest = AProNew(T, **reinterpret_cast<const T**>(src));
            }

            virtual void move(const void** src, void** dest)
            {
                AProDestructObject<T>(*reinterpret_cast<T**>(dest));
                **reinterpret_cast<T**>(dest) = **reinterpret_cast<const T**>(src);
            }

            virtual void* get_value(void** src)
            {
                return *src;
            }
        };

        /// For every standard types, we choose the big policy.
        template<typename T>
        struct choose_policy
        {
            typedef big_variant_policy<T> type;
        };

        /// For every pointers we choose small policy.
        template<typename T>
        struct choose_policy<T*>
        {
            typedef small_variant_policy<T*> type;
        };

        /// Specializations for small types.
        #define SMALL_POLICY(TYPE) template<> struct \
        choose_policy<TYPE> { typedef small_variant_policy<TYPE> type; };

        SMALL_POLICY(signed char);
        SMALL_POLICY(unsigned char);
        SMALL_POLICY(signed short);
        SMALL_POLICY(unsigned short);
        SMALL_POLICY(signed int);
        SMALL_POLICY(unsigned int);
        SMALL_POLICY(signed long);
        SMALL_POLICY(unsigned long);
        SMALL_POLICY(float);
        SMALL_POLICY(bool);

        #undef SMALL_POLICY

        /// Returns a policy for each type.
        template<typename T>
        base_variant_policy* get_policy()
        {
            static typename choose_policy<T>::type policy;
            return &policy;
        }
    }

    ////////////////////////////////////////////////////////////
    /** @class Variant
     *  @brief An alternative to the correct Boost::any class.
     *
     *  Contains a value of virtually any type as long as that value
     *  supports copy construction and assignment.
     *
     *  Based on the code of cdiggins::any
     *  @see http://www.codeproject.com/Articles/11250/High-Performance-Dynamic-Typing-in-C-using-a-Repla
    **/
    ////////////////////////////////////////////////////////////
    class Variant
    {
    private:

        VariantPolicy::base_variant_policy* policy;
        void* object;

    public:

        Variant()
            : policy(VariantPolicy::get_policy<VariantPolicy::empty_variant>()), object(nullptr)
        {

        }

        template<typename T>
        Variant(const T& x)
            : policy(VariantPolicy::get_policy<VariantPolicy::empty_variant>()), object(nullptr)
        {
            assign(x);
        }

        Variant(const char* x)
            : policy(VariantPolicy::get_policy<VariantPolicy::empty_variant>()), object(nullptr)
        {
            assign(x);
        }

        Variant(const Variant& other)
            : policy(VariantPolicy::get_policy<VariantPolicy::empty_variant>()), object(nullptr)
        {
            assign(other);
        }

        ~Variant()
        {
            if(!isEmpty())
            {
                policy->static_delete(&object);
            }
        }

    public:

        Variant& swap(const Variant& other)
        {
            Algo::swap(policy, other.policy);
            Algo::swap(object, other.object);
            return *this;
        }

        Variant& assign(const Variant& other)
        {
            clear();
            if(!other.isEmpty())
            {
                policy = other.policy;
                policy->clone(&other.object, &object);
            }

            return *this;
        }

        template<typename T>
        Variant& assign(const T& x)
        {
            clear();
            policy = VariantPolicy::get_policy<T>();
            policy->copy_from_value(&x, &object);
            return *this;
        }

        Variant& operator = (const Variant& x) { return assign(x); }
        Variant& operator = (const char* x) { return assign(x); }
        template<typename T> Variant& operator = (const T& x) { return assign(x); }

    public:

        void clear()
        {
            if(!isEmpty())
            {
                policy->static_delete(object);
                policy = VariantPolicy::get_policy<VariantPolicy::empty_variant>();
                object = nullptr;
            }
        }

        bool isEmpty() const
        {
            return policy == VariantPolicy::get_policy<VariantPolicy::empty_variant>();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return true if type is the same as given Variant.
        **/
        ////////////////////////////////////////////////////////////
        bool isCompatible(const Variant& x) const
        {
            return policy == x.policy;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return true if type given is the holded one.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        bool isCompatible() const
        {
            return policy == VariantPolicy::get_policy<T>();
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Cast holded object to the original type.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        T& cast()
        {
            if(policy != VariantPolicy::get_policy<T>())
                aprothrow(VariantPolicy::BadVariantCast);
            T* r = reinterpret_cast<T*>(policy->get_value(&object));
            return *r;
        }
    };
}

#endif
