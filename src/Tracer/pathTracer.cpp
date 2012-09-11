#include "pathTracer.hpp"
using namespace Tracer;

void PathTracer::Initialize(){
	InitializeScenes();


}

Vec PathTracer::shade(const Vec &x, const Vec &n, const Shape &obj, RNG &rng) {
		
		bool isAbsorption = rng.RandomFloat() > obj.absorption;
		Vec radiance = Vec::Zero;
		if (!isAbsorption){//no absorption
			if (true) {
				float phi = 2 * M_PI * rng.RandomFloat();
				float sintheta2 = rng.RandomFloat();
				float costheta = sqrt(1 - sintheta2);
				float sintheta = sqrt(sintheta2);

				Vec w = n;
				Vec wo = w.x < -0.1 || w.x > 0.1 ? Vec::YAxis : Vec::XAxis;
				/*
				Vec u = (wo ^ w).norm(); 
				Vec v = w ^ u;
				*/
				Vec u = Cross(wo,w);
				u.norm();
				Vec v = Cross(w,u);

				Vec d = u * cos(phi) * sintheta + v * sin(phi) * sintheta + w * costheta;
				d.norm();

				Vec test = CosineSampleHemisphere(rng.RandomFloat(),rng.RandomFloat());

				if(obj.e.x != 0){
					radiance = radiance + obj.e;
				}
				else{
					Vec Li = trace(Ray(x, d),rng);
					float tmp = BRDF(obj);
					radiance = Li*obj.c;
				}
			}
		}

		return radiance+obj.e;
};

PathTracer::PathTracer(){};

Vec PathTracer::trace(const Ray &pixelCol, RNG &rng){
	float t; 
	Shape* obj = intersect(pixelCol, t);
	if(!obj) 
		return Vec::Zero;
	Vec x = pixelCol.o + pixelCol.d * t;
	//Vec n = (x - obj->p).norm();
	Vec n = obj->getNorm(x);
	//n = n % pixelCol.d < 0 ? n : n * -1;
	
	n = Dot(n,pixelCol.d) < 0 ? n : n * -1;

	return shade(x,n, *obj, rng);
}

int PathTracer::Render(void * ptr) {
	Vec* c = (Vec*)ptr;

	clock_t start = clock(); 

	const int w = 256;
	const int h = 256;

	const int samps =  10; // # samples

	//const Ray cam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm()); // cam pos, dir
	//const Vec cx(w * .5135 / h);
	//const Vec cy = (Cross(cx,cam.d)).norm() * .5135;

	Cam::Persp persp = Cam::Persp(	Vec(0,0,0),
									Vec(0,0,-1),
									90,256,256);
	
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


double PathTracer::BRDF(const Shape &obj){
	return 1;//2*INV_PI;
}

