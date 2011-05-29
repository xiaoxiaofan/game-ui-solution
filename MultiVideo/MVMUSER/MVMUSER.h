/*****************************************************************************************************\
*MVMUSER.lib MVMUSER.dll MultiVMR9.dll
*����MultiVMR9.dll �� system32Ŀ¼�� ����regsvr32 MultiVMR9.dll
*������Ҫ����ͷ�ļ�
*#include <streams.h>
*#include <dshow.h>
*#include <d3d9.h>
��ʼ��CoInitialize(0);
ж��CoUninitialize();
\*****************************************************************************************************/
/*****************************************************************************************************\
*Bug :	CMediaHelper�ļ���Enum����,���ݵ�ָ��LPNAMELIST( vector<wstring>*)����ָ�򲻰����κ����ݵ�
*		vector<wstring>(Ҳ����˵ LPNAMELIST->enpty() == true),ͬʱLPNAMELIST��ָ��� vector<wstring>
*		������������֮ǰ����CMediaHelper::ClearVector( vector<wstring>*);
\*****************************************************************************************************/
/*****************************************************************************************************\
* ����ֵ��HRESULT
* �ɹ�����S_OK;
* ʧ��	������ֵ����ʧ����Ϣ��
* ������SECCEEDED(HRESULT hr) �͡�FAILED(HRESULT hr)���жϷ���ֵ��ʾ�ɹ�����ʧ��
\*****************************************************************************************************/
/*****************************************************************************************************\
 �ṹ,��������
*   AM_MEDIA_TYPE,DirectShow�ṹ,DirectX SDK���и���ϸ������
	typedef struct  _MediaType {
	GUID      majortype;			// ��ý������,MEDIATYPE_Video(��Ƶ)MEDIATYPE_Audio(��Ƶ)��
	GUID      subtype;				// ͼ������(��ɫ�ռ���ɫ��ѹ��),MEDIASUBTYPE_RGB555,MEDIASUBTYPE_RGB32,
									// MEDIASUBTYPE_RGB24,,MEDIASUBTYPE_YUY2 ��
	BOOL      bFixedSizeSamples;	// TRUE ��ʾ�̶�����,FALSE��ʾ���̶�����
	BOOL      bTemporalCompression;	// �Ƿ�ʹ��֡��ѹ��
	ULONG     lSampleSize;			// ������С
	GUID      formattype;			// pbFormat��ָ�ṹ������,�����Ƕ�Ӧ��ϵ
										����						�ṹ
										FORMAT_None					None. 
										FORMAT_DvInfo				DVINFO 
										FORMAT_MPEGVideo			MPEG1VIDEOINFO 
										FORMAT_MPEG2Video			MPEG2VIDEOINFO 
										FORMAT_VideoInfo			VIDEOINFOHEADER 
										FORMAT_VideoInfo2			VIDEOINFOHEADER2 
										FORMAT_WaveFormatEx			WAVEFORMATEX 

	IUnknown  *pUnk;				// ������ʹ��
	ULONG     cbFormat;				// pbFormat��ָ�ṹ��С
	[size_is(cbFormat)]
			BYTE *pbFormat;			// formattype���͵Ľṹ
	} AM_MEDIA_TYPE;

*	VIDEO_STREAM_CONFIG_CAPS,DirectShow�ṹ,DirectX SDK���и���ϸ������
	typedef struct _VIDEO_STREAM_CONFIG_CAPS {
	GUID guid;						// ͬAM_MEDIA_TYPE�ĳ�Աformattype
	ULONG VideoStandard;			// ֧�ֵ���Ƶ��ʽ,����ͬʱ֧�ֶ�����ʽ,ͨ��"|"��������
										AnalogVideo_None       = 0x00000000
										AnalogVideo_NTSC_M     = 0x00000001, 
										AnalogVideo_NTSC_M_J   = 0x00000002,  
										AnalogVideo_NTSC_433   = 0x00000004,
										AnalogVideo_PAL_B      = 0x00000010,
										AnalogVideo_PAL_D      = 0x00000020,
										AnalogVideo_PAL_H      = 0x00000080,
										AnalogVideo_PAL_I      = 0x00000100,
										AnalogVideo_PAL_M      = 0x00000200,
										AnalogVideo_PAL_N      = 0x00000400,
										AnalogVideo_PAL_60     = 0x00000800,
										AnalogVideo_SECAM_B    = 0x00001000,
										AnalogVideo_SECAM_D    = 0x00002000,
										AnalogVideo_SECAM_G    = 0x00004000,
										AnalogVideo_SECAM_H    = 0x00008000,
										AnalogVideo_SECAM_K    = 0x00010000,
										AnalogVideo_SECAM_K1   = 0x00020000,
										AnalogVideo_SECAM_L    = 0x00040000,
										AnalogVideo_SECAM_L1   = 0x00080000,
										AnalogVideo_PAL_N_COMBO = 0x00100000

	SIZE InputSize;					// �����С
	SIZE MinCroppingSize;			// ��С�������
	SIZE MaxCroppingSize;			// ���������
	int CropGranularityX;			// ˮƽ����������ֵ��������(�ȱ�����ԭʼ��С�Ļ�����,�Ը�ֵ������������)
	int CropGranularityY;			// ��ֱ����������ֵ��������
	int CropAlignX;					// Required horizontal alignment of the source rectangle. 
	int CropAlignY;					// Required vertical alignment of the source rectangle
	SIZE MinOutputSize;				// ��С���
	SIZE MaxOutputSize;				// ������
	int OutputGranularityX;			// ˮƽ�������ֵ��������
	int OutputGranularityY;			// ��ֱ�������ֵ��������
	int StretchTapsX;				// Indicates how well the filter can stretch the image horizontally. 
	int StretchTapsY;				// Indicates how well the filter can stretch the image vertically.
	int ShrinkTapsX;				// Indicates how well the filter can shrink the image horizontally.
	int ShrinkTapsY;				// Indicates how well the filter can shrink the image vertically.
	LONGLONG MinFrameInterval;		// ��С֡����(��λUNITS)
	LONGLONG MaxFrameInterval;		// ���֡����(��λUNITS)
	LONG MinBitsPerSecond;			// ��Сλ��(bps)
	LONG MaxBitsPerSecond;			// ���λ��(bps)
	} VIDEO_STREAM_CONFIG_CAPS;
*	D3DFORMAT			Direct3D	ͼ���ʽ,���õ���
									D3DFMT_R8G8B8 20 24-bit RGB pixel format with 8 bits per channel. 
									D3DFMT_A8R8G8B8 21 32-bit ARGB pixel format with alpha, using 8 bits per channel. 
									D3DFMT_X8R8G8B8 22 32-bit RGB pixel format, where 8 bits are reserved for each color. 
									D3DFMT_R5G6B5 23 16-bit RGB pixel format with 5 bits for red, 6 bits for green, and 5 bits for blue. 
									D3DFMT_X1R5G5B5 24 16-bit pixel format where 5 bits are reserved for each color. 
									D3DFMT_A1R5G5B5 
									D3DFMT_YUY2
*	IDirect3DSurface9	Direct3D�ӿ���,��CSurfaceBuff()������һЩIDirect3DSurface9�Ĳ�������,DirectX SDK���и���ϸ������
*	IFilterGraph		DirectShow�ӿ���,�������Ӻ͹���Filter
*	IBaseFilter			DirectShow Filter
*	
\*****************************************************************************************************/

