//
// CDESPropertySetter.cpp
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
#include "streams.h"
#include <qedit.h>
#include "CDESPropertySetter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
CDESPropertySetter::CDESPropertySetter()
{
	mSetter = NULL;
}

CDESPropertySetter::~CDESPropertySetter()
{
	ReleaseSelf();
}

void CDESPropertySetter::ReleaseSelf(void)
{
	if (mSetter != NULL)
	{
		mSetter->Release();
		mSetter = NULL;
	}
}

bool CDESPropertySetter::Initialize(void)
{
	if (mSetter == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_PropertySetter, 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									IID_IPropertySetter, 
									(void**) &mSetter);
		if (FAILED(hr))
		{
			mSetter = NULL;
			return false;
		}
	}
	return true;
}

IPropertySetter * CDESPropertySetter::GetPropertySetter(void)
{
	return mSetter;
}

bool CDESPropertySetter::Attach(IPropertySetter * inSetter)
{
	ReleaseSelf();
	if (inSetter != NULL)
	{
		// OutStanding reference
		inSetter->AddRef();
	}
	mSetter = inSetter;
	return true;
}

bool CDESPropertySetter::AddProp(DEXTER_PARAM inParam, DEXTER_VALUE * inValue)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->AddProp(inParam, inValue);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::ClearProps(void)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->ClearProps();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::CloneProps(CDESPropertySetter & outSetter, 
									REFERENCE_TIME inStart, 
									REFERENCE_TIME inStop)
{
	if (mSetter)
	{
		IPropertySetter * pSetter = NULL;
		HRESULT hr = mSetter->CloneProps(&pSetter, inStart, inStop);
		if (SUCCEEDED(hr))
		{
			outSetter.Attach(pSetter);
			pSetter->Release();
			return true;
		}
	}
	return false;
}

bool CDESPropertySetter::GetProps(LONG * outCount, 
								  DEXTER_PARAM ** outParamArray, 
								  DEXTER_VALUE ** outValueArray)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->GetProps(outCount, outParamArray, outValueArray);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::FreeProps(LONG inCount, 
								   DEXTER_PARAM * inParamArray, 
								   DEXTER_VALUE * inValueArray)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->FreeProps(inCount, inParamArray, inValueArray);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::SaveToBlob(LONG * outSize, BYTE ** outData)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->SaveToBlob(outSize, outData);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::LoadFromBlob(LONG inSize, BYTE * inData)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->LoadFromBlob(inSize, inData);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::LoadXML(IUnknown * inXml)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->LoadXML(inXml);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::PrintXML(char * outXML, int inSize, 
								  int * outPrinted, int inIndent)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->PrintXML(outXML, inSize, outPrinted, inIndent);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// Called by DES, an application will not normally call this method
bool CDESPropertySetter::SetProps(IUnknown * inTarget, REFERENCE_TIME inTime)
{
	if (mSetter)
	{
		HRESULT hr = mSetter->SetProps(inTarget, inTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// An easy way to set properties
bool CDESPropertySetter::AddProperty(LPOLESTR inParamName, double inValue, 
									 BOOL inIsJump, double inStartTime)
{
	if (mSetter)
	{
		DWORD  dwInterp = inIsJump ? DEXTERF_JUMP : DEXTERF_INTERPOLATE;
		DEXTER_PARAM  Param;
		Param.Name    = inParamName;
		Param.nValues = 1;          // how many values we want to set
		DEXTER_VALUE  Value;
		memset(&Value, 0, sizeof(Value));
		VariantClear(&Value.v);
		V_R8(&Value.v) = inValue; // Param value
		V_VT(&Value.v) = VT_R8;
		Value.rt       = inStartTime * UNITS;
		Value.dwInterp = dwInterp;

		HRESULT hr = mSetter->AddProp(Param, &Value);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESPropertySetter::AddProperty(LPOLESTR inParamName, LPOLESTR inValue, 
									 BOOL inIsJump, double inStartTime)
{
	if (mSetter)
	{
		DWORD  dwInterp = inIsJump ? DEXTERF_JUMP : DEXTERF_INTERPOLATE;
		DEXTER_PARAM  Param;
		Param.Name    = inParamName;
		Param.nValues = 1;             // how many values we want to set
		DEXTER_VALUE  Value;
		memset(&Value, 0, sizeof(Value));
		VariantClear(&Value.v );
		V_VT(&Value.v)    = VT_BSTR;
		V_BSTR(&Value.v)  = inValue; // Param value
		Value.rt          = inStartTime * UNITS;
		Value.dwInterp    = dwInterp;

		HRESULT hr = mSetter->AddProp(Param, &Value);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}
