#ifndef THREAD_H_
#define THREAD_H_
#include <string>
#include <SDL_thread.h>
#include "Mutex.h"

class Thread
{
public:
	Thread ();
	Thread (std::string nombre, int (*)(void*));
	Thread (std::string nombre, int (*)(void*), void* data);

	void detach();
	int wait();  // Bloquea hasta que el thread termine, y luego pasa el retorno/excepcion del thread.

private:
	int retval;
	SDL_Thread* myThread;
	std::exception_ptr thread_exc;

};

#endif /* THREAD_H_ */
