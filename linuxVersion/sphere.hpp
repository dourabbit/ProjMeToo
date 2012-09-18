#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "shape.hpp"

class Sphere:public Shape{
public:
	
	Sphere();
	Sphere(string name,const Vec& p,float rad, const Vec& e, const Vec& c, Refl_t refl) ;
	virtual ~Sphere();
	virtual bool intersect(const Ray &pixelCol,  float &eps);
	virtual Vec getNorm(Vec x);

	float rad;       // radius
	Vec p;
	float sqRad; 

};
#endif 