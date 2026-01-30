#include "Test.h"

testfn axes() {
	bool passing = true;
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-0, -1)), -SML_PI * 0.5f, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-0, +1)), +SML_PI * 0.5f, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-1, -0)), -SML_PI, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(-1, -0)), +SML_PI, 1e-6f);
	testCheckFloatEpsilon(passing |=, smlVec2Direction(smlVec2Ptr(+1, -0)), 0.0f, 1e-6f);
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
		testCreateTest(magnitude),
		testCreateTest(axes)

	));
}
