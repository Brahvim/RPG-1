#include "Test.h"
#include "Test.h"

testfn copy() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22Copy(smlMat22Ptr(1, 2, 3, 4), &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r12, 2.0f);
	testCheckFloat(passing |=, out.r21, 3.0f);
	testCheckFloat(passing |=, out.r22, 4.0f);

	return passing;
}

testfn mult() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22Mult(smlMat22Ptr(1, 2, 3, 4), smlMat22Ptr(5, 6, 7, 8), &out);
	testCheckFloat(passing |=, out.r11, 19.0f);
	testCheckFloat(passing |=, out.r12, 22.0f);
	testCheckFloat(passing |=, out.r21, 43.0f);
	testCheckFloat(passing |=, out.r22, 50.0f);

	return passing;
}

testfn invert() {
	struct SmlMat22 id;
	bool passing = true;
	struct SmlMat22 inv;
	struct SmlMat22 m = smlMat22Val(1, 2, 3, 4);
	float const det = smlMat22Invert(&m, &inv);

	smlMat22Mult(&m, &inv, &id);
	testCheckFloatEpsilon(passing |=, id.r11, 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r12, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r21, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r22, 1.0f, 1e-6f);

	return passing;
}

testfn multVec2() {
	struct SmlVec2 out;
	bool passing = true;

	smlMat22MultVec2(smlMat22Ptr(1, 2, 3, 4), smlVec2Ptr(1, 1), &out);
	testCheckFloat(passing |=, out.x, 3.0f);
	testCheckFloat(passing |=, out.y, 7.0f);

	return passing;
}

testfn adjugate() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22Adjugate(smlMat22Ptr(1, 2, 3, 4), &out);
	testCheckFloat(passing |=, out.r11, +4.0f);
	testCheckFloat(passing |=, out.r12, -2.0f);
	testCheckFloat(passing |=, out.r21, -3.0f);
	testCheckFloat(passing |=, out.r22, +1.0f);

	return passing;
}

testfn identity() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22Identity(&out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r12, 0.0f);
	testCheckFloat(passing |=, out.r21, 0.0f);
	testCheckFloat(passing |=, out.r22, 1.0f);

	return passing;
}

testfn transpose() {
	bool passing = true;
	struct SmlMat22 m = smlMat22Val(1, 2, 3, 4);

	smlMat22TransposeSame(smlMat22Ptr(1, 2, 3, 4));
	testCheckFloat(passing |=, m.r11, 4.0f);
	testCheckFloat(passing |=, m.r12, 3.0f);
	testCheckFloat(passing |=, m.r21, 2.0f);
	testCheckFloat(passing |=, m.r22, 1.0f);

	return passing;
}

testfn addScalar() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22AddScalar(smlMat22Ptr(1, 2, 3, 4), 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 3.0f);
	testCheckFloat(passing |=, out.r12, 4.0f);
	testCheckFloat(passing |=, out.r21, 5.0f);
	testCheckFloat(passing |=, out.r22, 6.0f);

	return passing;
}

testfn subScalar() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22SubScalar(smlMat22Ptr(5, 6, 7, 8), 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 3.0f);
	testCheckFloat(passing |=, out.r12, 4.0f);
	testCheckFloat(passing |=, out.r21, 5.0f);
	testCheckFloat(passing |=, out.r22, 6.0f);

	return passing;
}

testfn divScalar() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22DivScalar(smlMat22Ptr(2, 4, 6, 8), 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 1.0f);
	testCheckFloat(passing |=, out.r12, 2.0f);
	testCheckFloat(passing |=, out.r21, 3.0f);
	testCheckFloat(passing |=, out.r22, 4.0f);

	return passing;
}

testfn multScalar() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22MultScalar(smlMat22Ptr(1, 2, 3, 4), 2.0f, &out);
	testCheckFloat(passing |=, out.r11, 2.0f);
	testCheckFloat(passing |=, out.r12, 4.0f);
	testCheckFloat(passing |=, out.r21, 6.0f);
	testCheckFloat(passing |=, out.r22, 8.0f);

	return passing;
}

testfn subMembers() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22Sub(smlMat22Ptr(5, 6, 7, 8), smlMat22Ptr(1, 2, 3, 4), &out);
	testCheckFloat(passing |=, out.r11, 4.0f);
	testCheckFloat(passing |=, out.r12, 4.0f);
	testCheckFloat(passing |=, out.r21, 4.0f);
	testCheckFloat(passing |=, out.r22, 4.0f);

	return passing;
}

