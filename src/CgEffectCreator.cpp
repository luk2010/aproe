/** @file CgEffectCreator.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 28/12/2012
 *
 *  @addtogroup Global
 *  @addtogroup Shaders
 *
 *  This file defines the CgEffectCreator class.
 *
**/
#include "CgEffectCreator.h"
/*
namespace APro
{
    CGtype convertSPTtoCg(CGtype t)
    {
        switch (t)
        {
        case ShadersEffectParameter::Type::None:
        default:
            return CG_UNKNOWN_TYPE;
        }
    }

    CgEffectCreator::CgEffectCreator()
    {

    }

    CgEffectCreator::~CgEffectCreator()
    {

    }

    void CgEffectCreator::init()
    {
        cgSetErrorHandler(CgEffectCreator::ErrorHandler, this);
        context = cgCreateContext();
    }

    void CgEffectCreator::deinit()
    {
        if(context)
        {
            cgDestroyContext(context);
            context = NULL;
        }

        cgSetErrorHandler(NULL, NULL);
    }

    String CgEffectCreator::getName() const
    {
        return String("CgEffectCreator");
    }

    ShadersEffect::ptr CgEffectCreator::createEffect(const String& name, const String& file) const
    {
        return AProNew(1, CgShadersEffect) (name, file, context);
    }

    ShadersEffectParameter::ptr CgEffectCreator::createParameter(const String& name, ShadersEffectParameter::Type::_ type) const
    {
        if(name.isEmpty()) return ShadersEffectParameter::ptr;
        if(type == ShadersEffectParameter::Type::None) return ShadersEffectParameter::ptr;

        CGtype t = convertSPTtoCg(type);

        CGparameter param = cgCreateParameter(context, t);
        return AProNew(1, CgShadersEffectParameter) (name, param);
    }

    void CgEffectCreator::ErrorHandler(CGcontext ctxt, CGerror err, void* pdata)
    {
        if(err != CG_NO_ERROR)
        {
            const char * pErr = cgGetErrorString(err);
            String strErr(pErr == NULL ? "" : pErr);

            Main::get().getConsole() << "\n[ShadersEffectManager] ERROR : " << strErr;

            if(err == CG_COMPILER_ERROR)
            {
                pErr = cgGetLastListing(ctxt_);
                strErr = String(pErr == NULL ? "" : pErr);

                Main::get().getConsole() << "\n    [ERROR] : " << strErr;
            }
        }
    }
}
*/
