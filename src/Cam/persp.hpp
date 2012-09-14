#ifndef _PERSP_HPP
#define _PERSP_HPP
	

//#include <common.h>
#include <Math/Math.hpp>
namespace Cam{
class Persp{
public:
	int height;
	int width;
	
	float aspect;
	float fov;
	
	Vec origin, direction, target;
	Mat4 viewMat, viewMatInv;

	Vec leftBottomVP;
	float xDelta, yDelta;
	const float vpDistance;
	Persp(Vec &origin, Vec &target, float fov,int width,int height);
	Ray UnProject(int U, int V, RNG &rng);
	~Persp();
};
}
#endif