#pragma once
#ifdef HIYAZUTILS_PLATFORM_WINDOWS
#ifdef HIYAZUTILS_BUILD_DLL
#define HIYAZUTILS_API __declspec(dllexport)
#else
#define HIYAZUTILS_API __declspec(dllimport)
#endif
#else
#error HIYAZUTILS Only Support Windows!
#endif
// HIYAZUTILS_PLATFORM_WINDOWS;HIYAZUTILS_BUILD_DLL;HIYAZUTILS_API;