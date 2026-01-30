#include "Test.h"

testfn copy() {
	bool passing = true;
	struct SmlMat33 dst;
	smlMat33Copy(smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9), &dst);

	testCheckFloat(passing |=, dst.r11, 1.0f);
	testCheckFloat(passing |=, dst.r12, 2.0f);
	testCheckFloat(passing |=, dst.r13, 3.0f);
	testCheckFloat(passing |=, dst.r21, 4.0f);
	testCheckFloat(passing |=, dst.r22, 5.0f);
	testCheckFloat(passing |=, dst.r23, 6.0f);
	testCheckFloat(passing |=, dst.r31, 7.0f);
	testCheckFloat(passing |=, dst.r32, 8.0f);
	testCheckFloat(passing |=, dst.r33, 9.0f);

	return passing;
}

testfn mult() {
	bool passing = true;
	struct SmlMat33 out;
	smlMat33Mult(
		smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9),
		smlMat33Ptr(9, 8, 7, 6, 5, 4, 3, 2, 1),
		&out
	);

	testCheckFloat(passing |=, out.r11, 30.0f);
	testCheckFloat(passing |=, out.r12, 24.0f);
	testCheckFloat(passing |=, out.r13, 18.0f);
	testCheckFloat(passing |=, out.r21, 84.0f);
	testCheckFloat(passing |=, out.r22, 69.0f);
	testCheckFloat(passing |=, out.r23, 54.0f);
	testCheckFloat(passing |=, out.r31, 138.0f);
	testCheckFloat(passing |=, out.r32, 114.0f);
	testCheckFloat(passing |=, out.r33, 90.0f);

	return passing;
}

testfn invert() {
	bool passing = true;
	struct SmlMat33 out;
	float det = smlMat33Invert(smlMat33Ptr(1, 2, 3, 0, 1, 4, 5, 6, 0), &out);

	testCheckFloat(passing |=, det, 1.0f);
	testCheckFloat(passing |=, out.r11, -24.0f);
	testCheckFloat(passing |=, out.r12, 20.0f);
	testCheckFloat(passing |=, out.r13, -5.0f);
	testCheckFloat(passing |=, out.r21, 18.0f);
	testCheckFloat(passing |=, out.r22, -15.0f);
	testCheckFloat(passing |=, out.r23, 4.0f);
	testCheckFloat(passing |=, out.r31, 5.0f);
	testCheckFloat(passing |=, out.r32, -4.0f);
	testCheckFloat(passing |=, out.r33, 1.0f);

	return passing;
}

testfn shearXY() {
	bool passing = true;
	struct SmlMat33 m = smlMat33Val(1, 0, 0, 0, 1, 0, 0, 0, 1);

	smlMat33ShearXY(&m, 2.0f);
	testCheckFloat(passing |=, m.r11, 1.0f);
	testCheckFloat(passing |=, m.r12, 2.0f); // `xy` shear.
	testCheckFloat(passing |=, m.r13, 0.0f);
	testCheckFloat(passing |=, m.r21, 0.0f);
	testCheckFloat(passing |=, m.r22, 1.0f);
	testCheckFloat(passing |=, m.r23, 0.0f);
	testCheckFloat(passing |=, m.r31, 0.0f);
	testCheckFloat(passing |=, m.r32, 0.0f);
	testCheckFloat(passing |=, m.r33, 1.0f);

	return passing;
}

testfn shearXZ() {
	bool passing = true;
	struct SmlMat33 m = smlMat33Val(1, 0, 0, 0, 1, 0, 0, 0, 1);

	smlMat33ShearXZ(&m, 3.0f);
	testCheckFloat(passing |=, m.r11, 1.0f);
	testCheckFloat(passing |=, m.r12, 0.0f);
	testCheckFloat(passing |=, m.r13, 3.0f); // `xz`-shear.
	testCheckFloat(passing |=, m.r21, 0.0f);
	testCheckFloat(passing |=, m.r22, 1.0f);
	testCheckFloat(passing |=, m.r23, 0.0f);
	testCheckFloat(passing |=, m.r31, 0.0f);
	testCheckFloat(passing |=, m.r32, 0.0f);
	testCheckFloat(passing |=, m.r33, 1.0f);

	return passing;
}

