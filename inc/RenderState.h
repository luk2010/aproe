/** @file RenderState.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 15/12/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the RenderState enum.
 *
**/
#ifndef APRORENDERSTATE_H
#define APRORENDERSTATE_H

#include "Platform.h"

namespace APro
{
    class RenderState
    {
    public:
        enum _
        {
            None,
            PreRender,
            Render,
            PostRender
        };

    public:

        static String toString(RenderState::_ state)
        {
            switch (state)
            {
            case None:
                return String("None");
            case PreRender:
                return String("PreRender");
            case Render:
                return String("Render");
            case PostRender:
                return String("PostRender");
            default:
                return String("InvalidState");
            }
        }

        static RenderState::_ fromString(const String& state)
        {
            if(state == String("None"))
                return RenderState::None;
            else if (state == String("PreRender"))
                return RenderState::PreRender;
            else if (state == String("Render"))
                return RenderState::Render;
            else if (state == String("PostRender"))
                return RenderState::PostRender;
            else
                return RenderState::None;
        }
    };
}

#endif // APRORENDERSTATE_H
