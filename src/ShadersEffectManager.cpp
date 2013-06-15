/** @file ShadersEffectManager.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/11/2012
 *
 *  @addtogroup Global
 *  @addtogroup Shaders
 *
 *  This file defines the ShadersEffectManager class.
 *
**/
#include "ShadersEffectManager.h"
#include "Main.h"
#include "RenderState.h"
/*
namespace APro
{
    ShadersEffectManager::ShadersEffectManager()
    {
        initialized = false;
    }

    ShadersEffectManager::~ShadersEffectManager()
    {

    }

    void ShadersEffectManager::OnInit()
    {
        if(!initialized)
        {
            _OnInit();
            initialized = true;
        }
    }

    void ShadersEffectManager::OnDeinit()
    {
        if(!initialized)
            return;

        clearCreators();
        clearEffects();
        clearGlobalParameters();

        _OnDeInit();
        initialized = false;
    }

    void ShadersEffectManager::_OnInit()
    {

    }

    void ShadersEffectManager::_OnDeInit()
    {

    }

    void ShadersEffectManager::addEffectCreator(const EffectCreator::ptr& creator)
    {
        if(creator.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't add Null Creator.";
            return;
        }

        if(creatorsByName.exists(creator->getName()))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] WARNING : Creator " << creator->getName() << " already exist and loaded !";
        }
        else
        {
            creators.append(creator);
            creatorsByName.push(creator->getName(), creator);

            creator->init();
            Main::get().getConsole() << "\n[ShadersEffectManager] New Creator added : " << creator->getName() << ".";
        }
    }

    void ShadersEffectManager::removeEffectCreator(const String& name)
    {
        if(!creatorsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] WARNING : Can't remove creator " << name << " because it doesn't exist !";
        }
        else
        {
            EffectCreator::ptr creator = creatorsByName[name];
            creatorsByName.pop(name);

            creators.erase(creators.find(creator));

            Main::get().getConsole() << "\n[ShadersEffectManager] Releasing every effect created with creator " << name << ".";

            EffectsList& effects = effectsByCreator[name];
            for(unsigned int i = 0; i < effects.size(); ++i)
            {
                destroyEffect(effects.at(i)->getName());
            }

            creator->deinit();
            Main::get().getConsole() << "\n[ShadersEffectManager] Creator " << name << " removed !";
        }
    }

    ShadersEffect::ptr ShadersEffectManager::createEffect(const String& name, const String& file, const String& creatorname)
    {
        if(file.isEmpty())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't create effect " << name << " from empty file.";
            return ShadersEffect::ptr;
        }

        if(name.isEmpty())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't create effect from file " << file << " with empty name.";
            return ShadersEffect::ptr;
        }

        if(effectsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " already exists !";
            return ShadersEffect::ptr;
        }

        EffectCreator::ptr creator;

        if(!creatorsByName.exists(creatorname))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't find creator " << creatorname << " to create effect " << name
            << " from file " << file << ". Using default CgEffectCreator.";

            creator = creatorsByName[String("CgEffectCreator")];
        }
        else
        {
            creator = creatorsByName[creatorname];
        }

        if(creator.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't find a suitable creator to create effect " << name << " from file "
            << file << ".";
            return ShadersEffect::ptr;
        }

        ShadersEffect::ptr effect = creator->createEffect(name, file);
        if(effect.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't create effect " << name << " !";
            return ShadersEffect::ptr;
        }

        effectsList.append(effect);
        effectsByName.push(name, effect);
        effectsSelected[RenderState::None].append(effect);
        effectsByCreator[creator->getName()].append(effect);

        Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " created from file " << file << " with creator "
        << creator->getName() << ".";

        return effect;
    }

    ShadersEffect::ptr ShadersEffectManager::getEffectByName(const String& name)
    {
        if(effectsByName.exists(name))
            return effectsByName[name];
        else
            return ShadersEffect::ptr;
    }

    const ShadersEffectManager::EffectsList & ShadersEffectManager::getEffects() const
    {
        return effectsList;
    }

    ShadersEffectManager::EffectsList & ShadersEffectManager::getEffects()
    {
        return effectsList;
    }

    const ShadersEffectManager::EffectsMap& ShadersEffectManager::getEffectsByName() const
    {
        return effectsByName;
    }

    ShadersEffectManager::EffectsMap& ShadersEffectManager::getEffectsByName()
    {
        return effectsByName;
    }

    void ShadersEffectManager::destroyEffect(const String& name)
    {
        if(!effectsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't find and destroy effect " << name << ".";
            return;
        }

        ShadersEffect::ptr effect = effectsByName[name];

        if(effect.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Error getting effect " << name << " : Null.";
        }

        unselectEffect(name);

        effectsByName.pop(name);
        effectsList.erase(effectsList.find(effect));
        effectsByCreator[effect->getCreatorName()].erase(effectsByCreator[effect->getCreatorName()].find(effect));

        Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " destroyed.";
    }

    void ShadersEffectManager::clearEffects()
    {
        while(effectsList.size() > 0)
        {
            ShadersEffect::ptr effect = effectsList.at(0);

            effectsList.erase(0);
            effectsByName.pop(effect->getName());
        }

        effectsSelected.clear();
        effectsByCreator.clear();
    }

    void ShadersEffectManager::selectEffectForRender(const String& name, RenderState::_ state)
    {
        if(!effectsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " doesn't exists.";
            return;
        }

        ShadersEffect::ptr effect = effectsByName[name];
        if(effect.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Error getting effect " << name << " : Null.";
            return;
        }

        if(effectsSelected[state].find(effect) == -1)
        {
            effectsSelected[state].append(effect);

            int index = effectsSelected[RenderState::None].find(effect);
            if(index != -1)
                effectsSelected[RenderState::None].erase(index);
        }
        else
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name
            << " already selected for state " << RenderState::toString(state) << ".";
        }
    }

    void ShadersEffectManager::unselectEffectForRender(const String& name, RenderState::_ state)
    {
        if(!effectsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " doesn't exists.";
            return;
        }

        ShadersEffect::ptr effect = effectsByName[name];
        if(effect.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Error getting effect " << name << " : Null.";
            return;
        }

        int index = effectsSelected[state].find(effect);

        if(index != -1)
        {
            effectsSelected[state].erase(index);
        }
        else
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name
            << " already unselected for state " << RenderState::toString(state) << ".";
        }

        if(!isEffectSelectedForRender(name, RenderState::PreRender) &&
           !isEffectSelectedForRender(name, RenderState::Render) &&
           !isEffectSelectedForRender(name, RenderState::PostRender))
        {
            index = effectsSelected[RenderState::None].find(effect);

            if(index == -1)
                effectsSelected[RenderState::None].append(effect);
        }
    }

    void ShadersEffectManager::unselectEffect(const String& name)
    {
        if(!effectsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " doesn't exists.";
            return;
        }

        ShadersEffect::ptr effect = effectsByName[name];
        if(effect.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Error getting effect " << name << " : Null.";
            return;
        }

        if(isEffectSelectedForRender(name, RenderState::None))
            return;

        if(isEffectSelectedForRender(name, RenderState::PreRender))
            unselectEffectForRender(name, RenderState::PreRender);
        if(isEffectSelectedForRender(name, RenderState::Render))
            unselectEffectForRender(name, RenderState::Render);
        if(isEffectSelectForRender(name, RenderState::PostRender))
            unselectEffectForRender(name, RenderState::PostRender);
    }

    bool ShadersEffectManager::isEffectSelectedForRender(const String& name, RenderState::_ state) const
    {
        if(!effectsByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Effect " << name << " doesn't exists.";
            return false;
        }

        ShadersEffect::ptr effect = effectsByName[name];
        if(effect.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Error getting effect " << name << " : Null.";
            return false;
        }

        return effectsSelected[state].find(effect) != -1;
    }

    ShadersEffectParameter::ptr ShadersEffectManager::createGlobalParameter(const String& name, CGtype type, const String& creator)
    {
        if(name.isEmpty())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't create Global Parameter with empty name !";
            return ShadersEffectParameter::ptr;
        }

        if(globalParametersByName.exists(name))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Global Parameter " << name << " already exists !";
            return ShadersEffectParameter::ptr;
        }

        String creatorf(creator);

        if(creatorf.isEmpty())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't create Global Parameter with empty creator ! Using CgEffectCreator.";
            creatorf = "CgEffectCreator";
        }

        if(!creatorsByName.exists(creatorf))
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Can't find creator " << creatorf << "! Creation of parameter " << name << " canceled.";
            return ShadersEffectParameter::ptr;
        }

        EffectCreator::ptr creatorp;

        creatorp = creatorsByName[creatorf];

        if(creatorp.isNull())
        {
            Main::get().getConsole() << "\n[ShadersEffectManager] Error while getting creator " << creatorf << " : Null. Can't Create parameter " << name << ".";
            return ShadersEffectParameter::ptr;
        }
    }


}
*/
