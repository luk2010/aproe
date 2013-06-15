////////////////////////////////////////////////////////////
/** @file Renderer.cpp
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 05/05/2013
 *
 *  Implements the Renderer class.
 *
**/
////////////////////////////////////////////////////////////
#include "Console.h"
#include "Renderer.h"

#include "ThreadMutex.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{
    Renderer::Renderer()
        : Implementable(String("APro::Renderer")), ThreadSafe()
    {
        createImplementation();
    }

    Renderer::Renderer(const Renderer& other)
        : Implementable(String("APro::Renderer")), ThreadSafe(),
        render_step_func_map(other.render_step_func_map), render_step_activated(other.render_step_activated),
        scene_manager(other.scene_manager),
        started(false)
    {

    }

    Renderer::~Renderer()
    {
        if(started)
        {
            reset();
        }
    }

    void Renderer::initImplementation()
    {
        Implementable::implement->renderer = this;
    }

    void Renderer::addStepFunction(int step, Renderer::RenderStepFunc func)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(isStepValid(step))
        {
            if(!isStepFunction(step, func))
            {
                render_step_func_map[step] = func;
            }
            else
            {
                Console::get() << "\n[Renderer]{addStepFunction} Function \"" << (int) func << "\" already set in step \"" << step << "\".";
            }
        }
        else
        {
            Console::get() << "\n[Renderer]{addStepFunction} Step \"" << step << "\" invalid.";
        }
    }

    void Renderer::removeStepFunction(int step, Renderer::RenderStepFunc func)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(isStepValid(step))
        {
            if(isStepFunction(step, func))
            {
                render_step_func_map[step].erase(render_step_func_map[step].find(func));
            }
            else
            {
                Console::get() << "\n[Renderer]{removeStepFunction} Function \"" << (int) func << "\" not part of step \"" << step << "\".";
            }
        }
        else
        {
            Console::get() << "\n[Renderer]{removeStepFunction} Step \"" << step << "\" invalid.";
        }
    }

    void Renderer::clearStepFunctions(int step)
    {
        if(isStepValid(step))
        {
            render_step_func_map[step].clear();
        }
        else
        {
            Console::get() << "\n[Renderer]{clearStepFunctions} Step \"" << step << "\" invalid.";
        }
    }

    void Renderer::clearStepFunctions()
    {
        render_step_func_map.clear();
    }

    bool Renderer::isStepFunction(int step, Renderer::RenderStepFunc func) const
    {
        if(isStepValid(step))
        {
            return (render_step_func_map[step].find(func) > -1);
        }
    }

    bool Renderer::isStepValid(int step) const
    {
        return step < RenderStep::InvalidPost && step > RenderStep::Invalid;
    }

    bool Renderer::isStepActivated(int step) const
    {
        if(isStepValid(step))
        {
            return render_step_activated[step];
        }
        else
        {
            return false;
        }
    }

    void Renderer::activateStep(int step, bool state)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(isStepValid(step))
        {
            render_step_activated[step] = state;
        }
        else
        {
            Console::get() << "\n[Renderer]{activateStep} Step \"" << step << "\" invalid.";
        }
    }

    void Renderer::resetStepState()
    {
        APRO_THREADSAFE_AUTOLOCK

        for(int i = RenderStep::PreRender; i < RenderStep::InvalidPost; ++i)
        {
            activateStep(i, false);
        }

        /* Activate the 3 main steps. */
        activateStep(RenderStep::PreRender, true);
        activateStep(RenderStep::MainRender, true);
        activateStep(RenderStep::PostRender, true);
    }

    void Renderer::deactivateEveryStep()
    {
        APRO_THREADSAFE_AUTOLOCK

        for(int i = RenderStep::PreRender; i < RenderStep::InvalidPost; ++i)
        {
            activateStep(i, false);
        }
    }

    bool Renderer::render()
    {
        APRO_THREADSAFE_AUTOLOCK

        if(Implementable::implement.isNull())
        {
            return false;
        }

        if(started)
        {
            bool end_state = true;
            /* For each scene we render every step. */
            for(unsigned int i = 0; i < scene_manager.getScenes().size(); ++i)
            {
                if(!render(scene_manager.getScene(i)))
                {
                    end_state = false;
                }
            }

            return end_state;
        }

        return false;
    }

    bool Renderer::render(const String& scene_name)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(Implementable::implement.isNull())
        {
            return false;
        }

        if(!started)
        {
            return false;
        }

        Scene::ptr scene = scene_manager.getScene(scene_name);
        if(!scene.isNull())
        {
            return render(scene);
        }
        else
        {
            return false;
        }
    }

    bool Renderer::render(const Scene::ptr& scene_pointer)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(Implementable::implement.isNull())
        {
            return false;
        }

        /* Currently bypass, don't know how we will render for now. */
        return true;
    }

    bool Renderer::start()
    {
        APRO_THREADSAFE_AUTOLOCK

        /* We start the renderer by setting up environnments settings. */
        if(Implementable::implement.isNull())
        {
            return false;
        }
        else
        {
            bool start_ok = true;
            if(!Implementable::implement->setupEnvironment())
                start_ok = false;

            resetStepState();
        }
    }

    bool Renderer::shutdown()
    {
        APRO_THREADSAFE_AUTOLOCK

        if(started && !Implementable::implement.isNull())
        {
            deactivateEveryStep();
            clearStepFunctions();
            return true;
        }

        return false;
    }

    bool Renderer::isStarted() const
    {
        return started;
    }

    void Renderer::reset()
    {
        APRO_THREADSAFE_AUTOLOCK

        if(started)
        {
            shutdown();
        }

        scene_manager.clear();
    }

    SceneManager& Renderer::getSceneManager()
    {
        return scene_manager;
    }

    const SceneManager& Renderer::getSceneManager() const
    {
        return scene_manager;
    }
}
