
#include <Shape/triangle.hpp>

Triangle::Triangle(	string name,const Vec& p1,const Vec& p2,const Vec& p3,
				    const Vec& e, const Vec& c, Refl_t refl) :
	Shape(name,Zero,Zero,e,c,refl)
{
		this->e = e;
		this->c = c;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		
}
	
Triangle::~Triangle(){};

Vec Triangle::getNorm(Vec x){
	Vec a = p2-p1;
	Vec b = p3-p1;

	Vec result = Cross(a,b);
	result.norm();
	return result;
};

bool Triangle::intersect(const Ray &ray, float &t){
		Vec e1 = p2 - p1;
		Vec e2 = p3 - p1;
		Vec s1 = Cross(ray.d, e2);
		float divisor = Dot(s1, e1);
    
		if (divisor == 0.)
			return false;
		float invDivisor = 1.f / divisor;

		// Compute first barycentric coordinate
		Vec d = ray.o - p1;
		float b1 = Dot(d, s1) * invDivisor;
		if (b1 < 0. || b1 > 1.)
			return false;

		// Compute second barycentric coordinate
		Vec s2 = Cross(d, e1);
		float b2 = Dot(ray.d, s2) * invDivisor;
		if (b2 < 0. || b1 + b2 > 1.)
			return false;

		// Compute _t_ to intersection point
		t = Dot(e2, s2) * invDivisor;
		if (t < 0 || t > FLT_MAX)
			return false;

		return true;
	
};