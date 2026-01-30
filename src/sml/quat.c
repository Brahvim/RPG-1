#include "Sml.h"
#include <math.h>
#include "Macros.h"

inline float smlQuatMagnitude(struct SmlQuat const *const p_quaternion) {
	return __builtin_sqrtf(smlQuatMagnitudeSquared(p_quaternion));
}

inline struct SmlQuat* smlQuatIdentity(struct SmlQuat *const p_destination) {
	p_destination->x = 0;
	p_destination->y = 0;
	p_destination->z = 0;
	p_destination->w = 1;
	return p_destination;
}

inline float smlQuatMagnitudeSquared(struct SmlQuat const *const p_quaternion) {
#define S(x) x * x
	return S(p_quaternion->x)
		+ S(p_quaternion->z)
		+ S(p_quaternion->y)
		+ S(p_quaternion->w);
#undef S
}

inline float smlQuatDot(struct SmlQuat const *const p_first, struct SmlQuat const *const p_second) {
	return
		p_first->x * p_second->x +
		p_first->y * p_second->y +
		p_first->z * p_second->z +
		p_first->w * p_second->w;
}

inline struct SmlQuat* smlQuatFromMatrix33(struct SmlMat33 const *p_matrix, struct SmlQuat *p_quaternion) {
	float const trace = p_matrix->r11 + p_matrix->r22 + p_matrix->r33; // Sum of mat digonals!

	if (likely(trace > 0.0f)) {

		float const s = 2.0f * __builtin_sqrtf(trace + 1.0f); // `4w`
		float const i = 1.0f / s;
		p_quaternion->x = (p_matrix->r32 - p_matrix->r23) * i;
		p_quaternion->y = (p_matrix->r13 - p_matrix->r31) * i;
		p_quaternion->z = (p_matrix->r21 - p_matrix->r12) * i;
		p_quaternion->w = s * 0.25f;

	}
	else { // TODO: Figure out how to lower branches if one *actually* can...

		if (unlikely(p_matrix->r11 > p_matrix->r22 && p_matrix->r11 > p_matrix->r33)) {

			float const s = 2.0f * __builtin_sqrtf(1.0f + p_matrix->r11 - p_matrix->r22 - p_matrix->r33);
			float const sInv = 1.0f / s;
			p_quaternion->x = s * 0.25f;
			p_quaternion->y = (p_matrix->r12 + p_matrix->r21) * sInv;
			p_quaternion->z = (p_matrix->r13 + p_matrix->r31) * sInv;
			p_quaternion->w = (p_matrix->r32 - p_matrix->r23) * sInv;

		}
		else if (unlikely(p_matrix->r22 > p_matrix->r33)) {

			float const s = 2.0f * __builtin_sqrtf(1.0f + p_matrix->r22 - p_matrix->r11 - p_matrix->r33);
			float const sInv = 1.0f / s;
			p_quaternion->x = (p_matrix->r12 + p_matrix->r21) * sInv;
			p_quaternion->y = s * 0.25f;
			p_quaternion->z = (p_matrix->r23 + p_matrix->r32) * sInv;
			p_quaternion->w = (p_matrix->r13 - p_matrix->r31) * sInv;

		}
		else {

			float const s = 2.0f * __builtin_sqrtf(1.0f + p_matrix->r33 - p_matrix->r11 - p_matrix->r22);
			float const sInv = 1.0f / s;
			p_quaternion->x = (p_matrix->r13 + p_matrix->r31) * sInv;
			p_quaternion->y = (p_matrix->r23 + p_matrix->r32) * sInv;
			p_quaternion->z = s * 0.25f;
			p_quaternion->w = (p_matrix->r21 - p_matrix->r12) * sInv;

		}

	}

	return p_quaternion;
}

inline struct SmlMat44* smlQuatToMatrix44(struct SmlQuat const *const p_source, struct SmlMat44 *p_destination) {
	smlQuatToMatrix33(p_source, &(p_destination->mat33));

	/*
	 _ 	 		   	                  _
	/     0       1      2     [3]     \ <-----\
	|     4       5      6     [7]     | <----- Note these!
	|     8       9     10    [11]     | <----- (and how `[15]` is part of both the "4x4 row and column".)
	\_   [12]   [13]   [14]   [15]    _/ <-----/
	*/

	// Those are the ones that are supposed to be updated, to *part* of an IDENTITY 4x4 matrix.

	// Row:
	p_destination->one[3] = 0;
	p_destination->one[7] = 0;
	p_destination->one[11] = 0;

	// Column:
	p_destination->one[12] = 0;
	p_destination->one[13] = 0;
	p_destination->one[14] = 0;

	// 4th element in both:
	p_destination->one[15] = 1;

	return p_destination;
}

