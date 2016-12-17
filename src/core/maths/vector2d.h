#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include "lwMath.h"

namespace lwge
{
	namespace core
	{
		template <class T>
		class vector2
		{
		public:
			//! Default constructor (null vector)
			vector2() : x(0), y(0) {}
			//! Constructor with two different values
			vector2(T nx, T ny) : x(nx), y(ny) {}
			//! Constructor with the same value for both members
			explicit vector2(T n) : x(n), y(n) {}
			//! Copy constructor
			vector2(const vector2<T>& other) : x(other.x), y(other.y) {}

			// operators
			vector2<T>	operator-	() const							{ return vector2<T>(-x, -y); }

			vector2<T>	operator+	(const vector2<T>& other) const		{ return vector2<T>(x + other.x, y + other.y); }
			vector2<T>	operator-	(const vector2<T>& other) const		{ return vector2<T>(x - other.x, y - other.y); }
			vector2<T>	operator*	(const vector2<T>& other) const		{ return vector2<T>(x * other.x, y * other.y); }
			vector2<T>	operator/	(const vector2<T>& other) const		{ return vector2<T>(x / other.x, y / other.y); }

			vector2<T>	operator+	(const T v) const					{ return vector2<T>(x + v, y + v); }
			vector2<T>	operator-	(const T v) const					{ return vector2<T>(x - v, y - v); }
			vector2<T>	operator*	(const T v) const					{ return vector2<T>(x * v, y * v); }
			vector2<T>	operator/	(const T v) const					{ return vector2<T>(x / v, y / v); }

			vector2<T>& operator=	(const vector2<T>& other)			{ x = other.x; y = other.y; return *this; }			
			vector2<T>& operator+=	(const vector2<T>& other)			{ x += other.x; y += other.y; return *this; }
			vector2<T>& operator-=	(const vector2<T>& other)			{ x -= other.x; y -= other.y; return *this; }
			vector2<T>& operator*=	(const vector2<T>& other)			{ x *= other.x; y *= other.y; return *this; }
			vector2<T>& operator/=	(const vector2<T>& other)			{ x /= other.x; y /= other.y; return *this; }

			vector2<T>& operator+=	(const T v)							{ x += v; y += v; return *this; }
			vector2<T>& operator-=	(const T v)							{ x -= v; y -= v; return *this; }
			vector2<T>& operator*=	(const T v)							{ x *= v; y *= v; return *this; }
			vector2<T>& operator/=	(const T v)							{ x /= v; y /= v; return *this; }

			bool		operator==	(const vector2<T>& other) const		{ return equals(other); }
			bool		operator!=	(const vector2<T>& other) const		{ return !equals(other); }

			// functions

			//! Checks if this vector equals the other one.
			/** Takes floating point rounding errors into account.
			\param other Vector to compare with.
			\return True if the two vector are (almost) equal, else false. */
			bool equals(const vector2<T>& other) const
			{
				return equals(x, other.x) && equals(y, other.y);
			}

			vector2<T>& set(T nx, T ny) { x = nx; y = ny; return *this; }
			vector2<T>& set(const vector2<T>& p) { x = p.x; y = p.y; return *this; }

			//! Gets the length of the vector.
			/** \return The length of the vector. */
			T getLength() const { return sqrt(x*x + y*y); }

			//! Get the squared length of this vector
			/** This is useful because it is much faster than getLength().
			\return The squared length of the vector. */
			T getLengthSQ() const { return x*x + y*y; }

			//! Get the dot product of this vector with another.
			/** \param other Other vector to take dot product with.
			\return The dot product of the two vectors. */
			T dotProduct(const vector2<T>& other) const
			{
				return x*other.x + y*other.y;
			}

			//! Gets distance from another point.
			/** Here, the vector is interpreted as a point in 2-dimensional space.
			\param other Other vector to measure from.
			\return Distance from other point. */
			T getDistanceFrom(const vector2<T>& other) const
			{
				return vector2<T>(x - other.x, y - other.y).getLength();
			}

			//! Returns squared distance from another point.
			/** Here, the vector is interpreted as a point in 2-dimensional space.
			\param other Other vector to measure from.
			\return Squared distance from other point. */
			T getDistanceFromSQ(const vector2<T>& other) const
			{
				return vector2<T>(x - other.x, y - other.y).getLengthSQ();
			}

			//! Normalize the vector.
			/** The null vector is left untouched.
			\return Reference to this vector, after normalization. */
			vector2<T>& normalize()
			{
				f32 length = (f32)(x*x + y*y);
				if (length == 0)
					return *this;
				length = 1.0f / length;
				x = (T)(x * length);
				y = (T)(y * length);
				return *this;
			}

			//! Calculates the angle of this vector in degrees in the trigonometric sense.
			/** 0 is to the right (3 o'clock), values increase counter-clockwise.
			This method has been suggested by Pr3t3nd3r.
			\return Returns a value between 0 and 360. */
			f64 getAngleTrig() const
			{
				if (y == 0)
					return x < 0 ? 180 : 0;
				else
					if (x == 0)
						return y < 0 ? 270 : 90;

				if (y > 0)
					if (x > 0)
						return atan((irr::f64)y / (irr::f64)x) * RADTODEG64;
					else
						return 180.0 - atan((irr::f64)y / -(irr::f64)x) * RADTODEG64;
				else
					if (x > 0)
						return 360.0 - atan(-(irr::f64)y / (irr::f64)x) * RADTODEG64;
					else
						return 180.0 + atan(-(irr::f64)y / -(irr::f64)x) * RADTODEG64;
			}

