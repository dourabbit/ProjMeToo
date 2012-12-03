#ifndef _COMMON_H_
#define _COMMON_H_

typedef float DATA;
typedef unsigned char IMGDATA;
#ifdef __MSC_VER
#define INLINE __forceinline 
//#define INLINE __declspec(noinline)
#else
#define INLINE inline
#endif

//#include <Math/Math.hpp>


// These includes are necessary to get the plug-in compile !
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>
#define cimg_plugin "plugins/jpeg_buffer.h"
#include "CImg.h"
#include "ImgWriter.hpp"

#include "Mat.h"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "areaLight.hpp"
#include "sphereLight.hpp"
#include <stdlib.h>
#include <stdio.h> 
#include <cstdlib>
#include <vector>

#include <SDL_thread.h>
#include <SDL_timer.h>
//class _MathHelper;
//class Mat4;
//class Quat;
//class Ray;
//class Point;
//class Shape;
//
//class Vec;
//class RNG;



typedef int (SDLCALL *AfterRenderExec)(const void*);

static std::vector<Shape*> sceneObjs;
static std::vector<Light*> lights;
static std::vector<float> dis;
static std::vector<const Vec*> points;

static float shortDis = 1000;


static int EXITFLAG = 0;
static SDL_mutex *mutLock;
static SDL_mutex *writerLock;
static void prepareLights(){
	for (int i = 0; i<sceneObjs.size(); i++) {
		Light* light=NULL;
		light = dynamic_cast<Light*>(sceneObjs[i]);

		if(light) 
			lights.push_back(light);
	}

}

static void InitializeScenes(){

	//sceneObjs.push_back(new Sphere(1e5,  Vec( 1e5+1,40.8,81.6),  Vec::Zero, Vec(.75,.25,.25),DIFF));//Left
	//sceneObjs.push_back(new Sphere(1e5,  Vec(-1e5+99,40.8,81.6), Vec::Zero, Vec(.25,.25,.75), DIFF));//Right
	//sceneObjs.push_back(new Sphere(1e5,  Vec(50,40.8, 1e5),      Vec::Zero, Vec(.75,.75,.75), DIFF));//Back
	//sceneObjs.push_back(new Sphere(1e5,  Vec(50,40.8,-1e5+170),  Vec::Zero, Vec::Zero,        DIFF));//Front
	//sceneObjs.push_back(new Sphere(1e5,  Vec(50, 1e5, 81.6),     Vec::Zero, Vec(.75,.75,.75), DIFF));//Bottom
	//sceneObjs.push_back(new Sphere(1e5,  Vec(50,-1e5+81.6,81.6), Vec::Zero, Vec(.75,.75,.75), DIFF));//Top

	
	//sceneObjs.push_back(new Triangle( Vec(-20,-12,-47),Vec(3,-40,-47),Vec(7,30,-47),Vec::Zero, Vec(.75,.25,.25),DIFF));
	Vec t1 = Vec(-50,50,-20);
	Vec t2 = Vec(-50,50,-70);
	Vec t3 = Vec(50,50,-20);
	Vec t4 = Vec(50,50,-70);

	Vec b1 = Vec(-50,-50,-20);
	Vec b2 = Vec(-50,-50,-70);
	Vec b3 = Vec(50,-50,-70);
	Vec b4 =Vec(50,-50,-20);
	
	//sceneObjs.push_back(new Plane( t1,t2,b2,b1, Vec::Zero, Vec(.75,.25,.25),DIFF));//Left
	//sceneObjs.push_back(new Plane( t3,t4,b3,b4, Vec::Zero, Vec(.25,.25,.75),DIFF));//Right
	//
	//sceneObjs.push_back(new Plane( t1,t2,t4,t3, Vec::Zero, Vec(.25,.25,.25),DIFF));//Top
	//sceneObjs.push_back(new Plane(b1,b2,b3,b4, Vec::Zero, Vec(.25,.25,.25),DIFF));//Bottom
	//

	//sceneObjs.push_back(new Plane("right",Vec(0,0,0),Vec(0,0,90),100,50,Zero, Vec(.25,.25,.25),DIFF));//Right
	//sceneObjs.push_back(new Plane("bottom",Vec(0,-50,-45),Zero,100,50,Zero, Vec(.25,.25,.25),DIFF));//Bottom
	
	//sceneObjs.push_back(new Plane( t2,t4,b3,b2, Vec::Zero, Vec(.25,.25,.25),DIFF));//Back
	
	//sceneObjs.push_back(new SphereLight("sphere",Vec(0,0,0),2,Vec(150,150,150)));//Glass
	//sceneObjs.push_back(new SphereLight("sphere",Vec(0,2,0),2,Vec(150,150,150)));//Glass
	
	sceneObjs.push_back(new Sphere("sphere",Vec(-10,4,0),9, Zero,  Vec(.25,.25,.25),DIFF));//Glass
	AreaLight* light = new AreaLight("AreaLight",Vec(0,30,10),Vec(180,0,0),10,10,Vec(120,120,120));
	sceneObjs.push_back(light);//Light
	sceneObjs.push_back(new Plane("right",	Vec(40,0,0),	Vec(0,0,90),	80,80,		Zero,Vec(.75,.25,.25),DIFF));//Right
	sceneObjs.push_back(new Plane("left",	Vec(-40,0,0),	Vec(0,0,-90),	80,80,		Zero,Vec(.25,.25,.75),DIFF));//Left
	sceneObjs.push_back(new Plane("top",	Vec(0,40,0),	Vec(0,0,-180),	80,80,		Zero,Vec(.25,.25,.25),DIFF));//Top
	sceneObjs.push_back(new Plane("bottom",	Vec(0,-40,0),	Vec(0,0,0),		80,80,		Zero,Vec(.25,.25,.25),DIFF));//Bottom
	sceneObjs.push_back(new Plane("back",	Vec(0,0,-40),	Vec(90,0,0),	80,80,		Zero,Vec(.25,.25,.25),DIFF));//Back
	sceneObjs.push_back(new Plane("back",	Vec(0,0,60),	Vec(-90,0,0),	80,80,		Zero,Vec(.25,.25,.25),DIFF));//Back
	
	//sceneObjs.push_back(new AreaLight("AreaLight",Vec(40,0,0),Vec(0,0,90),20,20,Vec(150,150,150)));//Light
	
	prepareLights();
};





INLINE float clamp(float x) { 
	if (x < 0)
		return 0;
	else if (x > 1)
		return 1;
	else
		return x;
}

INLINE int toInt(float x) { 
	return int(pow(clamp(x), 1 / 2.2f) * 255.0f + .5f); 
}

//This extremely low efficient
INLINE Shape* intersect(const Ray &pixelCol, float &t) {
	t = 1e20;
	Shape* result = NULL;
	
	//for (Sphere* s = sceneObjs; s != sceneObjs + sizeof(sceneObjs) / sizeof(Sphere); ++s) {
	int dd = sceneObjs.size();
	for (int i = 0; i<sceneObjs.size(); i++) {
		float d=0.0f;
		bool isIntersect = sceneObjs[i]->intersect(pixelCol,d);
		if(!isIntersect)
			continue;

		if (d<t && d>THRESHOLD) {
			t = d;
			result = sceneObjs[i];
		}
	}
	return result;
}

#endif
