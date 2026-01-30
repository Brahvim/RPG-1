#include "Test.h"

testfn dot() {
	bool passing = true;
	struct SmlQuat q1, q2;

	smlQuatFromAxisAngle(smlVec3Ptr(1, 0, 0), SML_PI * 0.5f, &q1);
	smlQuatFromAxisAngle(smlVec3Ptr(0, 1, 0), SML_PI * 0.5f, &q2);

	smlQuatNormalize(&q1, &q1);
	smlQuatNormalize(&q2, &q2);

	testCheckFloatEpsilon(passing |=,
		smlQuatMagnitudeSquared(&q1),
		smlQuatDot(&q1, &q1),
		1e-6f
	);

	return passing;
}

testfn invRot() {
	bool passing = true;
	struct SmlQuat q, inv;
	struct SmlVec3 tmp, out;
	struct SmlVec3 v = smlVec3Val(0, 0, 1);

	smlQuatFromAxisAngle(smlVec3Ptr(0, 1, 0), SML_PI * 0.75f, &q);
	smlQuatNormalize(&q, &q);
	smlQuatInvert(&q, &inv);

	smlQuatRotateVector3d(&q, &v, &tmp);
	smlQuatRotateVector3d(&inv, &tmp, &out);

	testCheckFloatEpsilon(passing |=, out.x, v.x, 1e-5f);
	testCheckFloatEpsilon(passing |=, out.y, v.y, 1e-5f);
	testCheckFloatEpsilon(passing |=, out.z, v.z, 1e-5f);

	return passing;
}

testfn toEuler() {
	bool passing = true;
	struct SmlVec3 euler;
	struct SmlQuat q, q2;

	smlQuatFromAxisAngle(smlVec3Ptr(0, 0, 1), SML_PI * 0.25f, &q);
	smlQuatNormalize(&q, &q);

	smlQuatToEuler(&q, &euler);
	smlQuatFromAngle3d(euler.x, euler.y, euler.z, &q2);
	smlQuatNormalize(&q2, &q2);

	testCheckFloatEpsilon(passing |=, fabsf(smlQuatDot(&q, &q2)), 1.0f, 1e-4f);

	return passing;
}

testfn toMat33() {
	bool passing = true;
	struct SmlQuat q;
	struct SmlMat33 m33;
	struct SmlVec3 qOut, mOut;
	struct SmlVec3 v = smlVec3Val(0, 0, 1);

	smlQuatFromAxisAngle(smlVec3Ptr(1, 0, 0), SML_PI * 0.5f, &q);
	smlQuatNormalize(&q, &q);

	smlQuatRotateVector3d(&q, &v, &qOut);
	smlQuatToMatrix33(&q, &m33);
	smlMat33MultVec3(&m33, &v, &mOut);

	testCheckFloatEpsilon(passing |=, qOut.x, mOut.x, 1e-5f);
	testCheckFloatEpsilon(passing |=, qOut.y, mOut.y, 1e-5f);
	testCheckFloatEpsilon(passing |=, qOut.z, mOut.z, 1e-5f);

	return passing;
}

testfn toMat44() {
	struct SmlQuat out;
	bool passing = true;
	struct SmlMat44 m = {

		.r11 = 1, .r12 = 2, .r13 = 3, .r14 = 4,
		.r21 = 5, .r22 = 6, .r23 = 7, .r24 = 8,
		.r31 = 9, .r32 = 10, .r33 = 11, .r34 = 12,
		.r41 = 13, .r42 = 14, .r43 = 15, .r44 = 16,

	};

	smlMat44MultQuat(&m, smlQuatPtr(1, 2, 3, 4), &out);

	testCheckFloat(passing |=, out.x, 1 * 1 + 2 * 2 + 3 * 3 + 4 * 4);   	//  1 +  4 +  9 + 16	= 30
	testCheckFloat(passing |=, out.y, 5 * 1 + 6 * 2 + 7 * 3 + 8 * 4);   	//  5 + 12 + 21 + 32	= 70
	testCheckFloat(passing |=, out.z, 9 * 1 + 10 * 2 + 11 * 3 + 12 * 4); 	//  9 + 20 + 33 + 48	= 110
	testCheckFloat(passing |=, out.w, 13 * 1 + 14 * 2 + 15 * 3 + 16 * 4);	// 13 + 28 + 45 + 64	= 150

	return passing;
}

