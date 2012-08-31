

#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <math.h>
#include <float.h>
#include <string.h>


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

//class RandomLCG {
//	unsigned mSeed;
//
//public:
//	INLINE RandomLCG(unsigned seed = 0) : mSeed(seed) {
//	}
//
//	INLINE float operator()() { 
//		mSeed = 214013u * mSeed + 2531011u; 
//		return mSeed * (1.0 / 4294967296.0);
//	}
//};

#define uint32_t unsigned __int32

#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */




template <class T> const T& max ( const T& a, const T& b ) {
  return (a<b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}



// Random Number Declarations
class RNG {
public:
    RNG(uint32_t seed = 5489UL) {
        mti = N+1; /* mti==N+1 means mt[N] is not initialized */
        Seed(seed);
    }

	void Seed(uint32_t seed) const{
		mt[0]= seed & 0xffffffffUL;
		for (mti=1; mti<N; mti++) {
			mt[mti] =
			(1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
			/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
			/* In the previous versions, MSBs of the seed affect   */
			/* only MSBs of the array mt[].                        */
			/* 2002/01/09 modified by Makoto Matsumoto             */
			mt[mti] &= 0xffffffffUL;
			/* for >32 bit machines */
		}
	};
	float RandomFloat() const{
		float v = (RandomUInt() & 0xffffff) / float(1 << 24);
		return v;
	};
	unsigned long RandomUInt() const{
		unsigned long y;
		static unsigned long mag01[2]={0x0UL, MATRIX_A};
		/* mag01[x] = x * MATRIX_A  for x=0,1 */

		if (mti >= N) { /* generate N words at one time */
			int kk;

			if (mti == N+1)   /* if Seed() has not been called, */
				Seed(5489UL); /* default initial seed */

			for (kk=0;kk<N-M;kk++) {
				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
				mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			for (;kk<N-1;kk++) {
				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
				mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

			mti = 0;
		}

		y = mt[mti++];

		/* Tempering */
		y ^= (y >> 11);
		y ^= (y << 7) & 0x9d2c5680UL;
		y ^= (y << 15) & 0xefc60000UL;
		y ^= (y >> 18);

		return y;
	
	};

private:
    static const int N = 624;
    mutable unsigned long mt[N]; /* the array for the state vector  */
    mutable int mti;
};




struct Vec { 
	float x, y, z;

	//static const Vec Zero;
	//static const Vec XAxis;
	//static const Vec YAxis;
	//static const Vec ZAxis;


	INLINE Vec(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {
	}

	INLINE bool operator==(const Vec& b) const { 
		return x==b.x&&y==b.y&&z==b.z?true:false; 
	}




	INLINE Vec operator+(const Vec& b) const { 
		return Vec(x + b.x, y + b.y,z + b.z); 
	}

	INLINE Vec operator-(const Vec& b) const { 
		return Vec(x - b.x, y - b.y, z - b.z); 
	}

	INLINE Vec operator*(float b) const { 
		return Vec(x * b, y * b, z * b); 
	}
	INLINE Vec operator/(float b) const { 
		float inv = 1.f/b;
		return Vec(x * inv, y *inv, z *inv); 
	}


	friend INLINE Vec operator*(const Vec& a, const Vec& b) {
		return Vec(a.x * b.x , a.y * b. y, a.z * b.z); 
	}




	INLINE float length() const{
		return sqrt(x * x + y * y + z * z);
	}

	INLINE Vec norm(){ 
		float l = length();
		x=x/l;y=y/l;z=z/l;
		return *this / l ; 
	}
	INLINE float Dot(const Vec& b) const { // dot
		return x * b.x + y * b.y + z * b.z; 
	}

	INLINE Vec Cross(const Vec& b) const { // cross
		return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
};

#define Zero Vec(0,0,0)
#define XAxis Vec(1,0,0)
#define YAxis Vec(0,1,0)
#define ZAxis Vec(0,0,1)


INLINE Vec Cross(const Vec& v1,const Vec& v2){ // cross
	
	float v1x = v1.x, v1y = v1.y, v1z = v1.z;
    float v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vec((v1y * v2z) - (v1z * v2y),
                  (v1z * v2x) - (v1x * v2z),
                  (v1x * v2y) - (v1y * v2x));
};
	
INLINE float Dot(const Vec& a,const Vec& b){ // dot
		return a.x * b.x + a.y * b.y + a.z * b.z; 
};



struct Ray { 
	Vec o, d;
	INLINE Ray(){}
	INLINE Ray(const Vec &o, const Vec &d) : o(o), d(d) {
	} 
};

// Mat4 Declarations Copy from Physical Based Rendering
// Some modifications have been applied
struct Mat4 {
    // Mat4 Public Methods
    Mat4() {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] =
             m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] =
             m[3][0] = m[3][1] = m[3][2] = 0.f;
    }
    Mat4(	float t00, float t01, float t02, float t03,
            float t10, float t11, float t12, float t13,
            float t20, float t21, float t22, float t23,
            float t30, float t31, float t32, float t33) {
    m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
    m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
    m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
    m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
	};

    static Mat4 Mul(const Mat4 &m1, const Mat4 &m2) {
        Mat4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.m[i][j] = m1.m[i][0] * m2.m[0][j] +
                            m1.m[i][1] * m2.m[1][j] +
                            m1.m[i][2] * m2.m[2][j] +
                            m1.m[i][3] * m2.m[3][j];
        return r;
    };

	static Vec Mul(const Mat4 &m, const Vec &v){
		Vec result;

		result.x = m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3];
		result.y = m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3];
		result.z = m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3];
		return result;
	};

	static Ray Mul(const Mat4 &m, const Ray &r){
		Ray result;
		result.o = Mul(m,r.o);
		result.d = Mul(m,r.d);

		return result;
	};
    friend Mat4 Inverse(const Mat4 &);
    float m[4][4];
};
class _MathHelper{
public:
	_MathHelper(){

	};
	~_MathHelper(){

	};
	Mat4 CreateLookAt(Vec eyePos,Vec target, Vec up){
		//Mat4 result;
		Vec x,y,z;

		if(eyePos == target) return Mat4();

		Vec t = target - eyePos;

		z = ((target-eyePos)*-1.0f).norm();
		x = Cross(up,z);
		y = Cross(z ,x);

		Mat4 result = Mat4::Mat4(
			x.x,	x.y,	x.z, -(x.x * eyePos.x + x.y * eyePos.y + x.z * eyePos.z),
			y.z,	y.y,	y.z, -(y.x * eyePos.x + y.y * eyePos.y + y.z * eyePos.z),
			z.x,	z.y,	z.z, -(z.x * eyePos.x + z.y * eyePos.y + z.z * eyePos.z),
			0,		0,		0,	 1
			);
		return result;
	};

	Mat4 Inverse(const Mat4 &m){
  float minv[4][4];
    memcpy(minv, m.m, 4*4*sizeof(float));
	float
        b00 = minv[0][0] * minv[1][1] - minv[0][1] * minv[1][0],
        b01 = minv[0][0] * minv[1][2] - minv[0][2] * minv[1][0],
        b02 = minv[0][0] * minv[1][3] - minv[0][3] * minv[1][0],
        b03 = minv[0][1] * minv[1][2] - minv[0][2] * minv[1][1],
        b04 = minv[0][1] * minv[1][3] - minv[0][3] * minv[1][1],
        b05 = minv[0][2] * minv[1][3] - minv[0][3] * minv[1][2],
        b06 = minv[2][0] * minv[3][1] - minv[2][1] * minv[3][0],
        b07 = minv[2][0] * minv[3][2] - minv[2][2] * minv[3][0],
        b08 = minv[2][0] * minv[3][3] - minv[2][3] * minv[3][0],
        b09 = minv[2][1] * minv[3][2] - minv[2][2] * minv[3][1],
        b10 = minv[2][1] * minv[3][3] - minv[2][3] * minv[3][1],
        b11 = minv[2][2] * minv[3][3] - minv[2][3] * minv[3][2],

        d = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06),
        invDet;

        // Calculate the determinant
        if (!d) { return Mat4(); }
        invDet = 1 / d;
		Mat4 result = Mat4(
		(minv[1][1]  * b11 - minv[1][2] * b10 + minv[1][3] * b09) * invDet,
		(-minv[0][1] * b11 + minv[0][2] * b10 - minv[0][3] * b09) * invDet,
		(minv[3][1]  * b05 - minv[3][2] * b04 + minv[3][3] * b03) * invDet,
		(-minv[2][1] * b05 + minv[2][2] * b04 - minv[2][3] * b03) * invDet,
		(-minv[1][0] * b11 + minv[1][2] * b08 - minv[1][3] * b07) * invDet,
		(minv[0][0]  * b11 - minv[0][2] * b08 + minv[0][3] * b07) * invDet,
		(-minv[3][0] * b05 + minv[3][2] * b02 - minv[3][3] * b01) * invDet,
		(minv[2][0]  * b05 - minv[2][2] * b02 + minv[2][3] * b01) * invDet,
		(minv[1][0]  * b10 - minv[1][1] * b08 + minv[1][3] * b06) * invDet,
		(-minv[0][0] * b10 + minv[0][1] * b08 - minv[0][3] * b06) * invDet,
		(minv[3][0]  * b04 - minv[3][1] * b02 + minv[3][3] * b00) * invDet,
		(-minv[2][0] * b04 + minv[2][1] * b02 - minv[2][3] * b00) * invDet,
		(-minv[1][0] * b09 + minv[1][1] * b07 - minv[1][2] * b06) * invDet,
		(minv[0][0]  * b09 - minv[0][1] * b07 + minv[0][2] * b06) * invDet,
		(-minv[3][0] * b03 + minv[3][1] * b01 - minv[3][2] * b00) * invDet,
		(minv[2][0]  * b03 - minv[2][1] * b01 + minv[2][2] * b00) * invDet);

    return result;

	};
};
static _MathHelper MathHelper = _MathHelper();
#endif
