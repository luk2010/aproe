/** @file MathFunctionManager.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Maths
 *
 *  This file defines the MathFunctionManager class.
 *
**/
#include "MathFunctionManager.h"
#include "Maths.h"

namespace APro
{
    Variant MathFunctionCos(const List<Variant>& args)
    {
        double arg1 = args.at(0).to<double>();
        return Variant(Angle::Cos(arg1));
    }

    Variant MathFunctionSin(const List<Variant>& args)
    {
        double arg1 = args.at(0).to<double>();
        return Variant(Angle::Sin(arg1));
    }

    MathFunctionManager::MathFunctionManager()
    {
        MathModule::ptr stdModule( AProNew(1, MathModule) (String("Std"), String("Standard Module.")) );

        MathFunction::ptr cosFunction ( AProNew(1, MathFunction) (String("Cos"),
                                                               String("double:double"),
                                                               String("Cosinus of an angle, in radian."),
                                                               MathFunctionCos));

        stdModule->pushFunction(cosFunction);

        MathFunction::ptr sinFunction ( AProNew(1, MathFunction) (String("Sin"),
                                                               String("double:double"),
                                                               String("Sinus of an angle, in radian."),
                                                               MathFunctionSin));
        stdModule->pushFunction(sinFunction);

        push(stdModule);
    }

    MathFunctionManager::~MathFunctionManager()
    {

    }

    MathFunction::ptr MathFunctionManager::find(const String& completeName)
    {
        List<String> names = completeName.explode('.');
        if(names.size() > 1)
        {
            List<String>::Iterator it = names.end(); it--;
            String func = it.get();
            MathModule::ptr curModule = module(names.begin().get());
            int i = 1;
            while(!curModule.isNull())
            {
                MathModule::ptr tmp = curModule->findModule(names.at(i));
                if(tmp.isNull())
                    break;

                curModule = tmp;
                i++;
            }

            if(i < (int) names.size() - 2)// Can't reach last module
                return MathFunction::ptr();
            else
                return curModule->findFunction(func);
        }

        return MathFunction::ptr();
    }

    MathModule::ptr MathFunctionManager::module(const String& moduleName)
    {
        List<MathModule::ptr>& modules = Manager<MathModule>::objects;
        for(unsigned int i = 0; i < modules.size(); ++i)
        {
            MathModule::ptr tmp = modules.at(i);
            if(tmp->getName() == moduleName)
                return tmp;
        }

        return MathModule::ptr(nullptr);
    }

    bool MathFunctionManager::hasModule(const String& moduleName)
    {
        return !(module(moduleName).isNull());
    }

    bool MathFunctionManager::hasFunction(const String& functionName)
    {
        return !(find(functionName).isNull());
    }
}
