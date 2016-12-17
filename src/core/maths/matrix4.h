#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "lwMath.h"
#include "float3.h"
#include "float2.h"
//#include "plane3d.h"
//#include "aabbox3d.h"
//#include "rect.h"
//#include "irrString.h"
#include <string.h>

// enable this to keep track of changes to the matrix
// and make simpler identity check for seldomly changing matrices
// otherwise identity check will always compare the elements
//#define USE_MATRIX_TEST

// this is only for debugging purposes
//#define USE_MATRIX_TEST_DEBUG

#if defined( USE_MATRIX_TEST_DEBUG )

struct MatrixTest
{
	MatrixTest () : ID(0), Calls(0) {}
	char buf[256];
	int Calls;
	int ID;
};
static MatrixTest MTest;

#endif

namespace lwge
{
namespace core
{

	//! 4x4 matrix. Mostly used as transformation matrix for 3d calculations.
	/** The matrix is a D3D style matrix, row major with translations in the 4th row. */
	class matrix4
	{
		public:

			//! Constructor Flags
			enum eConstructor
			{
				EM4CONST_NOTHING = 0,
				EM4CONST_COPY,
				EM4CONST_IDENTITY,
				EM4CONST_TRANSPOSED,
				EM4CONST_INVERSE,
				EM4CONST_INVERSE_TRANSPOSED
			};

			//! Default constructor
			/** \param constructor Choose the initialization style */
			matrix4( eConstructor constructor = EM4CONST_IDENTITY );
			//! Copy constructor
			/** \param other Other matrix to copy from
			\param constructor Choose the initialization style */
			matrix4(const matrix4& other, eConstructor constructor = EM4CONST_COPY);

			//! Simple operator for directly accessing every element of the matrix.
			f32& operator()(const s32 row, const s32 col)
			{
#if defined ( USE_MATRIX_TEST )
				definitelyIdentityMatrix=false;
#endif
				return m[ row * 4 + col ];
			}

			//! Simple operator for directly accessing every element of the matrix.
			const f32& operator()(const s32 row, const s32 col) const { return m[row * 4 + col]; }

			//! Simple operator for linearly accessing every element of the matrix.
			f32& operator[](u32 index)
			{
#if defined ( USE_MATRIX_TEST )
				definitelyIdentityMatrix=false;
#endif
				return m[index];
			}

			//! Simple operator for linearly accessing every element of the matrix.
			const f32& operator[](u32 index) const { return m[index]; }

			//! Sets this matrix equal to the other matrix.
			inline matrix4& operator=(const matrix4 &other);

			//! Sets all elements of this matrix to the value.
			inline matrix4& operator=(const f32& scalar);

			//! Returns pointer to internal array
			const f32* pointer() const { return m; }
			f32* pointer()
			{
#if defined ( USE_MATRIX_TEST )
				definitelyIdentityMatrix=false;
#endif
				return m;
			}

			//! Returns true if other matrix is equal to this matrix.
			bool operator==(const matrix4 &other) const;

			//! Returns true if other matrix is not equal to this matrix.
			bool operator!=(const matrix4 &other) const;

			//! Add another matrix.
			matrix4 operator+(const matrix4& other) const;

			//! Add another matrix.
			matrix4& operator+=(const matrix4& other);

			//! Subtract another matrix.
			matrix4 operator-(const matrix4& other) const;

			//! Subtract another matrix.
			matrix4& operator-=(const matrix4& other);

			//! set this matrix to the product of two matrices
			/** Calculate b*a */
			inline matrix4& setbyproduct(const matrix4& other_a,const matrix4& other_b );

			//! Set this matrix to the product of two matrices
			/** Calculate b*a, no optimization used,
			use it if you know you never have a identity matrix */
			matrix4& setbyproduct_nocheck(const matrix4& other_a,const matrix4& other_b );

			//! Multiply by another matrix.
			/** Calculate other*this */
			matrix4 operator*(const matrix4& other) const;

			//! Multiply by another matrix.
			/** Calculate and return other*this */
			matrix4& operator*=(const matrix4& other);

			//! Multiply by scalar.
			matrix4 operator*(const f32& scalar) const;

			//! Multiply by scalar.
			matrix4& operator*=(const f32& scalar);

			//! Set matrix to identity.
			inline matrix4& makeIdentity();

			//! Returns true if the matrix is the identity matrix
			inline bool isIdentity() const;

			//! Returns true if the matrix is orthogonal
			inline bool isOrthogonal() const;

			//! Returns true if the matrix is the identity matrix
			bool isIdentity_integer_base () const;

			//! Set the translation of the current matrix. Will erase any previous values.
			matrix4& setTranslation( const float3& translation );

			//! Gets the current translation
			float3 getTranslation() const;

			//! Set the inverse translation of the current matrix. Will erase any previous values.
			matrix4& setInverseTranslation( const float3& translation );

			//! Make a rotation matrix from Euler angles. The 4th row and column are unmodified.
			inline matrix4& setRotationRadians( const float3& rotation );

			//! Make a rotation matrix from Euler angles. The 4th row and column are unmodified.
			matrix4& setRotationDegrees( const float3& rotation );

			//! Returns the rotation, as set by setRotation().
			/** This code was orginally written by by Chev. */
			core::float3 getRotationDegrees() const;

			//! Make an inverted rotation matrix from Euler angles.
			/** The 4th row and column are unmodified. */
			inline matrix4& setInverseRotationRadians( const float3& rotation );

			//! Make an inverted rotation matrix from Euler angles.
			/** The 4th row and column are unmodified. */
			inline matrix4& setInverseRotationDegrees( const float3& rotation );

			//! Make a rotation matrix from angle and axis, assuming left handed rotation.
			/** The 4th row and column are unmodified. */
			inline matrix4& setRotationAxisRadians(const f32& angle, const float3& axis);

			//! Set Scale
			matrix4& setScale( const float3& scale );

			//! Set Scale
			matrix4& setScale( const f32 scale ) { return setScale(core::float3(scale,scale,scale)); }

			//! Get Scale
			core::float3 getScale() const;

			//! Translate a vector by the inverse of the translation part of this matrix.
			void inverseTranslateVect( float3& vect ) const;

			//! Rotate a vector by the inverse of the rotation part of this matrix.
			void inverseRotateVect( float3& vect ) const;

			//! Rotate a vector by the rotation part of this matrix.
			void rotateVect( float3& vect ) const;

			//! An alternate transform vector method, writing into a second vector
			void rotateVect(core::float3& out, const core::float3& in) const;

			//! An alternate transform vector method, writing into an array of 3 floats
			void rotateVect(f32 *out,const core::float3 &in) const;

			//! Transforms the vector by this matrix
			void transformVect( float3& vect) const;

			//! Transforms input vector by this matrix and stores result in output vector
			void transformVect( float3& out, const float3& in ) const;

			//! An alternate transform vector method, writing into an array of 4 floats
			void transformVect(f32 *out,const core::float3 &in) const;

			//! An alternate transform vector method, reading from and writing to an array of 3 floats
			void transformVec3(f32 *out, const f32 * in) const;

			//! Translate a vector by the translation part of this matrix.
			void translateVect( float3& vect ) const;

			//! Transforms a plane by this matrix
			//void transformPlane( core::plane3d<f32> &plane) const;

			//! Transforms a plane by this matrix
			//void transformPlane( const core::plane3d<f32> &in, core::plane3d<f32> &out) const;

			//! Transforms a axis aligned bounding box
			/** The result box of this operation may not be accurate at all. For
			correct results, use transformBoxEx() */
			//void transformBox(core::aabbox3d<f32>& box) const;

			//! Transforms a axis aligned bounding box
			/** The result box of this operation should by accurate, but this operation
			is slower than transformBox(). */
			//void transformBoxEx(core::aabbox3d<f32>& box) const;

			//! Multiplies this matrix by a 1x4 matrix
			void multiplyWith1x4Matrix(f32* matrix) const;

			//! Calculates inverse of matrix. Slow.
			/** \return Returns false if there is no inverse matrix.*/
			bool makeInverse();


			//! Inverts a primitive matrix which only contains a translation and a rotation
			/** \param out: where result matrix is written to. */
			bool getInversePrimitive ( matrix4& out ) const;

			//! Gets the inversed matrix of this one
			/** \param out: where result matrix is written to.
			\return Returns false if there is no inverse matrix. */
			bool getInverse(matrix4& out) const;

