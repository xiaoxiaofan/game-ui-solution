/*****************************************************************************************************\
*MVMUSER.lib MVMUSER.dll MultiVMR9.dll
*复制MultiVMR9.dll 到 system32目录下 运行regsvr32 MultiVMR9.dll
*可能需要下列头文件
*#include <streams.h>
*#include <dshow.h>
*#include <d3d9.h>
初始化CoInitialize(0);
卸载CoUninitialize();
\*****************************************************************************************************/
/*****************************************************************************************************\
*Bug :	CMediaHelper的几个Enum函数,传递的指正LPNAMELIST( vector<wstring>*)必须指向不包含任何数据的
*		vector<wstring>(也就是说 LPNAMELIST->enpty() == true),同时LPNAMELIST所指向的 vector<wstring>
*		必须在其析构之前调用CMediaHelper::ClearVector( vector<wstring>*);
\*****************************************************************************************************/
/*****************************************************************************************************\
* 返回值　HRESULT
* 成功　　S_OK;
* 失败	　返回值包含失败信息　
* 可以用SECCEEDED(HRESULT hr) 和　FAILED(HRESULT hr)宏判断返回值表示成功或者失败
\*****************************************************************************************************/
/*****************************************************************************************************\
 结构,数据类型
*   AM_MEDIA_TYPE,DirectShow结构,DirectX SDK中有更详细的资料
	typedef struct  _MediaType {
	GUID      majortype;			// 主媒体类型,MEDIATYPE_Video(视频)MEDIATYPE_Audio(视频)等
	GUID      subtype;				// 图表类型(颜色空间或叫色彩压缩),MEDIASUBTYPE_RGB555,MEDIASUBTYPE_RGB32,
									// MEDIASUBTYPE_RGB24,,MEDIASUBTYPE_YUY2 等
	BOOL      bFixedSizeSamples;	// TRUE 表示固定采样,FALSE表示不固定采样
	BOOL      bTemporalCompression;	// 是否使用帧间压缩
	ULONG     lSampleSize;			// 采样大小
	GUID      formattype;			// pbFormat所指结构的类型,下面是对应关系
										类型						结构
										FORMAT_None					None. 
										FORMAT_DvInfo				DVINFO 
										FORMAT_MPEGVideo			MPEG1VIDEOINFO 
										FORMAT_MPEG2Video			MPEG2VIDEOINFO 
										FORMAT_VideoInfo			VIDEOINFOHEADER 
										FORMAT_VideoInfo2			VIDEOINFOHEADER2 
										FORMAT_WaveFormatEx			WAVEFORMATEX 

	IUnknown  *pUnk;				// 保留不使用
	ULONG     cbFormat;				// pbFormat所指结构大小
	[size_is(cbFormat)]
			BYTE *pbFormat;			// formattype类型的结构
	} AM_MEDIA_TYPE;

*	VIDEO_STREAM_CONFIG_CAPS,DirectShow结构,DirectX SDK中有更详细的资料
	typedef struct _VIDEO_STREAM_CONFIG_CAPS {
	GUID guid;						// 同AM_MEDIA_TYPE的成员formattype
	ULONG VideoStandard;			// 支持的视频制式,可以同时支持多种制式,通过"|"运算连接
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

	SIZE InputSize;					// 输入大小
	SIZE MinCroppingSize;			// 最小剪切输出
	SIZE MaxCroppingSize;			// 最大剪切输出
	int CropGranularityX;			// 水平方向剪切输出值调整粒度(既必须在原始大小的基础上,以该值得整数倍增长)
	int CropGranularityY;			// 竖直方向剪切输出值调整粒度
	int CropAlignX;					// Required horizontal alignment of the source rectangle. 
	int CropAlignY;					// Required vertical alignment of the source rectangle
	SIZE MinOutputSize;				// 最小输出
	SIZE MaxOutputSize;				// 最大输出
	int OutputGranularityX;			// 水平方向输出值调整粒度
	int OutputGranularityY;			// 竖直方向输出值调整粒度
	int StretchTapsX;				// Indicates how well the filter can stretch the image horizontally. 
	int StretchTapsY;				// Indicates how well the filter can stretch the image vertically.
	int ShrinkTapsX;				// Indicates how well the filter can shrink the image horizontally.
	int ShrinkTapsY;				// Indicates how well the filter can shrink the image vertically.
	LONGLONG MinFrameInterval;		// 最小帧间间隔(单位UNITS)
	LONGLONG MaxFrameInterval;		// 最大帧间间隔(单位UNITS)
	LONG MinBitsPerSecond;			// 最小位速(bps)
	LONG MaxBitsPerSecond;			// 最大位速(bps)
	} VIDEO_STREAM_CONFIG_CAPS;
*	D3DFORMAT			Direct3D	图像格式,常用的有
									D3DFMT_R8G8B8 20 24-bit RGB pixel format with 8 bits per channel. 
									D3DFMT_A8R8G8B8 21 32-bit ARGB pixel format with alpha, using 8 bits per channel. 
									D3DFMT_X8R8G8B8 22 32-bit RGB pixel format, where 8 bits are reserved for each color. 
									D3DFMT_R5G6B5 23 16-bit RGB pixel format with 5 bits for red, 6 bits for green, and 5 bits for blue. 
									D3DFMT_X1R5G5B5 24 16-bit pixel format where 5 bits are reserved for each color. 
									D3DFMT_A1R5G5B5 
									D3DFMT_YUY2
*	IDirect3DSurface9	Direct3D接口类,类CSurfaceBuff()集成了一些IDirect3DSurface9的操作方法,DirectX SDK中有更详细的资料
*	IFilterGraph		DirectShow接口类,用于连接和管理Filter
*	IBaseFilter			DirectShow Filter
*	
\*****************************************************************************************************/

