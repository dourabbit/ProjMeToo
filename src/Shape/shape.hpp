
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <Math/Math.hpp>
#include <Mat/Mat.h>
class Shape{
public:
	
	Shape(const Vec& e, const Vec& c, Refl_t refl);
	Shape();
	virtual ~Shape();
	virtual bool intersect(const Ray &pixelCol, double &eps);
	virtual Vec getNorm(Vec x);

	Vec e, c;      // position, emission, color
	Vec cc;
	double maxC;
	double absorption;
	Refl_t refl;

};
#endif