// AI-generated when asked to write a 7-dimensional cross product function
// The AI really went a "little" above and beyond

/*#pragma once
// ===========================================================================
//  cross7.hpp - 7-dimensional cross product for clmvec<Size, T>
//
//  R^7 is (with R^3) the only dimension admitting a bilinear, alternating,
//  metric-compatible vector product:
//
//      a x b = -(b x a)                       (alternating)
//      <a x b, a> = <a x b, b> = 0            (orthogonal to both inputs)
//      |a x b|^2 = |a|^2 |b|^2 - <a,b>^2      (metric / Lagrange identity)
//      <a x b, c> is fully antisymmetric      (the G2 associative 3-form)
//
//  It is NOT associative, and it depends on a choice of orientation of the
//  Fano plane. There are exactly 16 admissible sign choices out of the 2^7 =
//  128 possible orientations of the 7 lines (checked by exhaustive search);
//  this implementation uses the classic one, i.e. for the imaginary octonion
//  units e1..e7 (1-based labels here):
//      e1 x e2 = e3,   e1 x e4 = e7,   e1 x e5 = e6,   e2 x e4 = e6,
//      e2 x e5 = -e7,  e3 x e4 = e5,   e3 x e6 = e7.
//  (Flipping every sign gives the other member of the same orientation pair.)
//
//  Assumptions about clmvec<Size, T>:
//    * 0-based access: T& operator[](int) and const T& operator[](int) const
//    * default-constructible object; every component we return is assigned
//      before returning, so zero-initialisation is NOT required.
//    * T supports *, +, -, +=, -= and value-initialisation T() == 0
//      (works for int, float, double, __int128, boost::multiprecision, ...)
// ===========================================================================

#include <type_traits>

// The real definition is expected to come from the project's own header;
// this is only a re-declaration so the header can be compiled stand-alone.
template <int Size, typename T> class clmvec;

namespace clm {

// ---------------------------------------------------------------------------
// Table-driven version: 7 oriented Fano-plane triples.
// Semantics: e[i] x e[j] = s * e[k], and by cyclicity
//            e[j] x e[k] = s * e[i],  e[k] x e[i] = s * e[j].
// (0-based indices; s is the orientation sign of that line.)
// ---------------------------------------------------------------------------
struct FanoTriple { int i, j, k, s; };

inline constexpr FanoTriple kFano7[7] = {
    { 0, 1, 2,  1 },   // e1 x e2 = e3
    { 0, 3, 6,  1 },   // e1 x e4 = e7
    { 0, 4, 5,  1 },   // e1 x e5 = e6
    { 1, 3, 5,  1 },   // e2 x e4 = e6
    { 1, 4, 6, -1 },   // e2 x e5 = -e7
    { 2, 3, 4,  1 },   // e3 x e4 = e5
    { 2, 5, 6,  1 },   // e3 x e6 = e7
};

/// 7D cross product, generic over the element type.
/// Only the first 7 components participate, so Size must be exactly 7.
template <int Size, typename T>
inline clmvec<Size, T> cross7(const clmvec<Size, T>& a, const clmvec<Size, T>& b)
{
    static_assert(Size == 7,
        "cross7 is defined on clmvec<7, T>. If your vector is larger, either "
        "slice it, or relax this assert to Size >= 7 and decide what the "
        "trailing components should contain (they would stay default-constructed).");
    static_assert(std::is_default_constructible<T>::value,
        "cross7 needs a value-initialised zero accumulator: T() must be 0.");

    T acc[7] = { T(), T(), T(), T(), T(), T(), T() };

    for (int t = 0; t < 7; ++t) {
        const FanoTriple f = kFano7[t];
        const T cij = a[f.i] * b[f.j] - a[f.j] * b[f.i];   // -> component k
        const T cjk = a[f.j] * b[f.k] - a[f.k] * b[f.j];   // -> component i
        const T cki = a[f.k] * b[f.i] - a[f.i] * b[f.k];   // -> component j
        if (f.s > 0) { acc[f.k] += cij; acc[f.i] += cjk; acc[f.j] += cki; }
        else           { acc[f.k] -= cij; acc[f.i] -= cjk; acc[f.j] -= cki; }
    }

    clmvec<Size, T> out;
    for (int i = 0; i < 7; ++i) out[i] = acc[i];
    return out;
}

// ---------------------------------------------------------------------------
// Hand-unrolled version: identical maths, 42 products / 21 differences,
// no accumulator, no loop. Usually the faster of the two and the easiest to
// vectorise; keep it as the reference implementation if you profile.
// In 1-based textbook notation (a1..a7):
//   (a x b)_1 = a2 b3 - a3 b2 + a4 b7 - a7 b4 + a5 b6 - a6 b5
//   (a x b)_2 = a3 b1 - a1 b3 + a4 b6 - a6 b4 + a7 b5 - a5 b7
//   ... and so on, see the code below for all seven components.
// ---------------------------------------------------------------------------
template <int Size, typename T>
inline clmvec<Size, T> cross7_unrolled(const clmvec<Size, T>& a, const clmvec<Size, T>& b)
{
    static_assert(Size == 7, "cross7_unrolled is defined on clmvec<7, T>.");

    clmvec<Size, T> out;
    out[0] = a[1] * b[2] - a[2] * b[1]
           + a[3] * b[6] - a[6] * b[3]
           + a[4] * b[5] - a[5] * b[4];
    out[1] = a[2] * b[0] - a[0] * b[2]
           + a[3] * b[5] - a[5] * b[3]
           + a[6] * b[4] - a[4] * b[6];
    out[2] = a[0] * b[1] - a[1] * b[0]
           + a[3] * b[4] - a[4] * b[3]
           + a[5] * b[6] - a[6] * b[5];
    out[3] = a[6] * b[0] - a[0] * b[6]
           + a[5] * b[1] - a[1] * b[5]
           + a[4] * b[2] - a[2] * b[4];
    out[4] = a[5] * b[0] - a[0] * b[5]
           + a[1] * b[6] - a[6] * b[1]
           + a[2] * b[3] - a[3] * b[2];
    out[5] = a[0] * b[4] - a[4] * b[0]
           + a[1] * b[3] - a[3] * b[1]
           + a[6] * b[2] - a[2] * b[6];
    out[6] = a[0] * b[3] - a[3] * b[0]
           + a[4] * b[1] - a[1] * b[4]
           + a[2] * b[5] - a[5] * b[2];
    return out;
}

} // namespace clm
*/