////////////////////////////////////////////////////////////
/** @file Renderer.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/05/2013
 *
 *  Defines the Renderer class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRORENDERER_H
#define APRORENDERER_H

#include "Platform.h"
#include "SharedPointer.h"
#include "ThreadSafe.h"
#include "Implementable.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Renderer
     *  @ingroup Rendering
     *  @brief Objects that is used to render numerous Scene in
     *  a Scene Manager.
     *  @details The Renderer is implementable and is external-API
     *  dependant. Also, it is thread-safe.
     *  The Renderer can render objects in multiple steps. By default,
     *  there are 3 steps : <br />
     *  <ul><li>PreRender</li>
     *  <li>MainRender</li>
     *  <li>PostRender</li>
     *  The Pre and Post Render shouldn't be deactivated, unless you know
     *  what you're doing.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Renderer : public Implementable<RendererImplementation>,
                              public ThreadSafe
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Renderer)

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        Renderer();

        ////////////////////////////////////////////////////////////
        /** Copy Constructor.
         *  @note The renderer is copied but not started. You must
         *  start it manually.
        **/
        ////////////////////////////////////////////////////////////
        Renderer(const Renderer& other);

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~Renderer();

        ////////////////////////////////////////////////////////////
        /** Init the implementation object.
         *  @see Implementable::initImplementation
        **/
        ////////////////////////////////////////////////////////////
        void initImplementation();

    public:

        ////////////////////////////////////////////////////////////
        /**
         * @name Render Steps functions
         * @{

           Rendering is organized in 20 steps, that can be fully customized. You can add functions
           that will be executed during the rendering process at given step, but there are no way
           to know in wich order will the function be executed in the step.

           You can activate or deactivate rendering Steps. So, you can prepare a step for some effect
           and just switch to it whenever you want.

           By default, only steps 1, 10 and 20 are activated during the start process.

        **/
        ////////////////////////////////////////////////////////////

        class RenderStep
        {
            public: enum t
            {
                Invalid     = 0, ///< Invalid Pre-Step.
                PreRender   = 1, ///< PreRender Step.
                MainRender  = 10, ///< Main render step. This is the principal step of the rendering process.
                PostRender  = 20, ///< Post Rendering step. Generally switch framebuffer and things.
                InvalidPost = 21 ///< Invalid post step.
            };
        };

        typedef void (*RenderStepFunc) (Renderer*);///< Functions that will be called by steps must follow this signature.
        typedef Map<int, Array<RenderStepFunc> > RenderStepFuncMap;///< Function map.
        typedef Map<int, bool> RenderStepActivated;

    protected:

        RenderStepFuncMap   render_step_func_map;///< Functions map
        RenderStepActivated render_step_activated;///< Steps activated

    public:

        void addStepFunction(int step, RenderStepFunc func);
        void removeStepFunction(int step, RenderStepFunc func);

        void clearStepFunctions(int step);
        void clearStepFunctions();

        bool isStepFunction(int step, RenderStepFunc func) const;
        bool isStepValid(int step) const;

        bool isStepActivated(int step) const;
        void activateStep(int step, bool state);

        void resetStepState();// Reset step state to false but the 3 main steps
        void deactivateEveryStep();// Set everry steps to false

        ////////////////////////////////////////////////////////////
        /**
         *  @}
        **/
        ////////////////////////////////////////////////////////////

    public:

        /*
            ---------- General Rendering Function

            This function is used to render the scenes in the scene manager of the renderer. Every scenes
            are drawed, or you can specify wich scene the renderer should draw.
        */

        bool render();// Render every scenes
        bool render(const String& scene_name);// Render just one scene
        bool render(const Scene::ptr& scene_pointer); // Render just one scene

        bool start();// Initialize the renderer
        bool shutdown();// Shutdown the renderer

        bool isStarted() const;// Renderer is started ?
        void reset();// Reset the renderer

    protected:

        bool started;

    protected:

        /*
            ---------- The Scene Manager Object

            This object store every informations about the scenes that will be drawed by
            the renderer.
        */

        SceneManager scene_manager;

    public:

        SceneManager& getSceneManager();
        const SceneManager& getSceneManager() const;

    };
}

#endif
