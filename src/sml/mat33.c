#include "Sml.h"
#include <math.h>
#include "Macros.h"

inline float smlMat33Determinant(struct SmlMat33 const *const p_matrix) {
	return p_matrix->r11 * (p_matrix->r22 * p_matrix->r33 - p_matrix->r23 * p_matrix->r32)
		- p_matrix->r12 * (p_matrix->r21 * p_matrix->r33 - p_matrix->r23 * p_matrix->r31)
		+ p_matrix->r13 * (p_matrix->r21 * p_matrix->r32 - p_matrix->r22 * p_matrix->r31);
}

inline struct SmlMat33* smlMat33AdjugateSame(struct SmlMat33 *const p_matrix) {
	struct SmlMat33 cof;
	smlMat33Cofactors(p_matrix, &cof);
	smlMat33Transpose(&cof, p_matrix);
	return p_matrix;
}

inline struct SmlMat33* smlMat33Identity(struct SmlMat33 *const p_destination) {
	p_destination->r11 = 1;
	p_destination->r12 = 0;
	p_destination->r13 = 0;
	p_destination->r21 = 0;
	p_destination->r22 = 1;
	p_destination->r23 = 0;
	p_destination->r31 = 0;
	p_destination->r32 = 0;
	p_destination->r33 = 1;

	return p_destination;
}

inline struct SmlMat33* smlMat33TransposeSame(struct SmlMat33 *const p_matrix) {
	float temp;

	temp = p_matrix->r12;  p_matrix->r12 = p_matrix->r21;  p_matrix->r21 = temp;
	temp = p_matrix->r13;  p_matrix->r13 = p_matrix->r31;  p_matrix->r31 = temp;
	temp = p_matrix->r23;  p_matrix->r23 = p_matrix->r32;  p_matrix->r32 = temp;

	return p_matrix;
}

inline struct SmlMat33* smlMat33ShearXY(struct SmlMat33 *const p_matrix, float const p_shear) {
	p_matrix->r13 += p_matrix->r11 * p_shear;
	p_matrix->r23 += p_matrix->r21 * p_shear;
	p_matrix->r33 += p_matrix->r31 * p_shear;
	return p_matrix;
}

inline struct SmlMat33* smlMat33ShearXZ(struct SmlMat33 *const p_matrix, float const p_shear) {
	p_matrix->r12 += p_matrix->r11 * p_shear;
	p_matrix->r22 += p_matrix->r21 * p_shear;
	p_matrix->r32 += p_matrix->r31 * p_shear;
	return p_matrix;
}

inline struct SmlMat33* smlMat33ShearYZ(struct SmlMat33 *const p_matrix, float const p_shear) {
	p_matrix->r12 += p_matrix->r13 * p_shear;
	p_matrix->r22 += p_matrix->r23 * p_shear;
	p_matrix->r32 += p_matrix->r33 * p_shear;
	return p_matrix;
}

inline struct SmlMat33* smlMat33RotateX(struct SmlMat33 *const p_matrix, float const p_angle) {
	float const cosA = cosf(p_angle);
	float const sinA = sinf(p_angle);

	for (int i = 0; i < 3; ++i) {

		float const y = p_matrix->two[1][i];
		float const z = p_matrix->two[2][i];

		p_matrix->two[1][i] = y * cosA - z * sinA;
		p_matrix->two[2][i] = y * sinA + z * cosA;

	}

	return p_matrix;
}

inline struct SmlMat33* smlMat33RotateY(struct SmlMat33 *const p_matrix, float const p_angle) {
	float const cosA = cosf(p_angle);
	float const sinA = sinf(p_angle);

	for (int i = 0; i < 3; ++i) {

		float const x = p_matrix->two[0][i];
		float const z = p_matrix->two[2][i];

		p_matrix->two[0][i] = x * cosA + z * sinA;
		p_matrix->two[2][i] = -x * sinA + z * cosA;

	}

	return p_matrix;
}