testfn multiply() {
	bool passing = true;
	struct SmlQuat qx, qy, q;
	struct SmlVec3 out1, out2;
	struct SmlVec3 v = smlVec3Val(1, 0, 0);

	smlQuatFromAxisAngle(smlVec3Ptr(0, 1, 0), SML_PI * 0.5f, &qy);
	smlQuatFromAxisAngle(smlVec3Ptr(0, 0, 1), SML_PI * 0.5f, &qx);

	smlQuatNormalize(&qx, &qx);
	smlQuatNormalize(&qy, &qy);

	// Sequential multiplication:
	smlQuatRotateVector3d(&qy, &v, &out1);
	smlQuatRotateVector3d(&qx, &out1, &out1);

	// Composed multiplication: 
	smlQuatMult(&qx, &qy, &q);
	smlQuatRotateVector3d(&q, &v, &out2);

	testCheckFloatEpsilon(passing |=, out1.x, out2.x, 1e-5f);
	testCheckFloatEpsilon(passing |=, out1.y, out2.y, 1e-5f);
	testCheckFloatEpsilon(passing |=, out1.z, out2.z, 1e-5f);

	return passing;
}

testfn identity() {
	struct SmlQuat q;
	bool passing = true;

	smlQuatIdentity(&q);
	testCheckFloat(passing |=, q.x, 0.0f);
	testCheckFloat(passing |=, q.y, 0.0f);
	testCheckFloat(passing |=, q.z, 0.0f);
	testCheckFloat(passing |=, q.w, 1.0f);

	testCheckFloatEpsilon(passing |=, smlQuatDot(&q, &q), 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlQuatMagnitude(&q), 1.0f, 1e-6f);

	return passing;
}

testfn normalize() {
	struct SmlQuat out;
	bool passing = true;
	struct SmlQuat q = smlQuatVal(1, 2, 3, 4);

	smlQuatNormalize(&q, &out);
	testCheckFloatEpsilon(passing |=, smlQuatMagnitude(&out), 1.0f, 1e-6f);

	smlQuatNormalizeUnchecked(&q, &out);
	testCheckFloatEpsilon(passing |=, smlQuatMagnitude(&out), 1.0f, 1e-6f);

	return passing;
}

testfn rotateVec3() {
	struct SmlQuat q;
	struct SmlVec3 out;
	bool passing = true;
	struct SmlVec3 v = smlVec3Val(1, 0, 0);

	smlQuatFromAxisAngle(smlVec3Ptr(0, 1, 0), SML_PI * 0.5f, &q);

	smlQuatNormalize(&q, &q);
	smlQuatRotateVector3d(&q, &v, &out);

	testCheckFloatEpsilon(passing |=, out.x, 0.0f, 1e-5f);
	testCheckFloatEpsilon(passing |=, out.z, -1.0f, 1e-5f);
	testCheckFloatEpsilon(passing |=, smlVec3Magnitude(&out), 1.0f, 1e-6f);

	return passing;
}

testfn fromAngle3d() {
	struct SmlQuat q;
	bool passing = true;

	// A few simple Euler rotations (`x`-`y`-`z` order!):
	float const angles[][3] = {

		{ 0.0f,			 0.0f,			0.0f },
		{ SML_PI * 0.5f, 0.0f,			0.0f },
		{ 0.0f,			 SML_PI * 0.5f, 0.0f },
		{ 0.0f,			 0.0f,			SML_PI * 0.5f },
		{ SML_PI * 0.5f, SML_PI * 0.5f, SML_PI * 0.5f },

	};

#define V	0.70710678f
	struct SmlQuat expected[] = {
		{ 0,	0,	  0,	1 },	// No rotation!
		{ V,	0,	  0,	V },	// `90d` on `x`,
		{ 0,	V,	  0,	V },	// `90d` on `y`,
		{ 0,	0,	  V,	V },	// `90d` on `z`,
		{ 0.5f, 0.5f, 0.5f, 0.5f }	// `90d`, `x`-`y`-`z`...!
	};
#undef V

	for (size_t i = 0; i < sizearr(angles); ++i) {

		smlQuatFromAngle3d(angles[i][0], angles[i][1], angles[i][2], &q);
		testCheckFloatEpsilon(passing |=, q.x, expected[i].x, 1e-5f);
		testCheckFloatEpsilon(passing |=, q.y, expected[i].y, 1e-5f);
		testCheckFloatEpsilon(passing |=, q.z, expected[i].z, 1e-5f);
		testCheckFloatEpsilon(passing |=, q.w, expected[i].w, 1e-5f);

	}

	return passing;
}

