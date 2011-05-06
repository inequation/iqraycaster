/*
===========================================================================
Copyright (C) 2011 Leszek Godlewski

This file is part of iqraycaster source code.

iqraycaster source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

iqraycaster source code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along
with iqraycaster source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#ifndef MATH_H
#define MATH_H

/// \addtogroup internal_API
/// @{

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cmath>
#include <ostream>

#ifdef USE_SSE
	// SSE intrinsics headers
	#include <xmmintrin.h>

	#ifdef __GNUC__
		#define ALIGNED_16 __attribute__ ((__aligned__ (16)))
	#else
		#define ALIGNED_16 __declspec(align(16))
	#endif

	// This is to fix certain SSE-related crashes. What happens is that since I'm
	// mixing non-SSE and SSE code, it can sometimes happen that the stack is
	// aligned to 4 bytes (the legacy way) instead of 16 bytes (what SSE expects).
	// This can lead to seemingly random crashes. Adding this attribute causes the
	// compiler to add some code to enforce 16-byte alignment.
	#define STACK_ALIGN __attribute__((force_align_arg_pointer))
#else
	// dummy defines
	#define ALIGNED_16
	#define STACK_ALIGN
#endif // USE_SSE

// forward declarations
template <typename T>
class Tuple2;
template <typename T>
class Tuple4;
class Vec2f;
class Vec3f;

/// 2-component tuple.
template <typename T>
class Tuple2 {
	public:
		/// Zero-initialization contructor.
		Tuple2() {memset(m_v, 0, sizeof(T) * 2);}
		/// \param all	value to initialize all components with
		Tuple2(T all) {m_v[0] = m_v[1] = all;}
		/// \param x	value to initialize the x component with
		/// \param y	value to initialize the y component with
		Tuple2(T x, T y) {m_v[0] = x; m_v[1] = y;}
		/// \param f	2-element array to initialize the components with
		Tuple2(T f[2]) {memcpy(m_v, f, sizeof(T) * 2);}

		inline Tuple2<T> operator+(const Tuple2<T>& other) const {
			return Tuple2<T>(m_v[0] + other.m_v[0], m_v[1] + other.m_v[1]);
		}
		inline Tuple2<T> operator-(const Tuple2<T>& other) const {
			return Tuple2<T>(m_v[0] - other.m_v[0], m_v[1] - other.m_v[1]);
		}
		inline Tuple2<T> operator*(const Tuple2<T>& other) const {
			return Tuple2<T>(m_v[0] * other.m_v[0], m_v[1] * other.m_v[1]);
		}
		inline Tuple2<T> operator/(const Tuple2<T>& other) const {
			return Tuple2<T>(m_v[0] / other.m_v[0], m_v[1] / other.m_v[1]);
		}

		inline Tuple2<T>& operator+=(const Tuple2<T>& other) {
			m_v[0] += other.m_v[0]; m_v[1] += other.m_v[1];
			return *this;
		}
		inline Tuple2<T>& operator-=(const Tuple2<T>& other) {
			m_v[0] -= other.m_v[0]; m_v[1] -= other.m_v[1];
			return *this;
		}
		inline Tuple2<T>& operator*=(const Tuple2<T>& other) {
			m_v[0] *= other.m_v[0]; m_v[1] *= other.m_v[1];
			return *this;
		}
		inline Tuple2<T>& operator/=(const Tuple2<T>& other) {
			m_v[0] /= other.m_v[0]; m_v[1] /= other.m_v[1];
			return *this;
		}

		inline Tuple2<T> operator*(const T other) const {
			return Tuple2<T>(m_v[0] * other, m_v[1] * other);
		}
		inline Tuple2<T> operator/(const T other) const {
			return Tuple2<T>(m_v[0] / other, m_v[1] / other);
		}
		inline Tuple2<T>& operator*=(const T other) {
			m_v[0] *= other; m_v[1] *= other;
			return *this;
		}
		inline Tuple2<T>& operator/=(const T other) {
			m_v[0] /= other.m_v[0]; m_v[1] /= other.m_v[1];
			return *this;
		}

		inline T& operator[](const unsigned int i) {return m_v[std::min(i, 1U)];}
		inline T operator[](const unsigned int i) const {return m_v[std::min(i, 1U)];}

		inline T& X() {return m_v[0];}
		inline T& Y() {return m_v[1];}
		inline const T X() const {return m_v[0];}
		inline const T Y() const {return m_v[1];}

	protected:
		T	m_v[2];

		/// Data dumping stream operator.
		friend inline std::ostream& operator<<(std::ostream& out, const Tuple2<float>& tuple);
		/// For high/low tuple initialization.
		friend class Tuple4<float>;
};

//template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Tuple2<float>& tuple) {
	out << '[' << tuple.m_v[0] << "; " << tuple.m_v[1] << ']';
	return out;
}

/// 4-component tuple
template <typename T>
class Tuple4 {
	public:
		/// Zero-initialization contructor.
		Tuple4() {memset(m_v, 0, sizeof(T) * 4);}
		/// \param all	value to initialize all components with
		Tuple4(T all) {m_v[0] = m_v[1] = m_v[2] = m_v[3] = all;}
		/// \param x	value to initialize the x component with
		/// \param y	value to initialize the y component with
		/// \param z	value to initialize the z component with
		/// \param w	value to initialize the w component with
		Tuple4(T x, T y, T z, T w) {
			m_v[0] = x; m_v[1] = y; m_v[2] = z; m_v[3] = w;
		}
		/// \param low	tuple to initialize the lower 2 components with
		/// \param high	tuple to initialize the higher 2 components with
		Tuple4(const Tuple2<T>& low, const Tuple2<T>& high) {
			memcpy(m_v, low.m_v, sizeof(T) * 2);
			memcpy(m_v + 2, high.m_v, sizeof(T) * 2);
		}

	#define BINARYOP(op)																\
		inline const Tuple4<T> operator op(const Tuple4<T>& other) const {			\
			return Tuple4<T>(m_v[0] op other.m_v[0], m_v[1] op other.m_v[1],			\
							m_v[2] op other.m_v[2], m_v[3] op other.m_v[3]);			\
		}

	#define COMPASSIGNOP(op)															\
		inline Tuple4<T>& operator op(const Tuple4<T>& other) {						\
			m_v[0] op other.m_v[0]; m_v[1] op other.m_v[1];								\
			m_v[2] op other.m_v[2]; m_v[3] op other.m_v[3];								\
			return *this;																\
		}

	#define SCALARBINARYOP(op)															\
		inline const Tuple4<T> operator op(const T other) const {						\
			return Tuple4<float>(m_v[0] op other, m_v[1] op other,						\
								m_v[2] op other, m_v[3] op other);						\
		}

	#define SCALARCOMPASSIGNOP(op)														\
		inline Tuple4<T>& operator op(const T other) {									\
			m_v[0] op other; m_v[1] op other;											\
			m_v[2] op other; m_v[3] op other;											\
			return *this;																\
		}

		BINARYOP(+);
		BINARYOP(-);
		BINARYOP(*);
		BINARYOP(/);
		COMPASSIGNOP(+=);
		COMPASSIGNOP(-=);
		COMPASSIGNOP(*=);
		COMPASSIGNOP(/=);
		SCALARBINARYOP(*);
		SCALARBINARYOP(/);
		SCALARCOMPASSIGNOP(*=);
		SCALARCOMPASSIGNOP(/=);

#undef BINARYOP
#undef COMPASSIGNOP
#undef SCALARCOMPASSIGNOP
#undef SCALARBINARYOP

		inline T& X() {return m_v[0];}
		inline T& Y() {return m_v[1];}
		inline T& Z() {return m_v[2];}
		inline T& W() {return m_v[3];}
		inline T X() const {return m_v[0];}
		inline T Y() const {return m_v[1];}
		inline T Z() const {return m_v[2];}
		inline T W() const {return m_v[3];}

		inline T& operator[](const unsigned int i) {return m_v[std::min(i, 3U)];}
		inline T operator[](const unsigned int i) const {return m_v[std::min(i, 3U)];}

	protected:
		T	m_v[4];

		template <typename _T>
		friend inline std::ostream& operator<<(std::ostream& out, const Tuple4<_T>& tuple);
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Tuple4<T>& tuple) {
	out << '[' << tuple.m_v[0] << "; " << tuple.m_v[1] << "; "
		<< tuple.m_v[2] << "; " << tuple.m_v[3] << ']';
	return out;
}

#ifdef USE_SSE
// if SSE is enabled, use template specialization for floats
template <>
class Tuple4<float> {
	public:
		Tuple4() {memset(m_v.f, 0, sizeof(float) * 4);}
		Tuple4(float all) {m_v.sse = _mm_set1_ps(all);}
		Tuple4(float x, float y, float z, float w) {
			m_v.f[0] = x; m_v.f[1] = y; m_v.f[2] = z; m_v.f[3] = w;
		}
		Tuple4(Tuple2<float>& low, Tuple2<float>& high) {
			memcpy(m_v.f, low.m_v, sizeof(float) * 2);
			memcpy(m_v.f + 2, high.m_v, sizeof(float) * 2);
		}
		Tuple4(__m128 sse) {m_v.sse = sse;}

	#define BINARYOP(op, ssein) 													\
		inline const Tuple4<float> operator op(const Tuple4<float>& other) const	\
			STACK_ALIGN {															\
			return Tuple4<float>(ssein(m_v.sse, other.m_v.sse));					\
		}

	#define COMPASSIGNOP(op, ssein)													\
		inline Tuple4<float>& operator op(const Tuple4<float>& other) STACK_ALIGN	\
		{																			\
			m_v.sse = ssein(m_v.sse, other.m_v.sse);								\
			return *this;															\
		}

	#define SCALARBINARYOP(op, ssein, sseprefix)									\
		inline const Tuple4<float> operator op(const float other) const			\
			STACK_ALIGN {															\
			__m128 tmp = _mm_set1_ps(sseprefix other);								\
			return Tuple4<float>(ssein(m_v.sse, tmp));								\
		}

	#define SCALARCOMPASSIGNOP(op, ssein, sseprefix)								\
		inline Tuple4<float>& operator op(const float other) STACK_ALIGN {			\
			__m128 tmp = _mm_set1_ps(sseprefix other);								\
			m_v.sse = ssein(m_v.sse, tmp);											\
			return *this;															\
		}

		BINARYOP(+, _mm_add_ps);
		BINARYOP(-, _mm_sub_ps);
		BINARYOP(*, _mm_mul_ps);
		COMPASSIGNOP(+=, _mm_add_ps);
		COMPASSIGNOP(-=, _mm_sub_ps);
		COMPASSIGNOP(*=, _mm_mul_ps);
		SCALARBINARYOP(*, _mm_mul_ps, );
		SCALARBINARYOP(/, _mm_mul_ps, 1.f /);
		SCALARCOMPASSIGNOP(*=, _mm_mul_ps, );
		SCALARCOMPASSIGNOP(/=, _mm_mul_ps, 1.f /);

#undef BINARYOP
#undef COMPASSIGNOP
#undef SCALARCOMPASSIGNOP
#undef SCALARBINARYOP

		inline const Tuple4<float> operator/(const Tuple4<float>& other) const {
			return Tuple4<float>(m_v.f[0] / other.m_v.f[0], m_v.f[1] / other.m_v.f[1],
							m_v.f[2] / other.m_v.f[2], m_v.f[3] / other.m_v.f[3]);
		}

		inline Tuple4<float>& operator/=(const Tuple4<float>& other) {
			m_v.f[0] /= other.m_v.f[0]; m_v.f[1] /= other.m_v.f[1];
			m_v.f[2] /= other.m_v.f[2]; m_v.f[3] /= other.m_v.f[3];
			return *this;
		}

		inline float& X() {return m_v.f[0];}
		inline float& Y() {return m_v.f[1];}
		inline float& Z() {return m_v.f[2];}
		inline float& W() {return m_v.f[3];}
		inline float X() const {return m_v.f[0];}
		inline float Y() const {return m_v.f[1];}
		inline float Z() const {return m_v.f[2];}
		inline float W() const {return m_v.f[3];}

		inline float& operator[](const unsigned int i) {return m_v.f[std::min(i, 3U)];}
		inline float operator[](const unsigned int i) const {return m_v.f[std::min(i, 3U)];}

	protected:
		union {
			ALIGNED_16 float	f[4];
			__m128				sse;
		}	m_v;
};

// specialized operator for float tuples
template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Tuple4<float>& tuple) {
	out << '[' << tuple.m_v.f[0] << "; " << tuple.m_v.f[1] << "; "
		<< tuple.m_v.f[2] << "; " << tuple.m_v.f[3] << ']';
	return out;
}
#endif // USE_SSE

/// 2-dimensional vector.
class Vec2f : public Tuple2<float> {
	public:
		Vec2f() : Tuple2<float>() {}
		Vec2f(float all) : Tuple2<float>(all) {}
		Vec2f(float x, float y) : Tuple2<float>(x, y) {}
		Vec2f(float f[2]) : Tuple2<float>(f) {}
		Vec2f(Tuple2<float> tuple) : Tuple2<float>(tuple) {}

		/// \return dot product of this and other
		inline float dot(const Vec2f& other) const {
			return m_v[0] * other.m_v[0] + m_v[1] * other.m_v[1];
		}

		/// \return squared euclidean length of this
		inline float lengthSquared() const {
			return this->dot(*this);
		}

		/// \return euclidean length of this
		inline float length() const {
			return sqrtf(this->lengthSquared());
		}

		/// Normalizes this (divides all components by length).
		inline void normalize() {
			assert(this->lengthSquared() > 0.f);
			*this *= 1.f / this->length();
		}

		/// \return a normalized copy of this
		inline Vec2f normalized() const {
			assert(this->lengthSquared() > 0.f);
			return *this / this->length();
		}
};

/// 3-dimensional vector.
class Vec3f : public Tuple4<float> {
	// choose the way to refer to tuple components
#ifdef USE_SSE
	#define M_ARR	m_v.f
#else
	#define M_ARR	m_v
#endif // USE_SSE
	public:
		Vec3f() : Tuple4<float>() {}
		Vec3f(float all) : Tuple4<float>(all) {}
		Vec3f(float x, float y, float z) {
			M_ARR[0] = x; M_ARR[1] = y; M_ARR[2] = z; M_ARR[3] = 0.f;
		}
		Vec3f(float f[3]) {
			memcpy(M_ARR, f, sizeof(float) * 3);
			M_ARR[3] = 0.f;
		}
		Vec3f(Tuple4<float> tuple) : Tuple4<float>(tuple) {}

		/// \return dot product of this and other
		inline float dot(const Vec3f& other) const {
			return M_ARR[0] * other.M_ARR[0]
				+ M_ARR[1] * other.M_ARR[1]
				+ M_ARR[2] * other.M_ARR[2];
		}

		/// \return squared euclidean length of this
		inline float lengthSquared() const {
			return this->dot(*this);
		}

		/// \return euclidean length of this
		inline float length() const {
			return sqrtf(this->lengthSquared());
		}

		/// Normalizes this (divides all components by length).
		inline void normalize() {
			assert(this->lengthSquared() > 0.f);
			*this *= 1.f / this->length();
		}

		/// \return a normalized copy of this
		inline Vec3f normalized() const {
			assert(this->lengthSquared() > 0.f);
			return *this / this->length();
		}

		inline Vec3f cross(const Vec3f& other) const {
			return Vec3f(M_ARR[1] * other.M_ARR[2] - M_ARR[2] * other.M_ARR[1],
				M_ARR[2] * other.M_ARR[0] - M_ARR[0] * other.M_ARR[2],
				M_ARR[0] * other.M_ARR[1] - M_ARR[1] * other.M_ARR[0]);
		}

		static Vec3f random() {
			return Vec3f(
				2.f * (float)rand() / (float)RAND_MAX - 1.f,
				2.f * (float)rand() / (float)RAND_MAX - 1.f,
				2.f * (float)rand() / (float)RAND_MAX - 1.f
			);
		}
};

inline std::ostream& operator<<(std::ostream& out, const Vec3f& vec) {
	out << '[' << vec[0] << "; " << vec[1] << "; " << vec[2] << ']';
	return out;
}

/// @}

#endif // MATH_H
