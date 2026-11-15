#ifndef CLFE_CLMATH_QUATOP_H
#define CLFE_CLMATH_QUATOP_H

#include "mdef.h"
#include "quat.h"

namespace clfe
{

	// quat * quat
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr auto operator*(const clmquat<T>& vec1, const clmquat<U>& vec2) -> clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))>
	{
		return clmquat<decltype(static_cast<T>(0) * static_cast<U>(0))>(
			vec1.get(3) * vec2.get(0) + vec1.get(0) * vec2.get(3) + vec1.get(1) * vec2.get(2) - vec1.get(2) * vec2.get(1),
			vec1.get(3) * vec2.get(1) - vec1.get(0) * vec2.get(2) + vec1.get(1) * vec2.get(3) + vec1.get(2) * vec2.get(0),
			vec1.get(3) * vec2.get(2) + vec1.get(0) * vec2.get(1) - vec1.get(1) * vec2.get(0) + vec1.get(2) * vec2.get(3),
			vec1.get(3) * vec2.get(3) - vec1.get(0) * vec2.get(0) - vec1.get(1) * vec2.get(1) - vec1.get(2) * vec2.get(2)
		);
	}

	// quat *= quat
	// Equals quat1 = quat2 * quat1
	template <typename T, typename U>
		requires arithmetic<T, U>
	constexpr clmquat<T>& operator*=(clmquat<T>& vec1, const clmquat<U>& vec2)
	{
		vec1 = vec2 * vec1;
		return vec1;
	}

	// -quat
	template <typename T>
		requires arithmetic<T>
	constexpr clmquat<T> operator-(const clmquat<T>& vec)
	{
		return clmquat<T>(-vec.get(0), -vec.get(1), -vec.get(2), vec.get(3));
	}

}

#endif // CLFE_CLMATH_QUATOP_H