testfn scalarStuff() {
	bool passing = true;
	struct SmlQuat a, b;
	struct SmlQuat q = smlQuatVal(1, 2, 3, 4);

	smlQuatScale(&q, 2.0f, &a);
	smlQuatMultScalar(&q, 2.0f, &b);

	testCheckFloat(passing |=, a.x, b.x);
	testCheckFloat(passing |=, a.y, b.y);
	testCheckFloat(passing |=, a.z, b.z);
	testCheckFloat(passing |=, a.w, b.w);

	return passing;
}

testfn interpolation() {
	bool passing = true;
	struct SmlQuat a, b, out;

	smlQuatIdentity(&a);
	smlQuatFromAxisAngle(smlVec3Ptr(0, 0, 1), SML_PI, &b);

	smlQuatLerp(&a, &b, 0.0f, &out);
	testCheckFloatEpsilon(passing |=, out.w, a.w, 1e-6f);

	smlQuatLerp(&a, &b, 1.0f, &out);
	testCheckFloatEpsilon(passing |=, out.w, b.w, 1e-6f);

	smlQuatSlerp(&a, &b, 0.5f, &out);
	testCheckFloatEpsilon(passing |=, smlQuatMagnitude(&out), 1.0f, 1e-6f);

	smlQuatNlerp(&a, &b, 0.5f, &out);
	testCheckFloatEpsilon(passing |=, smlQuatMagnitude(&out), 1.0f, 1e-6f);

	return passing;
}

testfn fromAxisAngle() {
	struct SmlQuat q;
	bool passing = true;
	struct SmlVec3 axis = smlVec3Val(0, 1, 0);

	smlQuatFromAxisAngle(&axis, 0.0f, &q);
	testCheckFloatEpsilon(passing |=, q.x, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, q.y, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, q.z, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, q.w, 1.0f, 1e-6f);

	smlQuatFromAxisAngle(&axis, SML_PI, &q);
	testCheckFloatEpsilon(passing |=, smlQuatMagnitude(&q), 1.0f, 1e-6f);

	return passing;
}

testfn conjugateInvert() {
	bool passing = true;
	struct SmlQuat q, conj, inv, id;

	smlQuatFromAxisAngle(smlVec3Ptr(0, 1, 0), SML_PI * 0.5f, &q);
	smlQuatNormalize(&q, &q);

	smlQuatConjugate(&q, &conj);
	smlQuatInvert(&q, &inv);

	testCheckFloatEpsilon(passing |=, conj.x, inv.x, 1e-6f);
	testCheckFloatEpsilon(passing |=, conj.y, inv.y, 1e-6f);
	testCheckFloatEpsilon(passing |=, conj.z, inv.z, 1e-6f);
	testCheckFloatEpsilon(passing |=, conj.w, inv.w, 1e-6f);

	smlQuatMult(&q, &inv, &id);
	testCheckFloatEpsilon(passing |=, id.w, 1.0f, 1e-6f);

	return passing;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(conjugateInvert),
		testCreateTest(fromAxisAngle),
		testCreateTest(interpolation),
		testCreateTest(scalarStuff),
		testCreateTest(fromAngle3d),
		testCreateTest(rotateVec3),
		testCreateTest(normalize),
		testCreateTest(identity),
		testCreateTest(multiply),
		testCreateTest(toMat44),
		testCreateTest(toMat33),
		testCreateTest(toEuler),
		testCreateTest(invRot),
		testCreateTest(dot)

	));
}
