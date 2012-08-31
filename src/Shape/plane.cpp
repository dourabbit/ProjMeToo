
#include <Shape/Plane.hpp>

Plane::Plane(	const Vec& p1,const Vec& p2,const Vec& p3,const Vec& p4,
				    const Vec& e, const Vec& c, Refl_t refl)// :
	//t1(p1,p2,p3,e,c,refl),t2(p1,p3,p4,e,c,refl)
	//e(e), c(c), p1(p1),p2(p2),p3(p3), refl(refl) 
{
		this->e = e;
		this->c = c;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;

		this->t1 = new Triangle(p1,p2,p3,e,c,refl);
		this->t2 = new Triangle(p3,p4,p1,e,c,refl);
		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
		cc = c * (1.0 / maxC);
		this->absorption = maxC;
}
	
Plane::~Plane(){

	//something needs to be added here;
	delete t1,t2;
};

Vec Plane::getNorm(Vec x){
	Vec a = p2-p1;
	Vec b = p3-p1;

	Vec result = Cross(a,b);
	result.norm();
	return result;
};

bool Plane::intersect(const Ray &ray, float &eps){
		bool result = t1->intersect(ray, eps)||t2->intersect(ray, eps);
		return result;
};