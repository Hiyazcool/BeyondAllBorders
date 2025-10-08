#pragma once
#ifdef CATALYST_WINDOWS_PLATFORM
#ifdef CATALYST_BUILD_DLL
#define CATALYST_API __declspec(dllexport)
#else
#define CATALYST_API __declspec(dllimport)
#endif
#else
#error Auxilium Only Has Windows Support
#endif