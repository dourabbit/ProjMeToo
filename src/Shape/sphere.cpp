
#include <Shape/sphere.hpp>

Sphere::Sphere(double rad, const Vec& p, const Vec& e, const Vec& c, Refl_t refl) :
	p(p), e(e), c(c), rad(rad), refl(refl) {
		sqRad = rad * rad;
		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
		cc = c * (1.0 / maxC);
		this->absorption = maxC;
}
	
Sphere::~Sphere(){};

bool Sphere::intersect(const Ray &pixelCol, double &eps){
		//Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-pixelCol^2 = 0
		Vec op = p - pixelCol.o;
		double b = op % pixelCol.d;
		double det = b * b - op % op + sqRad;

		if (det < 0)
			return false;
		else {
			double dets = sqrt(det);

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