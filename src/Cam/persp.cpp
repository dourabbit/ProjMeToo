#include <Cam/persp.hpp>
#include <math.h>
using namespace Cam;
Persp::Persp(Vec &origin, Vec &target, float fov, int height, int width):vpDistance(0.1f){
	
	this->target = target;
	this->direction = (target-origin).norm();
	this->origin = origin;

	this->aspect = (float)width/(float)height;
	this->fov = fov;

	this->height = height;
	this->width = width;

	
	float yHeight= vpDistance* tan( fov/2) * 2;
	float xWidth = yHeight * this->aspect;

	this->xDelta = xWidth/(float)this->width;
	this->yDelta = yHeight/(float)this->height;
	this->leftBottomVP = Vec(-xWidth/2.0f,-yHeight/2.0f,-vpDistance);
	this->viewMat = MathHelper.CreateLookAt(origin, this->target, Vec::YAxis);
	this->viewMatInv = MathHelper.Inverse(this->viewMat);
}


Ray Persp::UnProject(int U, int V, RNG &rng){
	Ray result;
	Vec centerOfPixel = leftBottomVP + 
						Vec(U*xDelta,V*yDelta,0) + 
						Vec(xDelta/2.0f,yDelta/2.0f,.0f);
	float epsilon1 = rng.RandomFloat(); float epsilon2 = rng.RandomFloat();
	centerOfPixel = centerOfPixel + Vec( epsilon1*xDelta, epsilon2*yDelta,.0f);
	Vec dir = Vec(centerOfPixel.x, centerOfPixel.y, centerOfPixel.z);
	dir.norm();

	result = Mat4::Mul(this->viewMatInv,Ray(centerOfPixel, dir));
	return result;
}
Persp::~Persp(){

}
	