inline struct SmlMat33* smlMat33RotateZ(struct SmlMat33 *const p_matrix, float const p_angle) {
	float const cosA = cosf(p_angle);
	float const sinA = sinf(p_angle);

	for (int i = 0; i < 3; ++i) {

		float const x = p_matrix->two[0][i];
		float const y = p_matrix->two[1][i];

		p_matrix->two[0][i] = x * cosA - y * sinA;
		p_matrix->two[1][i] = x * sinA + y * cosA;

	}

	return p_matrix;
}

inline float smlMat33Invert(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination) {
	float const det = smlMat33Determinant(p_matrix);

	if (unlikely(det == 0.0f)) {

		return 0.0f;

	}

	smlMat33InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);

	return det;
}

inline struct SmlMat33* smlMat33RotateQuat(struct SmlMat33 *const p_matrix, struct SmlQuat *const p_quat) {
	float const x = p_quat->x;
	float const y = p_quat->y;
	float const z = p_quat->z;
	float const w = p_quat->w;

	float const xx = x * x;
	float const yy = y * y;
	float const zz = z * z;

	float const xy = x * y;
	float const xz = x * z;
	float const yz = y * z;

	float const wx = w * x;
	float const wy = w * y;
	float const wz = w * z;

	p_matrix->r11 = 1.0f - 2.0f * (yy + zz);
	p_matrix->r12 = 2.0f * (xy - wz);
	p_matrix->r13 = 2.0f * (xz + wy);

	p_matrix->r21 = 2.0f * (xy + wz);
	p_matrix->r22 = 1.0f - 2.0f * (xx + zz);
	p_matrix->r23 = 2.0f * (yz - wx);

	p_matrix->r31 = 2.0f * (xz - wy);
	p_matrix->r32 = 2.0f * (yz + wx);
	p_matrix->r33 = 1.0f - 2.0f * (xx + yy);

	return p_matrix;
}

inline struct SmlMat33* smlMat33Adjugate(struct SmlMat33 *const p_matrix, struct SmlMat33 *const p_destination) {
	smlMat33Cofactors(p_matrix, p_destination);
	smlMat33TransposeSame(p_destination);
	return p_destination;
}

inline struct SmlMat33* smlMat33Transpose(struct SmlMat33 *const p_matrix, struct SmlMat33 *const p_destination) {
	smlMat33Copy(p_matrix, p_destination);
	smlMat33TransposeSame(p_destination);
	return p_destination;
}

inline float smlMat33InvertUnchecked(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination) {
	float const det = smlMat33Determinant(p_matrix);
	smlMat33InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);
	return det;
}

inline struct SmlMat33* smlMat33Copy(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11;
	p_destination->r12 = p_matrix->r12;
	p_destination->r13 = p_matrix->r13;
	p_destination->r21 = p_matrix->r21;
	p_destination->r22 = p_matrix->r22;
	p_destination->r23 = p_matrix->r23;
	p_destination->r31 = p_matrix->r31;
	p_destination->r32 = p_matrix->r32;
	p_destination->r33 = p_matrix->r33;


	return p_destination;
}

inline struct SmlMat33* smlMat33Cofactors(struct SmlMat33 const* const p_matrix, struct SmlMat33 *const p_destination) {
	p_destination->r11 = (p_matrix->r22 * p_matrix->r33 - p_matrix->r23 * p_matrix->r32);
	p_destination->r12 = -(p_matrix->r12 * p_matrix->r33 - p_matrix->r13 * p_matrix->r32);
	p_destination->r13 = (p_matrix->r12 * p_matrix->r23 - p_matrix->r13 * p_matrix->r22);
	p_destination->r21 = -(p_matrix->r21 * p_matrix->r33 - p_matrix->r23 * p_matrix->r31);
	p_destination->r22 = (p_matrix->r11 * p_matrix->r33 - p_matrix->r13 * p_matrix->r31);
	p_destination->r23 = -(p_matrix->r11 * p_matrix->r23 - p_matrix->r13 * p_matrix->r21);
	p_destination->r31 = (p_matrix->r21 * p_matrix->r32 - p_matrix->r22 * p_matrix->r31);
	p_destination->r32 = -(p_matrix->r11 * p_matrix->r32 - p_matrix->r12 * p_matrix->r31);
	p_destination->r33 = (p_matrix->r11 * p_matrix->r22 - p_matrix->r12 * p_matrix->r21);

	return p_destination;
}

