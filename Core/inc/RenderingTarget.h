////////////////////////////////////////////////////////////
/** @file RenderingTarget.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 31/12/2014 - 17/01/2015
 *
 *  @brief 
 *  Defines the RenderingTarget interface.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
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
#ifndef APRO_RENDERINGTARGET_H
#define APRO_RENDERINGTARGET_H

#include "Platform.h"
#include "BaseObject.h"
#include "ThreadSafe.h"
#include "NonCopyable.h"

#include "List.h"
#include "Array.h"

namespace APro
{
	////////////////////////////////////////////////////////////
	/** @class RenderingTarget
	 *  @ingroup Rendering
	 *  @brief A surface where the Renderer can draw objects.
	 *
	 *  A RenderingTarget is an abstract representation of a Surface
	 *  which can be drawn by a RenderingAPI. Those "targets" must
	 *  be activated in the RenderingAPI to be drawn. 
	 *
	 *  @note
	 *  Generally, the RenderingTarget objects are specific to the
	 *  RenderingAPI, so you may have to call something like
	 *  RenderingAPI::createWindow() (A Window is a RenderingTarget).
	**/
	////////////////////////////////////////////////////////////
	class RenderingTarget : 
		public BaseObject<RenderingTarget>,
		public NonCopyable,
		virtual public ThreadSafe
	{
	public:
		
		RenderingTarget();
		virtual ~RenderingTarget();
		
		////////////////////////////////////////////////////////////
        /** @brief Activates or deactivates the RenderingTarget.
        **/
        ////////////////////////////////////////////////////////////
		void setActivated(bool activated);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns true if activated, false otherwise.
        **/
        ////////////////////////////////////////////////////////////
		bool isActivated() const;
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the name of this RenderingTarget.
        **/
        ////////////////////////////////////////////////////////////
		const String& getName() const;
		
	protected:
		
		////////////////////////////////////////////////////////////
        /** @brief Sets the name of this RenderingTarget.
        **/
        ////////////////////////////////////////////////////////////
		void setName(const String& name);
		
	protected:
		
		String m_targetname; ///< @brief Name of this RenderingTarget.
		bool   m_activated;  ///< @brief Stores the activated state.
	};
	
	typedef List<RenderingTarget> RenderingTargetList;
	typedef Array<RenderingTarget> RenderingTargetArray;
}

#endif // APRO_RENDERINGTARGET_H