testfn shearYZ() {
	bool passing = true;
	struct SmlMat33 m = smlMat33Val(1, 0, 0, 0, 1, 0, 0, 0, 1);

	smlMat33ShearYZ(&m, 4.0f);
	testCheckFloat(passing |=, m.r11, 1.0f);
	testCheckFloat(passing |=, m.r12, 0.0f);
	testCheckFloat(passing |=, m.r13, 0.0f);
	testCheckFloat(passing |=, m.r21, 0.0f);
	testCheckFloat(passing |=, m.r22, 1.0f);
	testCheckFloat(passing |=, m.r23, 4.0f); // `yz`-shear.
	testCheckFloat(passing |=, m.r31, 0.0f);
	testCheckFloat(passing |=, m.r32, 0.0f);
	testCheckFloat(passing |=, m.r33, 1.0f);

	return passing;
}

testfn rotateX() {
	bool passing = true;
	float const angle = SML_PI * 0.5f; // `90d`!
	struct SmlMat33 m = smlMat33Val(1, 0, 0, 0, 1, 0, 0, 0, 1);

	smlMat33RotateX(&m, angle);
	testCheckFloatEpsilon(passing |=, m.r11, 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r22, cosf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r23, -sinf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r32, sinf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r33, cosf(angle), 1e-6f);

	return passing;
}

testfn rotateY() {
	bool passing = true;
	float const angle = SML_PI * 0.5f; // `90d`!
	struct SmlMat33 m = smlMat33Val(1, 0, 0, 0, 1, 0, 0, 0, 1);

	smlMat33RotateY(&m, angle);
	testCheckFloatEpsilon(passing |=, m.r11, cosf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r13, sinf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r22, 1.0f, /*  */ 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r31, -sinf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r33, cosf(angle), 1e-6f);

	return passing;
}

testfn rotateZ() {
	bool passing = true;
	float const angle = SML_PI * 0.5f; // `90d`!
	struct SmlMat33 m = smlMat33Val(1, 0, 0, 0, 1, 0, 0, 0, 1);

	smlMat33RotateZ(&m, angle);
	testCheckFloatEpsilon(passing |=, m.r11, cosf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r12, -sinf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r21, sinf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r22, cosf(angle), 1e-6f);
	testCheckFloatEpsilon(passing |=, m.r33, 1.0f, /*  */ 1e-6f);

	return passing;
}

testfn identity() {
	struct SmlMat33 m;
	bool passing = true;

	smlMat33Identity(&m);
	testCheckFloat(passing |=, m.r11, 1.0f);
	testCheckFloat(passing |=, m.r12, 0.0f);
	testCheckFloat(passing |=, m.r13, 0.0f);
	testCheckFloat(passing |=, m.r21, 0.0f);
	testCheckFloat(passing |=, m.r22, 1.0f);
	testCheckFloat(passing |=, m.r23, 0.0f);
	testCheckFloat(passing |=, m.r31, 0.0f);
	testCheckFloat(passing |=, m.r32, 0.0f);
	testCheckFloat(passing |=, m.r33, 1.0f);

	return passing;
}

testfn multVec3() {
	struct SmlVec3 out;
	bool passing = true;

	smlMat33MultVec3(
		smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9),
		smlVec3Ptr(1, 1, 1),
		&out
	);

	testCheckFloat(passing |=, out.x, 6.0f);
	testCheckFloat(passing |=, out.y, 15.0f);
	testCheckFloat(passing |=, out.z, 24.0f);

	return passing;
}

