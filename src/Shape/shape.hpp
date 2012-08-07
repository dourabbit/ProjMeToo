
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <Math/Math.hpp>
class Shape{
public:
	
	Shape();
	virtual ~Shape();
	virtual bool intersect(const Ray &pixelCol, const double &eps)=0;
};
#endif