

#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <math.h>
#include <float.h>


#ifndef M_PI
#define M_PI 3.141592653589793238462643	
#endif

#ifndef INV_PI
#define INV_PI 0.3183098861837907
#endif

#ifdef __MSC_VER
#define INLINE __forceinline 
//#define INLINE __declspec(noinline)
#else
#define INLINE inline
#endif

class RandomLCG {
	unsigned mSeed;

public:
	INLINE RandomLCG(unsigned seed = 0) : mSeed(seed) {
	}

	INLINE double operator()() { 
		mSeed = 214013u * mSeed + 2531011u; 
		return mSeed * (1.0 / 4294967296.0);
	}
};



struct Vec { 
	double x, y, z;

	static const Vec Zero;
	static const Vec XAxis;
	static const Vec YAxis;
	static const Vec ZAxis;

	INLINE Vec(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {
	}

	INLINE Vec operator+(const Vec& b) const { 
		return Vec(x + b.x, y + b.y,z + b.z); 
	}

	INLINE Vec operator-(const Vec& b) const { 
		return Vec(x - b.x, y - b.y, z - b.z); 
	}

	INLINE Vec operator*(double b) const { 
		return Vec(x * b, y * b, z * b); 
	}
	INLINE Vec operator/(double b) const { 
		return Vec(x / b, y / b, z / b); 
	}


	friend INLINE Vec operator*(const Vec& a, const Vec& b) {
		return Vec(a.x * b.x , a.y * b. y, a.z * b.z); 
	}

	INLINE Vec norm() const { 
		return *this * (1.0 / sqrt(x * x + y * y + z * z)); 
	}
	INLINE double Dot(const Vec& b) const { // dot
		return x * b.x + y * b.y + z * b.z; 
	}

	INLINE Vec Cross(const Vec& b) const { // cross
		return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}

	//INLINE double operator%(const Vec& b) const { // dot
	//	return x * b.x + y * b.y + z * b.z; 
	//}

	//INLINE Vec operator^(const Vec& b) const { // cross
	//	return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	//}
};

INLINE Vec Cross(const Vec& v1,const Vec& v2){ // cross
	
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vec((v1y * v2z) - (v1z * v2y),
                  (v1z * v2x) - (v1x * v2z),
                  (v1x * v2y) - (v1y * v2x));
};
	
INLINE double Dot(const Vec& a,const Vec& b){ // dot
		return a.x * b.x + a.y * b.y + a.z * b.z; 
};

//const Vec Vec::Zero(0, 0, 0);
//const Vec Vec::XAxis(1, 0, 0);
//const Vec Vec::YAxis(0, 1, 0);
//const Vec Vec::ZAxis(0, 0, 1);

struct Ray { 
	Vec o, d;

	INLINE Ray(const Vec &o, const Vec &d) : o(o), d(d) {
	} 
};


#endif
