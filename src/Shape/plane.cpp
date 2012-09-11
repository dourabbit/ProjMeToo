
#include <Shape/Plane.hpp>
#include <cmath>
//Plane::Plane(	const Vec& p1,const Vec& p2,const Vec& p3,const Vec& p4,
//				  const Vec& e, const Vec& c, Refl_t refl)// :
//	//t1(p1,p2,p3,e,c,refl),t2(p1,p3,p4,e,c,refl)
//	//e(e), c(c), p1(p1),p2(p2),p3(p3), refl(refl) 
//{
//		this->e = e;
//		this->c = c;
//		this->p1 = p1;
//		this->p2 = p2;
//		this->p3 = p3;
//		this->p4 = p4;
//
//
//
//		this->t1 = new Triangle(p1,p2,p3,e,c,refl);
//		this->t2 = new Triangle(p3,p4,p1,e,c,refl);
//		maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
//		cc = c * (1.0 / maxC);
//		this->absorption = maxC;
//}

Plane::Plane(string inputNm,const Vec& trans, const Vec& rot,const float &width, 
		const float &height,const Vec& e, const Vec& c, Refl_t refl):
	Shape(inputNm,trans,rot,e,c,DIFF)
{
		name = inputNm;
		this->width = width;
		this->height = height;
		
		//this->p1 = this->translate -Vec(width*0.5,0,height*0.5);

		this->p1 = Vec(-width*0.5,0,-height*0.5);
		this->p2 = Vec(p1.x+width,p1.y,p1.z);
		this->p3 = Vec(p2.x,p2.y,p2.z+height);
		this->p4 = Vec(p1.x,p1.y,p1.z+height);

		this->p1 = Mat4::Mul(this->worldMat,this->p1);
		this->p2 =  Mat4::Mul(this->worldMat , this->p2);
		this->p3 =  Mat4::Mul(this->worldMat , this->p3);
		this->p4 =  Mat4::Mul(this->worldMat , this->p4);

		/*this->t1 = new Triangle(p1,p2,p3,e,c,refl);
		this->t2 = new Triangle(p3,p4,p1,e,c,refl);
		*/
		
		/*maxC = c.x > c.y && c.y > c.z ? c.x : c.y > c.z ? c.y : c.z;
		cc = maxC==0?0:c * (1.0 / maxC);
		this->absorption = maxC;*/
		//this->norm = Mat4::Mul(this->worldMat, norm);
		//this->norm.norm();

		

		//this->norm = Quat::Rotate(norm,this->quat);
		this->norm = Mat4::Mul(this->rotMat, Vec(0,1,0));
		this->e = e;
		this->c = c;
}
	
Plane::Plane(){};
Plane::~Plane(){

	//something needs to be added here;
	delete t1,t2;
};

Vec Plane::getNorm(Vec x){
	if(norm.x!=0||norm.y!=0||norm.z!=0) return this->norm;

	Vec a = p2-p1;
	Vec b = p3-p1;

	Vec result = Cross(a,b);
	result.norm();

	this->norm = result;
	return result;
};

bool Plane::intersect(const Ray &ray, float &eps){
	Ray wToO = Mat4::Mul(this->worldInvMat,ray);
	Mat4 test = Mat4::Mul(this->worldInvMat, this->worldMat);
	float a = -Dot(wToO.o,Vec(0,1,0));
	float b = Dot(wToO.d,Vec(0,1,0));

	if(b==0)
		return false;

	eps = a/b;
	Vec intersection = wToO.o +  wToO.d*eps;

	float c = abs(intersection.x);
	float d = abs(intersection.z);
	if(abs(intersection.x)<width&&abs(intersection.z)<height)
		return true;
	
	return false;
};