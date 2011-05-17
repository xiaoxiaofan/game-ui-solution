//IMXEC_Export.h

#ifndef __IMXEC_EXPORT_H__
#define __IMXEC_EXPORT_H__

#ifdef IMXEC_EXPORT
#define IMXEC_API _declspec(dllexport)
#elif IMXEC_DLL
#define IMXEC_API _declspec(dllimport)
#else
#define IMXEC_API
#endif

#endif