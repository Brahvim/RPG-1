#include "Sml.h"
#include <math.h>
#include "Macros.h"

inline float smlVec3Direction2d(struct SmlVec3* p_vector) {
	return atan2f(p_vector->y, p_vector->x);
}

inline float smlVec3Magnitude(struct SmlVec3 const *p_vector) {
	return __builtin_sqrtf(smlVec3MagnitudeSquared(p_vector));
}

inline struct SmlVec3* smlVec3One(struct SmlVec3 *const p_vector) {
	p_vector->x = 1;
	p_vector->y = 1;
	p_vector->z = 1;
	return p_vector;
}

inline struct SmlVec3* smlVec3Zero(struct SmlVec3 *const p_vector) {
	p_vector->x = 0;
	p_vector->y = 0;
	p_vector->z = 0;
	return p_vector;
}

inline float smlVec3MagnitudeSquared(struct SmlVec3 const *p_vector) {
#define S(x) x * x
	return S(p_vector->x) + S(p_vector->y) + S(p_vector->z);
#undef S
}

inline struct SmlVec3* smlVec3FromAngle2d(struct SmlVec3 *const p_vector, float const p_angle) {
	p_vector->x = cosf(p_angle);
	p_vector->y = sinf(p_angle);
	p_vector->z = 0;
	return p_vector;
}

inline float smlVec3Dot(struct SmlVec3 const *const p_first, struct SmlVec3 const *const p_second) {
	return p_first->x * p_second->x + p_first->y * p_second->y + p_first->z * p_second->z;
}

inline struct SmlVec3* smlVec3Normalize(struct SmlVec3 const *p_vector, struct SmlVec3 *const p_destination) {
	float mag = smlVec3MagnitudeSquared(p_vector);
	mag = mag == 0.0 ? 1 : __builtin_sqrtf(mag);

	float const magInv = 1.0f / mag;
	p_destination->x = p_vector->x * magInv;
	p_destination->y = p_vector->y * magInv;
	p_destination->z = p_vector->z * magInv;
	return p_destination;
}

inline struct SmlVec3* smlVec3Set(struct SmlVec3 *const p_vector, float const p_x, float const p_y, float const p_z) {
	p_vector->x = p_x;
	p_vector->y = p_y;
	p_vector->z = p_z;
	return p_vector;
}

inline struct SmlVec3* smlVec3NormalizeUnchecked(struct SmlVec3 const *p_vector, struct SmlVec3 *const p_destination) {
	float const magInv = 1.0f / smlVec3Magnitude(p_vector);

	p_destination->x = p_vector->x * magInv;
	p_destination->y = p_vector->y * magInv;
	p_destination->z = p_vector->z * magInv;
	return p_destination;
}

inline struct SmlVec3* smlVec3Scale(struct SmlVec3 *const p_vector, float const p_scalar, struct SmlVec3 *const p_destination) {
	smlVec3Normalize(p_vector, p_destination);
	return smlVec3Mult(p_vector, p_scalar, p_destination);
}

inline struct SmlVec3* smlVec3ScaleUnchecked(struct SmlVec3 *const p_vector, float p_scalar, struct SmlVec3 *const p_destination) {
	smlVec3NormalizeUnchecked(p_vector, p_destination);
	return smlVec3Mult(p_vector, p_scalar, p_destination);
}

inline struct SmlVec3* smlVec3FromAngle3d(float const x, float const y, float const z, struct SmlVec3 *const p_destination) {
	float const cosPitch = cosf(y);

	p_destination->x = cosf(x) * cosPitch;
	p_destination->y = sinf(y);
	p_destination->z = sinf(x) * cosPitch;
	return p_destination;
}

inline struct SmlVec3* smlVec3Mult(struct SmlVec3 const *const p_vector, float const p_scalar, struct SmlVec3 *const p_destination) {
	p_destination->x = p_scalar * p_vector->x;
	p_destination->y = p_scalar * p_vector->y;
	p_destination->z = p_scalar * p_vector->z;
	return p_destination;
}

inline struct SmlVec3* smlVec3Add(struct SmlVec3 const *const p_first, struct SmlVec3 const *const p_second, struct SmlVec3 *const p_destination) {
	p_destination->x = p_first->x + p_second->x;
	p_destination->y = p_first->y + p_second->y;
	p_destination->z = p_first->z + p_second->z;
	return p_destination;
}

inline struct SmlVec3* smlVec3Sub(struct SmlVec3 const *const p_first, struct SmlVec3 const *const p_second, struct SmlVec3 *const p_destination) {
	p_destination->x = p_first->x - p_second->x;
	p_destination->y = p_first->y - p_second->y;
	p_destination->z = p_first->z - p_second->z;
	return p_destination;
}

inline struct SmlVec3* smlVec3Cross(struct SmlVec3 const *const p_first, struct SmlVec3 const *const p_second, struct SmlVec3 *const p_destination) {
	p_destination->x = p_first->y * p_second->z - p_first->z * p_second->y;
	p_destination->y = p_first->z * p_second->x - p_first->x * p_second->z;
	p_destination->z = p_first->x * p_second->y - p_first->y * p_second->x;
	return p_destination;
}
