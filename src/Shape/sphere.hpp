#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <Shape/shape.hpp>
#include <Mat/Mat.h>
class Sphere{
public:
	Vec p, e, c;      // position, emission, color
	Vec cc;
	double rad;       // radius
	double sqRad; 
	double maxC;
	double absorption;
	Refl_t refl;

	Sphere(double rad, const Vec& p, const Vec& e, const Vec& c, Refl_t refl) ;
	virtual ~Sphere();
	virtual bool intersect(const Ray &pixelCol, double &eps);
};
#endif