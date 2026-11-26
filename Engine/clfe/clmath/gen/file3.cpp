constexpr clmvec<4,T> qslerp(const clmvec<4,T>& q0, const clmvec<4,T>& q1, T t)
{
    clmvec<4,T> r = qmul(qconj(q0), q1), b = q1;
    if (r[0] < T(0)) { r = qneg(r); b = qneg(b); }          // nearer representative
    const T c = r[0];                                       // == cos(th)
    const T s = sqrt(r[1]*r[1] + r[2]*r[2] + r[3]*r[3]);    // == sin(th), no cancellation
    if (s <= T(0)) return qnormalize(q0);                   // same orientation
    const T th = atan2(s, c), w1 = sin(t*th)/s, w0 = cos(t*th) - c*w1;
    return qadd(qscale(q0, w0), qscale(b, w1));
}
constexpr clmvec<4,T> qnlerp(const clmvec<4,T>& q0, const clmvec<4,T>& q1, T t)
{
    const clmvec<4,T> b = (qdot(q0,q1) < T(0)) ? qneg(q1) : q1;
    return qnormalize(qadd(qscale(q0, T(1)-t), qscale(b, t)));
}