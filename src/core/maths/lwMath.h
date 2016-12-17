#ifndef __LWMATH_H__
#define __LWMATH_H__

#include "lwTypes.h"
#include <math.h>
#include <float.h>

namespace lwge
{
	namespace core
	{
#ifdef PI // make sure we don't collide with a define
#undef PI
#endif
		//! Constant for PI.
		const f32 PI = 3.14159265359f;

#ifdef PI64 // make sure we don't collide with a define
#undef PI64
#endif
		//! Constant for 64bit PI.
		const f64 PI64 = 3.1415926535897932384626433832795028841971693993751;

		//! 32bit Constant for converting from degrees to radians
		const f32 DEGTORAD = PI / 180.0f;

		//! 32bit constant for converting from radians to degrees (formally known as GRAD_PI)
		const f32 RADTODEG = 180.0f / PI;

		//! 64bit constant for converting from degrees to radians (formally known as GRAD_PI2)
		const f64 DEGTORAD64 = PI64 / 180.0;

		//! 64bit constant for converting from radians to degrees
		const f64 RADTODEG64 = 180.0 / PI64;

		//! Utility function to convert a radian value to degrees
		/** Provided as it can be clearer to write radToDeg(X) than RADTODEG * X
		\param radians	The radians value to convert to degrees.
		*/
		inline f32 radToDeg(f32 radians)
		{
			return RADTODEG * radians;
		}

		//! Utility function to convert a radian value to degrees
		/** Provided as it can be clearer to write radToDeg(X) than RADTODEG * X
		\param radians	The radians value to convert to degrees.
		*/
		inline f64 radToDeg(f64 radians)
		{
			return RADTODEG64 * radians;
		}

		//! Utility function to convert a degrees value to radians
		/** Provided as it can be clearer to write degToRad(X) than DEGTORAD * X
		\param degrees	The degrees value to convert to radians.
		*/
		inline f32 degToRad(f32 degrees)
		{
			return DEGTORAD * degrees;
		}

		//! Utility function to convert a degrees value to radians
		/** Provided as it can be clearer to write degToRad(X) than DEGTORAD * X
		\param degrees	The degrees value to convert to radians.
		*/
		inline f64 degToRad(f64 degrees)
		{
			return DEGTORAD64 * degrees;
		}

		//! returns linear interpolation of a and b with ratio t
		//! \return: a if t==0, b if t==1, and the linear interpolation else
		template<class T>
		inline T lerp(const T& a, const T& b, const f32 t)
		{
			return (T)(a*(1.f - t)) + (b*t);
		}

		//! returns if a equals b, taking possible rounding errors into account
		inline bool equals(const f64 a, const f64 b, const f64 tolerance = LDBL_EPSILON)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals b, taking possible rounding errors into account
		inline bool equals(const f32 a, const f32 b, const f32 tolerance = FLT_EPSILON)
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals b, not using any rounding tolerance
		inline bool equals(const s32 a, const s32 b)
		{
			return (a == b);
		}

		inline bool equals(const u32 a, const u32 b)
		{
			return (a == b);
		}

		inline bool equals(const u64 a, const u64 b)
		{
			return (a == b);
		}

		inline bool equals(const s64 a, const s64 b)
		{
			return (a == b);
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const f64 a, const f64 tolerance = LDBL_EPSILON)
		{
			return fabs(a) <= tolerance;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const f32 a, const f32 tolerance = FLT_EPSILON)
		{
			return fabsf(a) <= tolerance;
		}

		//! returns if a equals not zero, taking rounding errors into account
		inline bool isnotzero(const f32 a, const f32 tolerance = FLT_EPSILON)
		{
			return fabsf(a) > tolerance;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const s32 a, const s32 tolerance = 0)
		{
			return a == 0;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const u32 a, const u32 tolerance = 0)
		{
			return a == 0;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const u64 a, const u64 tolerance = 0)
		{
			return a == 0;
		}

		//! returns if a equals zero, taking rounding errors into account
		inline bool iszero(const s64 a, const s64 tolerance = 0)
		{
			return a == 0;
		}
	}
}

#endif