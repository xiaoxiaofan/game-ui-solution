//
// CDESPropertySetter.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESPropertySetter__
#define __H_CDESPropertySetter__

class CDESPropertySetter
{
private:
	IPropertySetter *        mSetter;

public:
	CDESPropertySetter();
	~CDESPropertySetter();

	IPropertySetter * GetPropertySetter(void); // NOT outstanding referencc!!
	bool Attach(IPropertySetter * inSetter);
	bool Initialize(void);

	bool AddProp(DEXTER_PARAM inParam, DEXTER_VALUE * inValue);
	bool ClearProps(void);
	bool CloneProps(CDESPropertySetter & outSetter, REFERENCE_TIME inStart, REFERENCE_TIME inStop);
	bool GetProps(LONG * outCount, DEXTER_PARAM ** outParamArray, DEXTER_VALUE ** outValueArray);
	bool FreeProps(LONG inCount, DEXTER_PARAM * inParamArray, DEXTER_VALUE * inValueArray);
	bool SaveToBlob(LONG * outSize, BYTE ** outData);
	bool LoadFromBlob(LONG inSize, BYTE * inData);
	bool LoadXML(IUnknown * inXml);
	bool PrintXML(char * outXML, int inSize, int * outPrinted, int inIndent);
	// Called by DES, an application will not normally call this method
	bool SetProps(IUnknown * inTarget, REFERENCE_TIME inTime);

	// An easy way to set properties
	bool AddProperty(LPOLESTR inParamName, double inValue, BOOL inIsJump, double inStartTime = 0);
	bool AddProperty(LPOLESTR inParamName, LPOLESTR inValue, BOOL inIsJump, double inStartTime = 0);

private:
	void ReleaseSelf(void);
};

#endif // __H_CDESPropertySetter__