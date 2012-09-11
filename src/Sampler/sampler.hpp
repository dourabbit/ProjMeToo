#ifndef _SAMPLER_HPP_
#define _SAMPLER_HPP_

#include <Sampler/sampler.hpp>
#include <Mat/Mat.h>
#include <vector>
#include <Math/Math.hpp>

void ConcentricSampleDisk(float u1, float u2, float *dx, float *dy);
inline Vec CosineSampleHemisphere(float u1, float u2) {
    Vec ret;
    ConcentricSampleDisk(u1, u2, &ret.x, &ret.y);
    ret.z = sqrtf(Max(0.f, 1.f - ret.x*ret.x - ret.y*ret.y));
    return ret;
}
#endif