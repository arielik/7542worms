#ifndef CONDITION_H_
#define CONDITION_H_
class SDL_cond;
class Mutex;

class Condition
{
public:
	Condition (Mutex& mutex);
	~Condition ();
	void wait ();
	void signal ();
	void broadcast ();

private:
	Mutex* mutex;
	SDL_cond* cond;
};
#endif
