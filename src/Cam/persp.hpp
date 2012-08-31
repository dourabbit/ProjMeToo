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

	Vec origin, direction;
	Mat4 viewMat;

	Vec leftBottomVP;
	float xDelta, yDelta;
	const float vpDistance;
	Persp(Vec &origin, Vec &direction, float fov,int height,int width);
	Ray UnProject(int U, int V, RNG &rng);
	~Persp();
};
}
#endif