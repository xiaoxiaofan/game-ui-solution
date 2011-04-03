//
// CDESXml.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESXml__
#define __H_CDESXml__

class CDESTimeLine; 
class CDESXml
{
private:
	IXml2Dex *        mXmlInterface;

public:
	CDESXml();
	~CDESXml();

	bool Initialize(void);  // Must be invoked!!

	bool ReadXMLFile(CDESTimeLine & ioTimeline, const char * inXmlFile);
	bool WriteXMLFile(CDESTimeLine & inTimeline, const char * inXmlFile);
	bool WriteXML(CDESTimeLine & inTimeline, BSTR * outXMLString);
	bool WriteGrfFile(IUnknown * inGraph, const char * inFileName);
};

#endif // __H_CDESXml__