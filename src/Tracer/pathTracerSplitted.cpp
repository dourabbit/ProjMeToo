#include "pathTracerSplitted.hpp"
#include <Light/light.hpp>
using namespace Tracer;

void PathTracerSplitted::Initialize(){
	InitializeScenes();
}

int PathTracerSplitted::shaRays = 0;
int PathTracerSplitted::pathRays = 0;
int PathTracerSplitted::width = 0;
int PathTracerSplitted::height = 0;


PathTracerSplitted::PathTracerSplitted(){
	shaRays = 8;
	pathRays = 64;
};

Vec PathTracerSplitted:: indirectIllumination(const Point &x, const RNG &rng){
	float absorption	= rng.RandomFloat();
	bool isAbsorption	= absorption> x.obj->absorption;
	Vec radiance = Zero;
	//return radiance;
	if(!isAbsorption){
		//for(int i=0; i<pathRays;i++){
			//////////////////////////////////////////Sample dir on hemisphere
			//////////////////////////////////////////////////////////////////
			float phi = 2 * M_PI * rng.RandomFloat();
			float sintheta2 = rng.RandomFloat();
			float costheta = sqrt(1 - sintheta2);
			float sintheta = sqrt(sintheta2);

			Vec w = x.obj->getNorm(x);
			Vec wo = w.x < -0.1 || w.x > 0.1 ? YAxis : XAxis;

			Vec u = Cross(wo,w);
			u.norm();
			Vec v = Cross(w,u);

			Vec dir =	u * cos(phi) * sintheta + 
						v * sin(phi) * sintheta + 
						w * costheta;
			dir.norm();//////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			Ray r = Ray(x,dir);
			Point y = trace (r);
			
			//float d = (y-x).length();
			if(y.obj!= NULL){
				float pdf = costheta * INV_PI;
				float cosNx_dir = Dot(x.obj->getNorm(x),dir);
				float brdf = BRDF(*x.obj);
				float d = (y-x).length();
				radiance =	radiance + y.obj->c *
				computeRadiance(y,rng)*brdf* cosNx_dir/(pdf);
			}
		//}// end of For all the paths
		//radiance = radiance/pathRays;
	}//end of isAbsorption
	return radiance/(1-absorption);
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

Vec PathTracerSplitted::computeRadiance(const Point &x, const RNG &rng){
	Vec result;
	result = result + directIllumination(x, rng);
	result = result + indirectIllumination(x, rng);
	return result;
}


Point PathTracerSplitted::trace(const Ray &ray){
	float t; 
	Point result = Point();
	Shape* obj = intersect(ray, t);
	if(!obj) 
		return result;
	Vec x = ray.o + ray.d * t;
	Vec n = obj->getNorm(x);
	
	return Point(obj, x);
}

Vec PathTracerSplitted::trace(const Ray &pixelCol,const RNG &rng){
	//float t; 
	//Shape* obj = intersect(pixelCol, t);
	//if(!obj) 
	//	return Vec::Zero;
	//Vec x = pixelCol.o + pixelCol.d * t;
	//Vec n = obj->getNorm(x);
	//
	//Point p = Point(obj, x);
	//n = Dot(n,pixelCol.d) < 0 ? n : n * -1;//??????????????????

	Point p = trace(pixelCol);

	if(p.obj==NULL) return Zero;

	Light* light = dynamic_cast<Light*>(p.obj);
	if(light)
		return p.obj->e;
	else
		return computeRadiance(p, rng);

	return Zero;
}



int PathTracerSplitted::Render(void * ptr) {
	Vec* c = (Vec*)ptr;

	clock_t start = clock(); 


	const int samps =  128;

	Cam::Persp persp = Cam::Persp(	Vec(-10,0,100),
									Vec(0,0,0),
									45,width,height);
	
#pragma omp parallel for schedule(dynamic, 1)       //OpenMP
	RNG rng = RNG();


	// Loop over image rows
	for (int y = 0; y < height; y++) {
		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps,100.*y/(height-1));
		//RandomLCG rand(y);
		// Loop cols
		for (unsigned short x=0; x<width; x++) {
			const int i = (height - y - 1) * width + x;
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

