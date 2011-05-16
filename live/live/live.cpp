#include "live.h"
#include "UsageEnvironment.hh"
#include "BasicUsageEnvironment.hh"
#include "RTSPServer.hh"
#include "NetAddress.hh"
#include "DynamicRTSPServer.hh"

LIVE_API void ServerConnect()
{
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = new UserAuthenticationDatabase;
	authDB->addUserRecord("1", "love");

	RTSPServer* rtspServer;
	portNumBits rtspServerPortNum = 554;
	rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	if (rtspServer == NULL) {
		rtspServerPortNum = 8554;
		rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	}

	 env->taskScheduler().doEventLoop(); // does not return
}

LIVE_API void SetLiveData(unsigned char* pData,int nSize)
{
	//LiveSource::Instance().setData(pData,nSize);
}


