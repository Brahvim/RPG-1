#include "Test.h"

testfn add() {
	struct SmlVec2 out;
	bool passing = true;

	smlVec2Add(smlVec2Ptr(1, 2), smlVec2Ptr(3, 4), &out);
	testCheckFloat(passing |=, out.x, 4.0f);
	testCheckFloat(passing |=, out.y, 6.0f);
	return passing;
}

testfn sub() {
	struct SmlVec2 out;
	bool passing = true;

	smlVec2Sub(smlVec2Ptr(5, 5), smlVec2Ptr(2, 3), &out);
	testCheckFloat(passing |=, out.x, 3.0f);
	testCheckFloat(passing |=, out.y, 2.0f);

	return passing;
}

testfn dot() {
	bool passing = true;
	testCheckFloat(passing |=, smlVec2Dot(smlVec2Ptr(1, 2), smlVec2Ptr(3, 4)), 11.0f);
	testCheckFloat(passing |=, smlVec2Dot(smlVec2Ptr(3, 4), smlVec2Ptr(3, 4)), 25.0f);
	testCheckFloat(passing |=, smlVec2Dot(smlVec2Ptr(1, 0), smlVec2Ptr(0, 1)), 0.0f);
	return passing;
}

testfn axes() {
	bool passing = true;
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-0, -1)), -SML_PI * 0.5f, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-0, +1)), +SML_PI * 0.5f, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-1, -0)), -SML_PI, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-1, -0)), +SML_PI, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(+1, -0)), 0.0f, 1e-6f);
	return passing;
}

testfn mult() {
	struct SmlVec2 out;
	bool passing = true;

	smlVec2Mult(smlVec2Ptr(1, -2), -2.0f, &out);
	testCheckFloat(passing |=, out.x, -2.0f);
	testCheckFloat(passing |=, out.y, 4.0f);

	return passing;
}

testfn cross() {
	struct SmlVec3 out;
	bool passing = true;

	smlVec2Cross(smlVec2Ptr(0, 1), smlVec2Ptr(1, 0), &out);
	testCheckFloat(passing |=, out.z, -1.0f);

	smlVec2Cross(smlVec2Ptr(1, 0), smlVec2Ptr(0, 1), &out);
	testCheckFloat(passing |=, out.x, 0.0f);
	testCheckFloat(passing |=, out.y, 0.0f);
	testCheckFloat(passing |=, out.z, 1.0f);

	return passing;
}

testfn scale() {
	struct SmlVec2 out;
	bool passing = true;

	smlVec2Scale(smlVec2Ptr(1, -2), 3.0f, &out);
	testCheckFloat(passing |=, out.y, -6.0f);
	testCheckFloat(passing |=, out.x, 3.0f);

	return passing;
}

testfn normalize() {
	struct SmlVec2 out;
	bool passing = true;

	/* What is zeroes, stay zeroed (Checked™!): */
	smlVec2Normalize(smlVec2Ptr(0, 0), &out);
	testCheckFloat(passing |=, out.x, 0.0f);
	testCheckFloat(passing |=, out.y, 0.0f);

	/* Unchecked: test only non-zeroed: */
	smlVec2NormalizeUnchecked(smlVec2Ptr(5, 0), &out);
	testCheckFloatEpsilon(passing |=, out.x, 1.0f, 1e-6f);
	testCheckFloatEpsilon(passing |=, out.y, 0.0f, 1e-6f);

	smlVec2Normalize(smlVec2Ptr(3, 4), &out);
	testCheckFloatEpsilon(passing |=, smlVec2Magnitude(&out), 1.0f, 1e-6f);

	return passing;
}

testfn magnitude() {
	bool passing = true;
	testCheckFloat(passing |=, smlVec2Magnitude(smlVec2Ptr(-3, -4)), 5.0f);
	testCheckFloat(passing |=, smlVec2Magnitude(smlVec2Ptr(3, 4)), 5.0f);
	testCheckFloat(passing |=, smlVec2Magnitude(smlVec2Ptr(1, 0)), 1.0f);
	testCheckFloat(passing |=, smlVec2Magnitude(smlVec2Ptr(0, 0)), 0.0f);
	return passing;
}

testfn fromAngle() {
	bool passing = true;
	struct SmlVec2 v;

	float angles[] = {

		0.0f,
		+SML_PI * 0.5f,
		-SML_PI * 0.5f,
		SML_PI,

	};

	for (size_t i = 0; i < sizearr(angles); ++i) {

		float const a = angles[i];
		smlVec2FromAngle(a, &v);
		float const dir = smlVec2Direction(&v);
		testCheckFloatEpsilon(passing |=, dir, a, 1e-6f);

	}

	return passing;
}

testfn setZeroOne() {
	bool passing = true;
	struct SmlVec2 v;

	smlVec2Zero(&v);
	testCheckFloat(passing |=, v.x, 0.0f);
	testCheckFloat(passing |=, v.y, 0.0f);

	smlVec2One(&v);
	testCheckFloat(passing |=, v.x, 1.0f);
	testCheckFloat(passing |=, v.y, 1.0f);

	smlVec2Set(&v, 3.0f, -4.0f);
	testCheckFloat(passing |=, v.x, 3.0f);
	testCheckFloat(passing |=, v.y, -4.0f);

	return passing;
}

testfn magAndMagSquared() {
	bool passing = true;

	testCheckFloat(passing |=, smlVec2Magnitude(smlVec2Ptr(0, 0)), 0.0f);
	testCheckFloat(passing |=, smlVec2Magnitude(smlVec2Ptr(3, 4)), 5.0f);

	testCheckFloat(passing |=, smlVec2MagnitudeSquared(smlVec2Ptr(+3, +4)), 25.0f);
	testCheckFloat(passing |=, smlVec2MagnitudeSquared(smlVec2Ptr(-3, -4)), 25.0f);

	return passing;
}

testfn magdirConsistency() {
	struct SmlVec2 const v = smlVec2Val(3, 4);
	float const mag = smlVec2Magnitude(&v);
	float const dir = smlVec2Direction(&v);
	float const x = cosf(dir) * mag;
	float const y = sinf(dir) * mag;
	bool passing = true;

	testCheckFloatEpsilon(passing |=, x, v.x, 1e-5f);
	testCheckFloatEpsilon(passing |=, y, v.y, 1e-5f);
	return passing;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(magdirConsistency),
		testCreateTest(magAndMagSquared),
		testCreateTest(setZeroOne),
		testCreateTest(fromAngle),
		testCreateTest(magnitude),
		testCreateTest(normalize),
		testCreateTest(cross),
		testCreateTest(scale),
		testCreateTest(mult),
		testCreateTest(axes),
		testCreateTest(dot),
		testCreateTest(sub),
		testCreateTest(add)

	));
}
