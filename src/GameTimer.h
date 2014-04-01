#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_

#include <SDL2/SDL.h>

class GameTimer {
public:
	GameTimer();
	~GameTimer();
	
	void start();
	void stop();
	void restart();
	unsigned int getElapsedTime();
	
private:
	bool m_isStarted;
	unsigned int m_startTime;
	unsigned int m_stopTime;
};

#endif // _GAMETIMER_H_