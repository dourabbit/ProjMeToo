#include <Cam/persp.hpp>
#include <math.h>
using namespace Cam;
Persp::Persp(Vec &origin, Vec &direction, float fov, int height, int width):vpDistance(0.1f){
	

	this->direction = direction;
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

	this->viewMat = MathHelper.CreateLookAt(origin, origin+direction, Vec::YAxis);
}


Ray Persp::UnProject(int U, int V, RNG &rng){
	Ray result;
	Vec centerOfPixel = leftBottomVP + 
						Vec(U*xDelta,V*yDelta,0) + 
						Vec(xDelta/2.0f,yDelta/2.0f,.0f);
	//float epsilon1 = rng.RandomFloat(); float epsilon2 = rng.RandomFloat();
	//centerOfPixel = centerOfPixel + Vec( epsilon1*xDelta, epsilon2*yDelta,.0f);
	centerOfPixel.norm();
	//result = Mat4::Mul(this->viewMat,Ray(centerOfPixel, centerOfPixel));
	result = Mat4::Mul(Mat4::Mat4(),Ray(centerOfPixel, centerOfPixel));
	//result.d.x -=0.2;
	//result.d.y += 0.2;
	//result.o.x -= 0.2;
	//result.o.y += 0.2;
	return result;
}
Persp::~Persp(){

}
	