testfn addMembers() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22Add(smlMat22Ptr(1, 2, 3, 4), smlMat22Ptr(5, 6, 7, 8), &out);
	testCheckFloat(passing |=, out.r11, 6.0f);
	testCheckFloat(passing |=, out.r12, 8.0f);
	testCheckFloat(passing |=, out.r21, 10.0f);
	testCheckFloat(passing |=, out.r22, 12.0f);

	return passing;
}

testfn divMembers() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22DivMembers(smlMat22Ptr(2, 3, 7, 8), smlMat22Ptr(10, 12, 14, 16), &out);
	testCheckFloat(passing |=, out.r11, 5.0f);
	testCheckFloat(passing |=, out.r12, 4.0f);
	testCheckFloat(passing |=, out.r21, 2.0f);
	testCheckFloat(passing |=, out.r22, 2.0f);

	return passing;
}

testfn multMembers() {
	bool passing = true;
	struct SmlMat22 out;

	smlMat22MultMembers(smlMat22Ptr(1, 2, 3, 4), smlMat22Ptr(5, 6, 7, 8), &out);
	testCheckFloat(passing |=, out.r11, 5.0f);
	testCheckFloat(passing |=, out.r12, 12.0f);
	testCheckFloat(passing |=, out.r21, 21.0f);
	testCheckFloat(passing |=, out.r22, 32.0f);

	return passing;
}

testfn determinant() {
	bool passing = true;
	testCheckFloat(passing |=, smlMat22Determinant(smlMat22Ptr(1, 2, 3, 4)), -2.0f);
	return passing;
}

testfn adjugateSame() {
	bool passing = true;
	struct SmlMat22 m = smlMat22Val(1, 2, 3, 4);

	smlMat22AdjugateSame(&m);
	testCheckFloat(passing |=, m.r11, +4.0f);
	testCheckFloat(passing |=, m.r12, -2.0f);
	testCheckFloat(passing |=, m.r21, -3.0f);
	testCheckFloat(passing |=, m.r22, +1.0f);

	return passing;
}

testfn invertUnchecked() {
	bool passing = true;
	struct SmlMat22 id, inv;
	struct SmlMat22 m = smlMat22Val(1, 2, 3, 4);

	smlMat22InvertUnchecked(&m, &inv);
	smlMat22Mult(&m, &inv, &id);

	testCheckFloatEpsilon(passing |=, id.r11, 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r12, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r21, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r22, 1.0f, 1e-6f);

	return passing;
}

testfn transposeToNew() {
	bool passing = true;
	struct SmlMat22 out;
	struct SmlMat22 m = smlMat22Val(1, 2, 3, 4);

	smlMat22Transpose(&m, &out);
	testCheckFloat(passing |=, out.r11, 4.0f);
	testCheckFloat(passing |=, out.r12, 3.0f);
	testCheckFloat(passing |=, out.r21, 2.0f);
	testCheckFloat(passing |=, out.r22, 1.0f);

	return passing;
}

testfn invertGivenInvertedDeterminant() {
	bool passing = true;
	struct SmlMat22 inv;
	struct SmlMat22 m = smlMat22Val(1, 2, 3, 4);
	float const det = 1.0f / smlMat22Determinant(&m);
	smlMat22InvertGivenInvertedDeterminant(&m, &inv, det);

	struct SmlMat22 id;
	smlMat22Mult(&m, &inv, &id);
	testCheckFloatEpsilon(passing |=, id.r11, 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r12, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r21, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, id.r22, 1.0f, 1e-6f);

	return passing;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(invertGivenInvertedDeterminant),
		testCreateTest(transposeToNew),
		testCreateTest(invertUnchecked),
		testCreateTest(adjugateSame),
		testCreateTest(transpose),
		testCreateTest(determinant),
		testCreateTest(multMembers),
		testCreateTest(divMembers),
		testCreateTest(addMembers),
		testCreateTest(subMembers),
		testCreateTest(multScalar),
		testCreateTest(divScalar),
		testCreateTest(subScalar),
		testCreateTest(addScalar),
		testCreateTest(identity),
		testCreateTest(adjugate),
		testCreateTest(multVec2),
		testCreateTest(invert),
		testCreateTest(mult)

	));
}
