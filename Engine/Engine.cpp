
#include <iostream>

#include "clfe/clmath/vector.h"
#include "clfe/clmath/matrix.h"
#include "clfe/clmath/quaternion.h"

#include "clfe/clutil/print.h"

#include "clfe/features.h"

#include "clfe/clmath/matutils.h"

#include "clfe/clwind/windows.h"


using namespace clfe;

int main()
{
	/*
	clfe::mat44i m44i(
		1, 0, 0, 0,
		0, 1, 0, 0,
		1, 0, -1, 0,
		1, 1, 0, -1
	);

	clfe::mat44i m44i2(
		1, 2, 3, 4,
		5, 6, 7, 8,
		1, 2, 3, 4,
		6, 8, 10, 12
	);

	clfe::println(m44i * m44i2);

	clfe::println(clfe::mrotatex(1.0f) * clfe::mrotatey(2.0f));
	clfe::println(clfe::mrotateyx(2.0f, 1.0f));

	clfe::println(clfe::mrotate(1.0f).inverse());

	std::cout << "\n\n\n";

	clfe::quat q1(1, 2, 3, 4);
	q1.normalize();
	clfe::println(q1 * -q1);
	clfe::println(clfe::vdot(q1, -q1));
	*/
		
	clfe::clwinit();

	clfe::window_hint(clfe::WS_START_VISIBLE | clfe::WS_NO_TASKBAR, true);
	//clfe::window_hint(clfe::WS_CLOSEABLE, false);
	clfe::window_hint(clfe::WS_TRANSPARENT);
	clwindow* window = clfe::create_window(800, 600, "Test Window");
	//clfe::window_hint(clfe::WS_DECORATED, false);
	//clfe::window_hint(clfe::WS_RESIZABLE, false);
	//clfe::window_hint_visible();
	//clwindow* window2 = new clwwindow(-1, -1, 800, 600, "default", 0);
	//clwindow* window2 = clfe::create_window(800, 600, "default");

	//window->cpos(200, 300);
	//window->y(1000);
	//window->cx(500);
	//window->csize(800, 600);
	//window->cwidth(1000);

	window->name("happy");

	std::cout << "pos: " << window->pos() << "\n";
	std::cout << "cpos: " << window->cpos() << "\n";
	std::cout << "size: " << window->size() << "\n";
	std::cout << "csize: " << window->csize() << "\n";
	std::cout << "title: " << window->name() << "\n";

	std::cout << "\n\n";
	std::cout << mconst<float>::epsilon() << "\n";
	std::cout << mconst<double>::epsilon() << "\n";

	vec4f a = vec4f(1, 2, 3, 4);
	std::cout << vlen2(a) << ", " << vlength(a) << ", " << vinv_len(a) << "\n";

	quatf q1 = quatf(1, 2, 3, 4).normalize();
	quatf q2 = quatf(4, 3, 2, 1).normalize();
	for (int i = 0; i < 11; i++)
	{
		float t = i / 10.0f;
		std::cout << "\n" << t << ":\n";
		std::cout << "qn: " << qnlerp(q1, q2, t) << "\n";
		std::cout << "qs: " << qslerp(q1, q2, t) << "\n";
		std::cout << "re: " << qslerp(q2, t) << "\n";
	}

	while (!window->close_requested())
	{
		clfe::clwstep();
	}

	//window->destroy();
	//delete window;

	clfe::clwterm();

	return 0;

	/*
	std::cout << __cplusplus << "\n";
	std::cout << _MSVC_LANG << "\n";
	std::cout << (_CPP_VERSION) << "\n";

	clfe::mat44f m44f(
		0, 2, 5, -1,
		6, -12, 6, 7,
		6, 7, 10, -5,
		1, 2, -3, -4);

	clfe::println(m44f);
	//clfe::println(m44f * m44f);
	//clfe::println(m44f + 2 * clfe::mat44f());

	clfe::println();

	clfe::vec4f v4f(1, 1, 1, 1);

	clfe::println(v4f * m44f);
	clfe::println(m44f * v4f);
	*/

	/*
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

	auto rvec = clfe::vresize<7, float>(v, 6, 7);
	std::cout << rvec << "\n";
	*/

	/*
	std::cout << "\n\n\n\nmatrix test:\n";

	clfe::clmmat<3, 3, float> mat1 = clfe::clmmat<3, 3, float>(5, 1, 3, 6, 3, 9, 1, 2, 0);
	clfe::println(mat1);

	std::cout << mat1 << "\n";
	std::cout << mat1.transpose() << "\n";
	clfe::println(mat1.determinant());
	clfe::println(mdeterminant(mat1));

	auto matinv = minverse(mat1);

	clfe::println(matinv);

	auto hopefullyidentity = mat1 * matinv;

	clfe::println(hopefullyidentity);

	auto shrunk = clfe::mresize<2, 1, int>(hopefullyidentity);
	clfe::println(shrunk);

	auto expanded = clfe::mresize<3, 3, float>(shrunk, 2, 3, 5, 6, 9, 6, 1);
	clfe::println(expanded);

	//clfe::println(mvcast(rvec));

	clfe::vec4f result;
	clfe::println(result);

	clfe::mat44d result2;
	clfe::println(result2);
	*/

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