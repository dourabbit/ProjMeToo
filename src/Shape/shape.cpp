#include <Shape/shape.hpp>
//Shape::Shape( const Vec& p, const Vec& e, const Vec& c, Refl_t refl)//:
//	/*p(p), e(e), c(c), refl(refl) {
//		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
//		cc = c * (1.0 / maxC);
//		this->absorption = maxC;*/
//{};

Shape::Shape(const Vec& e, const Vec& c, Refl_t refl):
	e(e), c(c), refl(refl) {
		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
		cc = c * (1.0 / maxC);
		this->absorption = maxC;
};


Shape::Shape(){};

Shape::~Shape(){};


bool Shape::intersect(const Ray &pixelCol, double &eps){
	return false;
}

Vec Shape::getNorm(Vec x){
	return Vec::Zero;
}
