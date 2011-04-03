//
// UDESUtils.cpp
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
#include <streams.h>
#include <qedit.h>
#include "UDESUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////
CTypeGuidList UDESUtils::sEffectList;
CTypeGuidList UDESUtils::sTransitionList;

WCHAR UDESUtils::sMsEffectProgIDs[][100] = 
{
	OLESTR("DXImageTransform.Microsoft.Alpha"),
	OLESTR("DXImageTransform.Microsoft.BasicImage"),
	OLESTR("DXImageTransform.Microsoft.Blur"),
	OLESTR("DXImageTransform.Microsoft.Chroma"),
	OLESTR("DXImageTransform.Microsoft.Compositor"),
	OLESTR("DXImageTransform.Microsoft.DropShadow"),
	OLESTR("DXImageTransform.Microsoft.Emboss"),
	OLESTR("DXImageTransform.Microsoft.Engrave"),
	OLESTR("DXImageTransform.Microsoft.Glow"),
	OLESTR("DXImageTransform.Microsoft.Light"),
	OLESTR("DXImageTransform.Microsoft.MaskFilter"),
	OLESTR("DXImageTransform.Microsoft.Matrix"),
	OLESTR("DXImageTransform.Microsoft.MotionBlur"),
	OLESTR("DXImageTransform.Microsoft.Shadow"),
	OLESTR("DXImageTransform.Microsoft.Wave"),
	// DES Video Effects 
	OLESTR("qedit.DxtAlphaSetter.1")
};

WCHAR UDESUtils::sMsTransitionProgIDs[][100] =
{
	OLESTR("DXImageTransform.Microsoft.Barn"),
	OLESTR("DXImageTransform.Microsoft.Blinds"),
	OLESTR("DXImageTransform.Microsoft.CheckerBoard"),
	OLESTR("DXImageTransform.Microsoft.Fade"),
	OLESTR("DXImageTransform.Microsoft.GradientWipe"),
	OLESTR("DXImageTransform.Microsoft.Inset"),
	OLESTR("DXImageTransform.Microsoft.Iris"),
	OLESTR("DXImageTransform.Microsoft.Pixelate"),
	OLESTR("DXImageTransform.Microsoft.RadialWipe"),
	OLESTR("DXImageTransform.Microsoft.RandomBars"),
	OLESTR("DXImageTransform.Microsoft.RandomDissolve"),
	OLESTR("DXImageTransform.Microsoft.Slide"),
	OLESTR("DXImageTransform.Microsoft.Spiral"),
	OLESTR("DXImageTransform.Microsoft.Stretch"),
	OLESTR("DXImageTransform.Microsoft.Strips"),
	OLESTR("DXImageTransform.Microsoft.Wheel"),
	OLESTR("DXImageTransform.Microsoft.Zigzag"),
	// DES Video Transitions
	OLESTR("qedit.DxtJpeg.1"),
	OLESTR("qedit.DxtCompositor.1"),
	OLESTR("qedit.DxtKey.1")
};


bool UDESUtils::QueryLocalAvailableEffects(void)
{
	sEffectList.RemoveAll();
	return QueryLocalGuids(CLSID_VideoEffects1Category, sEffectList);
}

bool UDESUtils::QueryLocalAvailableTransitions(void)
{
	sTransitionList.RemoveAll();
	return QueryLocalGuids(CLSID_VideoEffects2Category, sTransitionList);
}

bool UDESUtils::QueryLocalGuids(CLSID inCategory, CTypeGuidList & inList)
{
	ICreateDevEnum * pCreateDevEnum = NULL;
	IEnumMoniker *   pEnumMoniker   = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, 
								NULL, 
								CLSCTX_INPROC_SERVER,
								IID_ICreateDevEnum, 
								(void**) &pCreateDevEnum);
	bool pass = SUCCEEDED(hr) ? true : false;
	if (pass)
	{
		hr = pCreateDevEnum->CreateClassEnumerator(inCategory, &pEnumMoniker, 0);              
		pass = SUCCEEDED(hr) ? true : false;
	}

	if (pass)
	{
		ULONG      cFetched = 0;
		IMoniker * pMoniker = NULL;
		while (S_OK == pEnumMoniker->Next(1, &pMoniker, &cFetched) && cFetched == 1)
		{
			IPropertyBag * pBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if (SUCCEEDED(hr))
			{
				VARIANT  var1, var2;
				var1.vt = var2.vt = VT_BSTR;
				hr = pBag->Read(OLESTR("FriendlyName"), &var1, NULL);
				if (SUCCEEDED(hr))
				{	
					char       szName[MAX_PATH];
					WideCharToMultiByte(CP_ACP, 0, var1.bstrVal, -1, szName, MAX_PATH, 0, 0);
					SysFreeString(var1.bstrVal);	
					if (SUCCEEDED(pBag->Read(OLESTR("guid"), &var2, NULL)))
					{
						CDESGuid   newGuid;
						newGuid.mFriendlyName = szName;
						CLSIDFromString(var2.bstrVal, &newGuid.mGuid);
						SysFreeString(var2.bstrVal); 
						// Add this new found Guid to the list
					//	inList.AddTail(newGuid);
						////// Only pick out Microsoft Guids /////////////
						if (inCategory == CLSID_VideoEffects1Category)
						{
							if (IsMsEffect(&newGuid.mGuid))
							{
								inList.AddTail(newGuid);
							}
						}
						else
						{
							if (IsMsTransition(&newGuid.mGuid))
							{
								inList.AddTail(newGuid);
							}
						}
						/////////////////////////////////////////////////////
					}
				}
				pBag->Release();
			}
			pMoniker->Release();
		}
	}

	if (pEnumMoniker != NULL)
	{
		pEnumMoniker->Release();
		pEnumMoniker = NULL;
	}
	if (pCreateDevEnum != NULL)
	{
		pCreateDevEnum->Release();
		pCreateDevEnum = NULL;
	}
	return pass;
}

// Determine if the specified Effect or Transition is Microsoft developed for IE
bool UDESUtils::IsMsEffect(GUID * inEffectGuid)
{	
	int  guidCount = sizeof(sMsEffectProgIDs) / sizeof(sMsEffectProgIDs[0]);
	for (int i = 0; i < guidCount; i++)
	{
		CLSID   msClsid;
		HRESULT hr = CLSIDFromProgID(sMsEffectProgIDs[i], &msClsid);
		if (SUCCEEDED(hr) && IsEqualGUID(*inEffectGuid, msClsid))
		{
			return true;
		}
	}
	return false;
}

bool UDESUtils::IsMsTransition(GUID * inTransGuid)
{	
	int  guidCount = sizeof(sMsTransitionProgIDs) / sizeof(sMsTransitionProgIDs[0]);
	for (int i = 0; i < guidCount; i++)
	{
		CLSID   msClsid;
		HRESULT hr = CLSIDFromProgID(sMsTransitionProgIDs[i], &msClsid);
		if (SUCCEEDED(hr) && IsEqualGUID(*inTransGuid, msClsid))
		{
			return true;
		}
	}
	return false;
}