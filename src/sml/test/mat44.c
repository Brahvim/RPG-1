#include "Test.h"

testfn add() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 a = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);
	struct SmlMat44 b = smlMat44Val(
		16, 15, 14, 13,
		12, 11, 10, 9,
		8, 7, 6, 5,
		4, 3, 2, 1
	);

	smlMat44Add(&a, &b, &out);
	testCheckFloat(passing |=, out.r11, 17.0f);
	testCheckFloat(passing |=, out.r44, 17.0f);

	return passing;
}

testfn sub() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 a = smlMat44Val(
		10, 20, 30, 40,
		50, 60, 70, 80,
		90, 100, 110, 120,
		130, 140, 150, 160
	);
	struct SmlMat44 b = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44Sub(&a, &b, &out);
	testCheckFloat(passing |=, out.r11, 9.0f);
	testCheckFloat(passing |=, out.r44, 144.0f - 16.0f); // `160 - 16 = 144`. Yup!

	return passing;
}

testfn mult() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 a = smlMat44Val(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	struct SmlMat44 b = smlMat44Val(
		2, 3, 4, 5,
		6, 7, 8, 9,
		10, 11, 12, 13,
		14, 15, 16, 17
	);

	smlMat44Mult(&a, &b, &out);
	testCheckFloat(passing |=, out.r11, 2.0f);
	testCheckFloat(passing |=, out.r44, 17.0f);

	return passing;
}

testfn copy() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44Copy(&m, &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r44, 16.0f);

	return passing;
}

testfn invert() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 3, 0,
		0, 0, 0, 4
	);

	float const det = smlMat44Invert(&m, &out);

	testCheckFloat(passing |=, det, 24.0f); // *The Legend of The Determinant of The Diagonal...!*
	testCheckFloat(passing |=, out.r11, 1.0f / 1.0f);
	testCheckFloat(passing |=, out.r22, 1.0f / 2.0f);
	testCheckFloat(passing |=, out.r33, 1.0f / 3.0f);
	testCheckFloat(passing |=, out.r44, 1.0f / 4.0f);

	return passing;
}

testfn multQuat() {
	struct SmlQuat out;
	bool passing = true;
	struct SmlMat44 m = smlMat44Val(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	struct SmlQuat q = smlQuatVal(1, 2, 3, 4);

	smlMat44MultQuat(&m, &q, &out);
	testCheckFloat(passing |=, out.x, 1.0f);
	testCheckFloat(passing |=, out.w, 4.0f);

	return passing;
}

testfn adjugate() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44Adjugate(&m, &out);
	testCheckFloat(passing |=, out.r11, 0.0f); // Sanity check! Ack!
	testCheckFloat(passing |=, out.r44, 0.0f);

	return passing;
}

testfn identity() {
	struct SmlMat44 m;
	bool passing = true;

	smlMat44Identity(&m);
	testCheckFloat(passing |=, m.r11, 1.0f); // This.		And.
	testCheckFloat(passing |=, m.r22, 1.0f); // Is.			WILL.
	testCheckFloat(passing |=, m.r33, 1.0f); // Pretty.		Bite.
	testCheckFloat(passing |=, m.r44, 1.0f); // Lazy.		Me.

	return passing;
}

testfn cofactors() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44Cofactors(&m, &out);
	testCheckFloat(passing |=, out.r11, 0.0f); // Sanity Check S.E.
	testCheckFloat(passing |=, out.r44, 0.0f);

	return passing;
}

testfn transpose() {
	bool passing = true;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44TransposeSame(&m);
	testCheckFloat(passing |=, m.r44, 1.0f);
	testCheckFloat(passing |=, m.r11, 16.0f);

	return passing;
}

testfn addScalar() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44AddScalar(&m, 10.0f, &out);
	testCheckFloat(passing |=, out.r11, 11.0f);
	testCheckFloat(passing |=, out.r44, 26.0f);

	return passing;
}

testfn divScalar() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		2, 4, 6, 8,
		10, 12, 14, 16,
		18, 20, 22, 24,
		26, 28, 30, 32
	);

	smlMat44DivScalar(&m, 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r44, 16.0f);

	return passing;
}

testfn subScalar() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		10, 12, 14, 16,
		18, 20, 22, 24,
		26, 28, 30, 32,
		34, 36, 38, 40
	);

	smlMat44SubScalar(&m, 10.0f, &out);
	testCheckFloat(passing |=, out.r11, 0.0f);
	testCheckFloat(passing |=, out.r44, 30.0f);

	return passing;
}