/*****************************************************************************************************\
*时间单位,没有特殊说明下本类中所有时间单位均为UNITS
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
//视频源类型
enum  Graph_Type {
	 Un_Known							//未知类型
	,Image_DIB							//静态图片
	,Media_File							//视频文件
	,Capture_Device						//采集设备
};
//逐帧回调
typedef HRESULT (*TransformProc)(
		DWORD_PTR pdwID					//视频源标示符
		,IDirect3DSurface9* pD3DSurface	//3D表面,包含该帧的图像信息,
										//CSurfaceBuff类实现了一些提取3D表面数据的功能,
										//通常情况下TransformProc返回的pD3DSurface指定指向显存中的3D表面
										//如果需要读取数据,可以CSurfaceBuff类从将数据复制到内存中,然后再处理数据,
										//如果需要将处理后的数据返回给显存,再调用CSurfaceBuff::UpdateSurface()
										//需要IDirect3DSurface9更详细信息可以参考DirectX SDK
		,REFERENCE_TIME  rtStart		//该帧开始时间,单位为UNITS
		, REFERENCE_TIME  rtEnd			//该帧结束时间,单位为UNITS
		);
//设备连接方法
typedef HRESULT (*SourceConnectProc)(
		DWORD_PTR pdwID				//视频源标示符
		,IFilterGraph *   pGraph		//filter graph
		,IBaseFilter *	pSrcFilter	//源filter
		,IBaseFilter *	pRender		//最终filter
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
//新建CMVMixer类
MVMUSER_API HRESULT CreateMVMixer(
			CMVMixer** pMixer			// [out] 新建的CMVMixer
			,HWND hwnd					// [in ] 指定显示窗口
			,UINT Width					// [in ] 显示窗口宽度
			,UINT Height				// [in ] 显示窗口高度
			,D3DFORMAT format			// [in ] 合成后的图像格式,将决定录制合成后视频的图像格式
			,BOOL bBufferInSystemMem = 0	// [in ] 指示帧缓存是否放在系统内存,
										//		 如果帧缓存放在系统内存内,将加快原始流回调速度(全局回调不印象),
										//		 但画面质量将降低(会出现画面撕裂等问题),建议只在需要处理原始流回调的大块数据时将bBufferInSystemMem设为TRUE
			);
MVMUSER_API HRESULT CreateMVMixerEx(
			CMVMixer** pMixer			// [out] 新建的CMVMixer
			,HWND hwnd					// [in ] 指定显示窗口
			,HWND hwndCpy					// [in ] 指定显示窗口
			,UINT Width					// [in ] 显示窗口宽度
			,UINT Height				// [in ] 显示窗口高度
			,D3DFORMAT format			// [in ] 合成后的图像格式,将决定录制合成后视频的图像格式
			,BOOL bBufferInSystemMem = 0	// [in ] 指示帧缓存是否放在系统内存,
										//		 如果帧缓存放在系统内存内,将加快原始流回调速度(全局回调不印象),
										//		 但画面质量将降低(会出现画面撕裂等问题),建议只在需要处理原始流回调的大块数据时将bBufferInSystemMem设为TRUE
			);
/*****************************************************************************************************\
*CMVMixer
*视频合成类
*视频源 :	1.静态图片
*			2.视频文件
*			3.采集设备
*功能		1.合成显示 : 对多个视频源进行混合后显示,可以单独指定某个视频源的位置(3维,包括所在层数)、透明度
*			2.采集录像 : 录制单路视频或混合后的视频,也可以同时进行,同时提供压缩器的选择,录制时可以指定是否采集音频
*			3.逐帧回调 : 指定单路视频和混合视频的回调方法,程序每递交显示一帧画面之前都会处理一次回调方法
\*****************************************************************************************************/

