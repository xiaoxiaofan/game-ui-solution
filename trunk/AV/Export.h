#pragma once

#ifdef AVDEVICE_EXPORTS
#define AVDEVICE_API __declspec(dllexport)
#elif  AVDEVICE_DLL
#define AVDEVICE_API __declspec(dllimport)
#else
#define AVDEVICE_API
#endif