#ifndef UnKnowLiveSource_h__
#define UnKnowLiveSource_h__
#include "FramedSource.hh"
#include "UsageEnvironment.hh"

class UnKnowLiveSource : public FramedSource
{
public:
	UnKnowLiveSource(UsageEnvironment& env,int stream_id = 0);
	~UnKnowLiveSource(void);

private:
	void doGetNextFrame();

	void deliverFrame();
};


#endif // UnKnowLiveSource_h__


