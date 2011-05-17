#include "live.h"
#include "UsageEnvironment.hh"
#include "BasicUsageEnvironment.hh"
#include "RTSPServer.hh"
#include "NetAddress.hh"
#include "DynamicRTSPServer.hh"
#include "LiveSource.h"
LIVE_API unsigned __stdcall ServerConnect(void *pv)
{
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = new UserAuthenticationDatabase;
	authDB->addUserRecord("1", "1");

	RTSPServer* rtspServer;
	portNumBits rtspServerPortNum = 554;
	rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	if (rtspServer == NULL) {
		rtspServerPortNum = 8554;
		rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
	}

	 env->taskScheduler().doEventLoop(); // does not return
	 return 1;
}

LIVE_API void SetLiveData(unsigned char* pData,int nSize)
{
	LiveSource::Instance().setData(pData,nSize);
}