inline struct SmlQuat* smlQuatInvert(struct SmlQuat const *const p_quaternion, struct SmlQuat *const p_destination) {
	float const magSqInv = 1.0f / smlQuatMagnitudeSquared(p_quaternion);
	smlQuatConjugate(p_quaternion, p_destination);

	p_destination->x *= magSqInv;
	p_destination->y *= magSqInv;
	p_destination->z *= magSqInv;
	p_destination->w *= magSqInv;

	return p_destination;
}

inline struct SmlVec3* smlQuatToEuler(struct SmlQuat const *const p_quaternion, struct SmlVec3 *const p_destination) {
	float const fmsTwice = 2 * (p_quaternion->w * p_quaternion->y - p_quaternion->z * p_quaternion->x); // Basically an FMS op.

	p_destination->x = asinf(fmsTwice);

	p_destination->y = atan2f(
		2 * (p_quaternion->w * p_quaternion->x + p_quaternion->y * p_quaternion->z),
		1 - 2 * (p_quaternion->x * p_quaternion->x + p_quaternion->y * p_quaternion->y)
	);

	p_destination->z = atan2f(
		2 * (p_quaternion->w * p_quaternion->z + p_quaternion->x * p_quaternion->y),
		1 - 2 * (p_quaternion->y * p_quaternion->y + p_quaternion->z * p_quaternion->z)
	);

	return p_destination;
}

inline struct SmlMat33* smlQuatToMatrix33(struct SmlQuat const *const p_source, struct SmlMat33 *const p_destination) {
	float const xx = p_source->x * p_source->x;
	float const yy = p_source->y * p_source->y;
	float const zz = p_source->z * p_source->z;

	float const xy = p_source->x * p_source->y;
	float const xz = p_source->x * p_source->z;
	float const yz = p_source->y * p_source->z;

	float const wx = p_source->w * p_source->x;
	float const wy = p_source->w * p_source->y;
	float const wz = p_source->w * p_source->z;

	p_destination->one[0] = 1 - 2 * (yy + zz);
	p_destination->one[1] = 2 * (xy - wz);
	p_destination->one[2] = 2 * (xz + wy);

	p_destination->one[3] = 2 * (xy + wz);
	p_destination->one[4] = 1 - 2 * (xx + zz);
	p_destination->one[5] = 2 * (yz - wx);

	p_destination->one[6] = 2 * (xz - wy);
	p_destination->one[7] = 2 * (yz + wx);
	p_destination->one[8] = 1 - 2 * (xx + yy);

	return p_destination;
}

inline struct SmlQuat* smlQuatConjugate(struct SmlQuat const *const p_quaternion, struct SmlQuat *const p_destination) {
	p_destination->x = -p_quaternion->x;
	p_destination->y = -p_quaternion->y;
	p_destination->z = -p_quaternion->z;

	return p_destination;
}

inline struct SmlQuat* smlQuatNormalize(struct SmlQuat const *const p_quaternion, struct SmlQuat *const p_destination) {
	float magSq = smlQuatMagnitudeSquared(p_quaternion);
	magSq = magSq == 0.0 ? 1 : __builtin_sqrtf(magSq);

	float const magSqInv = 1.0f / magSq;
	p_destination->x = p_quaternion->x * magSqInv;
	p_destination->y = p_quaternion->y * magSqInv;
	p_destination->z = p_quaternion->z * magSqInv;
	p_destination->w = p_quaternion->w * magSqInv;

	return p_destination;
}

inline struct SmlQuat* smlQuatNormalizeUnchecked(struct SmlQuat const *const p_quaternion, struct SmlQuat *const p_destination) {
	float const magInv = 1.0f / smlQuatMagnitude(p_quaternion);

	p_destination->x = p_quaternion->x * magInv;
	p_destination->y = p_quaternion->y * magInv;
	p_destination->z = p_quaternion->z * magInv;
	p_destination->w = p_quaternion->w * magInv;

	return p_destination;
}

