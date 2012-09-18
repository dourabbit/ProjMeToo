#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "shape.hpp"
#include "Mat.h"
class Triangle:public Shape{
public:
	
	Vec p1, p2, p3;

	Triangle(string name,const Vec& p1,const Vec& p2,const Vec& p3, const Vec& e, const Vec& c, Refl_t refl) ;
	virtual ~Triangle();
	virtual bool intersect(const Ray &pixelCol, float &eps);
	virtual Vec getNorm(Vec x);
};
#endif