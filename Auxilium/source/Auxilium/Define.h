#pragma once
#include "axpch.h"

#ifdef AXLM_WINDOWS_PLATFORM 
	#ifdef AXLM_BUILD_DLL
		#define AXLM_API __declspec(dllexport)
	#else
		#define AXLM_API __declspec(dllimport)
	#endif
#else
		#error Auxilium Only Has Windows Support
#endif // AXLM_BUILD_DLL

#ifdef DEBUG 
	#define ASSERT(x, ...) {if (!(x)) {LOG ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else 
	#define ASSERT (x, ...)
#endif
#include "Catalyst.h"
#include "GeneralDefines.h"
using namespace Catalyst;
#define BIT(x) (0 << x)
#define AXLM Auxilium
#define DEBUG
#define CATCHBLOCK catch (std::invalid_argument e) { #ifdef DEBUG DebugLog(e.what); #endif }
#include "Log.h"
using namespace Auxilium;