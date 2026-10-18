// AI-generated file to test the AI-generated 7-dimensional cross product function

// ===========================================================================
//  cross7_selftest.cpp - compile & run to validate cross7.hpp
//      cl /std:c++17 /EHsc /W4 /O2 /utf-8 cross7_selftest.cpp
//      g++ -std=c++17 -Wall -O2 cross7_selftest.cpp -o selftest
//  Defines a throw-away stand-in for clmvec so the test is self-contained;
//  in your project, drop the stand-in and include your real clmvec header
//  before cross7.hpp.
// ===========================================================================
#include <cmath>
#include <cstdio>
#include <cstdlib>

#ifndef CLMVEC_STANDIN_DEFINED
#define CLMVEC_STANDIN_DEFINED
template <int Size, typename T>
class clmvec {
public:
    T v[Size];
    T&       operator[](int i)       { return v[i]; }
    const T& operator[](int i) const { return v[i]; }
};
#endif

#include "cross7.hpp"

static int failures = 0;
static void check(bool ok, const char* what)
{
    if (!ok) { std::printf("FAIL: %s\n", what); ++failures; }
}

template <typename T> static T dot(const clmvec<7, T>& a, const clmvec<7, T>& b)
{ T s = T(); for (int i = 0; i < 7; ++i) s += a[i] * b[i]; return s; }

static clmvec<7, int> make7(int a, int b, int c, int d, int e, int f, int g)
{ clmvec<7, int> v; v[0]=a; v[1]=b; v[2]=c; v[3]=d; v[4]=e; v[5]=f; v[6]=g; return v; }

static clmvec<7, int> add7(const clmvec<7, int>& a, const clmvec<7, int>& b)
{ clmvec<7, int> r; for (int i = 0; i < 7; ++i) r[i] = a[i] + b[i]; return r; }

static bool eq7(const clmvec<7, int>& a, const clmvec<7, int>& b)
{ for (int i = 0; i < 7; ++i) if (a[i] != b[i]) return false; return true; }

// documented Fano-plane basis products (0-based), must reproduce the table
static void test_basis_products()
{
    clmvec<7, int> e[7];
    for (int i = 0; i < 7; ++i) { e[i] = make7(0,0,0,0,0,0,0); e[i][i] = 1; }

    struct Expected { int i, j, k, s; };                    // e[i] x e[j] = s*e[k]
    static const Expected want[7] = {
        { 0, 1, 2,  1 }, { 0, 3, 6,  1 }, { 0, 4, 5,  1 }, { 1, 3, 5,  1 },
        { 1, 4, 6, -1 }, { 2, 3, 4,  1 }, { 2, 5, 6,  1 },
    };
    for (const Expected& w : want) {
        clmvec<7, int> r = clm::cross7(e[w.i], e[w.j]);
        clmvec<7, int> expct = make7(0,0,0,0,0,0,0);
        expct[w.k] = w.s;
        check(eq7(r, expct), "basis product e_i x e_j");
    }
    // a x a == 0 and e_i x e_i == 0
    for (int i = 0; i < 7; ++i)
        check(eq7(clm::cross7(e[i], e[i]), make7(0,0,0,0,0,0,0)), "self product vanishes");
}

static int rnd(int lo, int hi) { return lo + std::rand() % (hi - lo + 1); }

// exact integer checks of the defining identities + both implementations agree
static void test_identities_int()
{
    for (int t = 0; t < 20000; ++t) {
        clmvec<7, int> a = make7(rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9));
        clmvec<7, int> b = make7(rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9));
        clmvec<7, int> c = make7(rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9), rnd(-9,9));
        clmvec<7, int> x  = clm::cross7(a, b);
        clmvec<7, int> xu = clm::cross7_unrolled(a, b);

        check(eq7(x, xu), "table-driven == unrolled");                                   // (0)
        check(dot(x, a) == 0 && dot(x, b) == 0, "orthogonality");                        // (1)
        check(dot(x, x) == dot(a, a) * dot(b, b) - dot(a, b) * dot(a, b), "Lagrange identity"); // (2)
        check(eq7(clm::cross7(add7(a, b), c), add7(clm::cross7(a, c), clm::cross7(b, c))), "bilinearity"); // (3)
        // antisymmetry: a x b == -(b x a)
        clmvec<7, int> y = clm::cross7(b, a);
        bool anti = true;
        for (int i = 0; i < 7; ++i) if (x[i] + y[i] != 0) anti = false;
        check(anti, "antisymmetry");                                                     // (4)
        // <a x b, c> fully antisymmetric under exchange of any two slots
        check(dot(x, c) == -dot(clm::cross7(a, c), b) && dot(x, c) == dot(clm::cross7(b, c), a),
              "3-form antisymmetry");                                                   // (5)
    }
}

static void test_identities_double()
{
    const double tol = 1e-9;
    for (int t = 0; t < 20000; ++t) {
        clmvec<7, double> a, b;
        for (int i = 0; i < 7; ++i) { a[i] = rnd(-900, 900) / 100.0; b[i] = rnd(-900, 900) / 100.0; }
        clmvec<7, double> x  = clm::cross7(a, b);
        clmvec<7, double> xu = clm::cross7_unrolled(a, b);
        bool same = true;
        for (int i = 0; i < 7; ++i) if (std::fabs(x[i] - xu[i]) > tol) same = false;
        check(same, "double: both impls agree");
        double lhs = dot(x, x), rhs = dot(a, a) * dot(b, b) - dot(a, b) * dot(a, b);
        check(std::fabs(lhs - rhs) <= tol * (1.0 + std::fabs(rhs)), "double: Lagrange identity");
        check(std::fabs(dot(x, a)) <= tol && std::fabs(dot(x, b)) <= tol, "double: orthogonality");
    }
}

// the product is deliberately NOT associative; show a witness instead of asserting
static void show_nonassociativity()
{
    clmvec<7, int> e0 = make7(1,0,0,0,0,0,0), e1 = make7(0,1,0,0,0,0,0), e3 = make7(0,0,0,1,0,0,0);
    clmvec<7, int> lhs = clm::cross7(e0, clm::cross7(e1, e3));   // e0 x (e1 x e3)
    clmvec<7, int> rhs = clm::cross7(clm::cross7(e0, e1), e3);   // (e0 x e1) x e3
    std::printf("non-associativity witness: e1 x (e2 x e4) = (%d,%d,%d,%d,%d,%d,%d)\n",
                lhs[0],lhs[1],lhs[2],lhs[3],lhs[4],lhs[5],lhs[6]);
    std::printf("                           (e1 x e2) x e4 = (%d,%d,%d,%d,%d,%d,%d)\n",
                rhs[0],rhs[1],rhs[2],rhs[3],rhs[4],rhs[5],rhs[6]);
}

int main()
{
    std::srand(20261015u);
    test_basis_products();
    show_nonassociativity();
    test_identities_int();
    test_identities_double();
    std::printf(failures ? "RESULT: %d FAILED CHECKS\n" : "RESULT: all checks passed (%d failures)\n", failures);
    return failures ? 1 : 0;
}