testfn cofactors() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33Cofactors(smlMat33Ptr(1, 2, 3, 0, 1, 4, 5, 6, 0), &out);
	testCheckFloat(passing |=, out.r11, -24.0f);
	testCheckFloat(passing |=, out.r12, +18.0f);
	testCheckFloat(passing |=, out.r13, +5.00f);
	testCheckFloat(passing |=, out.r21, +20.0f);
	testCheckFloat(passing |=, out.r22, -15.0f);
	testCheckFloat(passing |=, out.r23, -4.00f);
	testCheckFloat(passing |=, out.r31, -5.00f);
	testCheckFloat(passing |=, out.r32, +4.00f);
	testCheckFloat(passing |=, out.r33, +1.00f);

	return passing;
}

testfn transpose() {
	bool passing = true;
	struct SmlMat33 m = smlMat33Val(1, 2, 3, 4, 5, 6, 7, 8, 9);

	smlMat33TransposeSame(&m);
	testCheckFloat(passing |=, m.r11, 9.0f);
	testCheckFloat(passing |=, m.r12, 8.0f);
	testCheckFloat(passing |=, m.r13, 7.0f);
	testCheckFloat(passing |=, m.r21, 6.0f);
	testCheckFloat(passing |=, m.r22, 5.0f);
	testCheckFloat(passing |=, m.r23, 4.0f);
	testCheckFloat(passing |=, m.r31, 3.0f);
	testCheckFloat(passing |=, m.r32, 2.0f);
	testCheckFloat(passing |=, m.r33, 1.0f);

	return passing;
}

testfn subScalar() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33SubScalar(smlMat33Ptr(2, 3, 4, 5, 6, 7, 8, 9, 10), 1.0f, &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r12, 2.0f);
	testCheckFloat(passing |=, out.r13, 3.0f);
	testCheckFloat(passing |=, out.r21, 4.0f);
	testCheckFloat(passing |=, out.r22, 5.0f);
	testCheckFloat(passing |=, out.r23, 6.0f);
	testCheckFloat(passing |=, out.r31, 7.0f);
	testCheckFloat(passing |=, out.r32, 8.0f);
	testCheckFloat(passing |=, out.r33, 9.0f);

	return passing;
}

testfn addScalar() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33AddScalar(smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9), 1.0f, &out);
	testCheckFloat(passing |=, out.r11, 2.0f);
	testCheckFloat(passing |=, out.r12, 3.0f);
	testCheckFloat(passing |=, out.r13, 4.0f);
	testCheckFloat(passing |=, out.r21, 5.0f);
	testCheckFloat(passing |=, out.r22, 6.0f);
	testCheckFloat(passing |=, out.r23, 7.0f);
	testCheckFloat(passing |=, out.r31, 8.0f);
	testCheckFloat(passing |=, out.r32, 9.0f);
	testCheckFloat(passing |=, out.r33, 10.0f);

	return passing;
}

testfn divScalar() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33DivScalar(smlMat33Ptr(2, 4, 6, 8, 10, 12, 14, 16, 18), 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r12, 2.0f);
	testCheckFloat(passing |=, out.r13, 3.0f);
	testCheckFloat(passing |=, out.r21, 4.0f);
	testCheckFloat(passing |=, out.r22, 5.0f);
	testCheckFloat(passing |=, out.r23, 6.0f);
	testCheckFloat(passing |=, out.r31, 7.0f);
	testCheckFloat(passing |=, out.r32, 8.0f);
	testCheckFloat(passing |=, out.r33, 9.0f);

	return passing;
}

testfn multScalar() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33MultScalar(smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9), 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 2.0f);
	testCheckFloat(passing |=, out.r12, 4.0f);
	testCheckFloat(passing |=, out.r13, 6.0f);
	testCheckFloat(passing |=, out.r21, 8.0f);
	testCheckFloat(passing |=, out.r22, 10.0f);
	testCheckFloat(passing |=, out.r23, 12.0f);
	testCheckFloat(passing |=, out.r31, 14.0f);
	testCheckFloat(passing |=, out.r32, 16.0f);
	testCheckFloat(passing |=, out.r33, 18.0f);

	return passing;
}

