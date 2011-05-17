#ifndef Export_h__
#define Export_h__

#ifdef LIVE_EXPORTS
#define LIVE_API  __declspec(dllexport)
#elif  LIVE_DLL
#define LIVE_API __declspec(dllimport)
#else
#define LIVE_API
#endif

#endif // Export_h__