inline struct SmlMat33* smlMat33AddScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 + p_scalar;
	p_destination->r12 = p_matrix->r12 + p_scalar;
	p_destination->r13 = p_matrix->r13 + p_scalar;
	p_destination->r21 = p_matrix->r21 + p_scalar;
	p_destination->r22 = p_matrix->r22 + p_scalar;
	p_destination->r23 = p_matrix->r23 + p_scalar;
	p_destination->r31 = p_matrix->r31 + p_scalar;
	p_destination->r32 = p_matrix->r32 + p_scalar;
	p_destination->r33 = p_matrix->r33 + p_scalar;

	return p_destination;
}

inline struct SmlMat33* smlMat33DivScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 / p_scalar;
	p_destination->r12 = p_matrix->r12 / p_scalar;
	p_destination->r13 = p_matrix->r13 / p_scalar;
	p_destination->r21 = p_matrix->r21 / p_scalar;
	p_destination->r22 = p_matrix->r22 / p_scalar;
	p_destination->r23 = p_matrix->r23 / p_scalar;
	p_destination->r31 = p_matrix->r31 / p_scalar;
	p_destination->r32 = p_matrix->r32 / p_scalar;
	p_destination->r33 = p_matrix->r33 / p_scalar;

	return p_destination;
}

inline struct SmlMat33* smlMat33SubScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 - p_scalar;
	p_destination->r12 = p_matrix->r12 - p_scalar;
	p_destination->r13 = p_matrix->r13 - p_scalar;
	p_destination->r21 = p_matrix->r21 - p_scalar;
	p_destination->r22 = p_matrix->r22 - p_scalar;
	p_destination->r23 = p_matrix->r23 - p_scalar;
	p_destination->r31 = p_matrix->r31 - p_scalar;
	p_destination->r32 = p_matrix->r32 - p_scalar;
	p_destination->r33 = p_matrix->r33 - p_scalar;

	return p_destination;
}

inline struct SmlMat33* smlMat33MultScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 * p_scalar;
	p_destination->r12 = p_matrix->r12 * p_scalar;
	p_destination->r13 = p_matrix->r13 * p_scalar;
	p_destination->r21 = p_matrix->r21 * p_scalar;
	p_destination->r22 = p_matrix->r22 * p_scalar;
	p_destination->r23 = p_matrix->r23 * p_scalar;
	p_destination->r31 = p_matrix->r31 * p_scalar;
	p_destination->r32 = p_matrix->r32 * p_scalar;
	p_destination->r33 = p_matrix->r33 * p_scalar;

	return p_destination;
}

