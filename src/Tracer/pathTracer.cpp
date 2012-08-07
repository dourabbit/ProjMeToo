#include "pathTracer.hpp"
using namespace Tracer;


Vec PathTracer::shade(const Vec &x, const Vec &n, const Sphere &obj ,RandomLCG& rand) {
		bool isAbsorption = rand() > obj.absorption;
		Vec radiance = Vec::Zero;
		if (!isAbsorption){//no absorption
			if (true) {
				double r1 = 2 * M_PI * rand();
				double r2 = rand();
				double r2s = sqrt(r2);

				Vec w = n;
				Vec wo = w.x < -0.1 || w.x > 0.1 ? Vec::YAxis : Vec::XAxis;
				Vec u = (wo ^ w).norm(); 
				Vec v = w ^ u;

				Vec d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();

				if(obj.e.x != 0){
					radiance = radiance + obj.e;
				}
				else{
					Vec Li = trace(Ray(x, d), rand);
					radiance = Li*BRDF(obj)*obj.c;
				}
			}
		}
		
		
		return radiance+obj.e;
	
}
PathTracer::PathTracer(){};

Vec PathTracer::trace(const Ray &pixelCol,RandomLCG& rand){
	double t; 
	Sphere* obj = intersect(pixelCol, t);
	if(!obj) return Vec::Zero;
	Vec x = pixelCol.o + pixelCol.d * t;
	Vec n = (x - obj->p).norm();
	n = n % pixelCol.d < 0 ? n : n * -1;

	return shade(x,n, *obj,rand);
}

int PathTracer::Render(void * ptr) {
	Vec* c = (Vec*)ptr;

	clock_t start = clock(); 

	const int w = 256;
	const int h = 256;

	const int samps =  100; // # samples

	const Ray cam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm()); // cam pos, dir
	const Vec cx(w * .5135 / h);
	const Vec cy = (cx ^ cam.d).norm() * .5135;
	//Vec* c = new Vec[w * h];

#pragma omp parallel for schedule(dynamic, 1)       //OpenMP
	// Loop over image rows
	for (int y = 0; y < h; y++) {
		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
		RandomLCG rand(y);

		// Loop cols
		for (unsigned short x=0; x<w; x++) {
			// 2x2 subpixel rows
			for (int sy = 0; sy < 2; sy++) {
				const int i = (h - y - 1) * w + x;

				// 2x2 subpixel cols
				for (int sx = 0; sx < 2; sx++) {        
					Vec pixelCol = Vec::Zero;
					for (int s = 0; s < samps; s++) {
						double r1 = 2 * rand();
						double r2 = 2 * rand();
						double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
						double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

						Vec d = cx * (((sx + .5 + dx) / 2 + x) / w - .5) +
							    cy * (((sy + .5 + dy) / 2 + y) / h - .5) + cam.d;

						pixelCol =pixelCol+ trace(Ray(cam.o + d * 140, d.norm()),  rand) * (1.0 / samps);
					}
					c[i] = c[i] + Vec(clamp(pixelCol.x), clamp(pixelCol.y), clamp(pixelCol.z)) * .25;
				}
			}
		}
	}
	return 0;
}


double PathTracer::BRDF(const Sphere &obj){
	return 2*INV_PI;
}