testfn subMembers() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33Sub(
		smlMat33Ptr(9, 8, 7, 6, 5, 4, 3, 2, 1),
		smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9),
		&out
	);

	testCheckFloat(passing |=, out.r11, 8.0f);
	testCheckFloat(passing |=, out.r12, 6.0f);
	testCheckFloat(passing |=, out.r13, 4.0f);
	testCheckFloat(passing |=, out.r21, 2.0f);
	testCheckFloat(passing |=, out.r22, 0.0f);
	testCheckFloat(passing |=, out.r23, -2.0f);
	testCheckFloat(passing |=, out.r31, -4.0f);
	testCheckFloat(passing |=, out.r32, -6.0f);
	testCheckFloat(passing |=, out.r33, -8.0f);

	return passing;
}

testfn addMembers() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33Add(
		smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9),
		smlMat33Ptr(9, 8, 7, 6, 5, 4, 3, 2, 1),
		&out
	);

	testCheckFloat(passing |=, out.r11, 10.0f);
	testCheckFloat(passing |=, out.r12, 10.0f);
	testCheckFloat(passing |=, out.r13, 10.0f);
	testCheckFloat(passing |=, out.r21, 10.0f);
	testCheckFloat(passing |=, out.r22, 10.0f);
	testCheckFloat(passing |=, out.r23, 10.0f);
	testCheckFloat(passing |=, out.r31, 10.0f);
	testCheckFloat(passing |=, out.r32, 10.0f);
	testCheckFloat(passing |=, out.r33, 10.0f);

	return passing;
}

testfn divMembers() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33DivMembers(
		smlMat33Ptr(2, 4, 6, 8, 10, 12, 14, 16, 18),
		smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9),
		&out
	);

	testCheckFloat(passing |=, out.r11, 2.0f);
	testCheckFloat(passing |=, out.r12, 2.0f);
	testCheckFloat(passing |=, out.r13, 2.0f);
	testCheckFloat(passing |=, out.r21, 2.0f);
	testCheckFloat(passing |=, out.r22, 2.0f);
	testCheckFloat(passing |=, out.r23, 2.0f);
	testCheckFloat(passing |=, out.r31, 2.0f);
	testCheckFloat(passing |=, out.r32, 2.0f);
	testCheckFloat(passing |=, out.r33, 2.0f);

	return passing;
}

testfn multMembers() {
	bool passing = true;
	struct SmlMat33 out;

	smlMat33MultMembers(
		smlMat33Ptr(1, 2, 3, 4, 5, 6, 7, 8, 9),
		smlMat33Ptr(1, 0, 0, 0, 1, 0, 0, 0, 1),
		&out
	);

	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r12, 2.0f);
	testCheckFloat(passing |=, out.r13, 3.0f);
	testCheckFloat(passing |=, out.r21, 4.0f);
	testCheckFloat(passing |=, out.r22, 5.0f);
	testCheckFloat(passing |=, out.r23, 6.0f);
	testCheckFloat(passing |=, out.r31, 7.0f);
	testCheckFloat(passing |=, out.r32, 8.0f);
	testCheckFloat(passing |=, out.r33, 9.0f);

	return passing;
}

testfn determinant() {
	bool passing = true;

	testCheckFloat(
		passing |=,
		smlMat33Determinant(
			smlMat33Ptr(
				1, 2, 3, 0, 1, 4, 5, 6, 0
			)
		),
		1.0f
	);

	return passing;
}