/*****************************************************************************************************\
*ʱ�䵥λ,û������˵���±���������ʱ�䵥λ��ΪUNITS
*SECONDS =			(1000)		*		MILLISECONDS;       // 10 ^ -3
*SECONDS =			(1000000000)*		NANOSECONDS;		// 10 ^ -9
*SECONDS =			(10000000)	*		UNITS;				// 10 ^ -7
\*****************************************************************************************************/
#ifndef MVMUSER_H
#define MVMUSER_H
#ifdef  MVMUSER_EXPORTS
#define MVMUSER_API __declspec(dllexport)
#else
#define MVMUSER_API __declspec(dllimport)
#endif

typedef vector<wstring>* LPNAMELIST;
//��ƵԴ����
enum  Graph_Type {
	 Un_Known							//δ֪����
	,Image_DIB							//��̬ͼƬ
	,Media_File							//��Ƶ�ļ�
	,Capture_Device						//�ɼ��豸
};
//��֡�ص�
typedef HRESULT (*TransformProc)(
		DWORD_PTR pdwID					//��ƵԴ��ʾ��
		,IDirect3DSurface9* pD3DSurface	//3D����,������֡��ͼ����Ϣ,
										//CSurfaceBuff��ʵ����һЩ��ȡ3D�������ݵĹ���,
										//ͨ�������TransformProc���ص�pD3DSurfaceָ��ָ���Դ��е�3D����
										//�����Ҫ��ȡ����,����CSurfaceBuff��ӽ����ݸ��Ƶ��ڴ���,Ȼ���ٴ�������,
										//�����Ҫ�����������ݷ��ظ��Դ�,�ٵ���CSurfaceBuff::UpdateSurface()
										//��ҪIDirect3DSurface9����ϸ��Ϣ���Բο�DirectX SDK
		,REFERENCE_TIME  rtStart		//��֡��ʼʱ��,��λΪUNITS
		, REFERENCE_TIME  rtEnd			//��֡����ʱ��,��λΪUNITS
		);
//�豸���ӷ���
typedef HRESULT (*SourceConnectProc)(
		DWORD_PTR pdwID				//��ƵԴ��ʾ��
		,IFilterGraph *   pGraph		//filter graph
		,IBaseFilter *	pSrcFilter	//Դfilter
		,IBaseFilter *	pRender		//����filter
		);
// Font creation flags
#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

