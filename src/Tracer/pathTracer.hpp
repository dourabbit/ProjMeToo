#ifndef _PATHTRACER_HPP
#define _PATHTRACER_HPP
	

#include <common.h>
//#include <test.hpp>
#include <Math/Math.hpp>
#include <Shape/sphere.hpp>

#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>		


namespace Tracer{
class PathTracer{
public:
	PathTracer();
	~PathTracer();
	void Initialize();
	int static Render(void * ptr);
private:
	Vec static trace (const Ray &pixelCol,RandomLCG& rand);
	Vec static shade(const Vec &x, const Vec &n, const Shape &obj ,RandomLCG& rand);
	static double BRDF(const Shape &obj);
};
}
#endif