			//! Builds a right-handed perspective projection matrix based on a field of view
			matrix4& buildProjectionMatrixPerspectiveFovRH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar);

			//! Builds a left-handed perspective projection matrix based on a field of view
			matrix4& buildProjectionMatrixPerspectiveFovLH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar);

			//! Builds a left-handed perspective projection matrix based on a field of view, with far plane at infinity
			matrix4& buildProjectionMatrixPerspectiveFovInfinityLH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 epsilon=0);

			//! Builds a right-handed perspective projection matrix.
			matrix4& buildProjectionMatrixPerspectiveRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);

			//! Builds a left-handed perspective projection matrix.
			matrix4& buildProjectionMatrixPerspectiveLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);

			//! Builds a left-handed orthogonal projection matrix.
			matrix4& buildProjectionMatrixOrthoLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);

			//! Builds a right-handed orthogonal projection matrix.
			matrix4& buildProjectionMatrixOrthoRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar);

			//! Builds a left-handed look-at matrix.
			matrix4& buildCameraLookAtMatrixLH(
					const float3& position,
					const float3& target,
					const float3& upVector);

			//! Builds a right-handed look-at matrix.
			matrix4& buildCameraLookAtMatrixRH(
					const float3& position,
					const float3& target,
					const float3& upVector);

			//! Builds a matrix that flattens geometry into a plane.
			/** \param light: light source
			\param plane: plane into which the geometry if flattened into
			\param point: value between 0 and 1, describing the light source.
			If this is 1, it is a point light, if it is 0, it is a directional light. */
			//matrix4& buildShadowMatrix(const core::float3& light, core::plane3df plane, f32 point=1.0f);

			//! Builds a matrix which transforms a normalized Device Coordinate to Device Coordinates.
			/** Used to scale <-1,-1><1,1> to viewport, for example from <-1,-1> <1,1> to the viewport <0,0><0,640> */
			//matrix4& buildNDCToDCMatrix( const core::rect<s32>& area, f32 zScale);

			//! Creates a new matrix as interpolated matrix from two other ones.
			/** \param b: other matrix to interpolate with
			\param time: Must be a value between 0 and 1. */
			matrix4 interpolate(const core::matrix4& b, f32 time) const;

			//! Gets transposed matrix
			matrix4 getTransposed() const;

			//! Gets transposed matrix
			inline void getTransposed( matrix4& dest ) const;

			//! Builds a matrix that rotates from one vector to another
			/** \param from: vector to rotate from
			\param to: vector to rotate to
			 */
			matrix4& buildRotateFromTo(const core::float3& from, const core::float3& to);

			//! Builds a combined matrix which translates to a center before rotation and translates from origin afterwards
			/** \param center Position to rotate around
			\param translate Translation applied after the rotation
			 */
			void setRotationCenter(const core::float3& center, const core::float3& translate);

			//! Builds a matrix which rotates a source vector to a look vector over an arbitrary axis
			/** \param camPos: viewer position in world coo
			\param center: object position in world-coo and rotation pivot
			\param translation: object final translation from center
			\param axis: axis to rotate about
			\param from: source vector to rotate from
			 */
			void buildAxisAlignedBillboard(const core::float3& camPos,
						const core::float3& center,
						const core::float3& translation,
						const core::float3& axis,
						const core::float3& from);

			/*
				construct 2D Texture transformations
				rotate about center, scale, and transform.
			*/
			//! Set to a texture transformation matrix with the given parameters.
			matrix4& buildTextureTransform( f32 rotateRad,
					const core::float2 &rotatecenter,
					const core::float2 &translate,
					const core::float2 &scale);

			//! Set texture transformation rotation
			/** Rotate about z axis, recenter at (0.5,0.5).
			Doesn't clear other elements than those affected
			\param radAngle Angle in radians
			\return Altered matrix */
			matrix4& setTextureRotationCenter( f32 radAngle );

			//! Set texture transformation translation
			/** Doesn't clear other elements than those affected.
			\param x Offset on x axis
			\param y Offset on y axis
			\return Altered matrix */
			matrix4& setTextureTranslate( f32 x, f32 y );

			//! Set texture transformation translation, using a transposed representation
			/** Doesn't clear other elements than those affected.
			\param x Offset on x axis
			\param y Offset on y axis
			\return Altered matrix */
			matrix4& setTextureTranslateTransposed( f32 x, f32 y );

			//! Set texture transformation scale
			/** Doesn't clear other elements than those affected.
			\param sx Scale factor on x axis
			\param sy Scale factor on y axis
			\return Altered matrix. */
			matrix4& setTextureScale( f32 sx, f32 sy );

			//! Set texture transformation scale, and recenter at (0.5,0.5)
			/** Doesn't clear other elements than those affected.
			\param sx Scale factor on x axis
			\param sy Scale factor on y axis
			\return Altered matrix. */
			matrix4& setTextureScaleCenter( f32 sx, f32 sy );

			//! Sets all matrix data members at once
			matrix4& setM(const f32* data);

			//! Sets if the matrix is definitely identity matrix
			void setDefinitelyIdentityMatrix( bool isDefinitelyIdentityMatrix);

			//! Gets if the matrix is definitely identity matrix
			bool getDefinitelyIdentityMatrix() const;

			//! Compare two matrices using the equal method
			//bool equals(const core::matrix4& other, const f32 tolerance=(f32)ROUNDING_ERROR_f64) const;

		private:
			//! Matrix data, stored in row-major order
			f32 m[16];
#if defined ( USE_MATRIX_TEST )
			//! Flag is this matrix is identity matrix
			mutable u32 definitelyIdentityMatrix;
#endif
#if defined ( USE_MATRIX_TEST_DEBUG )
			u32 id;
			mutable u32 calls;
#endif

	};

	// Default constructor
	inline matrix4::matrix4( eConstructor constructor )
#if defined ( USE_MATRIX_TEST )
		: definitelyIdentityMatrix(BIT_UNTESTED)
#endif
#if defined ( USE_MATRIX_TEST_DEBUG )
		,id ( MTest.ID++), calls ( 0 )
#endif
	{
		switch ( constructor )
		{
			case EM4CONST_NOTHING:
			case EM4CONST_COPY:
				break;
			case EM4CONST_IDENTITY:
			case EM4CONST_INVERSE:
			default:
				makeIdentity();
				break;
		}
	}

	// Copy constructor
	inline matrix4::matrix4( const matrix4& other, eConstructor constructor)
#if defined ( USE_MATRIX_TEST )
		: definitelyIdentityMatrix(BIT_UNTESTED)
#endif
#if defined ( USE_MATRIX_TEST_DEBUG )
		,id ( MTest.ID++), calls ( 0 )