// Font rendering flags
#define D3DFONT_CENTERED_X  0x0001
#define D3DFONT_CENTERED_Y  0x0002
#define D3DFONT_TWOSIDED    0x0004
#define D3DFONT_FILTERED    0x0008


class MVMUSER_API CMVMixer;
class MVMUSER_API CSurfaceBuff;
class MVMUSER_API CMediaHelper;
class MVMUSER_API CD3DText;
//�½�CMVMixer��
MVMUSER_API HRESULT CreateMVMixer(
			CMVMixer** pMixer			// [out] �½���CMVMixer
			,HWND hwnd					// [in ] ָ����ʾ����
			,UINT Width					// [in ] ��ʾ���ڿ��
			,UINT Height				// [in ] ��ʾ���ڸ߶�
			,D3DFORMAT format			// [in ] �ϳɺ��ͼ���ʽ,������¼�ƺϳɺ���Ƶ��ͼ���ʽ
			,BOOL bBufferInSystemMem = 0	// [in ] ָʾ֡�����Ƿ����ϵͳ�ڴ�,
										//		 ���֡�������ϵͳ�ڴ���,���ӿ�ԭʼ���ص��ٶ�(ȫ�ֻص���ӡ��),
										//		 ����������������(����ֻ���˺�ѵ�����),����ֻ����Ҫ����ԭʼ���ص��Ĵ������ʱ��bBufferInSystemMem��ΪTRUE
			);
MVMUSER_API HRESULT CreateMVMixerEx(
			CMVMixer** pMixer			// [out] �½���CMVMixer
			,HWND hwnd					// [in ] ָ����ʾ����
			,HWND hwndCpy					// [in ] ָ����ʾ����
			,UINT Width					// [in ] ��ʾ���ڿ��
			,UINT Height				// [in ] ��ʾ���ڸ߶�
			,D3DFORMAT format			// [in ] �ϳɺ��ͼ���ʽ,������¼�ƺϳɺ���Ƶ��ͼ���ʽ
			,BOOL bBufferInSystemMem = 0	// [in ] ָʾ֡�����Ƿ����ϵͳ�ڴ�,
										//		 ���֡�������ϵͳ�ڴ���,���ӿ�ԭʼ���ص��ٶ�(ȫ�ֻص���ӡ��),
										//		 ����������������(����ֻ���˺�ѵ�����),����ֻ����Ҫ����ԭʼ���ص��Ĵ������ʱ��bBufferInSystemMem��ΪTRUE
			);
/*****************************************************************************************************\
*CMVMixer
*��Ƶ�ϳ���
*��ƵԴ :	1.��̬ͼƬ
*			2.��Ƶ�ļ�
*			3.�ɼ��豸
*����		1.�ϳ���ʾ : �Զ����ƵԴ���л�Ϻ���ʾ,���Ե���ָ��ĳ����ƵԴ��λ��(3ά,�������ڲ���)��͸����
*			2.�ɼ�¼�� : ¼�Ƶ�·��Ƶ���Ϻ����Ƶ,Ҳ����ͬʱ����,ͬʱ�ṩѹ������ѡ��,¼��ʱ����ָ���Ƿ�ɼ���Ƶ
*			3.��֡�ص� : ָ����·��Ƶ�ͻ����Ƶ�Ļص�����,����ÿ�ݽ���ʾһ֡����֮ǰ���ᴦ��һ�λص�����
\*****************************************************************************************************/

class MVMUSER_API CMVMixer
{
public:

