#ifndef __FLOAT2_H__
#define __FLOAT2_H__

#include "lwMath.h"

namespace lwge
{
	namespace core
	{
		class float2
		{
		public:
			//! Default constructor (null vector)
			float2() : x(0.0f), y(0.0f) {}
			//! Constructor with two different values
			float2(f32 nx, f32 ny) : x(nx), y(ny) {}
			//! Constructor with the same value for both members
			explicit float2(f32 n) : x(n), y(n) {}
			//! Copy constructor
			float2(const float2& other) : x(other.x), y(other.y) {}

			// operators
			float2	operator-	() const					{ return float2(-x, -y); }

			float2	operator+	(const float2& other) const	{ return float2(x + other.x, y + other.y); }
			float2	operator-	(const float2& other) const	{ return float2(x - other.x, y - other.y); }
			float2	operator*	(const float2& other) const	{ return float2(x * other.x, y * other.y); }
			float2	operator/	(const float2& other) const	{ return float2(x / other.x, y / other.y); }

			float2	operator+	(const f32 v) const			{ return float2(x + v, y + v); }
			float2	operator-	(const f32 v) const			{ return float2(x - v, y - v); }
			float2	operator*	(const f32 v) const			{ return float2(x * v, y * v); }
			float2	operator/	(const f32 v) const			{ return float2(x / v, y / v); }

			float2& operator=	(const float2& other)		{ x = other.x; y = other.y; return *this; }			
			float2& operator+=	(const float2& other)		{ x += other.x; y += other.y; return *this; }
			float2& operator-=	(const float2& other)		{ x -= other.x; y -= other.y; return *this; }
			float2& operator*=	(const float2& other)		{ x *= other.x; y *= other.y; return *this; }
			float2& operator/=	(const float2& other)		{ x /= other.x; y /= other.y; return *this; }

			float2& operator+=	(const f32 v)				{ x += v; y += v; return *this; }
			float2& operator-=	(const f32 v)				{ x -= v; y -= v; return *this; }
			float2& operator*=	(const f32 v)				{ x *= v; y *= v; return *this; }
			float2& operator/=	(const f32 v)				{ x /= v; y /= v; return *this; }

			bool	operator==	(const float2& other) const	{ return equals(other); }
			bool	operator!=	(const float2& other) const	{ return !equals(other); }

			// functions

			//! Checks if this vector equals the other one.
			/** Takes floating point rounding errors into account.
			\param other Vector to compare with.
			\return True if the two vector are (almost) equal, else false. */
			bool equals(const float2& other) const
			{
				return core::equals(x, other.x) && core::equals(y, other.y);
			}

			float2& set(f32 nx, f32 ny) { x = nx; y = ny; return *this; }
			float2& set(const float2& p) { x = p.x; y = p.y; return *this; }

			//! Gets the length of the vector.
			/** \return The length of the vector. */
			f32 getLength() const { return sqrt(x*x + y*y); }

			//! Get the squared length of this vector
			/** This is useful because it is much faster than getLength().
			\return The squared length of the vector. */
			f32 getLengthSQ() const { return x*x + y*y; }

			//! Get the dot product of this vector with another.
			/** \param other Other vector to take dot product with.
			\return The dot product of the two vectors. */
			f32 dotProduct(const float2& other) const
			{
				return x*other.x + y*other.y;
			}

			//! Gets distance from another point.
			/** Here, the vector is interpreted as a point in 2-dimensional space.
			\param other Other vector to measure from.
			\return Distance from other point. */
			f32 getDistanceFrom(const float2& other) const
			{
				return float2(x - other.x, y - other.y).getLength();
			}

			//! Returns squared distance from another point.
			/** Here, the vector is interpreted as a point in 2-dimensional space.
			\param other Other vector to measure from.
			\return Squared distance from other point. */
			f32 getDistanceFromSQ(const float2& other) const
			{
				return float2(x - other.x, y - other.y).getLengthSQ();
			}

			//! Normalize the vector.
			/** The null vector is left untouched.
			\return Reference to this vector, after normalization. */
			float2& normalize()
			{
				f32 length = x*x + y*y;
				if (length == 0)
					return *this;
				length = 1.0f / length;
				x = x * length;
				y = y * length;
				return *this;
			}

			//! x coordinate of vector.
			f32 x;

			//! y coordinate of vector.
			f32 y;
		};

	} // end namespace core
} // end namespace lwge

#endif

