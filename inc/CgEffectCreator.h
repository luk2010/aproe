/** @file CgEffectCreator.h
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
#ifndef APRO_CGEFFECTCREATOR_H
#define APRO_CGEFFECTCREATOR_H
/*
#include "ShadersEffectManager.h"

#include <Cg/cg.h>

namespace APro
{
    class APRO_DLL CgEffectCreator : public ShadersEffectManager::EffectCreator
    {
    public:

        CgEffectCreator();
        virtual ~CgEffectCreator();

    public:

        virtual void init();
        virtual void deinit();

    public:

        virtual String getName() const;

        virtual ShadersEffect::ptr createEffect(const String& name, const String& file) const;
        virtual ShadersEffectParameter::ptr createParameter(const String& name, ShadersEffectParameter::Type::_ type) const;

    public:

        static void ErrorHandler(CGcontext ctxt, CGerror err, void* pdata);

    private:

        CGcontext context;
    };
}
*/
#endif // APRO_CGEFFECTCREATOR_H