#endif
	{
		switch ( constructor )
		{
			case EM4CONST_IDENTITY:
				makeIdentity();
				break;
			case EM4CONST_NOTHING:
				break;
			case EM4CONST_COPY:
				*this = other;
				break;
			case EM4CONST_TRANSPOSED:
				other.getTransposed(*this);
				break;
			case EM4CONST_INVERSE:
				if (!other.getInverse(*this))
					memset(m, 0, 16*sizeof(f32));
				break;
			case EM4CONST_INVERSE_TRANSPOSED:
				if (!other.getInverse(*this))
					memset(m, 0, 16*sizeof(f32));
				else
					*this=getTransposed();
				break;
		}
	}

	//! Add another matrix.
	inline matrix4 matrix4::operator+(const matrix4& other) const
	{
		matrix4 temp ( EM4CONST_NOTHING );

		temp[0] = m[0]+other[0];
		temp[1] = m[1]+other[1];
		temp[2] = m[2]+other[2];
		temp[3] = m[3]+other[3];
		temp[4] = m[4]+other[4];
		temp[5] = m[5]+other[5];
		temp[6] = m[6]+other[6];
		temp[7] = m[7]+other[7];
		temp[8] = m[8]+other[8];
		temp[9] = m[9]+other[9];
		temp[10] = m[10]+other[10];
		temp[11] = m[11]+other[11];
		temp[12] = m[12]+other[12];
		temp[13] = m[13]+other[13];
		temp[14] = m[14]+other[14];
		temp[15] = m[15]+other[15];

		return temp;
	}

	//! Add another matrix.
	inline matrix4& matrix4::operator+=(const matrix4& other)
	{
		m[0]+=other[0];
		m[1]+=other[1];
		m[2]+=other[2];
		m[3]+=other[3];
		m[4]+=other[4];
		m[5]+=other[5];
		m[6]+=other[6];
		m[7]+=other[7];
		m[8]+=other[8];
		m[9]+=other[9];
		m[10]+=other[10];
		m[11]+=other[11];
		m[12]+=other[12];
		m[13]+=other[13];
		m[14]+=other[14];
		m[15]+=other[15];

		return *this;
	}

	//! Subtract another matrix.
	inline matrix4 matrix4::operator-(const matrix4& other) const
	{
		matrix4 temp ( EM4CONST_NOTHING );

		temp[0] = m[0]-other[0];
		temp[1] = m[1]-other[1];
		temp[2] = m[2]-other[2];
		temp[3] = m[3]-other[3];
		temp[4] = m[4]-other[4];
		temp[5] = m[5]-other[5];
		temp[6] = m[6]-other[6];
		temp[7] = m[7]-other[7];
		temp[8] = m[8]-other[8];
		temp[9] = m[9]-other[9];
		temp[10] = m[10]-other[10];
		temp[11] = m[11]-other[11];
		temp[12] = m[12]-other[12];
		temp[13] = m[13]-other[13];
		temp[14] = m[14]-other[14];
		temp[15] = m[15]-other[15];

		return temp;
	}

	//! Subtract another matrix.
	inline matrix4& matrix4::operator-=(const matrix4& other)
	{
		m[0]-=other[0];
		m[1]-=other[1];
		m[2]-=other[2];
		m[3]-=other[3];
		m[4]-=other[4];
		m[5]-=other[5];
		m[6]-=other[6];
		m[7]-=other[7];
		m[8]-=other[8];
		m[9]-=other[9];
		m[10]-=other[10];
		m[11]-=other[11];
		m[12]-=other[12];
		m[13]-=other[13];
		m[14]-=other[14];
		m[15]-=other[15];

		return *this;
	}

	//! Multiply by scalar.
	inline matrix4 matrix4::operator*(const f32& scalar) const
	{
		matrix4 temp ( EM4CONST_NOTHING );

		temp[0] = m[0]*scalar;
		temp[1] = m[1]*scalar;
		temp[2] = m[2]*scalar;
		temp[3] = m[3]*scalar;
		temp[4] = m[4]*scalar;
		temp[5] = m[5]*scalar;
		temp[6] = m[6]*scalar;
		temp[7] = m[7]*scalar;
		temp[8] = m[8]*scalar;
		temp[9] = m[9]*scalar;
		temp[10] = m[10]*scalar;
		temp[11] = m[11]*scalar;
		temp[12] = m[12]*scalar;
		temp[13] = m[13]*scalar;
		temp[14] = m[14]*scalar;
		temp[15] = m[15]*scalar;

		return temp;
	}

	//! Multiply by scalar.
	inline matrix4& matrix4::operator*=(const f32& scalar)
	{
		m[0]*=scalar;
		m[1]*=scalar;
		m[2]*=scalar;
		m[3]*=scalar;
		m[4]*=scalar;
		m[5]*=scalar;
		m[6]*=scalar;
		m[7]*=scalar;
		m[8]*=scalar;
		m[9]*=scalar;
		m[10]*=scalar;
		m[11]*=scalar;
		m[12]*=scalar;
		m[13]*=scalar;
		m[14]*=scalar;
		m[15]*=scalar;

		return *this;
	}

	//! Multiply by another matrix.
	inline matrix4& matrix4::operator*=(const matrix4& other)
	{
#if defined ( USE_MATRIX_TEST )
		// do checks on your own in order to avoid copy creation
		if ( !other.isIdentity() )
		{
			if ( this->isIdentity() )
			{
				return (*this = other);
			}
			else
			{
				matrix4 temp ( *this );
				return setbyproduct_nocheck( temp, other );
			}
		}
		return *this;
#else
		matrix4 temp ( *this );
		return setbyproduct_nocheck( temp, other );
#endif
	}

	//! multiply by another matrix
	// set this matrix to the product of two other matrices
	// goal is to reduce stack use and copy
	inline matrix4& matrix4::setbyproduct_nocheck(const matrix4& other_a,const matrix4& other_b )
	{
		const f32 *m1 = other_a.m;
		const f32 *m2 = other_b.m;

		m[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
		m[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
		m[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
		m[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];

		m[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
		m[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
		m[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
		m[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];

		m[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
		m[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
		m[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
		m[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];

		m[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
		m[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
		m[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
		m[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}


	//! multiply by another matrix
	// set this matrix to the product of two other matrices
	// goal is to reduce stack use and copy
	inline matrix4& matrix4::setbyproduct(const matrix4& other_a, const matrix4& other_b )
	{
#if defined ( USE_MATRIX_TEST )
		if ( other_a.isIdentity () )
			return (*this = other_b);
		else
		if ( other_b.isIdentity () )
			return (*this = other_a);
		else
			return setbyproduct_nocheck(other_a,other_b);
#else
		return setbyproduct_nocheck(other_a,other_b);
#endif
	}

	//! multiply by another matrix
	inline matrix4 matrix4::operator*(const matrix4& m2) const
	{
#if defined ( USE_MATRIX_TEST )
		// Testing purpose..
		if ( this->isIdentity() )
			return m2;
		if ( m2.isIdentity() )
			return *this;
#endif

		matrix4 m3 ( EM4CONST_NOTHING );

		const f32 *m1 = m;

		m3[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
		m3[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
		m3[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
		m3[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];

		m3[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
		m3[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
		m3[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
		m3[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];

		m3[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
		m3[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
		m3[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
		m3[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];

		m3[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
		m3[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
		m3[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
		m3[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
		return m3;
	}

	inline float3 matrix4::getTranslation() const
	{
		return float3(m[12], m[13], m[14]);
	}

	inline matrix4& matrix4::setTranslation( const float3& translation )
	{
		m[12] = translation.x;
		m[13] = translation.y;
		m[14] = translation.z;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	inline matrix4& matrix4::setInverseTranslation( const float3& translation )
	{
		m[12] = -translation.x;
		m[13] = -translation.y;
		m[14] = -translation.z;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	inline matrix4& matrix4::setScale( const float3& scale )
	{
		m[0] = scale.x;
		m[5] = scale.y;
		m[10] = scale.z;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	//! Returns the absolute values of the scales of the matrix.
	/**
	Note that this returns the absolute (positive) values unless only scale is set.
	Unfortunately it does not appear to be possible to extract any original negative
	values. The best that we could do would be to arbitrarily make one scale
	negative if one or three of them were negative.
	FIXME - return the original values.
	*/
	inline float3 matrix4::getScale() const
	{
		// See http://www.robertblum.com/articles/2005/02/14/decomposing-matrices

		// Deal with the 0 rotation case first
		// Prior to Irrlicht 1.6, we always returned this value.
		if(core::iszero(m[1]) && core::iszero(m[2]) &&
			core::iszero(m[4]) && core::iszero(m[6]) &&
			core::iszero(m[8]) && core::iszero(m[9]))
			return float3(m[0], m[5], m[10]);

		// We have to do the full calculation.
		return float3(sqrtf(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]),
							sqrtf(m[4] * m[4] + m[5] * m[5] + m[6] * m[6]),
							sqrtf(m[8] * m[8] + m[9] * m[9] + m[10] * m[10]));
	}
	
	inline matrix4& matrix4::setRotationDegrees( const float3& rotation )
	{
		return setRotationRadians( rotation * core::DEGTORAD );
	}
	
	inline matrix4& matrix4::setInverseRotationDegrees( const float3& rotation )
	{
		return setInverseRotationRadians( rotation * core::DEGTORAD );
	}

	inline matrix4& matrix4::setRotationRadians( const float3& rotation )
	{
		const f64 cr = cos( rotation.x );
		const f64 sr = sin( rotation.x );
		const f64 cp = cos( rotation.y );
		const f64 sp = sin( rotation.y );
		const f64 cy = cos( rotation.z );
		const f64 sy = sin( rotation.z );

		m[0] = (f32)( cp*cy );
		m[1] = (f32)( cp*sy );
		m[2] = (f32)( -sp );

		const f64 srsp = sr*sp;
		const f64 crsp = cr*sp;

		m[4] = (f32)( srsp*cy-cr*sy );
		m[5] = (f32)( srsp*sy+cr*cy );
		m[6] = (f32)( sr*cp );

		m[8] = (f32)( crsp*cy+sr*sy );
		m[9] = (f32)( crsp*sy-sr*cy );
		m[10] = (f32)( cr*cp );
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	//! Returns a rotation that is equivalent to that set by setRotationDegrees().
	/** This code was sent in by Chev.  Note that it does not necessarily return
	the *same* Euler angles as those set by setRotationDegrees(), but the rotation will
	be equivalent, i.e. will have the same result when used to rotate a vector or node. */
	inline core::float3 matrix4::getRotationDegrees() const
	{
		//const matrix4 &mat = *this;
		//core::float3 scale = getScale();
		//// we need to check for negative scale on to axes, which would bring up wrong results
		//if (scale.y<0 && scale.z<0)
		//{
		//	scale.y =-scale.y;
		//	scale.z =-scale.z;
		//}
		//else if (scale.x<0 && scale.z<0)
		//{
		//	scale.x =-scale.x;
		//	scale.z =-scale.z;
		//}
		//else if (scale.x<0 && scale.y<0)
		//{
		//	scale.x =-scale.x;
		//	scale.y =-scale.y;
		//}
		//const core::float3<f64> invScale(core::reciprocal(scale.x),core::reciprocal(scale.y),core::reciprocal(scale.z));

		//f64 y = -asin(core::clamp(mat[2]*invScale.x, -1.0, 1.0));
		//const f64 C = cos(y);
		//y *= RADTODEG64;

		//f64 rotx, roty, x, z;

		//if (!core::iszero(C))
		//{
		//	const f64 invC = core::reciprocal(C);
		//	rotx = mat[10] * invC * invScale.z;
		//	roty = mat[6] * invC * invScale.y;
		//	x = atan2( roty, rotx ) * RADTODEG64;
		//	rotx = mat[0] * invC * invScale.x;
		//	roty = mat[1] * invC * invScale.x;
		//	z = atan2( roty, rotx ) * RADTODEG64;
		//}
		//else
		//{
		//	x = 0.0;
		//	rotx = mat[5] * invScale.y;
		//	roty = -mat[4] * invScale.y;
		//	z = atan2( roty, rotx ) * RADTODEG64;
		//}

		//// fix values that get below zero
		//if (x < 0.0) x += 360.0;
		//if (y < 0.0) y += 360.0;
		//if (z < 0.0) z += 360.0;

		//return float3((f32)x,(f32)y,(f32)z);
		
		return float3();
	}

	//! Sets matrix to rotation matrix of inverse angles given as parameters
	inline matrix4& matrix4::setInverseRotationRadians( const float3& rotation )
	{
		f64 cr = cos( rotation.x );
		f64 sr = sin( rotation.x );
		f64 cp = cos( rotation.y );
		f64 sp = sin( rotation.y );
		f64 cy = cos( rotation.z );
		f64 sy = sin( rotation.z );

		m[0] = (f32)( cp*cy );
		m[4] = (f32)( cp*sy );
		m[8] = (f32)( -sp );

		f64 srsp = sr*sp;
		f64 crsp = cr*sp;

		m[1] = (f32)( srsp*cy-cr*sy );
		m[5] = (f32)( srsp*sy+cr*cy );
		m[9] = (f32)( sr*cp );

		m[2] = (f32)( crsp*cy+sr*sy );
		m[6] = (f32)( crsp*sy-sr*cy );
		m[10] = (f32)( cr*cp );
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	//! Sets matrix to rotation matrix defined by axis and angle, assuming LH rotation
	inline matrix4& matrix4::setRotationAxisRadians( const f32& angle, const float3& axis )
	{
 		const f64 c = cos(angle);
		const f64 s = sin(angle);
		const f64 t = 1.0 - c;

		const f64 tx  = t * axis.x;
		const f64 ty  = t * axis.y;		
		const f64 tz  = t * axis.z;

		const f64 sx  = s * axis.x;
		const f64 sy  = s * axis.y;
		const f64 sz  = s * axis.z;
		
		m[0] = (f32)(tx * axis.x + c);
		m[1] = (f32)(tx * axis.y + sz);
		m[2] = (f32)(tx * axis.z - sy);

		m[4] = (f32)(ty * axis.x - sz);
		m[5] = (f32)(ty * axis.y + c);
		m[6] = (f32)(ty * axis.z + sx);

		m[8]  = (f32)(tz * axis.x + sy);
		m[9]  = (f32)(tz * axis.y - sx);
		m[10] = (f32)(tz * axis.z + c);

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}


	/*!
	*/
	inline matrix4& matrix4::makeIdentity()
	{
		memset(m, 0, 16*sizeof(f32));
		m[0] = m[5] = m[10] = m[15] = (f32)1;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=true;
#endif
		return *this;
	}


	/*
		check identity with epsilon
		solve floating range problems..
	*/
	inline bool matrix4::isIdentity() const
	{
#if defined ( USE_MATRIX_TEST )
		if (definitelyIdentityMatrix)
			return true;
#endif
		if (!core::equals( m[12], (f32)0 ) || !core::equals( m[13], (f32)0 ) || !core::equals( m[14], (f32)0 ) || !core::equals( m[15], (f32)1 ))
			return false;

		if (!core::equals( m[ 0], (f32)1 ) || !core::equals( m[ 1], (f32)0 ) || !core::equals( m[ 2], (f32)0 ) || !core::equals( m[ 3], (f32)0 ))
			return false;

		if (!core::equals( m[ 4], (f32)0 ) || !core::equals( m[ 5], (f32)1 ) || !core::equals( m[ 6], (f32)0 ) || !core::equals( m[ 7], (f32)0 ))
			return false;

		if (!core::equals( m[ 8], (f32)0 ) || !core::equals( m[ 9], (f32)0 ) || !core::equals( m[10], (f32)1 ) || !core::equals( m[11], (f32)0 ))
			return false;
/*
		if (!core::equals( m[ 0], (f32)1 ) ||
			!core::equals( m[ 5], (f32)1 ) ||
			!core::equals( m[10], (f32)1 ) ||
			!core::equals( m[15], (f32)1 ))
			return false;

		for (s32 i=0; i<4; ++i)
			for (s32 j=0; j<4; ++j)
				if ((j != i) && (!iszero((*this)(i,j))))
					return false;
*/
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=true;
#endif
		return true;
	}


	/* Check orthogonality of matrix. */
	inline bool matrix4::isOrthogonal() const
	{
		f32 dp=m[0] * m[4 ] + m[1] * m[5 ] + m[2 ] * m[6 ] + m[3 ] * m[7 ];
		if (!iszero(dp))
			return false;
		dp = m[0] * m[8 ] + m[1] * m[9 ] + m[2 ] * m[10] + m[3 ] * m[11];
		if (!iszero(dp))
			return false;
		dp = m[0] * m[12] + m[1] * m[13] + m[2 ] * m[14] + m[3 ] * m[15];
		if (!iszero(dp))
			return false;
		dp = m[4] * m[8 ] + m[5] * m[9 ] + m[6 ] * m[10] + m[7 ] * m[11];
		if (!iszero(dp))
			return false;
		dp = m[4] * m[12] + m[5] * m[13] + m[6 ] * m[14] + m[7 ] * m[15];
		if (!iszero(dp))
			return false;
		dp = m[8] * m[12] + m[9] * m[13] + m[10] * m[14] + m[11] * m[15];
		return (iszero(dp));
	}


	/*
		doesn't solve floating range problems..
		but takes care on +/- 0 on translation because we are changing it..
		reducing floating point branches
		but it needs the floats in memory..
	*/
	
	inline bool matrix4::isIdentity_integer_base() const
	{
#if defined ( USE_MATRIX_TEST )
		if (definitelyIdentityMatrix)
			return true;
#endif
		//if(IR(m[0])!=F32_VALUE_1)	return false;
		//if(IR(m[1])!=0)			return false;
		//if(IR(m[2])!=0)			return false;
		//if(IR(m[3])!=0)			return false;

		//if(IR(m[4])!=0)			return false;
		//if(IR(m[5])!=F32_VALUE_1)	return false;
		//if(IR(m[6])!=0)			return false;
		//if(IR(m[7])!=0)			return false;

		//if(IR(m[8])!=0)			return false;
		//if(IR(m[9])!=0)			return false;
		//if(IR(m[10])!=F32_VALUE_1)	return false;
		//if(IR(m[11])!=0)		return false;

		//if(IR(m[12])!=0)		return false;
		//if(IR(m[13])!=0)		return false;
		//if(IR(m[13])!=0)		return false;
		//if(IR(m[15])!=F32_VALUE_1)	return false;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=true;
#endif
		return true;
	}

	inline void matrix4::rotateVect( float3& vect ) const
	{
		float3 tmp = vect;
		vect.x = tmp.x*m[0] + tmp.y*m[4] + tmp.z*m[8];
		vect.y = tmp.x*m[1] + tmp.y*m[5] + tmp.z*m[9];
		vect.z = tmp.x*m[2] + tmp.y*m[6] + tmp.z*m[10];
	}

	//! An alternate transform vector method, writing into a second vector

	inline void matrix4::rotateVect(core::float3& out, const core::float3& in) const
	{
		out.x = in.x*m[0] + in.y*m[4] + in.z*m[8];
		out.y = in.x*m[1] + in.y*m[5] + in.z*m[9];
		out.z = in.x*m[2] + in.y*m[6] + in.z*m[10];
	}

	//! An alternate transform vector method, writing into an array of 3 floats
	inline void matrix4::rotateVect(f32 *out, const core::float3& in) const
	{
		out[0] = in.x*m[0] + in.y*m[4] + in.z*m[8];
		out[1] = in.x*m[1] + in.y*m[5] + in.z*m[9];
		out[2] = in.x*m[2] + in.y*m[6] + in.z*m[10];
	}
	
	inline void matrix4::inverseRotateVect( float3& vect ) const
	{
		float3 tmp = vect;
		vect.x = tmp.x*m[0] + tmp.y*m[1] + tmp.z*m[2];
		vect.y = tmp.x*m[4] + tmp.y*m[5] + tmp.z*m[6];
		vect.z = tmp.x*m[8] + tmp.y*m[9] + tmp.z*m[10];
	}

	
	inline void matrix4::transformVect( float3& vect) const
	{
		f32 vector[3];

		vector[0] = vect.x*m[0] + vect.y*m[4] + vect.z*m[8] + m[12];
		vector[1] = vect.x*m[1] + vect.y*m[5] + vect.z*m[9] + m[13];
		vector[2] = vect.x*m[2] + vect.y*m[6] + vect.z*m[10] + m[14];

		vect.x = vector[0];
		vect.y = vector[1];
		vect.z = vector[2];
	}
	
	inline void matrix4::transformVect( float3& out, const float3& in) const
	{
		out.x = in.x*m[0] + in.y*m[4] + in.z*m[8] + m[12];
		out.y = in.x*m[1] + in.y*m[5] + in.z*m[9] + m[13];
		out.z = in.x*m[2] + in.y*m[6] + in.z*m[10] + m[14];
	}
	
	inline void matrix4::transformVect(f32 *out, const core::float3 &in) const
	{
		out[0] = in.x*m[0] + in.y*m[4] + in.z*m[8] + m[12];
		out[1] = in.x*m[1] + in.y*m[5] + in.z*m[9] + m[13];
		out[2] = in.x*m[2] + in.y*m[6] + in.z*m[10] + m[14];
		out[3] = in.x*m[3] + in.y*m[7] + in.z*m[11] + m[15];
	}
	
	inline void matrix4::transformVec3(f32 *out, const f32 * in) const
	{
		out[0] = in[0]*m[0] + in[1]*m[4] + in[2]*m[8] + m[12];
		out[1] = in[0]*m[1] + in[1]*m[5] + in[2]*m[9] + m[13];
		out[2] = in[0]*m[2] + in[1]*m[6] + in[2]*m[10] + m[14];
	}

//	//! Transforms a plane by this matrix
//	inline void matrix4::transformPlane( core::plane3d<f32> &plane) const
//	{
//		float3 member;
//		// Transform the plane member point, i.e. rotate, translate and scale it.
//		transformVect(member, plane.getMemberPoint());
//
//		// Transform the normal by the transposed inverse of the matrix
//		matrix4 transposedInverse(*this, EM4CONST_INVERSE_TRANSPOSED);
//		float3 normal = plane.Normal;
//		transposedInverse.transformVect(normal);
//
//		plane.setPlane(member, normal);
//	}
//
//	//! Transforms a plane by this matrix
//	inline void matrix4::transformPlane( const core::plane3d<f32> &in, core::plane3d<f32> &out) const
//	{
//		out = in;
//		transformPlane( out );
//	}
//
//	//! Transforms the edge-points of a bounding box
//	//! Deprecated as it's usually not what people need (regards only 2 corners, but other corners might be outside the box after transformation)
//	//! Use transformBoxEx instead.
//	_IRR_DEPRECATED_ inline void matrix4::transformBox(core::aabbox3d<f32>& box) const
//	{
//#if defined ( USE_MATRIX_TEST )
//		if (isIdentity())
//			return;
//#endif
//
//		transformVect(box.MinEdge);
//		transformVect(box.MaxEdge);
//		box.repair();
//	}
//
//	//! Transforms a axis aligned bounding box more accurately than transformBox()
//	inline void matrix4::transformBoxEx(core::aabbox3d<f32>& box) const
//	{
//#if defined ( USE_MATRIX_TEST )
//		if (isIdentity())
//			return;
//#endif
//
//		const f32 Amin[3] = {box.MinEdge.x, box.MinEdge.y, box.MinEdge.z};
//		const f32 Amax[3] = {box.MaxEdge.x, box.MaxEdge.y, box.MaxEdge.z};
//
//		f32 Bmin[3];
//		f32 Bmax[3];
//
//		Bmin[0] = Bmax[0] = m[12];
//		Bmin[1] = Bmax[1] = m[13];
//		Bmin[2] = Bmax[2] = m[14];
//
//		const matrix4 &m = *this;
//
//		for (u32 i = 0; i < 3; ++i)
//		{
//			for (u32 j = 0; j < 3; ++j)
//			{
//				const f32 a = m(j,i) * Amin[j];
//				const f32 b = m(j,i) * Amax[j];
//
//				if (a < b)
//				{
//					Bmin[i] += a;
//					Bmax[i] += b;
//				}
//				else
//				{
//					Bmin[i] += b;
//					Bmax[i] += a;
//				}
//			}
//		}
//
//		box.MinEdge.x = Bmin[0];
//		box.MinEdge.y = Bmin[1];
//		box.MinEdge.z = Bmin[2];
//
//		box.MaxEdge.x = Bmax[0];
//		box.MaxEdge.y = Bmax[1];
//		box.MaxEdge.z = Bmax[2];
//	}


	//! Multiplies this matrix by a 1x4 matrix	
	inline void matrix4::multiplyWith1x4Matrix(f32* matrix) const
	{
		/*
		0  1  2  3
		4  5  6  7
		8  9  10 11
		12 13 14 15
		*/

		f32 mat[4];
		mat[0] = matrix[0];
		mat[1] = matrix[1];
		mat[2] = matrix[2];
		mat[3] = matrix[3];

		matrix[0] = m[0]*mat[0] + m[4]*mat[1] + m[8]*mat[2] + m[12]*mat[3];
		matrix[1] = m[1]*mat[0] + m[5]*mat[1] + m[9]*mat[2] + m[13]*mat[3];
		matrix[2] = m[2]*mat[0] + m[6]*mat[1] + m[10]*mat[2] + m[14]*mat[3];
		matrix[3] = m[3]*mat[0] + m[7]*mat[1] + m[11]*mat[2] + m[15]*mat[3];
	}

	inline void matrix4::inverseTranslateVect( float3& vect ) const
	{
		vect.x = vect.x-m[12];
		vect.y = vect.y-m[13];
		vect.z = vect.z-m[14];
	}

	inline void matrix4::translateVect( float3& vect ) const
	{
		vect.x = vect.x+m[12];
		vect.y = vect.y+m[13];
		vect.z = vect.z+m[14];
	}
	
	inline bool matrix4::getInverse(matrix4& out) const
	{
		/// Calculates the inverse of this Matrix
		/// The inverse is calculated using Cramers rule.
		/// If no inverse exists then 'false' is returned.

#if defined ( USE_MATRIX_TEST )
		if ( this->isIdentity() )
		{
			out=*this;
			return true;
		}
#endif
		const matrix4 &m = *this;

		f32 d = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
			(m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
			(m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)) +
			(m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) -
			(m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
			(m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));

		if( core::iszero ( d, FLT_MIN ) )
			return false;

		d = 1.0f / d;

		out(0, 0) = d * (m(1, 1) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) +
				m(1, 2) * (m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3)) +
				m(1, 3) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)));
		out(0, 1) = d * (m(2, 1) * (m(0, 2) * m(3, 3) - m(0, 3) * m(3, 2)) +
				m(2, 2) * (m(0, 3) * m(3, 1) - m(0, 1) * m(3, 3)) +
				m(2, 3) * (m(0, 1) * m(3, 2) - m(0, 2) * m(3, 1)));
		out(0, 2) = d * (m(3, 1) * (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) +
				m(3, 2) * (m(0, 3) * m(1, 1) - m(0, 1) * m(1, 3)) +
				m(3, 3) * (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)));
		out(0, 3) = d * (m(0, 1) * (m(1, 3) * m(2, 2) - m(1, 2) * m(2, 3)) +
				m(0, 2) * (m(1, 1) * m(2, 3) - m(1, 3) * m(2, 1)) +
				m(0, 3) * (m(1, 2) * m(2, 1) - m(1, 1) * m(2, 2)));
		out(1, 0) = d * (m(1, 2) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
				m(1, 3) * (m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2)) +
				m(1, 0) * (m(2, 3) * m(3, 2) - m(2, 2) * m(3, 3)));
		out(1, 1) = d * (m(2, 2) * (m(0, 0) * m(3, 3) - m(0, 3) * m(3, 0)) +
				m(2, 3) * (m(0, 2) * m(3, 0) - m(0, 0) * m(3, 2)) +
				m(2, 0) * (m(0, 3) * m(3, 2) - m(0, 2) * m(3, 3)));
		out(1, 2) = d * (m(3, 2) * (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) +
				m(3, 3) * (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) +
				m(3, 0) * (m(0, 3) * m(1, 2) - m(0, 2) * m(1, 3)));
		out(1, 3) = d * (m(0, 2) * (m(1, 3) * m(2, 0) - m(1, 0) * m(2, 3)) +
				m(0, 3) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
				m(0, 0) * (m(1, 2) * m(2, 3) - m(1, 3) * m(2, 2)));
		out(2, 0) = d * (m(1, 3) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0)) +
				m(1, 0) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
				m(1, 1) * (m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3)));
		out(2, 1) = d * (m(2, 3) * (m(0, 0) * m(3, 1) - m(0, 1) * m(3, 0)) +
				m(2, 0) * (m(0, 1) * m(3, 3) - m(0, 3) * m(3, 1)) +
				m(2, 1) * (m(0, 3) * m(3, 0) - m(0, 0) * m(3, 3)));
		out(2, 2) = d * (m(3, 3) * (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) +
				m(3, 0) * (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) +
				m(3, 1) * (m(0, 3) * m(1, 0) - m(0, 0) * m(1, 3)));
		out(2, 3) = d * (m(0, 3) * (m(1, 1) * m(2, 0) - m(1, 0) * m(2, 1)) +
				m(0, 0) * (m(1, 3) * m(2, 1) - m(1, 1) * m(2, 3)) +
				m(0, 1) * (m(1, 0) * m(2, 3) - m(1, 3) * m(2, 0)));
		out(3, 0) = d * (m(1, 0) * (m(2, 2) * m(3, 1) - m(2, 1) * m(3, 2)) +
				m(1, 1) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
				m(1, 2) * (m(2, 1) * m(3, 0) - m(2, 0) * m(3, 1)));
		out(3, 1) = d * (m(2, 0) * (m(0, 2) * m(3, 1) - m(0, 1) * m(3, 2)) +
				m(2, 1) * (m(0, 0) * m(3, 2) - m(0, 2) * m(3, 0)) +
				m(2, 2) * (m(0, 1) * m(3, 0) - m(0, 0) * m(3, 1)));
		out(3, 2) = d * (m(3, 0) * (m(0, 2) * m(1, 1) - m(0, 1) * m(1, 2)) +
				m(3, 1) * (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) +
				m(3, 2) * (m(0, 1) * m(1, 0) - m(0, 0) * m(1, 1)));
		out(3, 3) = d * (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
				m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
				m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));

#if defined ( USE_MATRIX_TEST )
		out.definitelyIdentityMatrix = definitelyIdentityMatrix;
#endif
		return true;
	}

	//! Inverts a primitive matrix which only contains a translation and a rotation
	//! \param out: where result matrix is written to.
	inline bool matrix4::getInversePrimitive ( matrix4& out ) const
	{
		out.m[0 ] = m[0];
		out.m[1 ] = m[4];
		out.m[2 ] = m[8];
		out.m[3 ] = 0;

		out.m[4 ] = m[1];
		out.m[5 ] = m[5];
		out.m[6 ] = m[9];
		out.m[7 ] = 0;

		out.m[8 ] = m[2];
		out.m[9 ] = m[6];
		out.m[10] = m[10];
		out.m[11] = 0;

		out.m[12] = (f32)-(m[12]*m[0] + m[13]*m[1] + m[14]*m[2]);
		out.m[13] = (f32)-(m[12]*m[4] + m[13]*m[5] + m[14]*m[6]);
		out.m[14] = (f32)-(m[12]*m[8] + m[13]*m[9] + m[14]*m[10]);
		out.m[15] = 1;

#if defined ( USE_MATRIX_TEST )
		out.definitelyIdentityMatrix = definitelyIdentityMatrix;
#endif
		return true;
	}

	/*!
	*/
	inline bool matrix4::makeInverse()
	{
#if defined ( USE_MATRIX_TEST )
		if (definitelyIdentityMatrix)
			return true;
#endif
		matrix4 temp ( EM4CONST_NOTHING );

		if (getInverse(temp))
		{
			*this = temp;
			return true;
		}

		return false;
	}

	inline matrix4& matrix4::operator=(const matrix4 &other)
	{
		if (this==&other)
			return *this;
		memcpy(m, other.m, 16*sizeof(f32));
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=other.definitelyIdentityMatrix;
#endif
		return *this;
	}

	inline matrix4& matrix4::operator=(const f32& scalar)
	{
		for (s32 i = 0; i < 16; ++i)
			m[i]=scalar;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}
	
	inline bool matrix4::operator==(const matrix4 &other) const
	{
#if defined ( USE_MATRIX_TEST )
		if (definitelyIdentityMatrix && other.definitelyIdentityMatrix)
			return true;
#endif
		for (s32 i = 0; i < 16; ++i)
			if (m[i] != other.m[i])
				return false;

		return true;
	}
	
	inline bool matrix4::operator!=(const matrix4 &other) const
	{
		return !(*this == other);
	}

	// Builds a right-handed perspective projection matrix based on a field of view
	inline matrix4& matrix4::buildProjectionMatrixPerspectiveFovRH(
			f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
	{
		const f64 h = 1.0 / tan(fieldOfViewRadians*0.5);
		//_IRR_DEBUG_BREAK_IF(aspectRatio==0.f); //divide by zero
		const f32 w = h / aspectRatio;

		//_IRR_DEBUG_BREAK_IF(zNear==zFar); //divide by zero
		m[0] = w;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)h;
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(zFar/(zNear-zFar)); // DirectX version
//		m[10] = (f32)(zFar+zNear/(zNear-zFar)); // OpenGL version
		m[11] = -1;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(zNear*zFar/(zNear-zFar)); // DirectX version
//		m[14] = (f32)(2.0f*zNear*zFar/(zNear-zFar)); // OpenGL version
		m[15] = 0;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a left-handed perspective projection matrix based on a field of view
	inline matrix4& matrix4::buildProjectionMatrixPerspectiveFovLH(
			f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
	{
		const f64 h = 1.0 / tan(fieldOfViewRadians*0.5);
		//_IRR_DEBUG_BREAK_IF(aspectRatio==0.f); //divide by zero
		const f32 w = h / aspectRatio;

		//_IRR_DEBUG_BREAK_IF(zNear==zFar); //divide by zero
		m[0] = w;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)h;
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(zFar/(zFar-zNear));
		m[11] = 1;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(-zNear*zFar/(zFar-zNear));
		m[15] = 0;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a left-handed perspective projection matrix based on a field of view, with far plane culling at infinity
	inline matrix4& matrix4::buildProjectionMatrixPerspectiveFovInfinityLH(
			f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 epsilon)
	{
		const f64 h = 1.0 / tan(fieldOfViewRadians*0.5);
		//_IRR_DEBUG_BREAK_IF(aspectRatio==0.f); //divide by zero
		const f32 w = h / aspectRatio;

		m[0] = w;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)h;
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(1.f-epsilon);
		m[11] = 1;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(zNear*(epsilon-1.f));
		m[15] = 0;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a left-handed orthogonal projection matrix.
	inline matrix4& matrix4::buildProjectionMatrixOrthoLH(
			f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
	{
		//_IRR_DEBUG_BREAK_IF(widthOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(heightOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(zNear==zFar); //divide by zero
		m[0] = (f32)(2/widthOfViewVolume);
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)(2/heightOfViewVolume);
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(1/(zFar-zNear));
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(zNear/(zNear-zFar));
		m[15] = 1;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a right-handed orthogonal projection matrix.
	inline matrix4& matrix4::buildProjectionMatrixOrthoRH(
			f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
	{
		//_IRR_DEBUG_BREAK_IF(widthOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(heightOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(zNear==zFar); //divide by zero
		m[0] = (f32)(2/widthOfViewVolume);
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)(2/heightOfViewVolume);
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(1/(zNear-zFar));
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(zNear/(zNear-zFar));
		m[15] = 1;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a right-handed perspective projection matrix.
	inline matrix4& matrix4::buildProjectionMatrixPerspectiveRH(
			f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
	{
		//_IRR_DEBUG_BREAK_IF(widthOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(heightOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(zNear==zFar); //divide by zero
		m[0] = (f32)(2*zNear/widthOfViewVolume);
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)(2*zNear/heightOfViewVolume);
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(zFar/(zNear-zFar));
		m[11] = -1;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(zNear*zFar/(zNear-zFar));
		m[15] = 0;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a left-handed perspective projection matrix.
	inline matrix4& matrix4::buildProjectionMatrixPerspectiveLH(
			f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
	{
		//_IRR_DEBUG_BREAK_IF(widthOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(heightOfViewVolume==0.f); //divide by zero
		//_IRR_DEBUG_BREAK_IF(zNear==zFar); //divide by zero
		m[0] = (f32)(2*zNear/widthOfViewVolume);
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (f32)(2*zNear/heightOfViewVolume);
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (f32)(zFar/(zFar-zNear));
		m[11] = 1;

		m[12] = 0;
		m[13] = 0;
		m[14] = (f32)(zNear*zFar/(zNear-zFar));
		m[15] = 0;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

//	// Builds a matrix that flattens geometry into a plane.
//	inline matrix4& matrix4::buildShadowMatrix(const core::float3& light, core::plane3df plane, f32 point)
//	{
//		plane.Normal.normalize();
//		const f32 d = plane.Normal.dotProduct(light);
//
//		m[ 0] = (f32)(-plane.Normal.x * light.x + d);
//		m[ 1] = (f32)(-plane.Normal.x * light.y);
//		m[ 2] = (f32)(-plane.Normal.x * light.z);
//		m[ 3] = (f32)(-plane.Normal.x * point);
//
//		m[ 4] = (f32)(-plane.Normal.y * light.x);
//		m[ 5] = (f32)(-plane.Normal.y * light.y + d);
//		m[ 6] = (f32)(-plane.Normal.y * light.z);
//		m[ 7] = (f32)(-plane.Normal.y * point);
//
//		m[ 8] = (f32)(-plane.Normal.z * light.x);
//		m[ 9] = (f32)(-plane.Normal.z * light.y);
//		m[10] = (f32)(-plane.Normal.z * light.z + d);
//		m[11] = (f32)(-plane.Normal.z * point);
//
//		m[12] = (f32)(-plane.D * light.x);
//		m[13] = (f32)(-plane.D * light.y);
//		m[14] = (f32)(-plane.D * light.z);
//		m[15] = (f32)(-plane.D * point + d);
//#if defined ( USE_MATRIX_TEST )
//		definitelyIdentityMatrix=false;
//#endif
//		return *this;
//	}

	// Builds a left-handed look-at matrix.	
	inline matrix4& matrix4::buildCameraLookAtMatrixLH(
				const float3& position,
				const float3& target,
				const float3& upVector)
	{
		float3 zaxis = target - position;
		zaxis.normalize();

		float3 xaxis = upVector.crossProduct(zaxis);
		xaxis.normalize();

		float3 yaxis = zaxis.crossProduct(xaxis);

		m[0] = (f32)xaxis.x;
		m[1] = (f32)yaxis.x;
		m[2] = (f32)zaxis.x;
		m[3] = 0;

		m[4] = (f32)xaxis.y;
		m[5] = (f32)yaxis.y;
		m[6] = (f32)zaxis.y;
		m[7] = 0;

		m[8] = (f32)xaxis.z;
		m[9] = (f32)yaxis.z;
		m[10] = (f32)zaxis.z;
		m[11] = 0;

		m[12] = (f32)-xaxis.dotProduct(position);
		m[13] = (f32)-yaxis.dotProduct(position);
		m[14] = (f32)-zaxis.dotProduct(position);
		m[15] = 1;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// Builds a right-handed look-at matrix.
	inline matrix4& matrix4::buildCameraLookAtMatrixRH(
				const float3& position,
				const float3& target,
				const float3& upVector)
	{
		float3 zaxis = position - target;
		zaxis.normalize();

		float3 xaxis = upVector.crossProduct(zaxis);
		xaxis.normalize();

		float3 yaxis = zaxis.crossProduct(xaxis);

		m[0] = (f32)xaxis.x;
		m[1] = (f32)yaxis.x;
		m[2] = (f32)zaxis.x;
		m[3] = 0;

		m[4] = (f32)xaxis.y;
		m[5] = (f32)yaxis.y;
		m[6] = (f32)zaxis.y;
		m[7] = 0;

		m[8] = (f32)xaxis.z;
		m[9] = (f32)yaxis.z;
		m[10] = (f32)zaxis.z;
		m[11] = 0;

		m[12] = (f32)-xaxis.dotProduct(position);
		m[13] = (f32)-yaxis.dotProduct(position);
		m[14] = (f32)-zaxis.dotProduct(position);
		m[15] = 1;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// creates a new matrix as interpolated matrix from this and the passed one.
	inline matrix4 matrix4::interpolate(const core::matrix4& b, f32 time) const
	{
		matrix4 mat ( EM4CONST_NOTHING );

		for (u32 i=0; i < 16; i += 4)
		{
			mat.m[i+0] = (f32)(m[i+0] + ( b.m[i+0] - m[i+0] ) * time);
			mat.m[i+1] = (f32)(m[i+1] + ( b.m[i+1] - m[i+1] ) * time);
			mat.m[i+2] = (f32)(m[i+2] + ( b.m[i+2] - m[i+2] ) * time);
			mat.m[i+3] = (f32)(m[i+3] + ( b.m[i+3] - m[i+3] ) * time);
		}
		return mat;
	}

	// returns transposed matrix
	inline matrix4 matrix4::getTransposed() const
	{
		matrix4 t ( EM4CONST_NOTHING );
		getTransposed ( t );
		return t;
	}

	// returns transposed matrix
	inline void matrix4::getTransposed( matrix4& o ) const
	{
		o[ 0] = m[ 0];
		o[ 1] = m[ 4];
		o[ 2] = m[ 8];
		o[ 3] = m[12];

		o[ 4] = m[ 1];
		o[ 5] = m[ 5];
		o[ 6] = m[ 9];
		o[ 7] = m[13];

		o[ 8] = m[ 2];
		o[ 9] = m[ 6];
		o[10] = m[10];
		o[11] = m[14];

		o[12] = m[ 3];
		o[13] = m[ 7];
		o[14] = m[11];
		o[15] = m[15];
#if defined ( USE_MATRIX_TEST )
		o.definitelyIdentityMatrix=definitelyIdentityMatrix;
#endif
	}

	//// used to scale <-1,-1><1,1> to viewport
	//inline matrix4& matrix4::buildNDCToDCMatrix( const core::rect<s32>& viewport, f32 zScale)
	//{
	//	const f32 scaleX = (viewport.getWidth() - 0.75f ) * 0.5f;
	//	const f32 scaleY = -(viewport.getHeight() - 0.75f ) * 0.5f;

	//	const f32 dx = -0.5f + ( (viewport.UpperLeftCorner.x + viewport.LowerRightCorner.x ) * 0.5f );
	//	const f32 dy = -0.5f + ( (viewport.UpperLeftCorner.y + viewport.LowerRightCorner.y ) * 0.5f );

	//	makeIdentity();
	//	m[12] = (f32)dx;
	//	m[13] = (f32)dy;
	//	return setScale(core::float3((f32)scaleX, (f32)scaleY, (f32)zScale));
	//}

	//! Builds a matrix that rotates from one vector to another
	/** \param from: vector to rotate from
	\param to: vector to rotate to

		http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/index.htm
	 */
	inline matrix4& matrix4::buildRotateFromTo(const core::float3& from, const core::float3& to)
	{
		// unit vectors
		core::float3 f(from);
		core::float3 t(to);
		f.normalize();
		t.normalize();

		// axis multiplication by sin
		core::float3 vs(t.crossProduct(f));

		// axis of rotation
		core::float3 v(vs);
		v.normalize();

		// cosinus angle
		f32 ca = f.dotProduct(t);

		core::float3 vt(v * (1 - ca));

		m[0] = vt.x * v.x + ca;
		m[5] = vt.y * v.y + ca;
		m[10] = vt.z * v.z + ca;

		vt.x *= v.y;
		vt.z *= v.x;
		vt.y *= v.z;

		m[1] = vt.x - vs.z;
		m[2] = vt.z + vs.y;
		m[3] = 0;

		m[4] = vt.x + vs.z;
		m[6] = vt.y - vs.x;
		m[7] = 0;

		m[8] = vt.z - vs.y;
		m[9] = vt.y + vs.x;
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = 0;
		m[15] = 1;

		return *this;
	}

	//! Builds a matrix which rotates a source vector to a look vector over an arbitrary axis
	/** \param camPos: viewer position in world coord
	\param center: object position in world-coord, rotation pivot
	\param translation: object final translation from center
	\param axis: axis to rotate about
	\param from: source vector to rotate from
	 */
	inline void matrix4::buildAxisAlignedBillboard(
				const core::float3& camPos,
				const core::float3& center,
				const core::float3& translation,
				const core::float3& axis,
				const core::float3& from)
	{
		// axis of rotation
		core::float3 up = axis;
		up.normalize();
		const core::float3 forward = (camPos - center).normalize();
		const core::float3 right = up.crossProduct(forward).normalize();

		// correct look vector
		const core::float3 look = right.crossProduct(up);

		// rotate from to
		// axis multiplication by sin
		const core::float3 vs = look.crossProduct(from);

		// cosinus angle
		const f32 ca = from.dotProduct(look);

		core::float3 vt(up * (1.f - ca));

		m[0] = vt.x * up.x + ca;
		m[5] = vt.y * up.y + ca;
		m[10] = vt.z * up.z + ca;

		vt.x *= up.y;
		vt.z *= up.x;
		vt.y *= up.z;

		m[1] = vt.x - vs.z;
		m[2] = vt.z + vs.y;
		m[3] = 0;

		m[4] = vt.x + vs.z;
		m[6] = vt.y - vs.x;
		m[7] = 0;

		m[8] = vt.z - vs.y;
		m[9] = vt.y + vs.x;
		m[11] = 0;

		setRotationCenter(center, translation);
	}

	//! Builds a combined matrix which translate to a center before rotation and translate afterwards
	inline void matrix4::setRotationCenter(const core::float3& center, const core::float3& translation)
	{
		m[12] = -m[0]*center.x - m[4]*center.y - m[8]*center.z + (center.x - translation.x );
		m[13] = -m[1]*center.x - m[5]*center.y - m[9]*center.z + (center.y - translation.y );
		m[14] = -m[2]*center.x - m[6]*center.y - m[10]*center.z + (center.z - translation.z );
		m[15] = (f32) 1.0;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
	}

	/*!
		Generate texture coordinates as linear functions so that:
			u = Ux*x + Uy*y + Uz*z + Uw
			v = Vx*x + Vy*y + Vz*z + Vw
		The matrix m for this case is:
			Ux  Vx  0  0
			Uy  Vy  0  0
			Uz  Vz  0  0
			Uw  Vw  0  0
	*/
	inline matrix4& matrix4::buildTextureTransform( f32 rotateRad,
			const core::float2 &rotatecenter,
			const core::float2 &translate,
			const core::float2 &scale)
	{
		const f32 c = cosf(rotateRad);
		const f32 s = sinf(rotateRad);

		m[0] = (f32)(c * scale.x);
		m[1] = (f32)(s * scale.y);
		m[2] = 0;
		m[3] = 0;

		m[4] = (f32)(-s * scale.x);
		m[5] = (f32)(c * scale.y);
		m[6] = 0;
		m[7] = 0;

		m[8] = (f32)(c * scale.x * rotatecenter.x + -s * rotatecenter.y + translate.x);
		m[9] = (f32)(s * scale.y * rotatecenter.x +  c * rotatecenter.y + translate.y);
		m[10] = 1;
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = 0;
		m[15] = 1;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// rotate about z axis, center ( 0.5, 0.5 )
	inline matrix4& matrix4::setTextureRotationCenter( f32 rotateRad )
	{
		const f32 c = cosf(rotateRad);
		const f32 s = sinf(rotateRad);
		m[0] = (f32)c;
		m[1] = (f32)s;

		m[4] = (f32)-s;
		m[5] = (f32)c;

		m[8] = (f32)(0.5f * ( s - c) + 0.5f);
		m[9] = (f32)(-0.5f * ( s + c) + 0.5f);

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix = definitelyIdentityMatrix && (rotateRad==0.0f);
#endif
		return *this;
	}
	
	inline matrix4& matrix4::setTextureTranslate ( f32 x, f32 y )
	{
		m[8] = (f32)x;
		m[9] = (f32)y;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix = definitelyIdentityMatrix && (x==0.0f) && (y==0.0f);
#endif
		return *this;
	}
	
	inline matrix4& matrix4::setTextureTranslateTransposed ( f32 x, f32 y )
	{
		m[2] = (f32)x;
		m[6] = (f32)y;

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix = definitelyIdentityMatrix && (x==0.0f) && (y==0.0f) ;
#endif
		return *this;
	}

	inline matrix4& matrix4::setTextureScale ( f32 sx, f32 sy )
	{
		m[0] = (f32)sx;
		m[5] = (f32)sy;
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix = definitelyIdentityMatrix && (sx==1.0f) && (sy==1.0f);
#endif
		return *this;
	}
	
	inline matrix4& matrix4::setTextureScaleCenter( f32 sx, f32 sy )
	{
		m[0] = (f32)sx;
		m[5] = (f32)sy;
		m[8] = (f32)(0.5f - 0.5f * sx);
		m[9] = (f32)(0.5f - 0.5f * sy);

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix = definitelyIdentityMatrix && (sx==1.0f) && (sy==1.0f);
#endif
		return *this;
	}

	// sets all matrix data members at once
	inline matrix4& matrix4::setM(const f32* data)
	{
		memcpy(m,data, 16*sizeof(f32));

#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix=false;
#endif
		return *this;
	}

	// sets if the matrix is definitely identity matrix
	inline void matrix4::setDefinitelyIdentityMatrix( bool isDefinitelyIdentityMatrix)
	{
#if defined ( USE_MATRIX_TEST )
		definitelyIdentityMatrix = isDefinitelyIdentityMatrix;
#endif
	}

	// gets if the matrix is definitely identity matrix
	inline bool matrix4::getDefinitelyIdentityMatrix() const
	{
#if defined ( USE_MATRIX_TEST )
		return definitelyIdentityMatrix;
#else
		return false;
#endif
	}

//	//! Compare two matrices using the equal method
//	inline bool matrix4::equals(const core::matrix4& other, const f32 tolerance) const
//	{
//#if defined ( USE_MATRIX_TEST )
//		if (definitelyIdentityMatrix && other.definitelyIdentityMatrix)
//			return true;
//#endif
//		for (s32 i = 0; i < 16; ++i)
//			if (!core::equals(m[i],other.m[i], tolerance))
//				return false;
//
//		return true;
//	}

	// Multiply by scalar.
	inline matrix4 operator*(const f32 scalar, const matrix4& mat)
	{
		return mat*scalar;
	}

	//! global const identity matrix
	//IRRLICHT_API extern const matrix4 IdentityMatrix;

} // end namespace core
} // end namespace lwge

#endif