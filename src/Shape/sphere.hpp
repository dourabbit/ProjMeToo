#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <Shape/shape.hpp>

class Sphere:public Shape{
public:
	
	Sphere();
	Sphere(double rad, const Vec& p, const Vec& e, const Vec& c, Refl_t refl) ;
	virtual ~Sphere();
	virtual bool intersect(const Ray &pixelCol,  double &eps);
	virtual Vec getNorm(Vec x);

	double rad;       // radius
	Vec p;
	double sqRad; 

};
#endif 