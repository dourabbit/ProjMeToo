#include "pathTracerSplitted.hpp"
#include "light.hpp"
//#include <omp.h>
using namespace Tracer;

void PathTracerSplitted::Initialize(){
	InitializeScenes();
}

int PathTracerSplitted::shaRays = 0;
int PathTracerSplitted::pathRays = 0;
int PathTracerSplitted::width = 0;
int PathTracerSplitted::height = 0;
int PathTracerSplitted::traceDepth = 0;

PathTracerSplitted::PathTracerSplitted(){
	shaRays = 4;
	pathRays = 100;
};
PathTracerSplitted::~PathTracerSplitted(){

};

Vec PathTracerSplitted:: indirectIllumination(const Point3D &x, RNG &rng){
	float absorption	= rng.RandomFloat();
	bool isAbsorption	= absorption > x.obj->absorption;
	Vec radiance = Zero;
	//return radiance;

	if(isAbsorption){
	
		return radiance;
	}
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
			Point3D y = trace (r);
			
			if(traceDepth==2&&y.obj!= NULL&&(y.obj->e.x!=0||y.obj->e.y!=0||y.obj->e.z!=0)){
				//return Zero;
			}

			if(y.obj==NULL){
			
				return Zero;
			}
			/////////////////////////////////////////////////////////////////
			//float d = (y-x).length();
			if(y.obj!= NULL){
				float pdf = costheta * INV_PI;
				float cosNx_dir = Dot(x.obj->getNorm(x),dir);
				
				float brdf = BRDF(*x.obj);
				float d = (y-x).length();
				//d = d<1?d+1:d/2;
				d += 1;
				
				
				////if hit the light, check the light direction
				////x is the point to be calcuated
				////y is the point on the light
				//if((y.obj->e.x!=0||y.obj->e.y!=0||y.obj->e.z!=0)&&	//If the light
				//	Dot(dir,y.obj->getNorm(y))<-THRESHOLD&&			//If not same direction
				//	traceDepth!=1){									//If not direct lighting
				//	float cosNy_dir = Dot( y.obj->getNorm(y),dir);
				//	radiance = y.obj->e+x.obj->c*brdf*cosNx_dir*abs(cosNy_dir)/(pdf*d*d);
				//}
				//else{
					Vec wi = computeRadiance(y, radiance,rng);

					if(wi.x==0&&wi.y==0&&wi.z==0)
						return Zero;
					/*
					if((x.obj->e.x!=0||x.obj->e.y!=0||x.obj->e.z!=0))
					{
						printf("asdf");
					}*/


					radiance =	radiance + x.obj->c *
								wi*brdf* cosNx_dir/(pdf*d*d);
				
					
				//}
			}


		//}// end of For all the paths
		//radiance = radiance/pathRays;
	}//end of isAbsorption
	radiance = radiance/(1-absorption);
	
	return radiance;
}

