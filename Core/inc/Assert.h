////////////////////////////////////////////////////////////
/** @file Assert.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/10/2013 - 11/12/2014
 *
 *  @brief
 *  Defines the throwing exception Assert function.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
