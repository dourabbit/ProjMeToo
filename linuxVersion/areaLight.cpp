#include "areaLight.hpp"

AreaLight::AreaLight(){};
AreaLight::~AreaLight(){};

AreaLight::AreaLight(string name,const Vec& trans,const Vec& rot,const float& width, 
					const float& height,const Vec& e):
	Plane(name,trans,rot,width,height,e, Zero,DIFF)
{
	

};

float AreaLight::Pdf(){
	return 1.0f/this->area;
};

Vec AreaLight::Sample(RNG* rng){
	float e1=rng->RandomFloat();float e2=rng->RandomFloat();
	Vec result;
	result = result + Vec(	e1*this->width- 0.5*this->width,
							0,
							e2*this->height- 0.5*this->height);
	result = this->worldMat.Mul(this->worldMat,result);
	return result;
};

//bool AreaLight::intersect(const Ray &ray, float &eps){
//	Ray rToO = Mat4::Mul(this->worldInvMat,ray);
//
//	float a = -Dot(rToO.o,Vec(0,1,0));
//	float b = Dot(rToO.d,Vec(0,1,0));
//
//	if(b==0)
//		return false;
//
//	eps = a/b;
//	Vec intersection = rToO.o +  rToO.d*eps;
//
//	float c = abs(intersection.x);
//	float d = abs(intersection.z);
//	if(abs(intersection.x)<width&&abs(intersection.z)<height)
//		return true;
//	
//	return false;
//}




	