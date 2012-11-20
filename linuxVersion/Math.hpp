

#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <math.h>
#include <cmath>
#include <float.h>
#include <string.h>
//#include <common.h>

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

//#define uint32_t unsigned __int32
#include <stdint.h>
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

#define THRESHOLD 0.0001

class Shape;


template <class T> const T& Max ( const T& a, const T& b ) {
  return (a<b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}

//class RNG {
//	unsigned mSeed;
//
//public:
//	INLINE RNG(unsigned seed = 0) : mSeed(seed) {
//	}
//
//	INLINE float RandomFloat(){ 
//		mSeed = 214013u * mSeed + 2531011u; 
//		return mSeed * (1.0 / 4294967296.0);
//	}
//};

// Random Number Declarations
class RNG {
public:
    RNG(uint32_t seed = 5489UL) {
        mti = N+1;
	 /* mti==N+1 means mt[N] is not initialized */
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

template <class T>
class Vec2D{
public:
    T x,y;
    
	INLINE Vec2D(T x = 0, T y = 0) : x(x), y(y){
	}
    
	INLINE bool operator==(const Vec2D& b) const {
		return x==b.x&&y==b.y?true:false;
	}
    
    
    
    
	INLINE Vec2D operator+(const Vec2D& b) const {
		return Vec2D(x + b.x, y + b.y);
	}
    
	INLINE Vec2D operator-(const Vec2D& b) const {
		return Vec2D(x - b.x, y - b.y);
	}
    
};



class Vec { 
public:
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
		return Vec(x,y,z); 
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

class Point3D:public Vec{
public:
	static Point3D Point3DZero;

	Shape* obj;
	Point3D(){
	
		obj = NULL;
	};
	Point3D(Shape * geometry,Vec vec):obj(geometry){
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	};

	~Point3D(){
		//delete obj;
	}
};



class Ray { 
public:
	Vec o, d;
	INLINE Ray(){o=Vec();d=Vec();};
	INLINE Ray(const Vec &o, const Vec &d) : o(o), d(d) {
	} 
};



class Quat{
public:
	union{
		float c[4];
		struct{
			float x,y,z,w;
		};
	};
	float & operator[](int i){
		return c[i];
	};
	Quat(){
		c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 1;
	};
	Quat(float x, float y, float z, float w){
		c[0] = x; c[1] = y; c[2] = z; c[3] = w;
	};

static Quat SetFromAxis(float theta, Vec axis) {
		Quat ret;
		ret.w = (float)cos(theta / 2.0);
		float s = (float)sin(theta / 2.0);
		ret.x = axis.x * s;
		ret.y = axis.y * s;
		ret.z = axis.z * s;
		return ret;
};



//http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
//Heading = rotation about y axis
//Attitude = rotation about z axis
//Bank = rotation about x axis
		

 // Assuming the angles are in radians.
 //   double c1 = Math.cos(heading);
 //   double s1 = Math.sin(heading);
 //   double c2 = Math.cos(attitude);
 //   double s2 = Math.sin(attitude);
 //   double c3 = Math.cos(bank);
 //   double s3 = Math.sin(bank);
 //   w = Math.sqrt(1.0 + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3) / 2.0;
 //   double w4 = (4.0 * w);
 //   x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
 //   y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
 //   z = (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;
		
static Quat SetFromEuler(Vec rot) {
	Quat result;

	float c = M_PI / 180,
	x = rot.x * c,
	y = rot.y * c,
	z = rot.z * c,

	c1 = cos( y  ),
	s1 = sin( y  ),
	c2 = cos( z ),
	s2 = sin( z ),
	c3 = cos( x  ),
	s3 = sin( x  ),
	w = sqrt(1.0+c1*c2+c1*c3-s1*s2*s3+c2*c3)/2.0,
	w4 = 4.0*w;
	
	result.x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
	result.y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
	result.z =  (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;
	result.w = sqrt(1.0+c1*c2+c1*c3-s1*s2*s3+c2*c3)/2.0;
	return result;

};

static Quat Mul(Quat const &a, Quat const &b) {
			Quat ret;
			//w is a.w * b.w - a.xyz * b.xyz
			ret.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

			//xyz is a.w*b.xyz+b.w*a.xyz+cross_product(a.xyz,b.xyz)
			ret.x = a.y * b.z - b.y * a.z + a.w * b.x + b.w * a.x;
			ret.y = a.z * b.x - b.z * a.x + a.w * b.y + b.w * a.y;
			ret.z = a.x * b.y - b.x * a.y + a.w * b.z + b.w * a.z;
			return ret;
};

static Vec Rotate(Vec const &v, Quat const &q){
	Quat tmp;
	tmp.w=0;
	tmp.x = v.x;
	tmp.y = v.y;
	tmp.z = v.z;
	tmp = Mul(q,Mul(tmp,Conjugate(q)));
	return Vec(tmp.x,tmp.y,tmp.z);
}
static Quat Conjugate(Quat const &a){
	Quat ret;
	ret.x = -a.x; ret.y = -a.y; ret.z = -a.z;ret.w = a.w;
	return ret;
}
	//INLINE Vec operator*(Quat const &a, Quat const &b) {
	//		Quat ret;
	//		//w is a.w * b.w - a.xyz * b.xyz
	//		ret.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

	//		//xyz is a.w*b.xyz+b.w*a.xyz+cross_product(a.xyz,b.xyz)
	//		ret.x = a.y * b.z - b.y * a.z + a.w * b.x + b.w * a.x;
	//		ret.y = a.z * b.x - b.z * a.x + a.w * b.y + b.w * a.y;
	//		ret.z = a.x * b.y - b.x * a.y + a.w * b.z + b.w * a.z;
	//		return ret;
	//};
};

INLINE Quat Mul(Quat const &a, Quat const &b) {
			Quat ret;
			//w is a.w * b.w - a.xyz * b.xyz
			ret.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

			//xyz is a.w*b.xyz+b.w*a.xyz+cross_product(a.xyz,b.xyz)
			ret.x = a.y * b.z - b.y * a.z + a.w * b.x + b.w * a.x;
			ret.y = a.z * b.x - b.z * a.x + a.w * b.y + b.w * a.y;
			ret.z = a.x * b.y - b.x * a.y + a.w * b.z + b.w * a.z;
			return ret;
};
/*INLINE Mat4 Mul(const Mat4 &m1, const Mat4 &m2) {
        Mat4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.m[i][j] = m1.m[i][0] * m2.m[0][j] +
                            m1.m[i][1] * m2.m[1][j] +
                            m1.m[i][2] * m2.m[2][j] +
                            m1.m[i][3] * m2.m[3][j];
        return r;
};*/

// Mat4 Declarations Copy from Physical Based Rendering
// Some modifications have been applied
class Mat4 {
public:
	union{
		float m[4][4];
		float mm[16];
	};

    // Mat4 Public Methods
    Mat4() {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] =
             m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] =
             m[3][0] = m[3][1] = m[3][2] = 0.f;
    };
    Mat4(const float* c) {
		m[0][0] = c[0]; m[0][1] = c[1]; m[0][2] = c[2]; m[0][3] = c[3];
		m[1][0] = c[4];	m[1][1] = c[5]; m[1][2] = c[6]; m[1][3] = c[7];
		m[2][0] = c[8];	m[2][1] = c[9];	m[2][2] = c[10];m[2][3] = c[11];
		m[3][0] = c[12];m[3][1] = c[13];m[3][2] = c[14];m[3][3] = c[15];
	};

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
		Mat4 rotMat = Mat4(m.m[0]);
		result.o = Mul(m,r.o);
		rotMat.m[0][3] = 0; rotMat.m[1][3] = 0; rotMat.m[2][3] = 0;
		result.d = Mul(rotMat,r.d);

		return result;
	};
    friend Mat4 Inverse(const Mat4 &);
    
	
	Mat4 operator*(Mat4 const &a) const{
		Mat4 result = Mat4();
		for (unsigned int r = 0; r < 4; ++r) {
			for (unsigned int c = 0; c < 4; ++c) {
				result.m[r][c] = 0;
				for (unsigned int i = 0; i < 4; ++i) {
					// Is this from Matt Pharr? 
					// This matrix is transposed!
					// Took me 2 hours to find out!
					// Thx! Matt
					result.m[r][c] += m[r][i] * a.m[i][c] ;
				}
			}
		}
		return result;
	};

	Vec operator*(Vec const &v) const{
		Vec result;

		result.x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3];
		result.y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3];
		result.z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3];
		return result;
	};
};




