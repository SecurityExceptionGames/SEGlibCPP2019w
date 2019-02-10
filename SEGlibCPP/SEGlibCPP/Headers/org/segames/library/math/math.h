#pragma once
#include <org/segames/library/dllmain.h>

#include <cmath>

#ifndef PI
#define PI 3.141592653589793238L	//PI
#endif

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace math
			{

				/*
					Returns the absolute of the given value
					* @param[in] value The value
				*/
				template<typename T> 
				inline T abs(const T value)
				{
					if (value < 0)
						return -value;
					return value;
				}

				/*
					A function that clamps the given value between the given minimum and maximum limit
					* @param[in] value The value to clamp
					* @param[in] min The minimum limit
					* @param[in] max The maximum limit
				*/
				template<typename T> 
				inline T clamp(const T value, const T min, const T max)
				{
					if (value > max)
						return max;
					else if (value < min)
						return min;
					return value;
				}

				/*
					Returns a reference to the given referenced value
				*/
				template<typename T> 
				inline T& max(T&& val)
				{
					return val;
				}

				/*
					A function that returns a reference to the latter value[s] if it is larger than the former, otherwise it returns a reference to the former
					* @param[in] val The former value
					* @param[in] vals The latter value[s]
				*/
				template<typename T, typename... T2> 
				inline T& max(T&& val, T2&&... vals)
				{
					auto& maxVal = max(vals...);
					if (maxVal > val)
						return maxVal;
					else
						return val;
				}

				/*
					Returns a reference to the given referenced value
				*/
				template<typename T> 
				inline T& min(T&& val)
				{
					return val;
				}

				/*
					A function that returns a reference to the latter value[s] if it is smaller than the former, otherwise it returns a reference to the former
					* @param[in] val The former value
					* @param[in] vals The latter value[s]
				*/
				template<typename T, typename... T2> 
				inline T& min(T&& val, T2&&... vals)
				{
					auto& maxVal = min(vals...);
					if (maxVal < val)
						return maxVal;
					else
						return val;
				}

				/*
					Performs a linear interpolation between x and y using a to weight between them
					* @param[in] x The primary value
					* @param[in] y The secondary value
					* @param[in] a The weighting value
				*/
				template<typename T> 
				inline T mix(const T x, const T y, const T a)
				{
					return x * (1 - a) + y * a;
				}

				/*
					Performes a smooth Hermite interpolation between 0 and 1 when edge0 < x < edge1. Undefined for edge0 >= edge1
					* @param[in] edge0 The lower edge of the Hermite function
					* @param[in] edge1 The upper edge of the Hermite function
					* @param[in] x The source value for interpolation
				*/
				template<typename T> 
				inline T smoothstep(const T edge0, const T edge1, const T x)
				{
					T t = clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
					return t * t * ((T)3.0 - (T)2.0 * t);
				}

				/*
					Converts the given degrees to radians
					* @param[in] degrees The degrees to convert to radians
				*/
				template<typename T> 
				inline T radians(const T degrees)
				{
					return (T)(degrees * PI / 180.0l);
				}

				/*
					Converts the given radians to degrees
					* @param[in] radians The radians to convert to degrees
				*/
				template<typename T> 
				inline T degrees(const T radians)
				{
					return (T)(radians * 180.0l / PI);
				}

				/*
					Returns a random value between 0 and 1 with standard floating point precision
				*/
				float SEG_API randomf();

				/*
					Returns a random value between 0 and 1 with double precision
				*/
				double SEG_API random();

			}

		}

	}

}