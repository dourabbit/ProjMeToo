#ifndef _PATHTRACERSPLITTED_HPP
#define _PATHTRACERSPLITTED_HPP
	

#include <common.h>
#include <Sampler/sampler.hpp>
#include <Math/Math.hpp>
#include <Shape/sphere.hpp>
#include <Cam/persp.hpp>

#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>		


namespace Tracer{
class PathTracerSplitted{
public:
	PathTracerSplitted();
	~PathTracerSplitted();
	void Initialize();
	int static Render(void * ptr);
private:/*
	Vec static trace (const Ray &pixelCol, RNG &rng);
	Vec static shade(const Vec &x, const Vec &n, const Shape &obj, RNG &rng);*/
	
	static int shaRays ;
	static int pathRays;
	static double BRDF(const Shape &obj);
	
	Vec static trace (const Ray &pixelCol,const RNG &rng);
	
	Vec static directIllumination(const Point &x,const RNG &rng);
	Vec static indirectIllumination(const Point &x, const RNG &rng);
	float static radianceTransfer(const Point &x, const Point &y );
	bool static visibility(const Point &x, const Point &y);
	void static getLightSample(float* pdf,const RNG* rng, Point &point);
};
}
#endif