class _MathHelper{
public:
	_MathHelper(){

	};
	~_MathHelper(){

	};

	float ToRadius(float degree){return degree*M_PI/180.0f;};

	Mat4 CreateTranslate(Vec translate){
		return Mat4(
			1,	0,	0,	translate.x,
			0,	1,	0,	translate.y,
			0,	0,	1,	translate.z,
			0,	0,	0,	1
		);
	};

	Mat4 CreateRotation(Quat const &a){
		float wx = a.w * a.x;
		float wy = a.w * a.y;
		float wz = a.w * a.z;

		float xx = a.x * a.x;
		float xy = a.x * a.y;
		float xz = a.x * a.z;

		float yy = a.y * a.y;
		float yz = a.y * a.z;

		float zz = a.z * a.z;

		float res[16] = {
			1 - 2*yy - 2*zz,	2 * xy + 2 * wz,	2 * xz - 2 * wy,	0,
			2 * xy - 2 * wz,	1 - 2*xx - 2*zz,	2 * yz + 2 * wx,	0,
			2 * xz + 2 * wy,	2 * yz - 2 * wx,	1 - 2*xx - 2*yy,	0,
			0,					0,					0,					1
		};

		return Mat4(res);

	};

	Mat4 CreateRotation(Vec const &v){
		Mat4 ret;

		float t = M_PI/180,
		p = t*v.x,
		h = t*v.y,
		b = t*v.z;

	/*	Rx(P)=	| 1      0       0 |
				| 0  cos P  -sin P |
				| 0  sin P   cos P |

		Ry(H)=	|  cos H  0  sin H |
				|      0  1      0 |
				| -sin H  0  cos H |

		Rz(B)=	| cos B  -sin B  0 |
				| sin B   cos B  0 |
				|     0       0  1 |*/


		Mat4 mx = Mat4(
						1,			0,			0,			0,
						0,			cos(p),		-sin(p),	0,	
						0,			sin(p),		cos(p),		0,
						0,			0,			0,			1
					);

		Mat4 my = Mat4(
						cos(h),		0,			sin(h),		0,
						0,			1,			0,			0,
						-sin(h),	0,			cos(h),		0,
						0,			0,			0,			1
					);
		Mat4 mz = Mat4(
						cos(b),		-sin(b),	0,			0,
						sin(b),		cos(b),		0,			0,
						0,			0,			1,			0,
						0,			0,			0,			1
					);

	    ret = mz*my*mx;
		return ret;
	};

	Mat4 CreateLookAt(Vec eyePos,Vec target, Vec up){
		//Mat4 result;
		Vec x,y,z;

		if(eyePos == target) return Mat4();

		//Vec t = target - eyePos;

		z = (target-eyePos)*-1.0f;
		z.norm();
		x = Cross(up,z);
		y = Cross(z ,x);

		Mat4 result = Mat4(
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
