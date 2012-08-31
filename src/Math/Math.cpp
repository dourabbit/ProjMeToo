#include <Math/Math.hpp>


//const Vec Zero(0, 0, 0);
//const Vec XAxis(1, 0, 0);
//const Vec YAxis(0, 1, 0);
//const Vec ZAxis(0, 0, 1);


//Mat4::Mat4(float t00, float t01, float t02, float t03,
//                     float t10, float t11, float t12, float t13,
//                     float t20, float t21, float t22, float t23,
//                     float t30, float t31, float t32, float t33) {
//    m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
//    m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
//    m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
//    m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
//};



//_MathHelper::_MathHelper(){};
//_MathHelper::~_MathHelper(){};
//Mat4 _MathHelper::CreateLookAt(Vec eyePos,Vec target, Vec up){
//	//Mat4 result;
//	Vec x,y,z;
//
//	if(eyePos == target) return Mat4();
//
//	z = (-1.0f*(target-eyePos)).norm();
//	x = Cross(up,z);
//	y = Cross(z ,x);
//
//	Mat4 result = Mat4::Mat4(
//		x.x,	x.y,	x.z, -(x.x * eyePos.x + x.y * eyePos.y + x.z * eyePos.z),
//		y.z,	y.y,	y.z, -(y.x * eyePos.x + y.y * eyePos.y + y.z * eyePos.z),
//		z.x,	z.y,	z.z, -(z.x * eyePos.x + z.y * eyePos.y + z.z * eyePos.z),
//		0,		0,		0,	 1
//		);
//	return result;
//}
//
//Mat4 Inverse(const Mat4 &m) {
//    float minv[4][4];
//    memcpy(minv, m.m, 4*4*sizeof(float));
//	float
//        b00 = minv[0][0] * minv[1][1] - minv[0][1] * minv[1][0],
//        b01 = minv[0][0] * minv[1][2] - minv[0][2] * minv[1][0],
//        b02 = minv[0][0] * minv[1][3] - minv[0][3] * minv[1][0],
//        b03 = minv[0][1] * minv[1][2] - minv[0][2] * minv[1][1],
//        b04 = minv[0][1] * minv[1][3] - minv[0][3] * minv[1][1],
//        b05 = minv[0][2] * minv[1][3] - minv[0][3] * minv[1][2],
//        b06 = minv[2][0] * minv[3][1] - minv[2][1] * minv[3][0],
//        b07 = minv[2][0] * minv[3][2] - minv[2][2] * minv[3][0],
//        b08 = minv[2][0] * minv[3][3] - minv[2][3] * minv[3][0],
//        b09 = minv[2][1] * minv[3][2] - minv[2][2] * minv[3][1],
//        b10 = minv[2][1] * minv[3][3] - minv[2][3] * minv[3][1],
//        b11 = minv[2][2] * minv[3][3] - minv[2][3] * minv[3][2],
//
//        d = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06),
//        invDet;
//
//        // Calculate the determinant
//        if (!d) { return Mat4(); }
//        invDet = 1 / d;
//		Mat4 result = Mat4(
//		(minv[1][1]  * b11 - minv[1][2] * b10 + minv[1][3] * b09) * invDet,
//		(-minv[0][1] * b11 + minv[0][2] * b10 - minv[0][3] * b09) * invDet,
//		(minv[3][1]  * b05 - minv[3][2] * b04 + minv[3][3] * b03) * invDet,
//		(-minv[2][1] * b05 + minv[2][2] * b04 - minv[2][3] * b03) * invDet,
//		(-minv[1][0] * b11 + minv[1][2] * b08 - minv[1][3] * b07) * invDet,
//		(minv[0][0]  * b11 - minv[0][2] * b08 + minv[0][3] * b07) * invDet,
//		(-minv[3][0] * b05 + minv[3][2] * b02 - minv[3][3] * b01) * invDet,
//		(minv[2][0]  * b05 - minv[2][2] * b02 + minv[2][3] * b01) * invDet,
//		(minv[1][0]  * b10 - minv[1][1] * b08 + minv[1][3] * b06) * invDet,
//		(-minv[0][0] * b10 + minv[0][1] * b08 - minv[0][3] * b06) * invDet,
//		(minv[3][0]  * b04 - minv[3][1] * b02 + minv[3][3] * b00) * invDet,
//		(-minv[2][0] * b04 + minv[2][1] * b02 - minv[2][3] * b00) * invDet,
//		(-minv[1][0] * b09 + minv[1][1] * b07 - minv[1][2] * b06) * invDet,
//		(minv[0][0]  * b09 - minv[0][1] * b07 + minv[0][2] * b06) * invDet,
//		(-minv[3][0] * b03 + minv[3][1] * b01 - minv[3][2] * b00) * invDet,
//		(minv[2][0]  * b03 - minv[2][1] * b01 + minv[2][2] * b00) * invDet);
//
//    return result;
//
//
//}