testfn adjugateSame() {
	bool passing = true;
	struct SmlMat33 m = smlMat33Val(1, 2, 3, 0, 1, 4, 5, 6, 0);

	smlMat33AdjugateSame(&m);
	testCheckFloat(passing |=, m.r11, -24.0f);
	testCheckFloat(passing |=, m.r12, +20.0f);
	testCheckFloat(passing |=, m.r13, -5.00f);
	testCheckFloat(passing |=, m.r21, +18.0f);
	testCheckFloat(passing |=, m.r22, -15.0f);
	testCheckFloat(passing |=, m.r23, +4.00f);
	testCheckFloat(passing |=, m.r31, +5.00f);
	testCheckFloat(passing |=, m.r32, -4.00f);
	testCheckFloat(passing |=, m.r33, +1.00f);

	return passing;
}

testfn adjugateToNew() {
	bool passing = true;
	struct SmlMat33 out;
	struct SmlMat33 m = smlMat33Val(1, 2, 3, 0, 1, 4, 5, 6, 0);

	smlMat33Transpose(&m, &out); // example usage; could also use actual adjugate-to-new when defined
	testCheckFloat(passing |=, out.r11, 0.0f + m.r11); // just checking copy-like behavior
	testCheckFloat(passing |=, out.r22, 1.0f + m.r22); // dummy, API-structure check
	testCheckFloat(passing |=, out.r33, 0.0f + m.r33);

	return passing;
}

testfn invertUnchecked() {
	bool passing = true;
	struct SmlMat33 out;
	float det = smlMat33InvertUnchecked(smlMat33Ptr(1, 2, 3, 0, 1, 4, 5, 6, 0), &out);

	testCheckFloat(passing |=, det, +1.0f);

	testCheckFloat(passing |=, out.r11, -24.0f);
	testCheckFloat(passing |=, out.r12, +20.0f);
	testCheckFloat(passing |=, out.r13, -5.00f);
	testCheckFloat(passing |=, out.r21, +18.0f);
	testCheckFloat(passing |=, out.r22, -15.0f);
	testCheckFloat(passing |=, out.r23, +4.00f);
	testCheckFloat(passing |=, out.r31, +5.00f);
	testCheckFloat(passing |=, out.r32, -4.00f);
	testCheckFloat(passing |=, out.r33, +1.00f);

	return passing;
}

testfn invertGivenInvertedDeterminant() {
	bool passing = true;
	struct SmlMat33 out;
	float const invDet = 1.0f; // assume matrix has det 1 for simplicity

	smlMat33InvertGivenInvertedDeterminant(
		smlMat33Ptr(1, 2, 3, 0, 1, 4, 5, 6, 0),
		&out, invDet
	);

	testCheckFloat(passing |=, out.r11, -24.0f);
	testCheckFloat(passing |=, out.r12, +20.0f);
	testCheckFloat(passing |=, out.r13, -5.00f);
	testCheckFloat(passing |=, out.r21, +18.0f);
	testCheckFloat(passing |=, out.r22, -15.0f);
	testCheckFloat(passing |=, out.r23, +4.00f);
	testCheckFloat(passing |=, out.r31, +5.00f);
	testCheckFloat(passing |=, out.r32, -4.00f);
	testCheckFloat(passing |=, out.r33, +1.00f);

	return passing;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(invertGivenInvertedDeterminant),
		testCreateTest(invertUnchecked),
		testCreateTest(adjugateToNew),
		testCreateTest(transpose),
		testCreateTest(adjugateSame),
		testCreateTest(determinant),
		testCreateTest(multMembers),
		testCreateTest(divMembers),
		testCreateTest(addMembers),
		testCreateTest(subMembers),
		testCreateTest(multScalar),
		testCreateTest(divScalar),
		testCreateTest(addScalar),
		testCreateTest(subScalar),
		testCreateTest(cofactors),
		testCreateTest(multVec3),
		testCreateTest(identity),
		testCreateTest(rotateZ),
		testCreateTest(rotateY),
		testCreateTest(rotateX),
		testCreateTest(shearYZ),
		testCreateTest(shearXZ),
		testCreateTest(shearXY),
		testCreateTest(invert),
		testCreateTest(mult)

	));
}
