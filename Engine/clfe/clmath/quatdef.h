#ifndef CLFE_CLMATH_QUATDEF_H
#define CLFE_CLMATH_QUATDEF_H

namespace clfe
{

	using quatf = clmquat<float>;
	using quatd = clmquat<double>;
	using quatld = clmquat<long double>;

	// No std::float here (niche and unnecessary)

	// Default quaternion type is float
	using quat = clmquat<float>;

}

#endif // CLFE_CLMATH_QUATDEF_H