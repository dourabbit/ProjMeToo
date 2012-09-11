#include "pathTracerSplitted.hpp"
#include <Light/light.hpp>
using namespace Tracer;

void PathTracerSplitted::Initialize(){
	InitializeScenes();
}

int PathTracerSplitted::shaRays = 0;

PathTracerSplitted::PathTracerSplitted(){
	shaRays = 16;
	pathRays = 16;
};

Vec PathTracerSplitted:: indirectIllumination(const Point &x, const RNG &rng){
	bool isAbsorption = rng.RandomFloat()> x.obj->absorption;
	Vec radiance = Zero;
	if(!isAbsorption){
				float phi = 2 * M_PI * rng.RandomFloat();
				float sintheta2 = rng.RandomFloat();
				float costheta = sqrt(1 - sintheta2);
				float sintheta = sqrt(sintheta2);

				Vec w = x.obj->getNorm(x);
				Vec wo = w.x < -0.1 || w.x > 0.1 ? YAxis : XAxis;

				Vec u = Cross(wo,w);
				u.norm();
				Vec v = Cross(w,u);

				Vec dir = u * cos(phi) * sintheta + v * sin(phi) * sintheta + w * costheta;
				dir.norm();

				Ray r = Ray(x,dir);
				trace (r,rng);
	
	}


}

Vec PathTracerSplitted::directIllumination(const Point &x,const RNG &rng){
	Vec estimatedRadiance = Vec();

	for(int i=0; i< shaRays;i++){
		
		float pdfy;
		Point y;
		getLightSample(&pdfy,&rng, y);
		//printf("<%f,%f,%f>\n",x.x,x.y,x.z);
		float G = radianceTransfer(x,y);
		
		if(G==0)
			continue;
		/*
		const Vec* point = &x;
		points.push_back(point);
		*/

		estimatedRadiance = estimatedRadiance+
			x.obj->c * y.obj->e * BRDF(*x.obj) * G/pdfy;
	}
	estimatedRadiance = estimatedRadiance / shaRays;
	return(estimatedRadiance);
};



void PathTracerSplitted::getLightSample(float* pdf,const RNG* rng, Point &result){
	
	float e = rng->RandomFloat();
	int index = (int)e*lights.size();

	*pdf = 1.0f/lights.size();
	*pdf *= lights[index]->Pdf();

	//This doesn't work somehow,
	//the data is swifting for some reason
	//Shape* shape = (Shape*)lights[index];
	
	
	AreaLight* light = (AreaLight*)lights[index];
	Shape* shape = (Shape*)light;
	Vec p = light->Sample(rng);

	//result = Point(shape,p);
	result.obj = shape;
	result.x = p.x;
	result.y = p.y;
	result.z = p.z;
}

//x is point on the object; y is point on the light
float PathTracerSplitted::radianceTransfer(const Point &x, const Point &y ){

	Vec vecx = Vec(x.x,x.y,x.z),vecy = Vec(y.x,y.y,y.z);
	Vec normy = y.obj->getNorm(y);
	
	//
	Vec vecyx = vecx - vecy;
	vecyx.norm();
	
	//Escape when the light is same direction
	float consine2 = Dot(vecyx,normy);

	if(consine2<0) 
		return 0;

	Vec vecxy = vecy - vecx;
	vecxy.norm();
	
	Vec normx = x.obj->getNorm(x);
	float consine1 = Dot(vecxy,normx);
	
	if(consine1<0) 
		return 0;

	if(!visibility(x,y))
		return 0;

	float r = (x-y).length();
	
	shortDis = shortDis < r? shortDis:r;
	//dis.push_back(r);

	return consine1*consine2/(r*r);
};

bool PathTracerSplitted::visibility(const Point &x, const Point &y){
	float t = 0, d = (x-y).length();
	Vec dir = (y-x).norm();
	Ray r = Ray(x,dir);
	Shape* obj = intersect(r, t);
	if(!obj||abs(t-d)<THRESHOLD)
		return true;

	return false;
}

Vec PathTracerSplitted::trace(const Ray &pixelCol,const RNG &rng){
	float t; 
	Shape* obj = intersect(pixelCol, t);
	if(!obj) 
		return Vec::Zero;
	Vec x = pixelCol.o + pixelCol.d * t;
	Vec n = obj->getNorm(x);
	
	Point p = Point(obj, x);
	n = Dot(n,pixelCol.d) < 0 ? n : n * -1;


	Light* light = dynamic_cast<Light*>(obj);
	if(light)
		return obj->e;
	else
		return directIllumination(p, rng);

	return Zero;
}



int PathTracerSplitted::Render(void * ptr) {
	Vec* c = (Vec*)ptr;

	clock_t start = clock(); 

	const int w = 256;
	const int h = 256;

	const int samps =  16; // # samples

	//const Ray cam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm()); // cam pos, dir
	//const Vec cx(w * .5135 / h);
	//const Vec cy = (Cross(cx,cam.d)).norm() * .5135;

	Cam::Persp persp = Cam::Persp(	Vec(-10,0,100),
									Vec(0,0,0),
									45,256,256);
	
#pragma omp parallel for schedule(dynamic, 1)       //OpenMP
	//// Loop over image rows
	//for (int y = 0; y < h; y++) {
	//	fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
	//	RandomLCG rand(y);
	//	// Loop cols
	//	for (unsigned short x=0; x<w; x++) {
	//		// 2x2 subpixel rows
	//		for (int sy = 0; sy < 2; sy++) {
	//			const int i = (h - y - 1) * w + x;

	//			// 2x2 subpixel cols
	//			for (int sx = 0; sx < 2; sx++) {        
	//				Vec pixelCol = Vec::Zero;
	//				for (int s = 0; s < samps; s++) {
	//					float r1 = 2 * rand();
	//					float sintheta2 = 2 * rand();
	//					float dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
	//					float dy = sintheta2 < 1 ? sqrt(sintheta2) - 1 : 1 - sqrt(2 - sintheta2);

	//					Vec dir = cx * (((sx + .5 + dx) / 2 + x) / w - .5) +
	//						    cy * (((sy + .5 + dy) / 2 + y) / h - .5) + cam.d;

	//					pixelCol = pixelCol + trace(Ray(cam.o + dir * 140, dir.norm()),  rand) * (1.0 / samps);
	//				}
	//				c[i] = c[i] + Vec(clamp(pixelCol.x), clamp(pixelCol.y), clamp(pixelCol.z)) * .25;
	//			}
	//		}
	//	}
	//}

	
	RNG rng = RNG();


	// Loop over image rows
	for (int y = 0; y < h; y++) {
		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
		//RandomLCG rand(y);
		// Loop cols
		for (unsigned short x=0; x<w; x++) {
			const int i = (h - y - 1) * w + x;
			Vec pixelCol = Zero;
			for(int s = 0; s<samps;s++){
				Ray ray = persp.UnProject(x,y,rng);
				pixelCol = pixelCol + trace(ray, rng) * (1.0 / samps);
			}
			c[i] = c[i] + Vec(clamp(pixelCol.x), clamp(pixelCol.y), clamp(pixelCol.z));
		}
	}



	return 0;
}


double PathTracerSplitted::BRDF(const Shape &obj){
	return 1;//2*INV_PI;
}