testfn divMembers() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 a = smlMat44Val(
		2, 4, 6, 8,
		10, 12, 14, 16,
		18, 20, 22, 24,
		26, 28, 30, 32
	);
	struct SmlMat44 b = smlMat44Val(
		2, 2, 2, 2,
		2, 2, 2, 2,
		2, 2, 2, 2,
		2, 2, 2, 2
	);

	smlMat44DivMembers(&a, &b, &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r44, 16.0f);

	return passing;
}

testfn multScalar() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44MultScalar(&m, 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 2.0f);
	testCheckFloat(passing |=, out.r44, 32.0f);

	return passing;
}

testfn rotateQuat() {
	struct SmlMat44 m;
	bool passing = true;
	smlMat44Identity(&m);
	struct SmlQuat q = smlQuatVal(0, 0, 0, 1); // identity quaternion

	smlMat44RotateQuat(&m, &q);
	testCheckFloat(passing |=, m.r11, 1.0f);
	testCheckFloat(passing |=, m.r22, 1.0f);
	testCheckFloat(passing |=, m.r33, 1.0f);
	testCheckFloat(passing |=, m.r44, 1.0f);

	return passing;
}

testfn multMembers() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 a = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);
	struct SmlMat44 b = smlMat44Val(
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4
	);

	smlMat44MultMembers(&a, &b, &out);
	testCheckFloat(passing |=, out.r11, 1.0f * 1.0f); // Klaxon Beat. Row 1, Col 1.
	testCheckFloat(passing |=, out.r44, 16.0f * 4.0f);

	return passing;
}

testfn determinant() {
	bool passing = true;
	testCheckFloat(
		passing |=,
		smlMat44Determinant(smlMat44Ptr(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		)), // This particular `SmlMat44` "is *singular"...!*
		0.0f
	);

	return passing;
}

testfn adjugateSame() {
	bool passing = true;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44AdjugateSame(&m);
	// Avoid unhinged vals. That's all:
	testCheckFloat(passing |=, m.r11, 0.0f);
	testCheckFloat(passing |=, m.r12, 0.0f);

	return passing;
}

testfn invertUnchecked() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		2, 0, 0, 0,
		0, 3, 0, 0,
		0, 0, 4, 0,
		0, 0, 0, 5
	);

	float const det = smlMat44InvertUnchecked(&m, &out);
	testCheckFloat(passing |=, det, 120.0f); // *The Determinant of The Diagonal...!*
	testCheckFloat(passing |=, out.r11, 1.0f / 2.0f);
	testCheckFloat(passing |=, out.r22, 1.0f / 3.0f);
	testCheckFloat(passing |=, out.r33, 1.0f / 4.0f);
	testCheckFloat(passing |=, out.r44, 1.0f / 5.0f);

	return passing;
}

testfn transposeToNew() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	smlMat44Transpose(&m, &out);
	testCheckFloat(passing |=, out.r44, 1.0f);
	testCheckFloat(passing |=, out.r11, 16.0f);

	return passing;
}

testfn invertGivenInvertedDeterminant() {
	bool passing = true;
	struct SmlMat44 out;
	struct SmlMat44 m = smlMat44Val(
		1, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 3, 0,
		0, 0, 0, 4
	);
	float deti = 1.0f / (1.0f * 2.0f * 3.0f * 4.0f); // Also *just* `1 / 24` BTW.

	smlMat44InvertGivenInvertedDeterminant(&m, &out, deti);
	testCheckFloat(passing |=, out.r33, 1.0f / 3.0f);
	testCheckFloat(passing |=, out.r44, 0.25f);
	testCheckFloat(passing |=, out.r22, 0.5f);
	testCheckFloat(passing |=, out.r11, 1.0f);

	return passing;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(invertGivenInvertedDeterminant),
		testCreateTest(transposeToNew),
		testCreateTest(invertUnchecked),
		testCreateTest(transpose),
		testCreateTest(adjugateSame),
		testCreateTest(determinant),
		testCreateTest(multMembers),
		testCreateTest(rotateQuat),
		testCreateTest(multScalar),
		testCreateTest(divMembers),
		testCreateTest(subScalar),
		testCreateTest(divScalar),
		testCreateTest(addScalar),
		testCreateTest(cofactors),
		testCreateTest(identity),
		testCreateTest(adjugate),
		testCreateTest(multQuat),
		testCreateTest(invert),
		testCreateTest(copy),
		testCreateTest(mult),
		testCreateTest(sub),
		testCreateTest(add)

	));
}
