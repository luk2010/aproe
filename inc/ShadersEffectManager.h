/** @file ShadersEffectManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 09/11/2012
 *
 *  @addtogroup Global
 *  @addtogroup Shaders
 *
 *  This file defines the ShadersEffectManager class.
 *
**/
#ifndef APROSHADERSEFFECTMANAGER_H
#define APROSHADERSEFFECTMANAGER_H
/*
#include "Platform.h"
#include "SString.h"
#include "Map.h"

namespace APro
{
    class Renderer;

    class APRO_DLL ShadersEffectManager
    {
    public:

        class EffectCreator
        {
            APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(EffectCreator)

        public:

            friend class ShadersEffectManager;

        public:

            EffectCreator()
            {

            }

            EffectCreator(const EffectCreator& other)
            {

            }

            virtual ~EffectCreator()
            {

            }

        public:
            virtual String getName() const = 0;

            virtual ShadersEffect::ptr createEffect(const String& name, const String& file) const = 0;
            virtual ShadersEffectParameter::ptr createParameter(const String& name, ShadersEffectParameter::Type type) const = 0;

        public:

            virtual void init() = 0;
            virtual void deinit() = 0;
        };

        void addEffectCreator(const EffectCreator::ptr& creator);
        void removeEffectCreator(const String & name);
        void clearCreators();

    public:

        typedef Map<String, ShadersEffect::ptr> EffectsMap;
        typedef List<ShadersEffect::ptr> EffectsList;
        typedef Map<RenderState::_, EffectsList> EffectsByState;
        typedef Map<String, EffectsList> EffectsByString;

        typedef Map<String, ShadersEffectParameter::ptr> EffectParametersMap;
        typedef List<ShadersEffectParameter::ptr> EffectParametersList;

        typedef List<EffectCreator::ptr> EffectCreatorList;
        typedef Map<String, EffectCreator::ptr> EffectCreatorMap;

    public:

        ShadersEffectManager();
        virtual ~ShadersEffectManager();

    public:

        void OnInit();
        void OnDeinit();

    protected:

        virtual _OnInit();
        virtual _OnDeInit();

    public:
        ShadersEffect::ptr createEffect(const String& name, const String& file, const String& creator = String("CgEffectCreator"));

        ShadersEffect::ptr getEffectByName(const String& name);

        const EffectsList& getEffects() const;
        EffectsList& getEffects();

        const EffectsMap& getEffectsByName() const;
        EffectsMap& getEffectsByName();

        void destroyEffect(const String& name);
        void clearEffects();

    public:

        void selectEffectForRender(const String& name, RenderState::_ state);

        void unselectEffectForRender(const String& name, RenderState::_ state);
        void unselectEffect(const String& name);

        bool isEffectSelectedForRender(const String& name, RenderState::_ state) const;

    public:

        ShadersEffectParameter::ptr createGlobalParameter(const String& name, ShadersEffectParameter::Type type, const String& creator = String("CgEffectCreator"));
        ShadersEffectParameter::ptr getGlobalParameterByName(const String& name);

        const EffectParametersList& getGlobalParameters() const;
        EffectParametersList& getGlobalParameters();

        const EffectParametersMap& getGlobalParametersByName() const;
        EffectParametersMap& getGlobalParametersByName();

        void destroyGlobalParameter(const String& name);
        void clearGlobalParameters();

    public:

        void setWorldMatrix(const Matrix4F& world);
        void setViewMatrix(const Matrix4F& view);
        void setProjectionMatrix(const Matrix4F& projection);

        void setApplicationTime(float time);
        void setElapsedTime(float time);

        void setGlobalAmbient(const Color& ambient);
        void setMaterial(const UntexturedMaterial& umaterial);

    public:

        bool isInitialized() const;

    protected:

        bool initialized;

        EffectParametersMap globalParametersByName;
        EffectParametersList globalParametersList;

        EffectsMap effectsByName;
        EffectsByString effectsByCreator;
        EffectsList effectsList;
        EffectsByState effectsSelected;

        EffectCreatorList creators;
        EffectCreatorMap creatorsByName;
    };
}
*/
#endif
