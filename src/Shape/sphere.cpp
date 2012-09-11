
#include <Shape/sphere.hpp>
//
//Sphere::Sphere(float rad, const Vec& p, const Vec& e, const Vec& c, Refl_t refl) :
//	p(p), e(e), c(c), rad(rad), refl(refl) {
//		sqRad = rad * rad;
//		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
//		cc = c * (1.0 / maxC);
//		this->absorption = maxC;
//}
	

Sphere::Sphere(){};
Sphere::Sphere(string name,const Vec& p,float rad , const Vec& e, const Vec& c, Refl_t refl):
	Shape(name,Zero,Zero,e,c,refl) {
		this->p = p;
		sqRad = rad * rad;
		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
		cc = c * (1.0 / maxC);
		this->absorption = maxC;
};
Sphere::~Sphere(){};

Vec Sphere::getNorm(Vec x){
	Vec result = Vec::Zero;
	result = (x-this->p).norm();

	return result;
};

bool Sphere::intersect(const Ray &pixelCol, float &eps){
		//Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-pixelCol^2 = 0
		Vec op = p - pixelCol.o;
		float b = Dot(op,pixelCol.d);
		float dd = Dot(op,op);
		float det = b * b - Dot(op,op) + sqRad;

		if (det < 0)
			return false;
		else {
			float dets = sqrt(det);

			if (b - dets > eps){
				eps = b - dets;
				return true;
			}
			else if (b + dets > eps){
				eps = b + dets;
				return true;
			}
			else
				return false;
		}
	
};