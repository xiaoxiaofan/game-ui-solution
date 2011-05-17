#ifndef UnKnowLiveSource_h__
#define UnKnowLiveSource_h__
#include "UsageEnvironment.hh"
#include "FramedSource.hh"

class UnKnowLiveSource : public FramedSource
{
public:
	UnKnowLiveSource(UsageEnvironment& env,int stream_id = 0);
	~UnKnowLiveSource(void);

	void doGetNextFrame();

	void deliverFrame();
};

#endif // UnKnowLiveSource_h__


