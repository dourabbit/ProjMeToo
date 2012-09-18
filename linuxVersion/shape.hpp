
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Math.hpp"
//#include <common.h>
#include "Mat.h"
#include <string>
using namespace std;
class Shape{
public:

	string name;
		
	Shape(string name,const Vec& trans, const Vec& rot,const Vec& e, const Vec& c, Refl_t refl);
	Shape();
	virtual ~Shape();
	virtual bool intersect(const Ray &pixelCol, float &eps);
	virtual Vec getNorm(Vec x);

	Mat4 worldMat;
	Mat4 worldInvMat;

	Vec translate;
	Vec rotation;
	
	Quat quat;
	Mat4 rotMat;
	Vec e, c;      // position, emission, color
	//Vec cc;
	float maxC;
	float absorption;
	Refl_t refl;

};
#endif