Vec PathTracerSplitted::directIllumination(const Point3D &x, RNG &rng){

	Vec estimatedRadiance = Vec();

	for(int i=0; i< shaRays;i++){
		
		float pdfy;
		Point3D y;
		getLightSample(&pdfy,&rng, y);
		
		if(!visibility(x,y))
			continue;
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



void PathTracerSplitted::getLightSample(float* pdf, RNG* rng, Point3D &result){
	
	int index = lights.size();

	while(index==lights.size()){
	
		float e = rng->RandomFloat();
		index = (int)e*lights.size();
	}


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
float PathTracerSplitted::radianceTransfer(const Point3D &x, const Point3D &y ){

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
	
	shortDis = shortDis < r? shortDis:r;//???????????????????
	//dis.push_back(r);

	return consine1*consine2/(r*r);
};

bool PathTracerSplitted::visibility(const Point3D &x, const Point3D &y){
	float t = 0, d = (x-y).length();
	Vec dir = (y-x).norm();
	Ray r = Ray(x,dir);
	Shape* obj = intersect(r, t);
	if(!obj||abs(t-d)<THRESHOLD)
		return true;

	return false;
}

Vec PathTracerSplitted::computeRadiance(const Point3D &x, Vec &result, RNG &rng){
	//Vec result;
	result = result + directIllumination(x, rng);
	result = result + indirectIllumination(x, rng);
	return result;
}


Point3D PathTracerSplitted::trace(const Ray &ray){
	
	
	float t; 
	Point3D result = Point3D();

	traceDepth++;
	/*if(traceDepth>2)
		return result;*/


	Shape* obj = intersect(ray, t);
	if(!obj) 
		return result;
	Vec x = ray.o + ray.d * t;
	Vec n = obj->getNorm(x);
	
	return Point3D(obj, x);
}

Vec PathTracerSplitted::trace(const Ray &ray,RNG &rng){

	Point3D p = trace(ray);

	if(p.obj==NULL) 
		return Zero;
	
	Light* light = dynamic_cast<Light*>(p.obj);
	if(light)
		return p.obj->e;
	//else
	//	return computeRadiance(p, rng);
	
	//computeRadiance(p, rng);
	Vec pixelCol;

	return computeRadiance(p, pixelCol ,rng);;
}



//int PathTracerSplitted::Render(void * ptr) {
//	Vec* c = (Vec*)ptr;
//
//	clock_t start = clock(); 
//
//
//	//const int samps =  128;
//
//	Cam::Persp persp = Cam::Persp(	Vec(0,0,50),
//									Vec(0,0,0),
//									80.0f,width,height);
//	
//	
//
////#pragma omp parallel for schedule(dynamic, 1)       //OpenMP
////#pragma omp parallel for
//
//
//	// Loop over image rows
//	for (int y = 0; y < height; y++) {
//		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",pathRays,100.*y/(height-1));
//		RNG rng = RNG(y);
//		// Loop cols
//		for (unsigned short x=0; x<width; x++) {
//			const int i = (height - y - 1) * width + x;
//			Vec pixelCol = Zero;
//			for(int s = 0; s<pathRays;s++){
//				Ray ray = persp.UnProject(x,y,rng);
//				traceDepth = 0;
//				Vec pCol = trace(ray, rng);
//				
//				pixelCol = pixelCol + pCol;
//				//printf("%d\n",traceDepth);
//			}
//			pixelCol = pixelCol * (1.0 / pathRays);
//			Vec color = Vec(clamp(pixelCol.x), clamp(pixelCol.y), clamp(pixelCol.z));
//			//c[i] = c[i] + Vec(clamp(pixelCol.x), clamp(pixelCol.y), clamp(pixelCol.z));
//			
//			
//			c[i] = color;
//		}
//	}
//
//
//
//	return 0;
//}




int PathTracerSplitted::Render(void * ptr){
    Block* block = (Block*)ptr;
    //Vec2D<int> a = Vec2D<int>(100,100);
	Cam::Persp persp = Cam::Persp(Vec(0,0,50),
                                  Vec(0,0,0),
                                  80.0f,width,height);
	
    //#pragma omp parallel for schedule(dynamic, 1)       //OpenMP
    //#pragma omp parallel for
    
    int x, y;
	// Loop over image rows
	for (int r = block->pos.y; r < block->height+block->pos.y; r++) {
		//fprintf(stderr,"\rRendering (%d spp) %5.2f%%",pathRays,100.*y/(height-1));
		RNG rng = RNG(r);
		// Loop cols
		for (unsigned short c=block->pos.x; c<block->width+block->pos.x; c++) {
			const int i = r * width+c;
			Vec pixelCol = Zero;
			for(int s = 0; s<pathRays;s++){
				x = c; y = height - r -1;	
				Ray ray = persp.UnProject(x,y,rng);
				traceDepth = 0;
				Vec pCol = trace(ray, rng);
				
				pixelCol = pixelCol + pCol;
				//printf("%d\n",traceDepth);
			}
			pixelCol = pixelCol * (1.0 / pathRays);
			Vec color = Vec(clamp(pixelCol.x), clamp(pixelCol.y), clamp(pixelCol.z));
		
			block->wholeBlock->col[i] = color;
		}
	}
    
	return 0;
}


double PathTracerSplitted::BRDF(const Shape &obj){
	return 1*INV_PI;
}

