#pragma once
class UnKnowLiveSource : public FramedSource
{
public:
	UnKnowLiveSource(UsageEnvironment& env,int stream_id = 0);
	~UnKnowLiveSource(void);

	void doGetNextFrame();

	void deliverFrame();
};