class MVMUSER_API CMVMixer
{
public:

	//得到当前显示数据（混合图像数据）
	virtual HRESULT GetData(
		 CSurfaceBuff** ppBuff			// [out] 图像数据
		)= 0;
	//设置全局回调函数(混合图像)
	virtual HRESULT SetTransformProc(
		 TransformProc   pProc			// [in]  指定函数指针
		,TransformProc* pOldProc		// [out] 返回原来的函数指针
		)= 0;
	//返回全局回调函数(混合图像)
	virtual HRESULT GetTransformProc(
		TransformProc * pProc			// [out] 
		)= 0;
	//初始化录像graph(录制合成后的图像)
	virtual HRESULT InitCapture(
		 LPCWSTR lpPath					// [in ] 录像存放路径
		,LPCWSTR pszVidComName			// [in ] 指定视频压缩器,可以为0,表示不压缩,
										//		 压缩器可以通过CMediaHelper::EnumVidCompression()枚举得到
		,LPCWSTR lpszAudDevice			// [in ] 指定音频输入,0表示只录制视频
		,LPCWSTR pszAudComName			// [in ] 指定音频压缩器,可以为0,表示不压缩,
										//  	 压缩器可以通过CMediaHelper::EnumAudCompression()枚举得到
		)= 0;
	//清除所有源
	virtual HRESULT ClearSource() = 0 ;
	//销毁录像graph
	virtual HRESULT TerminateCapture()= 0;
	//开始录像
	virtual HRESULT StartCapture()= 0;
	//停止录像
	virtual HRESULT StopCapture()= 0;
	//增加视频源(通过指定视频文件)
	virtual  HRESULT AddMediaFileSource(
		  LPCWSTR Path					// [in ] 视频文件路径,支持的视频格式视系统所安装的解码器而定
		, DWORD_PTR& dwID				// [out] 返回视频源标示符,应用程序通过标示符指定控制视频源
		, LPRECT rcDest	= 0				// [in ] 指定图像所在窗口中的位置,0表示充满整个窗口
		, SourceConnectProc Proc = 0	// [in ] 自定义连接方法(函数指针),使用自定义连接,将由应用程序负责Filter
										//		 的连接(比如需要在源Filter和Render Filter之间加入其他Filter
										//		 就需要使用该参数),若该指针为空,将使用默认的连接方法
		)= 0;
	//增加视频源(通过指定采集设备)
	virtual HRESULT AddCaptureDeviceSource(
		 UINT DeviceId					// [in ] 设备标号,>=0的整数,是CMediaHelper::EnumVidCompression()
										//		 枚举设备时的序号
		,GUID VidType					// [in ] 指定采集设备的图表类型(颜色空间或叫色彩压缩 (MEDIASUBTYPE_RGB555,MEDIASUBTYPE_RGB32,
										//		 MEDIASUBTYPE_RGB24,MEDIASUBTYPE_YUY2 等,需要更详细信息可以参考DirectX SDK),
										//		 CMediaHelper::EnumCapFormat()可以枚举设备支持的颜色空间以及其他信息
		,UINT Width						// [in ] 高度,该制必须在设备支持的最大分辨率内,且必须以某个值得整数倍增长,详细信息请看CMediaHelper::EnumCapFormat()说明
		,UINT Height					// [in ] 宽度,同上
		,int nFPS						// [in ] 刷新率
		,DWORD_PTR& dwID				// [out] 返回视频源标示符,应用程序通过标示符指定控制视频源
		,BOOL bUsingColorSpace = 0		// [in ] 部分采集卡采用YUY2色时,画面会出现杂质,使用bUsingColorSpace可以解决
		,LPRECT rcDest	= 0				// [in ] 指定图像所在窗口中的位置,0表示充满整个窗口
		,SourceConnectProc Proc = 0		// [in ] 自定义连接方法(函数指针),使用自定义连接,将由应用程序负责Filter
										//		 的连接(比如需要在源Filter和Render Filter之间加入其他Filter
										//		 就需要使用该参数),若该指针为空,将使用默认的连接方法
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

	//增加视频源(通过指定静态图片)
	virtual HRESULT AddImageDIBSource(
		LPCVOID pSrcMemory				// [in ] 图像数据
		,D3DFORMAT imgtp				// [in ] 图片类型,D3DFMT_X8R8G8B8(RGB32),D3DFMT_A8R8G8B8(RGB32);
										//		 指定为D3DFMT_X8R8G8B8时图片所有像素的Alpha值都将是0xFF;
										//		 指定为D3DFMT_A8R8G8B8时,图片使用原有的Alpha通道,
										//		 如果没有Alpha通道,图片将不可见(Alpha为0,全透明)
		,long bmWidthBytes				// [in ] 图片每一行的宽度,并不一定等于图像宽度的整数倍
		,LPRECT rcSrc					// [in ] 源图像显示区域,0表示显示整个图像
		,DWORD ColorKey					// [in ] 透明色,图片类型为D3DFMT_A8R8G8B8,被指定的夜色将不显示,
										//		 D3DFMT_X8R8G8B8时指定颜色将显示为黑色
		,DWORD_PTR& dwID				// [out] 返回视频源标示符,应用程序通过标示符指定控制视频源
		,LPRECT rcDest = 0				// [in ] 指定图像所在窗口中的位置,0表示充满整个窗口
		)= 0;
	//增加视频源(通过指定静态图片,从资源)
	virtual HRESULT AddImageDIBSource(
		UINT id							// [in ] 图像资源
		,D3DFORMAT imgtp				// [in ] 图片类型,D3DFMT_X8R8G8B8(RGB32),D3DFMT_A8R8G8B8(RGB32);
										//		 指定为D3DFMT_X8R8G8B8时图片所有像素的Alpha值都将是0xFF;
										//		 指定为D3DFMT_A8R8G8B8时,图片使用原有的Alpha通道,
										//		 如果没有Alpha通道,图片将不可见(Alpha为0,全透明)
		,LPRECT rcSrc					// [in ] 源图像显示区域,0表示显示整个图像
		,DWORD ColorKey					// [in ] 透明色,图片类型为D3DFMT_A8R8G8B8,被指定的夜色将不显示,
										//		 D3DFMT_X8R8G8B8时指定颜色将显示为黑色
		,DWORD_PTR& dwID				// [out] 返回视频源标示符,应用程序通过标示符指定控制视频源
		,LPRECT rcDest = 0				// [in ] 指定图像所在窗口中的位置,0表示充满整个窗口
		)= 0;
    //删除视频源
	virtual HRESULT DeleteSource(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//得到源数目
    virtual HRESULT  GetSourceNum(
		int * num						// [out] 得到当前视频源数量
		)= 0;
	//得到显示窗口
    virtual HRESULT     GetWindow(
		HWND *hWnd						// [out] 得到显示窗口
		)= 0;
	//设置刷新帧率(显示窗口的帧率,并非源的帧率)
    virtual HRESULT SetFrameRate(
		int nFPS						// [in ] 刷新率,默认值为25
		)= 0;
	//得到平均刷新率(显示窗口的帧率,并非源的帧率)
	virtual HRESULT GetFrameRateAvg(
		int *nFPS						// [out] 得到实际刷新率的平均值
		)= 0;
	//得到刷新帧率(显示窗口的帧率,并非源的帧率)
	virtual HRESULT  GetFrameRate(
		int *nFPS						// [out] 得到指定刷新率
		)= 0;
	//设置背景颜色
    virtual HRESULT SetBkColor(
		COLORREF color					// [in ] 背景颜色
		)= 0;
	//得到背景颜色
    virtual HRESULT GetBkColor(
		COLORREF *color					// [out] 背景颜色
		)= 0;
	//查看所有视频源,如果已停止,重新启动该视频源
	virtual HRESULT LoopSources()= 0;
	//单独设置视频源回调函数,
	virtual HRESULT SourceSetTransformProc(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,TransformProc pProc			// [in ] 指定的回调函数,若为0,则不使用回调函数
		,TransformProc* pOldProc		// [out] 返回原来的回调函数
		)= 0;
	//得到回调函数,
	virtual HRESULT SourceGetTransformProc(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,TransformProc * pProc			// [out] 返回的回调函数
		)= 0;
	//得到当前画面
	virtual HRESULT SourceGetData(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,CSurfaceBuff** ppBuff			// [out] 返回图像数据,使用完毕后,必须调用CSurfaceBuff::Release()释放内存
		)= 0;
	//运行视频源
	virtual HRESULT SourceRun(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//停止视频源
	virtual HRESULT SourceStop(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//设置时间格式(决定SourceStopAt(),SourceGetTimes(),SourceGetVideoLen(),SourceSeekto()的单位)
	virtual HRESULT SourceSetTimeFormat(
		DWORD_PTR dwID,					// [in ] 视频源标示符
		const GUID *pFormat				// [in ] 格式
										//		 TIME_FORMAT_NONE		No format. 
										//		 TIME_FORMAT_FRAME		Video frames. 
										//		 TIME_FORMAT_SAMPLE		Samples in the stream. 
										//		 TIME_FORMAT_FIELD		Interlaced video fields. 
										//		 TIME_FORMAT_BYTE		Byte offset within the stream. 
										//		 TIME_FORMAT_MEDIA_TIME	Reference time (100-nanosecond units). 

		) = 0;
	//得到时间格式
	virtual HRESULT SourceGetTimeFormat(
		DWORD_PTR dwID,					// [in ] 视频源标示符
		GUID *pFormat					// [in ] 格式
		) = 0;
	//停止时更新显示
	virtual HRESULT SourceStopWhenReady(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//停止在指定时间(单位为UNITS)
	virtual HRESULT SourceStopAt(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LONGLONG llDur					// [in ] 停止时间
		)= 0;
	//得到当前时间(单位为UNITS)
	virtual HRESULT SourceGetTimes(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LONGLONG &llCur				// [out] 当前时间
		,LONGLONG &llDur				// [out] 结束时间
		)= 0;
	//得到视频长度(单位为UNITS)
	virtual HRESULT SourceGetVideoLen(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LONGLONG &llLen				// [out] 视频长度
		)= 0;
	
	//暂停
	virtual HRESULT SourcePause(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//跳到指定时间(单位为UNITS),只有为媒体文件源时可用
	virtual HRESULT SourceSeekto(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LONGLONG llCur					// [in ] 指定时间
		)= 0;
	//显示/不显示指定源
	virtual HRESULT SourceShow(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,BOOL bVisible = TRUE			// [in ] TRUE为显示,FALSE为不显示
		)= 0;
	//得到在当前窗口中,输出纵横比不变时,最大的输出
	virtual HRESULT SourceGetIdealOutputRect(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LPRECT lprc					// [out] 最大的输出位置
		)= 0;
	//得到视频源实际大小
	virtual HRESULT SourceGetVideoSize(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,long *width					// [out] 宽度
		,long *height					// [out] 高度
		)= 0;
	//移动源到指定位置(x,y,z)
	virtual HRESULT SourceSetPos(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,int x							// [in ] 左上定点的X轴坐标
		,int y							// [in ] 左上定点的Y轴坐标
		,int cx							// [in ] 宽度
		,int cy							// [in ] 高度
		,int z							// [in ] 所在层,0为顶层
		)= 0;
	//移动源到指定位置
	virtual HRESULT SourceSetPos(		
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LPRECT lprc					// [in ] 所在区域
		,int z							// [in ] 所在层,0为顶层
		)= 0;
	//得到源位置
	virtual HRESULT SourceGetPos(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LPRECT lprc					// [out] 所在区域
		,int* z							// [out] 所在层,0为顶层
		)= 0;
	//设置源透明度
	virtual HRESULT SourceSetAlphaValue(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,BYTE	AlphaValue				// [in ] 透明度,0-255之间,
		)= 0;
	//得到源透明度
	virtual HRESULT SourceGetAlphaValue(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,BYTE	*AlphaValue				// [out] 透明度
		)= 0;
	//初始化录像graph
	virtual HRESULT SourceInitCapture(
		DWORD_PTR dwID					// [in ] 视频源标示符
		,LPCWSTR lpPath					// [in ] 录像存放路径
		,LPCWSTR pszVidComName			// [in ] 指定视频压缩器,可以为0,表示不压缩,
										//		 压缩器可以通过CMediaHelper::EnumVidCompression()枚举得到
		,LPCWSTR lpszAudDevice			// [in ] 指定音频输入,0表示只录制视频
		,LPCWSTR pszAudComName			// [in ] 指定音频压缩器,可以为0,表示不压缩,
										//  	 压缩器可以通过CMediaHelper::EnumAudCompression()枚举得到
		)= 0;

	//销毁录像功能
	virtual HRESULT SourceTerminateCapture(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//开始录像
	virtual HRESULT SourceStartCapture(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//停止录像
	virtual HRESULT SourceStopCapture(
		DWORD_PTR dwID					// [in ] 视频源标示符
		)= 0;
	//得到3D设备
	virtual HRESULT Get3DDevice(
		IDirect3DDevice9 ** pDevice		// [out ] IDirect3DDevice9**
		)= 0;		
	//销毁视频合成类
	virtual void Release()= 0;		
	//立即更新显示,不等待自动刷新
	virtual HRESULT UpdateImmediatly() = 0;
	
};
/*****************************************************************************************************\
*CMediaHelper
*常用媒体操作集合
*用于枚举、连接及销毁各类Filter
*
\*****************************************************************************************************/
//常用媒体操作集合
class  MVMUSER_API CMediaHelper
{
public:
	CMediaHelper(void);
	~CMediaHelper(void);
	//清除调用Enum函数时操作过的vector<wstring>
	void ClearVector(
		LPNAMELIST pList				// [in ] 指向vector<wstring>
		);
	//枚举音频采集设备
	HRESULT EnumVidCapDevice(
		LPNAMELIST pDeviceList			// [out] 保存设备名的容器,可以为0
		,int * iCount 					// [out] 设备数量
		);
	//枚举视频采集设备
	HRESULT EnumAudCapDevice(
		LPNAMELIST pDeviceList			// [out] 保存设备名的容器,可以为0
		,int * iCount = 0				// [out] 设备数量
		);
	//枚举音频压缩器
	HRESULT EnumAudCompression(
		LPNAMELIST pList				// [out] 保存设备名的容器,可以为0
		,int * iCount = 0 );			// [out] 设备数量
	//枚举视频压缩器,
	HRESULT EnumVidCompression(
		LPNAMELIST pList				// [out] 保存设备名的容器,可以为0
		,int * iCount = 0				// [out] 设备数量
		);
	//枚举采集卡支持的媒体格式
	
	HRESULT EnumCapFormat(
		 int  iDeviceCode			    // [in ] 设备标号,>=0的整数
		,int iIndex						// [in ] 支持的媒体类型序号,如0表示至此的第一种媒体类型
		,AM_MEDIA_TYPE **pmt			// [out] 媒体类型AM_MEDIA_TYPE结构,不需要事先分配内存,
										//		 但使用完后必须调用CMediaHelper::DeleteMediaType()释放内存
		,BYTE *pSCC						// [out] 结构VIDEO_STREAM_CONFIG_CAPS,必须事先分配内存,
		,int*formatnum					// [in ] 支持的媒体类型数量
		);
	//得到指定视频采集设备
	HRESULT GetVidCapDevice (
		int  iDeviceCode				// [in ] 设备序号
		,IBaseFilter ** ppCapFilter		// [out] 返回指针
		);
	HRESULT GetVidCapDevice ( 
		LPCWSTR  pwsName				// [in ] 设备名称
		,IBaseFilter ** ppCapFilter		// [out] 返回指针
		);
	HRESULT GetVidCapDevice ( 
		LPCWSTR  pwsName				// [in ] 设备名称
		,int index						// [in ] 同名设备序号
		,IBaseFilter ** ppCapFilter		// [out] 返回指针
		);
	//得到指定音频采集设备
	HRESULT GetAudCapDevice (
		int  iDeviceCode				// [in ] 设备序号
		,IBaseFilter ** ppCapFilter		// [out] 返回指针
		);
	HRESULT GetAudCapDevice (
		LPCWSTR  pwsName				// [in ] 设备名称
		,IBaseFilter ** ppCapFilter		// [out] 返回指针
		);
	HRESULT GetAudCapDevice (
		LPCWSTR  pwsName				// [in ] 设备名称
		,int index						// [in ] 同名设备序号
		,IBaseFilter ** ppCapFilter		// [out] 返回指针
		);
	//得到音频压缩器
	HRESULT GetAudCompression(
		int  iCode						// [in ] 设备序号
		,IBaseFilter ** ppFilter		// [out] 返回指针
		);
	//得到音频压缩器
	HRESULT GetAudCompression(
		LPCWSTR pwsName					// [in ] 设备名称
		,IBaseFilter ** ppFilter		// [out] 返回指针
		);
		HRESULT GetAudCompression(
		LPCWSTR pwsName					// [in ] 设备名称
		,int index						// [in ] 同名设备序号
		,IBaseFilter ** ppFilter		// [out] 返回指针
		);
	//得到视频压缩器
	HRESULT GetVidCompression(
		int  iCode						// [in ] 设备序号
		,IBaseFilter ** ppFilter		// [out] 返回指针
		);
	//得到视频压缩器
	HRESULT GetVidCompression(
		LPCWSTR pwsName					// [in ] 设备名称
		,IBaseFilter ** ppFilter		// [out] 返回指针
		);
	HRESULT GetVidCompression(
		LPCWSTR pwsName					// [in ] 设备名称
		,int index						// [in ] 同名设备序号
		,IBaseFilter ** ppFilter		// [out] 返回指针
		);
	//删除AM_MEDIA_TYPE结构
	void DeleteMediaType(
		AM_MEDIA_TYPE *pmt				// [in ] 指向AM_MEDIA_TYPE结构的指针
		);
	//销毁Filter Graph,删除Graph中的所有Filter
	HRESULT DestroyGraph(
		IFilterGraph * pGraph			// [in ] 指向IFilterGraph的指针
		);
	//断开连接
	HRESULT DisconnectPins( 
		IBaseFilter* pFilter			// [in ] 指向IBaseFilter的指针
		);
	//得到Filter
	HRESULT GetFilter(
		REFCLSID TypeId					// [in ] 序号
		,int  iCode						// [in ] 类型
		,IBaseFilter ** ppFilter		// [out] 指向IBaseFilter的指针
		);
	//得到Filter
	HRESULT GetFilter( REFCLSID TypeId	// [in ] 类型
		,LPCWSTR pwsName				// [in ] 名称
		,int index						// [in ] 同名设备序号
		,IBaseFilter ** ppFilter 
		);
	//得到Filter
	HRESULT GetFilter(
		REFCLSID TypeId					// [in ] 类型
		,LPCWSTR pwsName				// [in ] 名称
		,IBaseFilter ** ppFilter		// [out] 指向IBaseFilter的指针
		);
	//枚举Filter
	HRESULT EnumFilter(
		REFCLSID TypeId					// [in ] 类型
		,LPNAMELIST pList				// [out] 保存Filter名的容器 
		,int * iCount = 0				// [out] Filter数量
		);
	//枚举Filter支持的视频格式
	HRESULT EnumFormat(
		IBaseFilter * ppFilter			// [in ] 指定Filter
		,int iIndex						// [in ] 格式序号
		,AM_MEDIA_TYPE **pmt			// [out] 媒体类型
		,BYTE *pSCC						// [out] 结构AUDIO_STREAM_CONFIG_CAPS（音频） 或　VIDEO_STREAM_CONFIG_CAPS (视频)
		,int*formatnum					// [in ] 支持的媒体数量
		);
	

};
//CSurfaceBuff类，用于处理3d表面中的数据
class MVMUSER_API CSurfaceBuff
{
public:
	//构造函数
	CSurfaceBuff(
		IDirect3DSurface9* pSurface		// [in ] 指定3d表面 
		,BOOL bCopyFromVGA = 0			// [in ] 是否复制到内存
		);
	//析构
	~CSurfaceBuff(void);				
	//销毁
	void Release();	
	//更新显存的3D表面,构造函数指定bCopyFromVGA　= 1 时有效
	HRESULT UpdateSurface();
		
	//得到数组指针
	LPVOID Bits();
	//得到数据大小(单位BYTE)
	SIZE_T Size();
	//得到高度
	UINT   Height();
	//得到宽度
	UINT   Width();
	//得到每一行数据宽度
	UINT   Pitch();
	//得到图像类型
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
*在3D表面上绘制文本
*
\*****************************************************************************************************/
/*新建CMVMixer类*/
MVMUSER_API HRESULT CreatD3DText(
			CD3DText** pD3DText			// [out] 新建的CD3DText
			,const TCHAR* strFontName	// [in ] 字体名
			, DWORD dwHeight			// [in ] 字体高度
			, DWORD dwFlags	= 0			// [in ] 字体重量和倾斜参数,通过|连接
										//		 ,如D3DFONT_BOLD|D3DFONT_ITALIC
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