inline struct SmlQuat* smlQuatFromAngle3d(float const p_x, float const p_y, float const p_z, struct SmlQuat *const p_destination) {
	float const cx = cosf(p_x * 0.5f);
	float const sx = sinf(p_x * 0.5f);
	float const cy = cosf(p_y * 0.5f);
	float const sy = sinf(p_y * 0.5f);
	float const cz = cosf(p_z * 0.5f);
	float const sz = sinf(p_z * 0.5f);

	// `x`-`y`-`z` rotation:
	p_destination->w = cx * cy * cz + sx * sy * sz;
	p_destination->x = sx * cy * cz - cx * sy * sz;
	p_destination->y = cx * sy * cz + sx * cy * sz;
	p_destination->z = cx * cy * sz - sx * sy * cz;

	return p_destination;
}

inline struct SmlQuat* smlQuatScale(struct SmlQuat const *const p_quaternion, float const p_scalar, struct SmlQuat *const p_destination) {
	smlQuatNormalize(p_quaternion, p_destination);
	return smlQuatMultScalar(p_quaternion, p_scalar, p_destination);
}

inline struct SmlQuat* smlQuatSet(struct SmlQuat *const p_quaternion, float const p_x, float const p_y, float const p_z, float const p_w) {
	p_quaternion->x = p_x;
	p_quaternion->y = p_y;
	p_quaternion->z = p_z;
	p_quaternion->w = p_w;
	return p_quaternion;
}

inline struct SmlQuat* smlQuatMultScalar(struct SmlQuat const *const p_quaternion, float const p_scalar, struct SmlQuat *const p_destination) {
	p_destination->x *= p_scalar;
	p_destination->y *= p_scalar;
	p_destination->z *= p_scalar;
	p_destination->w *= p_scalar;

	return p_destination;
}

inline struct SmlQuat* smlQuatFromAxisAngle(struct SmlVec3 const *const p_axisVector, float const p_angle, struct SmlQuat *const p_destination) {
	float const sinHalf = sinf(p_angle * 0.5f);

	// I pray for this to be vectorized in loops...
	p_destination->x = p_axisVector->x * sinHalf;
	p_destination->y = p_axisVector->y * sinHalf;
	p_destination->z = p_axisVector->z * sinHalf;
	p_destination->w = cosf(p_angle * 0.5f);

	return p_destination;
}

inline struct SmlQuat* smlQuatScaleUnchecked(struct SmlQuat const *const p_quaternion, float const p_scalar, struct SmlQuat *const p_destination) {
	smlQuatNormalizeUnchecked(p_quaternion, p_destination);
	return smlQuatMultScalar(p_quaternion, p_scalar, p_destination);
}

inline struct SmlQuat* smlQuatAdd(struct SmlQuat const *const p_first, struct SmlQuat const *const p_second, struct SmlQuat *const p_destination) {
	p_destination->x = p_first->x + p_second->x;
	p_destination->y = p_first->y + p_second->y;
	p_destination->z = p_first->z + p_second->z;
	p_destination->w = p_first->w + p_second->w;

	return p_destination;
}

inline struct SmlQuat* smlQuatSub(struct SmlQuat const *const p_first, struct SmlQuat const *const p_second, struct SmlQuat *const p_destination) {
	p_destination->x = p_first->x - p_second->x;
	p_destination->y = p_first->y - p_second->y;
	p_destination->z = p_first->z - p_second->z;
	p_destination->w = p_first->w - p_second->w;

	return p_destination;
}

inline struct SmlQuat* smlQuatMult(struct SmlQuat const *const p_first, struct SmlQuat const *const p_second, struct SmlQuat *const p_destination) {
	p_destination->x = p_first->w * p_second->x + p_first->x * p_second->w + p_first->y * p_second->z - p_first->z * p_second->y;
	p_destination->y = p_first->w * p_second->y + p_first->y * p_second->w + p_first->z * p_second->x - p_first->x * p_second->z;
	p_destination->z = p_first->w * p_second->z + p_first->z * p_second->w + p_first->x * p_second->y - p_first->y * p_second->x;
	p_destination->w = p_first->w * p_second->w - p_first->x * p_second->x - p_first->y * p_second->y - p_first->z * p_second->z;

	return p_destination;
}

inline struct SmlVec3* smlQuatRotateVector3d(struct SmlQuat const *const p_quaternion, struct SmlVec3 *const p_vector, struct SmlVec3 *const p_destination) {
	struct SmlQuat quatVec = {

		.x = p_vector->x,
		.y = p_vector->y,
		.z = p_vector->z,
		.w = 0.0f

	};

	struct SmlQuat conj = { 0 };
	smlQuatConjugate(p_quaternion, &conj);

	smlQuatMult(p_quaternion, &quatVec, &quatVec); // First mult, `q * v`,
	smlQuatMult(&quatVec, &conj, &quatVec);        // Second mult, `q * v * (q ^ -1)`.

	p_destination->x = quatVec.x;
	p_destination->y = quatVec.y;
	p_destination->z = quatVec.z;

	return p_destination;
}

