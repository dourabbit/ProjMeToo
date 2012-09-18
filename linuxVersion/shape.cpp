#include "shape.hpp"
//Shape::Shape( const Vec& p, const Vec& e, const Vec& c, Refl_t refl)//:
//	/*p(p), e(e), c(c), refl(refl) {
//		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
//		cc = c * (1.0 / maxC);
//		this->absorption = maxC;*/
//{};

Shape::Shape(string name,const Vec &trans,const Vec &rot,const Vec& e, const Vec& c, Refl_t refl):
	e(e), c(c), refl(refl) {
		this->name = name;

		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
		//float luminance = maxC==0?0:c * (1.0 / maxC);
		this->absorption = 0.4; //= maxC+0.3>1?0.9:maxC+0.3;

		this->translate = trans;
		this->rotation = rot;

		this->quat = Quat::SetFromEuler(rot);

		Mat4 rotMat1 = MathHelper.CreateRotation(this->quat);
		this->rotMat = MathHelper.CreateRotation(rot);
		Mat4 transMat = MathHelper.CreateTranslate(trans);
		this->worldMat = transMat*rotMat;
		this->worldInvMat = MathHelper.Inverse(this->worldMat);
};


Shape::Shape(){};

Shape::~Shape(){};


bool Shape::intersect(const Ray &pixelCol, float &eps){
	return false;
}

Vec Shape::getNorm(Vec x){
	return Zero;
}