			//! Calculates the angle of this vector in degrees in the counter trigonometric sense.
			/** 0 is to the right (3 o'clock), values increase clockwise.
			\return Returns a value between 0 and 360. */
			inline f64 getAngle() const
			{
				if (y == 0) // corrected thanks to a suggestion by Jox
					return x < 0 ? 180 : 0;
				else if (x == 0)
					return y < 0 ? 90 : 270;

				// don't use getLength here to avoid precision loss with s32 vectors
				// avoid floating-point trouble as sqrt(y*y) is occasionally larger than y, so clamp
				const f64 tmp = core::clamp(y / sqrt((f64)(x*x + y*y)), -1.0, 1.0);
				const f64 angle = atan(core::squareroot(1 - tmp*tmp) / tmp) * RADTODEG64;

				if (x>0 && y>0)
					return angle + 270;
				else
					if (x > 0 && y < 0)
						return angle + 90;
					else
						if (x < 0 && y < 0)
							return 90 - angle;
						else
							if (x < 0 && y>0)
								return 270 - angle;

				return angle;
			}

			//! Calculates the angle between this vector and another one in degree.
			/** \param b Other vector to test with.
			\return Returns a value between 0 and 90. */
			inline f64 getAngleWith(const vector2<T>& b) const
			{
				f64 tmp = (f64)(x*b.x + y*b.y);

				if (tmp == 0.0)
					return 90.0;

				tmp = tmp / core::squareroot((f64)((x*x + y*y) * (b.x*b.x + b.y*b.y)));
				if (tmp < 0.0)
					tmp = -tmp;
				if (tmp > 1.0) //   avoid floating-point trouble
					tmp = 1.0;

				return atan(sqrt(1 - tmp*tmp) / tmp) * RADTODEG64;
			}

			//! Returns if this vector interpreted as a point is on a line between two other points.
			/** It is assumed that the point is on the line.
			\param begin Beginning vector to compare between.
			\param end Ending vector to compare between.
			\return True if this vector is between begin and end, false if not. */
			bool isBetweenPoints(const vector2<T>& begin, const vector2<T>& end) const
			{
				if (begin.x != end.x)
				{
					return ((begin.x <= x && x <= end.x) ||
						(begin.x >= x && x >= end.x));
				}
				else
				{
					return ((begin.y <= y && y <= end.y) ||
						(begin.y >= y && y >= end.y));
				}
			}

			//! Creates an interpolated vector between this vector and another vector.
			/** \param other The other vector to interpolate with.
			\param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
			Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
			\return An interpolated vector.  This vector is not modified. */
			vector2<T> getInterpolated(const vector2<T>& other, f64 d) const
			{
				f64 inv = 1.0f - d;
				return vector2<T>((T)(other.x*inv + x*d), (T)(other.y*inv + y*d));
			}

			//! Creates a quadratically interpolated vector between this and two other vectors.
			/** \param v2 Second vector to interpolate with.
			\param v3 Third vector to interpolate with (maximum at 1.0f)
			\param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
			Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
			\return An interpolated vector. This vector is not modified. */
			vector2<T> getInterpolated_quadratic(const vector2<T>& v2, const vector2<T>& v3, f64 d) const
			{
				// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
				const f64 inv = 1.0f - d;
				const f64 mul0 = inv * inv;
				const f64 mul1 = 2.0f * d * inv;
				const f64 mul2 = d * d;

				return vector2<T>((T)(x * mul0 + v2.x * mul1 + v3.x * mul2),
					(T)(y * mul0 + v2.y * mul1 + v3.y * mul2));
			}

			//! Sets this vector to the linearly interpolated vector between a and b.
			/** \param a first vector to interpolate with, maximum at 1.0f
			\param b second vector to interpolate with, maximum at 0.0f
			\param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
			Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
			*/
			vector2<T>& interpolate(const vector2<T>& a, const vector2<T>& b, f64 d)
			{
				x = (T)((f64)b.x + ((a.x - b.x) * d));
				y = (T)((f64)b.y + ((a.y - b.y) * d));
				return *this;
			}

			//! x coordinate of vector.
			T x;

			//! y coordinate of vector.
			T y;
		};

		//! Typedef for f32 2d vector.
		typedef vector2<f32> vector2df;

		//! Typedef for integer 2d vector.
		typedef vector2<s32> vector2di;

		template<class S, class T>
		vector2<T> operator*(const S scalar, const vector2<T>& vector) { return vector*scalar; }

		// These methods are declared in dimension2d, but need definitions of vector2
		template<class T>
		dimension2d<T>::dimension2d(const vector2<T>& other) : Width(other.x), Height(other.y) { }

		template<class T>
		bool dimension2d<T>::operator==(const vector2<T>& other) const { return Width == other.x && Height == other.y; }

	} // end namespace core
} // end namespace irr

#endif

