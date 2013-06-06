#ifndef GAME_TIMER_H
#define GAME_TIMER_H
class GameTimer
{
public:
	GameTimer();
	double GetGameTime()const; // in seconds
	double GetDeltaTime()const; // in seconds
	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop(); // Call when paused.
	void Tick(); // Call every frame.
	~GameTimer();
private:
	double mSecondsPerCount;
	double mDeltaTime;
	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;
	bool mStopped;
};
#endif