	//�õ���ǰ��ʾ���ݣ����ͼ�����ݣ�
	virtual HRESULT GetData(
		 CSurfaceBuff** ppBuff			// [out] ͼ������
		)= 0;
	//����ȫ�ֻص�����(���ͼ��)
	virtual HRESULT SetTransformProc(
		 TransformProc   pProc			// [in]  ָ������ָ��
		,TransformProc* pOldProc		// [out] ����ԭ���ĺ���ָ��
		)= 0;
	//����ȫ�ֻص�����(���ͼ��)
	virtual HRESULT GetTransformProc(
		TransformProc * pProc			// [out] 
		)= 0;
	//��ʼ��¼��graph(¼�ƺϳɺ��ͼ��)
	virtual HRESULT InitCapture(
		 LPCWSTR lpPath					// [in ] ¼����·��
		,LPCWSTR pszVidComName			// [in ] ָ����Ƶѹ����,����Ϊ0,��ʾ��ѹ��,
										//		 ѹ��������ͨ��CMediaHelper::EnumVidCompression()ö�ٵõ�
		,LPCWSTR lpszAudDevice			// [in ] ָ����Ƶ����,0��ʾֻ¼����Ƶ
		,LPCWSTR pszAudComName			// [in ] ָ����Ƶѹ����,����Ϊ0,��ʾ��ѹ��,
										//  	 ѹ��������ͨ��CMediaHelper::EnumAudCompression()ö�ٵõ�
		)= 0;
	//�������Դ
	virtual HRESULT ClearSource() = 0 ;
	//����¼��graph
	virtual HRESULT TerminateCapture()= 0;
	//��ʼ¼��
	virtual HRESULT StartCapture()= 0;
	//ֹͣ¼��
	virtual HRESULT StopCapture()= 0;
	//������ƵԴ(ͨ��ָ����Ƶ�ļ�)
	virtual  HRESULT AddMediaFileSource(
		  LPCWSTR Path					// [in ] ��Ƶ�ļ�·��,֧�ֵ���Ƶ��ʽ��ϵͳ����װ�Ľ���������
		, DWORD_PTR& dwID				// [out] ������ƵԴ��ʾ��,Ӧ�ó���ͨ����ʾ��ָ��������ƵԴ
		, LPRECT rcDest	= 0				// [in ] ָ��ͼ�����ڴ����е�λ��,0��ʾ������������
		, SourceConnectProc Proc = 0	// [in ] �Զ������ӷ���(����ָ��),ʹ���Զ�������,����Ӧ�ó�����Filter
										//		 ������(������Ҫ��ԴFilter��Render Filter֮���������Filter
										//		 ����Ҫʹ�øò���),����ָ��Ϊ��,��ʹ��Ĭ�ϵ����ӷ���
		)= 0;
	//������ƵԴ(ͨ��ָ���ɼ��豸)
	virtual HRESULT AddCaptureDeviceSource(
		 UINT DeviceId					// [in ] �豸���,>=0������,��CMediaHelper::EnumVidCompression()
										//		 ö���豸ʱ�����
		,GUID VidType					// [in ] ָ���ɼ��豸��ͼ������(��ɫ�ռ���ɫ��ѹ�� (MEDIASUBTYPE_RGB555,MEDIASUBTYPE_RGB32,
										//		 MEDIASUBTYPE_RGB24,MEDIASUBTYPE_YUY2 ��,��Ҫ����ϸ��Ϣ���Բο�DirectX SDK),
										//		 CMediaHelper::EnumCapFormat()����ö���豸֧�ֵ���ɫ�ռ��Լ�������Ϣ
		,UINT Width						// [in ] �߶�,���Ʊ������豸֧�ֵ����ֱ�����,�ұ�����ĳ��ֵ������������,��ϸ��Ϣ�뿴CMediaHelper::EnumCapFormat()˵��
		,UINT Height					// [in ] ���,ͬ��
		,int nFPS						// [in ] ˢ����
		,DWORD_PTR& dwID				// [out] ������ƵԴ��ʾ��,Ӧ�ó���ͨ����ʾ��ָ��������ƵԴ
		,BOOL bUsingColorSpace = 0		// [in ] ���ֲɼ�������YUY2ɫʱ,������������,ʹ��bUsingColorSpace���Խ��
		,LPRECT rcDest	= 0				// [in ] ָ��ͼ�����ڴ����е�λ��,0��ʾ������������
		,SourceConnectProc Proc = 0		// [in ] �Զ������ӷ���(����ָ��),ʹ���Զ�������,����Ӧ�ó�����Filter
										//		 ������(������Ҫ��ԴFilter��Render Filter֮���������Filter
										//		 ����Ҫʹ�øò���),����ָ��Ϊ��,��ʹ��Ĭ�ϵ����ӷ���
		)= 0;
	virtual HRESULT AddCaptureDeviceSource(
		LPCWSTR Devicename
		, GUID VidType 
		,UINT Width
		,UINT Height
		,int nFPS
		, DWORD_PTR& dwID
		,BOOL bUsingColorSpace	=	0
		,LPRECT rcDest	=	0
		,SourceConnectProc ConnectProc	=	0
		) = 0;
	virtual HRESULT AddCaptureDeviceSource(
		LPCWSTR Devicename
		,int nameIndex
		, GUID VidType 
		,UINT Width
		,UINT Height
		,int nFPS
		, DWORD_PTR& dwID
		,BOOL bUsingColorSpace	=	0
		,LPRECT rcDest	=	0
		,SourceConnectProc ConnectProc	=	0
		) = 0;

