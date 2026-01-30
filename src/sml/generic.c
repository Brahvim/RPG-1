#include "Sml.h"
#include <math.h>
#include <float.h>
#include "Macros.h"
#include <stddef.h>

#pragma region // `float` casts.
inline struct SmlVec2 smlVec2(float const *const p_array) {
	return (struct SmlVec2) { p_array[0], p_array[1], };
}

inline struct SmlVec3 smlVec3(float const *const p_array) {
	return (struct SmlVec3) { p_array[0], p_array[1], p_array[2], };
}

inline struct SmlQuat smlQuat(float const *const p_array) {
	return (struct SmlQuat) { { p_array[0], p_array[1], p_array[2], p_array[3], } };
}

inline struct SmlMat22 smlMat22(float const *const p_array) {
	return (struct SmlMat22) { // Looks perfectly aligned in non-monospace fonts 😅
		/*		*/  .r11 = p_array[0], .r12 = p_array[1],
			/*	*/	.r21 = p_array[2], .r22 = p_array[3],
	};
}

inline struct SmlMat33 smlMat33(float const *const p_array) {
	return (struct SmlMat33) { // Looks perfectly aligned in non-monospace fonts 😅
		/*		*/	.r11 = p_array[0], .r12 = p_array[1], .r13 = p_array[2],
			/*	*/	.r21 = p_array[3], .r22 = p_array[4], .r23 = p_array[5],
			/*	*/	.r31 = p_array[6], .r32 = p_array[7], .r33 = p_array[8],
	};
}

inline struct SmlMat44 smlMat44(float const *const p_array) {
	return (struct SmlMat44) { // Looks perfectly aligned in non-monospace fonts 😅
		/*		 */ .r11 = p_array[0], .r12 = p_array[1], .r13 = p_array[2], .r14 = p_array[3],
			/*	*/	.r21 = p_array[4], .r22 = p_array[5], .r23 = p_array[6], .r24 = p_array[7],
			/*	*/	.r31 = p_array[8], .r32 = p_array[9], .r33 = p_array[10], .r34 = p_array[11],
			/*	*/	.r41 = p_array[12], .r42 = p_array[13], .r43 = p_array[14], .r44 = p_array[15],
	};
}
#pragma endregion

float* smlMatMult(
	float *const p_destination,	// `p_leftColumnCount	x	p_rightColumnCount`
	float const *p_right,		// `p_rightRowCount		x	p_rightColumnCount`
	float const *p_left,		// `p_leftColumnCount	x	p_rightRowCount`
	size_t const p_rightRowCount,
	size_t const p_leftColumnCount,
	size_t const p_rightColumnCount
) {
	for (size_t i = 0; i < p_leftColumnCount; ++i) {

		for (size_t j = 0; j < p_rightColumnCount; ++j) {

			float sum = 0.0f;
			for (size_t k = 0; k < p_rightRowCount; ++k) {

				sum += p_left[i * p_rightRowCount + k] * p_right[k * p_rightColumnCount + j];

			}

			p_destination[i * p_rightColumnCount + j] = sum;

		}

	}

	return p_destination;
}

inline char smlFloatCompareFltEpsilon(const float p_first, const float p_second) {
	return smlFloatCompare(p_first, p_second, FLT_EPSILON);
}

inline char smlFloatCompare(const float p_first, const float p_second, float p_epsilon) {
	return fabsf(p_first - p_second) < p_epsilon;
}
