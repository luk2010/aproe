////////////////////////////////////////////////////////////
/** @file Assert.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/10/2013
 *
 *  Defines the throwing exception Assert function.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_ASSERT_H
#define APRO_ASSERT_H

namespace APro
{
    /** Throw an exception if _succeeded condition is false.
     *
     *  @note This function is used only by aproassert macro when
     *  options --with-exceptions and --with-exceptassert are set
     *  in debug mode.
    **/
    APRO_DLL void __assert_with_except(bool _succeeded, const char* _msg, const char* _condition);
}

#endif // APRO_ASSERT_H