	//������ƵԴ(ͨ��ָ����̬ͼƬ)
	virtual HRESULT AddImageDIBSource(
		LPCVOID pSrcMemory				// [in ] ͼ������
		,D3DFORMAT imgtp				// [in ] ͼƬ����,D3DFMT_X8R8G8B8(RGB32),D3DFMT_A8R8G8B8(RGB32);
										//		 ָ��ΪD3DFMT_X8R8G8B8ʱͼƬ�������ص�Alphaֵ������0xFF;
										//		 ָ��ΪD3DFMT_A8R8G8B8ʱ,ͼƬʹ��ԭ�е�Alphaͨ��,
										//		 ���û��Alphaͨ��,ͼƬ�����ɼ�(AlphaΪ0,ȫ͸��)
		,long bmWidthBytes				// [in ] ͼƬÿһ�еĿ��,����һ������ͼ���ȵ�������
		,LPRECT rcSrc					// [in ] Դͼ����ʾ����,0��ʾ��ʾ����ͼ��
		,DWORD ColorKey					// [in ] ͸��ɫ,ͼƬ����ΪD3DFMT_A8R8G8B8,��ָ����ҹɫ������ʾ,
										//		 D3DFMT_X8R8G8B8ʱָ����ɫ����ʾΪ��ɫ
		,DWORD_PTR& dwID				// [out] ������ƵԴ��ʾ��,Ӧ�ó���ͨ����ʾ��ָ��������ƵԴ
		,LPRECT rcDest = 0				// [in ] ָ��ͼ�����ڴ����е�λ��,0��ʾ������������
		)= 0;
	//������ƵԴ(ͨ��ָ����̬ͼƬ,����Դ)
	virtual HRESULT AddImageDIBSource(
		UINT id							// [in ] ͼ����Դ
		,D3DFORMAT imgtp				// [in ] ͼƬ����,D3DFMT_X8R8G8B8(RGB32),D3DFMT_A8R8G8B8(RGB32);
										//		 ָ��ΪD3DFMT_X8R8G8B8ʱͼƬ�������ص�Alphaֵ������0xFF;
										//		 ָ��ΪD3DFMT_A8R8G8B8ʱ,ͼƬʹ��ԭ�е�Alphaͨ��,
										//		 ���û��Alphaͨ��,ͼƬ�����ɼ�(AlphaΪ0,ȫ͸��)
		,LPRECT rcSrc					// [in ] Դͼ����ʾ����,0��ʾ��ʾ����ͼ��
		,DWORD ColorKey					// [in ] ͸��ɫ,ͼƬ����ΪD3DFMT_A8R8G8B8,��ָ����ҹɫ������ʾ,
										//		 D3DFMT_X8R8G8B8ʱָ����ɫ����ʾΪ��ɫ
		,DWORD_PTR& dwID				// [out] ������ƵԴ��ʾ��,Ӧ�ó���ͨ����ʾ��ָ��������ƵԴ
		,LPRECT rcDest = 0				// [in ] ָ��ͼ�����ڴ����е�λ��,0��ʾ������������
		)= 0;
    //ɾ����ƵԴ
	virtual HRESULT DeleteSource(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//�õ�Դ��Ŀ
    virtual HRESULT  GetSourceNum(
		int * num						// [out] �õ���ǰ��ƵԴ����
		)= 0;
	//�õ���ʾ����
    virtual HRESULT     GetWindow(
		HWND *hWnd						// [out] �õ���ʾ����
		)= 0;
	//����ˢ��֡��(��ʾ���ڵ�֡��,����Դ��֡��)
    virtual HRESULT SetFrameRate(
		int nFPS						// [in ] ˢ����,Ĭ��ֵΪ25
		)= 0;
	//�õ�ƽ��ˢ����(��ʾ���ڵ�֡��,����Դ��֡��)
	virtual HRESULT GetFrameRateAvg(
		int *nFPS						// [out] �õ�ʵ��ˢ���ʵ�ƽ��ֵ
		)= 0;
	//�õ�ˢ��֡��(��ʾ���ڵ�֡��,����Դ��֡��)
	virtual HRESULT  GetFrameRate(
		int *nFPS						// [out] �õ�ָ��ˢ����
		)= 0;
	//���ñ�����ɫ
    virtual HRESULT SetBkColor(
		COLORREF color					// [in ] ������ɫ
		)= 0;
	//�õ�������ɫ
    virtual HRESULT GetBkColor(
		COLORREF *color					// [out] ������ɫ
		)= 0;
	//�鿴������ƵԴ,�����ֹͣ,������������ƵԴ
	virtual HRESULT LoopSources()= 0;
	//����������ƵԴ�ص�����,
	virtual HRESULT SourceSetTransformProc(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,TransformProc pProc			// [in ] ָ���Ļص�����,��Ϊ0,��ʹ�ûص�����
		,TransformProc* pOldProc		// [out] ����ԭ���Ļص�����
		)= 0;
	//�õ��ص�����,
	virtual HRESULT SourceGetTransformProc(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,TransformProc * pProc			// [out] ���صĻص�����
		)= 0;
	//�õ���ǰ����
	virtual HRESULT SourceGetData(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,CSurfaceBuff** ppBuff			// [out] ����ͼ������,ʹ����Ϻ�,�������CSurfaceBuff::Release()�ͷ��ڴ�
		)= 0;
	//������ƵԴ
	virtual HRESULT SourceRun(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//ֹͣ��ƵԴ
	virtual HRESULT SourceStop(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//����ʱ���ʽ(����SourceStopAt(),SourceGetTimes(),SourceGetVideoLen(),SourceSeekto()�ĵ�λ)
	virtual HRESULT SourceSetTimeFormat(
		DWORD_PTR dwID,					// [in ] ��ƵԴ��ʾ��
		const GUID *pFormat				// [in ] ��ʽ
										//		 TIME_FORMAT_NONE		No format. 
										//		 TIME_FORMAT_FRAME		Video frames. 
										//		 TIME_FORMAT_SAMPLE		Samples in the stream. 
										//		 TIME_FORMAT_FIELD		Interlaced video fields. 
										//		 TIME_FORMAT_BYTE		Byte offset within the stream. 
										//		 TIME_FORMAT_MEDIA_TIME	Reference time (100-nanosecond units). 

		) = 0;
	//�õ�ʱ���ʽ
	virtual HRESULT SourceGetTimeFormat(
		DWORD_PTR dwID,					// [in ] ��ƵԴ��ʾ��
		GUID *pFormat					// [in ] ��ʽ
		) = 0;
	//ֹͣʱ������ʾ
	virtual HRESULT SourceStopWhenReady(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//ֹͣ��ָ��ʱ��(��λΪUNITS)
	virtual HRESULT SourceStopAt(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LONGLONG llDur					// [in ] ֹͣʱ��
		)= 0;
	//�õ���ǰʱ��(��λΪUNITS)
	virtual HRESULT SourceGetTimes(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LONGLONG &llCur				// [out] ��ǰʱ��
		,LONGLONG &llDur				// [out] ����ʱ��
		)= 0;
	//�õ���Ƶ����(��λΪUNITS)
	virtual HRESULT SourceGetVideoLen(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LONGLONG &llLen				// [out] ��Ƶ����
		)= 0;
	
	//��ͣ
	virtual HRESULT SourcePause(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//����ָ��ʱ��(��λΪUNITS),ֻ��Ϊý���ļ�Դʱ����
	virtual HRESULT SourceSeekto(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LONGLONG llCur					// [in ] ָ��ʱ��
		)= 0;
	//��ʾ/����ʾָ��Դ
	virtual HRESULT SourceShow(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,BOOL bVisible = TRUE			// [in ] TRUEΪ��ʾ,FALSEΪ����ʾ
		)= 0;
	//�õ��ڵ�ǰ������,����ݺ�Ȳ���ʱ,�������
	virtual HRESULT SourceGetIdealOutputRect(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LPRECT lprc					// [out] �������λ��
		)= 0;
	//�õ���ƵԴʵ�ʴ�С
	virtual HRESULT SourceGetVideoSize(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,long *width					// [out] ���
		,long *height					// [out] �߶�
		)= 0;
	//�ƶ�Դ��ָ��λ��(x,y,z)
	virtual HRESULT SourceSetPos(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,int x							// [in ] ���϶����X������
		,int y							// [in ] ���϶����Y������
		,int cx							// [in ] ���
		,int cy							// [in ] �߶�
		,int z							// [in ] ���ڲ�,0Ϊ����
		)= 0;
	//�ƶ�Դ��ָ��λ��
	virtual HRESULT SourceSetPos(		
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LPRECT lprc					// [in ] ��������
		,int z							// [in ] ���ڲ�,0Ϊ����
		)= 0;
	//�õ�Դλ��
	virtual HRESULT SourceGetPos(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LPRECT lprc					// [out] ��������
		,int* z							// [out] ���ڲ�,0Ϊ����
		)= 0;
	//����Դ͸����
	virtual HRESULT SourceSetAlphaValue(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,BYTE	AlphaValue				// [in ] ͸����,0-255֮��,
		)= 0;
	//�õ�Դ͸����
	virtual HRESULT SourceGetAlphaValue(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,BYTE	*AlphaValue				// [out] ͸����
		)= 0;
	//��ʼ��¼��graph
	virtual HRESULT SourceInitCapture(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		,LPCWSTR lpPath					// [in ] ¼����·��
		,LPCWSTR pszVidComName			// [in ] ָ����Ƶѹ����,����Ϊ0,��ʾ��ѹ��,
										//		 ѹ��������ͨ��CMediaHelper::EnumVidCompression()ö�ٵõ�
		,LPCWSTR lpszAudDevice			// [in ] ָ����Ƶ����,0��ʾֻ¼����Ƶ
		,LPCWSTR pszAudComName			// [in ] ָ����Ƶѹ����,����Ϊ0,��ʾ��ѹ��,
										//  	 ѹ��������ͨ��CMediaHelper::EnumAudCompression()ö�ٵõ�
		)= 0;

	//����¼����
	virtual HRESULT SourceTerminateCapture(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//��ʼ¼��
	virtual HRESULT SourceStartCapture(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//ֹͣ¼��
	virtual HRESULT SourceStopCapture(
		DWORD_PTR dwID					// [in ] ��ƵԴ��ʾ��
		)= 0;
	//�õ�3D�豸
	virtual HRESULT Get3DDevice(
		IDirect3DDevice9 ** pDevice		// [out ] IDirect3DDevice9**
		)= 0;		
	//������Ƶ�ϳ���
	virtual void Release()= 0;		
	//����������ʾ,���ȴ��Զ�ˢ��
	virtual HRESULT UpdateImmediatly() = 0;
	
};
/*****************************************************************************************************\
*CMediaHelper
*����ý���������
*����ö�١����Ӽ����ٸ���Filter
*
\*****************************************************************************************************/
//����ý���������
class  MVMUSER_API CMediaHelper
{
public:
	CMediaHelper(void);
	~CMediaHelper(void);
	//�������Enum����ʱ��������vector<wstring>
	void ClearVector(
		LPNAMELIST pList				// [in ] ָ��vector<wstring>
		);
	//ö����Ƶ�ɼ��豸
	HRESULT EnumVidCapDevice(
		LPNAMELIST pDeviceList			// [out] �����豸��������,����Ϊ0
		,int * iCount 					// [out] �豸����
		);
	//ö����Ƶ�ɼ��豸
	HRESULT EnumAudCapDevice(
		LPNAMELIST pDeviceList			// [out] �����豸��������,����Ϊ0
		,int * iCount = 0				// [out] �豸����
		);
	//ö����Ƶѹ����
	HRESULT EnumAudCompression(
		LPNAMELIST pList				// [out] �����豸��������,����Ϊ0
		,int * iCount = 0 );			// [out] �豸����
	//ö����Ƶѹ����,
	HRESULT EnumVidCompression(
		LPNAMELIST pList				// [out] �����豸��������,����Ϊ0
		,int * iCount = 0				// [out] �豸����
		);
	//ö�ٲɼ���֧�ֵ�ý���ʽ
	
	HRESULT EnumCapFormat(
		 int  iDeviceCode			    // [in ] �豸���,>=0������
		,int iIndex						// [in ] ֧�ֵ�ý���������,��0��ʾ���˵ĵ�һ��ý������
		,AM_MEDIA_TYPE **pmt			// [out] ý������AM_MEDIA_TYPE�ṹ,����Ҫ���ȷ����ڴ�,
										//		 ��ʹ�����������CMediaHelper::DeleteMediaType()�ͷ��ڴ�
		,BYTE *pSCC						// [out] �ṹVIDEO_STREAM_CONFIG_CAPS,�������ȷ����ڴ�,
		,int*formatnum					// [in ] ֧�ֵ�ý����������
		);
	//�õ�ָ����Ƶ�ɼ��豸
	HRESULT GetVidCapDevice (
		int  iDeviceCode				// [in ] �豸���
		,IBaseFilter ** ppCapFilter		// [out] ����ָ��
		);
	HRESULT GetVidCapDevice ( 
		LPCWSTR  pwsName				// [in ] �豸����
		,IBaseFilter ** ppCapFilter		// [out] ����ָ��
		);
	HRESULT GetVidCapDevice ( 
		LPCWSTR  pwsName				// [in ] �豸����
		,int index						// [in ] ͬ���豸���
		,IBaseFilter ** ppCapFilter		// [out] ����ָ��
		);
	//�õ�ָ����Ƶ�ɼ��豸
	HRESULT GetAudCapDevice (
		int  iDeviceCode				// [in ] �豸���
		,IBaseFilter ** ppCapFilter		// [out] ����ָ��
		);
	HRESULT GetAudCapDevice (
		LPCWSTR  pwsName				// [in ] �豸����
		,IBaseFilter ** ppCapFilter		// [out] ����ָ��
		);
	HRESULT GetAudCapDevice (
		LPCWSTR  pwsName				// [in ] �豸����
		,int index						// [in ] ͬ���豸���
		,IBaseFilter ** ppCapFilter		// [out] ����ָ��
		);
	//�õ���Ƶѹ����
	HRESULT GetAudCompression(
		int  iCode						// [in ] �豸���
		,IBaseFilter ** ppFilter		// [out] ����ָ��
		);
	//�õ���Ƶѹ����
	HRESULT GetAudCompression(
		LPCWSTR pwsName					// [in ] �豸����
		,IBaseFilter ** ppFilter		// [out] ����ָ��
		);
		HRESULT GetAudCompression(
		LPCWSTR pwsName					// [in ] �豸����
		,int index						// [in ] ͬ���豸���
		,IBaseFilter ** ppFilter		// [out] ����ָ��
		);
	//�õ���Ƶѹ����
	HRESULT GetVidCompression(
		int  iCode						// [in ] �豸���
		,IBaseFilter ** ppFilter		// [out] ����ָ��
		);
	//�õ���Ƶѹ����
	HRESULT GetVidCompression(
		LPCWSTR pwsName					// [in ] �豸����
		,IBaseFilter ** ppFilter		// [out] ����ָ��
		);
	HRESULT GetVidCompression(
		LPCWSTR pwsName					// [in ] �豸����
		,int index						// [in ] ͬ���豸���
		,IBaseFilter ** ppFilter		// [out] ����ָ��
		);
	//ɾ��AM_MEDIA_TYPE�ṹ
	void DeleteMediaType(
		AM_MEDIA_TYPE *pmt				// [in ] ָ��AM_MEDIA_TYPE�ṹ��ָ��
		);
	//����Filter Graph,ɾ��Graph�е�����Filter
	HRESULT DestroyGraph(
		IFilterGraph * pGraph			// [in ] ָ��IFilterGraph��ָ��
		);
	//�Ͽ�����
	HRESULT DisconnectPins( 
		IBaseFilter* pFilter			// [in ] ָ��IBaseFilter��ָ��
		);
	//�õ�Filter
	HRESULT GetFilter(
		REFCLSID TypeId					// [in ] ���
		,int  iCode						// [in ] ����
		,IBaseFilter ** ppFilter		// [out] ָ��IBaseFilter��ָ��
		);
	//�õ�Filter
	HRESULT GetFilter( REFCLSID TypeId	// [in ] ����
		,LPCWSTR pwsName				// [in ] ����
		,int index						// [in ] ͬ���豸���
		,IBaseFilter ** ppFilter 
		);
	//�õ�Filter
	HRESULT GetFilter(
		REFCLSID TypeId					// [in ] ����
		,LPCWSTR pwsName				// [in ] ����
		,IBaseFilter ** ppFilter		// [out] ָ��IBaseFilter��ָ��
		);
	//ö��Filter
	HRESULT EnumFilter(
		REFCLSID TypeId					// [in ] ����
		,LPNAMELIST pList				// [out] ����Filter�������� 
		,int * iCount = 0				// [out] Filter����
		);
	//ö��Filter֧�ֵ���Ƶ��ʽ
	HRESULT EnumFormat(
		IBaseFilter * ppFilter			// [in ] ָ��Filter
		,int iIndex						// [in ] ��ʽ���
		,AM_MEDIA_TYPE **pmt			// [out] ý������
		,BYTE *pSCC						// [out] �ṹAUDIO_STREAM_CONFIG_CAPS����Ƶ�� ��VIDEO_STREAM_CONFIG_CAPS (��Ƶ)
		,int*formatnum					// [in ] ֧�ֵ�ý������
		);
	

};
//CSurfaceBuff�࣬���ڴ���3d�����е�����
class MVMUSER_API CSurfaceBuff
{
public:
	//���캯��
	CSurfaceBuff(
		IDirect3DSurface9* pSurface		// [in ] ָ��3d���� 
		,BOOL bCopyFromVGA = 0			// [in ] �Ƿ��Ƶ��ڴ�
		);
	//����
	~CSurfaceBuff(void);				
	//����
	void Release();	
	//�����Դ��3D����,���캯��ָ��bCopyFromVGA��= 1 ʱ��Ч
	HRESULT UpdateSurface();
		
	//�õ�����ָ��
	LPVOID Bits();
	//�õ����ݴ�С(��λBYTE)
	SIZE_T Size();
	//�õ��߶�
	UINT   Height();
	//�õ����
	UINT   Width();
	//�õ�ÿһ�����ݿ��
	UINT   Pitch();
	//�õ�ͼ������
	D3DFORMAT   Format();
private:
	D3DSURFACE_DESC		_pDesc;
	IDirect3DSurface9* _pSurface;
	LPVOID _pBits;
	INT _iRes;
	INT _iPitch;
	IDirect3DSurface9* _pRenderTarget;
};
/*****************************************************************************************************\
*CD3DText
*��3D�����ϻ����ı�
*
\*****************************************************************************************************/
/*�½�CMVMixer��*/
MVMUSER_API HRESULT CreatD3DText(
			CD3DText** pD3DText			// [out] �½���CD3DText
			,const TCHAR* strFontName	// [in ] ������
			, DWORD dwHeight			// [in ] ����߶�
			, DWORD dwFlags	= 0			// [in ] ������������б����,ͨ��|����
										//		 ,��D3DFONT_BOLD|D3DFONT_ITALIC
			);
class MVMUSER_API CD3DText
{
	public:
	 // 2D and 3D text drawing functions
    virtual HRESULT DrawText( FLOAT x, FLOAT y, DWORD dwColor, 
                      const TCHAR* strText, DWORD dwFlags=0L ) = 0;
    virtual HRESULT DrawTextScaled( FLOAT x, FLOAT y, FLOAT z, 
                            FLOAT fXScale, FLOAT fYScale, DWORD dwColor, 
                            const TCHAR* strText, DWORD dwFlags=0L ) = 0;
    virtual HRESULT Render3DText( const TCHAR* strText, DWORD dwFlags=0L ) = 0;
    
    // Function to get extent of text
    virtual HRESULT GetTextExtent( const TCHAR* strText, SIZE* pSize ) = 0;

    // Initializing and destroying device-dependent objects
    virtual HRESULT InitDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice ) = 0;
    virtual HRESULT RestoreDeviceObjects() = 0;
    virtual HRESULT InvalidateDeviceObjects() = 0;
    virtual HRESULT DeleteDeviceObjects() = 0;
	virtual void Release() = 0 ;
};
#endif//MVMUSER_H