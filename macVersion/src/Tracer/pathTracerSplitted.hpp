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



	static int width;
	static int height;

	const static int maxDepth = 100;
	static int traceDepth;
	static int shaRays ;
	static int pathRays;

private:/*
	Vec static trace (const Ray &pixelCol, RNG &rng);
	Vec static shade(const Vec &x, const Vec &n, const Shape &obj, RNG &rng);*/
	
	static double BRDF(const Shape &obj);
	
	Vec static trace (const Ray &ray,  RNG &rng);
	Point3D static trace (const Ray &ray);
	Vec static computeRadiance(const Point3D &x, Vec &result, RNG &rng);

	Vec static directIllumination(const Point3D &x,RNG &rng);
	Vec static indirectIllumination(const Point3D &x, RNG &rng);
	float static radianceTransfer(const Point3D &x, const Point3D &y );
	bool static visibility(const Point3D &x, const Point3D &y);
	void static getLightSample(float* pdf,RNG* rng, Point3D &point);
};
}
#endif