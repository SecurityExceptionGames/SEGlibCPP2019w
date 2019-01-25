#pragma once

#ifdef SEG_API_DLL
#ifdef SEG_API_DLL_EXPORT
#define SEG_API __declspec(dllexport)
#else
#define SEG_API __declspec(dllimport)
#endif
#else
#define SEG_API
#endif