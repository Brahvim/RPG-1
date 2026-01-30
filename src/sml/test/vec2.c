#include "Test.h"

testfn magnitude() {
	testCheckFloat(smlVec2Magnitude(smlVec2Ptr(-3, -4)), 5.0f);
	testCheckFloat(smlVec2Magnitude(smlVec2Ptr(3, 4)), 5.0f);
	testCheckFloat(smlVec2Magnitude(smlVec2Ptr(1, 0)), 1.0f);
	testCheckFloat(smlVec2Magnitude(smlVec2Ptr(0, 0)), 0.0f);
	return true;
}

testfn axes() {
	testCheckFloatEpsilon(smlVec2Direction(smlVec2Ptr(-0, -1)), -SML_PI * 0.5f, 1e-6f);
	testCheckFloatEpsilon(smlVec2Direction(smlVec2Ptr(-0, +1)), +SML_PI * 0.5f, 1e-6f);
	testCheckFloatEpsilon(smlVec2Direction(smlVec2Ptr(-1, -0)), -SML_PI, 1e-6f);
	testCheckFloatEpsilon(smlVec2Direction(smlVec2Ptr(-1, -0)), +SML_PI, 1e-6f);
	testCheckFloatEpsilon(smlVec2Direction(smlVec2Ptr(+1, -0)), 0.0f, 1e-6f);
	return true;
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(magnitude),
		testCreateTest(axes)

	));
}
