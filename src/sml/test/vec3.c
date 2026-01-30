#include "Test.h"

testfn add() {
	struct SmlVec3 out;
	bool passing = true;

	smlVec3Add(smlVec3Ptr(1, 2, 3), smlVec3Ptr(3, 2, 1), &out);
	testCheckFloat(passing |=, out.x, 4.0f);
	testCheckFloat(passing |=, out.y, 4.0f);
	testCheckFloat(passing |=, out.z, 4.0f);
	return passing;
}

testfn sub() {
	struct SmlVec3 out;
	bool passing = true;

	smlVec3Sub(smlVec3Ptr(5, 5, 5), smlVec3Ptr(1, 2, 3), &out);
	testCheckFloat(passing |=, out.x, 4.0f);
	testCheckFloat(passing |=, out.y, 3.0f);
	testCheckFloat(passing |=, out.z, 2.0f);

	return passing;
}

testfn dot() {
	bool passing = true;
	testCheckFloat(passing |=, smlVec3Dot(smlVec3Ptr(1, 0, 0), smlVec3Ptr(0, 1, 0)), 0.0f);
	testCheckFloat(passing |=, smlVec3Dot(smlVec3Ptr(1, 2, 3), smlVec3Ptr(1, 2, 3)), 14.0f);
	return passing;
}

testfn mult() {
	struct SmlVec3 out;
	bool passing = true;

	smlVec3Mult(smlVec3Ptr(1, -2, 3), -1.0f, &out);
	testCheckFloat(passing |=, out.x, -1.0f);
	testCheckFloat(passing |=, out.y, +2.0f);
	testCheckFloat(passing |=, out.z, -3.0f);

	return passing;
}

testfn cross() {
	struct SmlVec3 out;
	bool passing = true;

	smlVec3Cross(smlVec3Ptr(1, 0, 0), smlVec3Ptr(0, 1, 0), &out);
	testCheckFloat(passing |=, out.x, 0.0f);
	testCheckFloat(passing |=, out.y, 0.0f);
	testCheckFloat(passing |=, out.z, 1.0f);

	smlVec3Cross(smlVec3Ptr(1, 0, 0), smlVec3Ptr(0, 1, 0), &out);
	testCheckFloat(passing |=, out.z, -1.0f);

	smlVec3Cross(smlVec3Ptr(1, 1, 1), smlVec3Ptr(2, 2, 2), &out);
	testCheckFloat(passing |=, out.z, 0.0f);
	testCheckFloat(passing |=, out.z, 0.0f);
	testCheckFloat(passing |=, out.z, 0.0f);

	return passing;
}

testfn scale() {
	struct SmlVec3 out;
	bool passing = true;

	smlVec3Scale(smlVec3Ptr(1, -2, 3), +2.0f, &out);
	testCheckFloat(passing |=, out.x, +2.0f);
	testCheckFloat(passing |=, out.y, -4.0f);
	testCheckFloat(passing |=, out.z, +6.0f);

	return passing;
}

testfn normalize() {
	struct SmlVec3 out;
	bool passing = true;

	/* What is zeroed, stay zeroed (Checked™!): */
	smlVec3Normalize(smlVec3Ptr(0, 0, 0), &out);
	testCheckFloat(passing |=, out.x, 0.0f);
	testCheckFloat(passing |=, out.y, 0.0f);
	testCheckFloat(passing |=, out.z, 0.0f);

	/* Unchecked: test only non-zeroed: */
	smlVec3NormalizeUnchecked(smlVec3Ptr(5, 0, 0), &out);
	testCheckFloatEpsilon(passing |=, out.x, 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, out.y, 0.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, out.y, 0.0f, 1e-6f);

	smlVec3Normalize(smlVec3Ptr(3, 4, 12), &out);
	testCheckFloatEpsilon(passing |=, smlVec3Magnitude(&out), 1.0f, 1e-6f);

	return passing;
}

testfn setZeroOne() {
	bool passing = true;
	struct SmlVec3 v;

	smlVec3Zero(&v);
	testCheckFloat(passing |=, v.x, 0.0f);
	testCheckFloat(passing |=, v.y, 0.0f);
	testCheckFloat(passing |=, v.z, 0.0f);

	smlVec3One(&v);
	testCheckFloat(passing |=, v.x, 1.0f);
	testCheckFloat(passing |=, v.y, 1.0f);
	testCheckFloat(passing |=, v.z, 1.0f);

	smlVec3Set(&v, +3.0f, -4.0f, -5.0f);
	testCheckFloat(passing |=, v.x, +3.0f);
	testCheckFloat(passing |=, v.y, -4.0f);
	testCheckFloat(passing |=, v.z, -5.0f);

	return passing;
}

testfn fromAngle3d() {
	struct SmlVec3 v;
	bool passing = true;

	/* Dotting with self should give `1.0f`...!: */
	testCheckFloatEpsilon(passing |=, smlVec3Dot(&v, &v), 1.0f, 1e-6f);

	smlVec3FromAngle3d(1.0f, 1.0f, 1.0f, &v);
	testCheckFloatEpsilon(passing |=, smlVec3Magnitude(&v), 1.0f, 1e-6f);

	return passing;

}

testfn magAndMagSquared() {
	bool passing = true;

	testCheckFloat(passing |=, smlVec3Magnitude(smlVec3Ptr(0, 0, 0)), 0.0f);
	testCheckFloat(passing |=, smlVec3Magnitude(smlVec3Ptr(1, 0, 0)), 1.0f);
	testCheckFloat(passing |=, smlVec3Magnitude(smlVec3Ptr(3, 4, 12)), 13.0f);
	testCheckFloat(passing |=, smlVec3MagnitudeSquared(smlVec3Ptr(3, 4, 12)), 169.0f);

	return passing;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(magAndMagSquared),
		testCreateTest(fromAngle3d),
		testCreateTest(setZeroOne),
		testCreateTest(normalize),
		testCreateTest(cross),
		testCreateTest(scale),
		testCreateTest(mult),
		testCreateTest(dot),
		testCreateTest(sub),
		testCreateTest(add)

	));
}
