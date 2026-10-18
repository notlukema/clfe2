
#include <iostream>

#include "clfe/clmath/vector.h"
#include "clfe/clmath/matrix.h"

#include "clfe/clutil/print.h"

#include "clfe/features.h"

template <typename T, typename U>
concept test1 = requires(T a, U b) {
	a + b;
};

template <typename T, typename U>
concept test2 = requires(T a, U b) {
	{ a + b } -> clfe::mcompat<float>;
};

struct f { f() {} };


int main()
{
	std::cout << __cplusplus << "\n";
	std::cout << _MSVC_LANG << "\n";
	std::cout << (_CPP_VERSION) << "\n";

	clfe::clmvec<5, float> v(1.6677754f);

	clfe::println(v);
	clfe::print(clfe::mconst<double>::numbers::pi);
	std::cout << "\n" << v << "\n";
	std::cout << v.normalized() << "\n";
	std::cout << clfe::vcast<int>(v) << "\n";

	std::cout << test2<clfe::clmvec<4, float>, clfe::clmvec<4, int>> << "\n";
	std::cout << test2<float, long> << "\n";

	v += -0.1f;

	std::cout << 5 - v << "\n";

	std::cout << typeid(decltype(static_cast<int>(0) + static_cast<float>(0))).name() << "\n";

	std::cout << (v != (v + 0.0001f)) << "\n";


	std::cout << "\n\n\n\nmatrix test:\n";

	clfe::clmmat<3, 3, float> mat1 = clfe::clmmat<3, 3, float>(5, 1, 3, 6, 3, 9, 1, 2, 0);
	clfe::println(mat1);

	std::cout << mat1 << "\n";
	std::cout << mat1.transpose() << "\n";
	clfe::println(mat1.determinant());

	auto matinv = mat1.inverse();

	clfe::println(matinv);

	auto hopefullyidentity = mat1 * matinv;

	clfe::println(hopefullyidentity);

	//clfe::print_num(14L);

	/*
	std::cout << "Hello World\n";
	clfe::clmvec<5, float> v(1.0f);
	clfe::clmvec<5, double> v2 = v;
	clfe::clmvec<5, float> v3 = v;

	std::cout << v[4] << "\n";

	std::cout << v3.dis2() << "\n";
	std::cout << v3.distance<float>() << "\n";
	std::cout << v3.snormalized().dis2() << "\n";
	
	v2.snormalize(clfe::clmvec<5, double>(2, 0, 0, 0, 0), 12.0);
	std::cout << v2.distance() << "\n";

	std::cout << clfe::mconst<float>::pi << "\n";

	clfe::vec4f v4 = clfe::vec4f(1, -5, 12, 6);
	v4.xr() = 4;

	clfe::vec3f v5 = v4.rba();

	v4.normalize();
	
	std::cout << v4.x() << ", " << v4[1] << ", " << v4[2] << ", " << v4[3] << "\n";
	std::cout << v5.x() << ", " << v5[1] << ", " << v5[2] << "\n";
	std::cout << v5.distance() << " : " << v4.distance() << "\n";

	int f = 0;
	int& f2 = f;
	int& f3 = f2;
	f3 = 9;
	std::cout << f2 << "\n";

	std::cout << clfe::arithmetic<int>;
	*/

	// "\n" or std::endl?
}