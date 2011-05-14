#ifndef Export_h__
#define Export_h__

#ifndef MEDIASERVER_EXPORTS
#define MEDIASERVER_API __declspec(dllexport)
#elif  MEDIASERVER_DLL
#define MEDIASERVER_API __declspec(dllimport)
#else
#define MEDIASERVER_API 
#endif


#endif // Export_h__

