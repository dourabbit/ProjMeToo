
#ifndef _SPHERELIGHT_HPP_
#define _SPHERELIGHT_HPP_

#include <Light/light.hpp>
#include <Shape/sphere.hpp>
#include <Math/Math.hpp>
class SphereLight:public Light,public Sphere{
public:
	SphereLight();
	SphereLight(string name,const Vec& trans,const float& radius,const Vec& e);
	virtual ~SphereLight();
	virtual Vec Sample(RNG* rng);
	virtual float Pdf();
	//virtual bool intersect(const Ray &pixelCol, float &eps);

private:
	float radius;
};
#endif