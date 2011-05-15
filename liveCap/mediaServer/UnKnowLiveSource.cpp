#include "UnKnowLiveSource.h"
#include "LiveSource.h"


UnKnowLiveSource::UnKnowLiveSource(UsageEnvironment& env)
	: FramedSource(env)
{

}


UnKnowLiveSource::~UnKnowLiveSource(void)
{
}

void UnKnowLiveSource::doGetNextFrame()
{
	deliverFrame();
}

void UnKnowLiveSource::deliverFrame()
{
	LiveSource::getData(fTo);
	nextTask()  = envir().taskScheduler().scheduleDelayedTask( 0, (TaskFunc*)afterGetting,
		this);
}