inline struct SmlMat33* smlMat33Add(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 + p_second->r11;
	p_destination->r12 = p_first->r12 + p_second->r12;
	p_destination->r13 = p_first->r13 + p_second->r13;
	p_destination->r21 = p_first->r21 + p_second->r21;
	p_destination->r22 = p_first->r22 + p_second->r22;
	p_destination->r23 = p_first->r23 + p_second->r23;
	p_destination->r31 = p_first->r31 + p_second->r31;
	p_destination->r32 = p_first->r32 + p_second->r32;
	p_destination->r33 = p_first->r33 + p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33Sub(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 - p_second->r11;
	p_destination->r12 = p_first->r12 - p_second->r12;
	p_destination->r13 = p_first->r13 - p_second->r13;
	p_destination->r21 = p_first->r21 - p_second->r21;
	p_destination->r22 = p_first->r22 - p_second->r22;
	p_destination->r23 = p_first->r23 - p_second->r23;
	p_destination->r31 = p_first->r31 - p_second->r31;
	p_destination->r32 = p_first->r32 - p_second->r32;
	p_destination->r33 = p_first->r33 - p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33Mult(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11 + p_first->r12 * p_second->r21 + p_first->r13 * p_second->r31;
	p_destination->r12 = p_first->r11 * p_second->r12 + p_first->r12 * p_second->r22 + p_first->r13 * p_second->r32;
	p_destination->r13 = p_first->r11 * p_second->r13 + p_first->r12 * p_second->r23 + p_first->r13 * p_second->r33;
	p_destination->r21 = p_first->r21 * p_second->r11 + p_first->r22 * p_second->r21 + p_first->r23 * p_second->r31;
	p_destination->r22 = p_first->r21 * p_second->r12 + p_first->r22 * p_second->r22 + p_first->r23 * p_second->r32;
	p_destination->r23 = p_first->r21 * p_second->r13 + p_first->r22 * p_second->r23 + p_first->r23 * p_second->r33;
	p_destination->r31 = p_first->r31 * p_second->r11 + p_first->r32 * p_second->r21 + p_first->r33 * p_second->r31;
	p_destination->r32 = p_first->r31 * p_second->r12 + p_first->r32 * p_second->r22 + p_first->r33 * p_second->r32;
	p_destination->r33 = p_first->r31 * p_second->r13 + p_first->r32 * p_second->r23 + p_first->r33 * p_second->r33;

	return p_destination;
}

inline struct SmlVec3* smlMat33MultVec3(struct SmlMat33 const *const p_matrix, struct SmlVec3 const *const p_vector3, struct SmlVec3 *const p_destination) {
	float const x = p_vector3->x;
	float const y = p_vector3->y;
	float const z = p_vector3->z;

	p_destination->x = p_matrix->r11 * x + p_matrix->r12 * y + p_matrix->r13 * z;
	p_destination->y = p_matrix->r21 * x + p_matrix->r22 * y + p_matrix->r23 * z;
	p_destination->z = p_matrix->r31 * x + p_matrix->r32 * y + p_matrix->r33 * z;

	return p_destination;
}

inline struct SmlMat33* smlMat33DivMembers(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 / p_second->r11;
	p_destination->r12 = p_first->r12 / p_second->r12;
	p_destination->r13 = p_first->r13 / p_second->r13;
	p_destination->r21 = p_first->r21 / p_second->r21;
	p_destination->r22 = p_first->r22 / p_second->r22;
	p_destination->r23 = p_first->r23 / p_second->r23;
	p_destination->r31 = p_first->r31 / p_second->r31;
	p_destination->r32 = p_first->r32 / p_second->r32;
	p_destination->r33 = p_first->r33 / p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33MultMembers(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11;
	p_destination->r12 = p_first->r12 * p_second->r12;
	p_destination->r13 = p_first->r13 * p_second->r13;
	p_destination->r21 = p_first->r21 * p_second->r21;
	p_destination->r22 = p_first->r22 * p_second->r22;
	p_destination->r23 = p_first->r23 * p_second->r23;
	p_destination->r31 = p_first->r31 * p_second->r31;
	p_destination->r32 = p_first->r32 * p_second->r32;
	p_destination->r33 = p_first->r33 * p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33InvertGivenInvertedDeterminant(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination, float const p_invertedDeterminant) {
	struct SmlMat33 cofs;
	smlMat33Transpose(
		smlMat33Cofactors(p_matrix, &cofs),
		p_destination
	);

	p_destination->one[0] *= p_invertedDeterminant;
	p_destination->one[1] *= p_invertedDeterminant;
	p_destination->one[2] *= p_invertedDeterminant;
	p_destination->one[3] *= p_invertedDeterminant;
	p_destination->one[4] *= p_invertedDeterminant;
	p_destination->one[5] *= p_invertedDeterminant;
	p_destination->one[6] *= p_invertedDeterminant;
	p_destination->one[7] *= p_invertedDeterminant;
	p_destination->one[8] *= p_invertedDeterminant;

	return p_destination;
}
