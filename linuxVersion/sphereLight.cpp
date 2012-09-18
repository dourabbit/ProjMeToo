#include "sphereLight.hpp"

SphereLight::SphereLight(){};
SphereLight::~SphereLight(){};

SphereLight::
	SphereLight(string name,const Vec& trans,const float& radius,const Vec& e):
	Sphere(name,trans,radius,e, Zero,DIFF)
{
	this->radius = radius;
};

float SphereLight::Pdf(){
	return 1.0f/2*M_PI*this->radius;
};

Vec SphereLight::Sample( RNG* rng){
	float e1=rng->RandomFloat();float e2=rng->RandomFloat();
	Vec result;
	
	//return this->translate;
	return result;
};





	