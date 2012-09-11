
#ifndef _AREALIGHT_HPP_
#define _AREALIGHT_HPP_

#include <Light/light.hpp>
#include <Shape/plane.hpp>
#include <Math/Math.hpp>
class AreaLight:public Light,public Plane{
public:
	AreaLight();
	AreaLight(string name,const Vec& trans,const Vec& rot,const float& width, const float& height,const Vec& e);
	virtual ~AreaLight();
	virtual Vec Sample(const RNG* rng);
	virtual float Pdf();
	//virtual bool intersect(const Ray &pixelCol, float &eps);

private:
	float area;
	float width;
	float height;
};
#endif