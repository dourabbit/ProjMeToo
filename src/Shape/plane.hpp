#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include <Shape/shape.hpp>
#include <Shape/triangle.hpp>
#include <Mat/Mat.h>
#include <vector>
class Plane:public Shape{
public:
	
	Vec p1, p2, p3, p4;
	Triangle* t1;
	Triangle* t2;
	Plane(const Vec& p1,const Vec& p2,const Vec& p3, const Vec &p4,
						const Vec& e, const Vec& c, Refl_t refl) ;
	virtual ~Plane();
	virtual bool intersect(const Ray &pixelCol, double &eps);
	virtual Vec getNorm(Vec x);
};
#endif