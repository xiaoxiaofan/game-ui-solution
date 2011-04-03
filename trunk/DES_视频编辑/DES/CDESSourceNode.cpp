//
// CDESSourceNode.cpp
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#include "stdafx.h"
#include "CDESSourceNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////
CDESSourceNode::CDESSourceNode()
{
	mVideoSource  = NULL;
	mAudioSource  = NULL;
	mVideoEffect  = NULL; 
}

CDESSourceNode::~CDESSourceNode()
{
	if (mVideoSource != NULL)
	{
		delete mVideoSource;
		mVideoSource = NULL;
	}
	if (mAudioSource != NULL)
	{
		delete mAudioSource;
		mAudioSource = NULL;
	}
	if (mVideoEffect != NULL)
	{
		delete mVideoEffect;
		mVideoEffect = NULL;
	}

}