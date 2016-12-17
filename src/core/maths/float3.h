#ifndef __FLOAT3_H__
#define __FLOAT3_H__

#include "lwMath.h"

namespace lwge
{
	namespace core
	{

		//! 3d vector template class with lots of operators and methods.
		/** The float3 class is used in Irrlicht for three main purposes:
			1) As a direction vector (most of the methods assume this).
			2) As a position in 3d space (which is synonymous with a direction vector from the origin to this position).
			3) To hold three Euler rotations, where x is pitch, y is yaw and z is roll.
			*/
		class float3
		{
		public:
			//! Default constructor (null vector).
			float3() : x(0), y(0), z(0) {}
			//! Constructor with three different values
			float3(f32 nx, f32 ny, f32 nz) : x(nx), y(ny), z(nz) {}
			//! Constructor with the same value for all elements
			explicit float3(f32 n) : x(n), y(n), z(n) {}
			//! Copy constructor
			float3(const float3& other) : x(other.x), y(other.y), z(other.z) {}

			// operators
			float3	operator-	() const					{ return float3(-x, -y, -z); }
			float3	operator+	(const float3& other) const { return float3(x + other.x, y + other.y, z + other.z); }
			float3	operator-	(const float3& other) const { return float3(x - other.x, y - other.y, z - other.z); }
			float3	operator*	(const float3& other) const { return float3(x * other.x, y * other.y, z * other.z); }
			float3	operator/	(const float3& other) const { return float3(x / other.x, y / other.y, z / other.z); }

			float3& operator=	(const float3& other)		{ x = other.x; y = other.y; z = other.z; return *this; }
			float3& operator+=	(const float3& other)		{ x += other.x; y += other.y; z += other.z; return *this; }
			float3& operator-=	(const float3& other)		{ x -= other.x; y -= other.y; z -= other.z; return *this; }
			float3& operator*=	(const float3& other)		{ x *= other.x; y *= other.y; z *= other.z; return *this; }
			float3& operator/=	(const float3& other)		{ x /= other.x; y /= other.y; z /= other.z; return *this; }

			float3	operator+	(const f32 v) const			{ return float3(x + v, y + v, z + v); }
			float3	operator-	(const f32 v) const			{ return float3(x - v, y - v, z - v); }
			float3	operator*	(const f32 v) const			{ return float3(x * v, y * v, z * v); }
			float3	operator/	(const f32 v) const			{ f32 i = (f32)1.0 / v; return float3(x * i, y * i, z * i); }

			float3& operator+=	(const f32 v)				{ x += v; y += v; z += v; return *this; }
			float3& operator-=	(const f32 v)				{ x -= v; y -= v; z -= v; return *this; }
			float3& operator*=	(const f32 v)				{ x *= v; y *= v; z *= v; return *this; }
			float3& operator/=	(const f32 v)				{ f32 i = (f32)1.0 / v; x *= i; y *= i; z *= i; return *this; }

			bool	operator==	(const float3& other) const	{ return equals(other); }
			bool	operator!=	(const float3& other) const	{ return !equals(other); }

			// functions

			//! returns if this vector equals the other one, taking floating point rounding errors into account
			bool equals(const float3& other) const
			{
				return core::equals(x, other.x) &&
					core::equals(y, other.y) &&
					core::equals(z, other.z);
			}

			float3& set(const f32 nx, const f32 ny, const f32 nz) { x = nx; y = ny; z = nz; return *this; }
			float3& set(const float3& p) { x = p.x; y = p.y; z = p.z; return *this; }

			//! Get length of the vector.
			f32 getLength() const { return sqrt(x*x + y*y + z*z); }

			//! Get squared length of the vector.
			/** This is useful because it is much faster than getLength().
			\return Squared length of the vector. */
			f32 getLengthSQ() const { return x*x + y*y + z*z; }

			//! Get the dot product with another vector.
			f32 dotProduct(const float3& other) const
			{
				return x*other.x + y*other.y + z*other.z;
			}

			//! Get distance from another point.
			/** Here, the vector is interpreted as point in 3 dimensional space. */
			f32 getDistanceFrom(const float3& other) const
			{
				return float3(x - other.x, y - other.y, z - other.z).getLength();
			}

			//! Returns squared distance from another point.
			/** Here, the vector is interpreted as point in 3 dimensional space. */
			f32 getDistanceFromSQ(const float3& other) const
			{
				return float3(x - other.x, y - other.y, z - other.z).getLengthSQ();
			}

			//! Calculates the cross product with another vector.
			/** \param p Vector to multiply with.
			\return Crossproduct of this vector with p. */
			float3 crossProduct(const float3& p) const
			{
				return float3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
			}

			//! Normalizes the vector.
			/** In case of the 0 vector the result is still 0, otherwise
			the length of the vector will be 1.
			\return Reference to this vector after normalization. */
			float3& normalize()
			{
				f64 length = x*x + y*y + z*z;
				if (length == 0) // this check isn't an optimization but prevents getting NAN in the sqrt.
					return *this;
				length = 1.0f / length;

				x = (f32)(x * length);
				y = (f32)(y * length);
				z = (f32)(z * length);
				return *this;
			}

			//! x coordinate of the vector
			f32 x;

			//! y coordinate of the vector
			f32 y;

			//! z coordinate of the vector
			f32 z;
		};

	} // end namespace core
} // end namespace lwge

#endif

