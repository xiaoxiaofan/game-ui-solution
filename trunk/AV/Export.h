#pragma once

#ifdef AVDEVICE_EXPORTS
#define AVDEVICE_API __declspec(dllexport)
#else
#define AVDEVICE_API __declspec(dllimport)
#endif