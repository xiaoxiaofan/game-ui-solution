#include "UnKnowLiveSource.h"
#include "LiveSource.h"


UnKnowLiveSource::UnKnowLiveSource(UsageEnvironment& env,int stream_id)
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
	LiveSource::Instance().getData(fTo);
	nextTask()  = envir().taskScheduler().scheduleDelayedTask( 0, (TaskFunc*)afterGetting,
		this);
}
