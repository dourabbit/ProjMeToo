#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "shape.hpp"
#include "triangle.hpp"
#include "Mat.h"
#include <vector>
class Plane:public Shape{
public:
	
	Vec p1, p2, p3, p4, norm;
	Triangle* t1;
	Triangle* t2;
	float width, height,area;
	Plane();
	/*Plane(const Vec& p1,const Vec& p2,const Vec& p3, const Vec &p4,
						const Vec& e, const Vec& c, Refl_t refl) ;
	*/
	Plane(string name, const Vec& trans,const Vec& rot,const float &width, const float &height,
			const Vec& e, const Vec& c, Refl_t refl);
	virtual ~Plane();
	virtual bool intersect(const Ray &pixelCol, float &eps);
	virtual Vec getNorm(Vec x);

};
#endif