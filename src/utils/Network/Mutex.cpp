#include "Mutex.h"
#include <SDL_thread.h>

Mutex::Mutex()
	: mutex(SDL_CreateMutex())
	, blocked(false)
{
	if (!mutex) {
		Log::e("Mutex::Couldn't create MUTEX");
	}
}

Mutex::~Mutex()
{
	if (blocked == true) {
		//Log::e("MUTEX ACTIVO - Eliminacion no permitida");
	}
	SDL_DestroyMutex(mutex);
}

void Mutex::lock ()
{
	SDL_LockMutex(mutex);
	blocked = true;
}

void Mutex::unlock ()
{
	blocked = false;
	SDL_UnlockMutex(mutex);
}
