/**
    This program test main fuctionnalities of the engine. Please buil and launch it once before
    you use the engine.
**/

#include <Main.h>
#include <Implementation.h>
#include <FileSystem.h>
#include <FileStream.h>
#include <WindowManager.h>

#include <unistd.h>

using namespace APro;

int main(int argc, const char* argv[])
{
    try
    {
        // Initialize the engine
        Main& m_main = Main::get().init(argc, argv);

        // Give current infos about current implementations
        m_main.getImplementationStore().drawInfos();


        // Assert we have a Window implementation
        if(m_main.getImplementationStore().find(Variant(String("APro::Window"))).isNull())
        {
            Console::get() << "\nSorry, no Window System implementation found ! Exiting.";
        }
        else
        {
            // On cree une fenetre de 1024x768

            WindowManager& wm = m_main.getWindowManager();
            Window::ptr window = wm.create(String("MyWindow"), String("First Window"), String("1024x768"), false);
            if(!window.isNull())
            {
                Console::get() << window->explainEvents();
                window->show();

              // On cree un context

                Context::ptr ctxt = AProNew(1, Context) ();
                ctxt->setWindow(window.getPtr());
/*
          NOT IMPLEMENTED YET

            // On cree un renderer

            Renderer::ptr renderer = m_main.getRendererFactoryManager().getFirstFactory()->create();
            SceneManager& sm = renderer->getSceneManager();

            // On cree une nouvelle scene

            Scene::ptr scene1 = sm.createScene(String("MyScene"));
            scene1->getGlobalLight().setAmbient(Color((unsigned char) 150, 150, 150, 255);

            // On ajoute le viewport a la scene

            ViewPort::ptr vps = scene1->addViewPort(String("DefaultViewPort"), ctxt->getDefaultViewPort());

            // On ajoute une camera associe au viewport

            Camera::ptr camera1 = renderer->createCamera(String("MyCamera"), Vector3F(0,0,0), Vector3F(1,1,1));
            camera1->associateViewPort(vps);

            // On ajoute la camera

            scene1->addSceneNode(scene1->createSceneNode(String("CameraSceneNode"), camera1, Vector3F(0,0,0)));

            // On cree un cube de 5 unites de cote

            MeshManager& mm = renderer->getMeshManager();
            Mesh::ptr cube = mm.createCube(5);

            // On rajoute un node ayant pour mesh le cube

            SceneNode::ptr msn = scene1->addSceneNode(scene1->createSceneNode(String("CubeSceneNode"), cube, Vector3F(10, 10, 10)));
            msn->setObject(Object::TypeStatic);
*/
            // On loop jusqu'a ce que la fenetre soit detruite par l'utilisateur
            while (window->isValid())
            {

                //renderer->render();

            }

            // On peut nettoyr le renderer. Les scenes et les meshs, ainsi que les cameras sont detruits pendant le processus.
            //renderer->clear();

            }
        }

        // Clear the engine i.e. end of the program.
        m_main.clear();
    }

    catch (Exception& e)
    {
        Console::get() << "\nException launched : " << e.getFullDescription().c_str();
    }

    // Report log and leaks
    Console::get().dump("testapplication.log");
    MemoryManager::get().dump("testapplication.leaks");

    Console::get() << "\n";

    return 0;
}
