#include "GameTimer.h"
#include <Windows.h>
#include <math.h>
GameTimer::GameTimer(void)
	:mSecondsPerCount(0),mDeltaTime(-1.0),
	 mPausedTime(0),mStopTime(0),mPrevTime(0),
	 mCurrTime(0)
{
	__int64 countsPerSecond;
	QueryPerformanceFrequency(
		reinterpret_cast<LARGE_INTEGER*>(&countsPerSecond));
	mSecondsPerCount = 1.0f/countsPerSecond;
}
void GameTimer::Reset()
{
	__int64 mCurrTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mCurrTime));
	mBaseTime = mCurrTime;
	mStopTime = 0;
	mPrevTime = mCurrTime;
	mStopped = false;
}
void GameTimer::Tick()
{
	if(mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mCurrTime));
	mDeltaTime = (mCurrTime - mPrevTime);
	mPrevTime = mCurrTime;
	mDeltaTime = max(mDeltaTime,0.0);
}
void GameTimer::Stop()
{
	if(mStopped)return;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mStopTime));
	mStopped = true;
}
void GameTimer::Start()
{
	if(!mStopped)return;
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));
	mPausedTime+=startTime-mStopTime;
	mPrevTime = startTime;
	mStopTime = 0;
	mStopped = false;

}
double GameTimer::GetGameTime()const
{
	if(mStopped)
		return (mStopTime-mBaseTime)*mSecondsPerCount;
	else
		return (mCurrTime-mBaseTime-mPausedTime)*mSecondsPerCount;
}
double GameTimer::GetDeltaTime()const
{
	return mDeltaTime*mSecondsPerCount;
}
GameTimer::~GameTimer(void)
{
}
