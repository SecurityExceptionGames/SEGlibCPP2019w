#pragma once

// Compiler macros:
//	SEG_API_DLL						Enables the dll features of the API, dll-import as standard
//	SEG_API_DLL_EXPORT				Sets the dll to export
//	SEG_API_DEBUG					Enables all debug macros
//	SEG_API_DEBUG_THROW				Enables throwing of debug exception, eg. index out of bounds
//
//  SEG_API_MATH_NO_TYPEDEFS		Disables the typedefs in the math library
//
//	SEG_API_VECMATH_NO_TYPEDEFS		Disables the typedefs in vecmath.h
//  SEG_API_VECMATH_ZERO_OFFSET		Long double offset for floating point precision near zero
//
//  SEG_API_GL_NO_TYPEDEFS			Disables the typedefs in the OpenGL part of the library

#ifdef SEG_API_DEBUG //Enables all debug macros
#ifndef SEG_API_DEBUG_THROW
#define SEG_API_DEBUG_THROW
#endif
#endif

#ifndef NULL
#define NULL 0						//Null
#endif

#ifndef TRUE
#define TRUE 1						//True
#endif

#ifndef FALSE
#define FALSE 0						//False
#endif