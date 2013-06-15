/*
    This application is an example on how to use the Thread
    system. This is a basic application of producer/customer.
*/

#include <Main.h>

#include <Thread.h>
#include <ThreadMutex.h>
#include <ThreadCondition.h>
#include <ThreadManager.h>

#include <iostream>
#include <unistd.h>
#include <stdint.h>

using namespace APro;

#define NB_CLIENTS 20
#define INITIAL_STOCK 200

typedef struct
{
    int stock;

    Thread::ptr thread_store;
    Thread::ptr thread_clients[NB_CLIENTS];

    ThreadMutex::ptr mutex_stock;
    ThreadCondition::ptr cond_stock;
    ThreadCondition::ptr cond_clients;
} store_t;

static store_t store =
{
    .stock = INITIAL_STOCK
};

bool continue_storing = true;

/* Fonction pour tirer un nombre au sort entre 0 et max. */
static int get_random (int max)
{
   double val;

   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}

/* Fonction pour le thread du magasin. */
static void fn_store (void * p_data)
{
   while (continue_storing)
   {
      /* Debut de la zone protegee. */
      store.mutex_stock->lock();
      store.cond_stock->wait(store.mutex_stock);

      char buffer[2];
      Console::get() << "\nDo you want to quit ? [O/N]";
      std::cin >> buffer;

      if(buffer[0] == 'O')
        continue_storing = false;

      store.stock = INITIAL_STOCK;
      Console::get() << "\nRemplissage du stock de " << store.stock << " articles !";

      store.cond_stock->signal();
      store.mutex_stock->unlock();
      /* Fin de la zone protegee. */
   }
}

/* Fonction pour les threads des clients. */
static void fn_clients (void * p_data)
{
   int nb = (intptr_t) p_data;

   while (continue_storing)
   {
      int val = get_random (6);


      sleep (get_random (3));

      /* Debut de la zone protegee. */
      store.mutex_stock->lock();

      if (val > store.stock)
      {
         store.cond_stock->signal();
         store.cond_clients->wait(store.mutex_stock);
      }

      store.stock = store.stock - val;
      Console::get() << "\nClient " << nb << " prend " << val << " du stock, reste " << store.stock << " en stock !";

      store.mutex_stock->unlock();
      /* Fin de la zone protegee. */
   }
}

int main(int argc, const char* argv[])
{
    try
    {
        Main& m_main = Main::get().init(argc, argv);

        Console::get() << "\n\n\nTesting threads"
                           << "\n---------------";

        Console::get() << "\nCreating store thread";
        store.thread_store = m_main.getThreadManager().createThread(String("ThreadStore"));

        if(store.thread_store.isNull())
        {
            Console::get() << "\nCreating store thread failed ! exiting";
            goto end_goto;
        }
        store.thread_store->setCallback(fn_store, NULL);

        Console::get() << "\nCreating clients threads";
        for(int i = 0; i < NB_CLIENTS; ++i)
        {
            store.thread_clients[i] = m_main.getThreadManager().createThread(String("ThreadClient") + String::toString(i));

            if(!store.thread_clients[i].isNull())
            {
                store.thread_clients[i]->setCallback(fn_clients, (void *) (intptr_t) i);
            }
        }

        Console::get() << "\nCreating mutex";
        store.mutex_stock = Main::get().getThreadManager().createMutex();
        Console::get() << "\nCreating condition";
        store.cond_clients = Main::get().getThreadManager().createCondition();
        store.cond_stock = Main::get().getThreadManager().createCondition();

        Console::get() << "\nRunning";
        store.thread_store->run();
        for(int i =  0; i < NB_CLIENTS; ++i)
        {
            store.thread_clients[i]->run();
        }

        Main::get().getThreadManager().stopAllThreads();

end_goto:
        m_main.clear();
    }
    catch(Exception const&  e)
    {
        Console::get() << "\nException launched : " << e.getFullDescription().c_str();
    }

    // Report log and leaks
    Console::get().dump("testapplication.log");
    MemoryManager::get().dump("testapplication.leaks");

    Console::get() << "\n";

    return 0;
}