inline struct SmlVec2* smlQuatRotateVector2d(struct SmlQuat const *const p_quaternion, struct SmlVec2 *const p_vector, struct SmlVec2 *const p_destination) {
	struct SmlQuat conj = { 0 };
	smlQuatConjugate(p_quaternion, &conj);

	struct SmlQuat quatVec2d = { // Convert vector to quaternion (`w = 0`!).

		.x = p_vector->x,
		.y = p_vector->y,
		.z = 0.0f,
		.w = 0.0f,

	};

	// Quaternion multiplication, `p_quaternion * quatVec2d * conj`:
	smlQuatMult(p_quaternion, &quatVec2d, &quatVec2d); // DO NOT change the order! This is #1.
	smlQuatMult(&quatVec2d, &conj, &quatVec2d); // DO NOT change the order! This is #2.

	p_destination->x = quatVec2d.x;
	p_destination->y = quatVec2d.y;

	return p_destination;
}

inline struct SmlQuat* smlQuatLerp(struct SmlQuat const *const p_source, struct SmlQuat const *const p_target, float const p_amount, struct SmlQuat *const p_destination) {
	p_destination->x = p_source->x + p_amount * (p_target->x - p_source->x);
	p_destination->y = p_source->y + p_amount * (p_target->y - p_source->y);
	p_destination->z = p_source->z + p_amount * (p_target->z - p_source->z);
	p_destination->w = p_source->w + p_amount * (p_target->w - p_source->w);

	return p_destination;
}

inline struct SmlQuat* smlQuatSlerp(struct SmlQuat const *const p_source, struct SmlQuat const *const p_target, float const p_amount, struct SmlQuat *const p_destination) {
	float dot = smlQuatDot(p_source, p_target);

	// If dot product is negative, take the long way around (flip target):
	struct SmlQuat target;
	if (unlikely(dot < 0.0f)) {

		dot = -dot;
		target.x = -p_target->x;
		target.y = -p_target->y;
		target.z = -p_target->z;
		target.w = -p_target->w;

	}
	else {

		target = *p_target;

	}

	// If the quaternions are too close, fallback to an n-lerp:
	// if (unlikely(dot > 0.9995f)) {
	// 	return smlQuatNlerp(p_source, &target, p_amount, p_destination);
	// }

	// S-lerp formula:
	float const theta = acosf(dot);
	float const sinTheta = sinf(theta);
	float const sinThetaInv = 1.0f / sinTheta;

	float const mixTarget = sinf(p_amount * theta) * sinThetaInv;
	float const mixSource = sinf((1.0f - p_amount) * theta) * sinThetaInv;

	p_destination->x = mixSource * p_source->x + mixTarget * target.x;
	p_destination->y = mixSource * p_source->y + mixTarget * target.y;
	p_destination->z = mixSource * p_source->z + mixTarget * target.z;
	p_destination->w = mixSource * p_source->w + mixTarget * target.w;

	return p_destination;
}

inline struct SmlQuat* smlQuatNlerp(struct SmlQuat const *const p_source, struct SmlQuat const *const p_target, float const p_amount, struct SmlQuat *const p_destination) {
	smlQuatLerp(p_source, p_target, p_amount, p_destination);
	smlQuatNormalize(p_destination, p_destination);
	return p_destination;
}

inline struct SmlQuat* smlQuatSlerpUnchecked(struct SmlQuat const *const p_source, struct SmlQuat const *const p_target, float const p_amount, struct SmlQuat *const p_destination) {
	float dot = smlQuatDot(p_source, p_target);

	// S-lerp formula:
	float const theta = acosf(dot);
	float const sinTheta = sinf(theta);
	float const mixTarget = sinf(p_amount * theta) / sinTheta;
	float const mixSource = sinf((1.0f - p_amount) * theta) / sinTheta;

	p_destination->x = mixSource * p_source->x + mixTarget * p_target->x;
	p_destination->y = mixSource * p_source->y + mixTarget * p_target->y;
	p_destination->z = mixSource * p_source->z + mixTarget * p_target->z;
	p_destination->w = mixSource * p_source->w + mixTarget * p_target->w;

	return p_destination;
}
