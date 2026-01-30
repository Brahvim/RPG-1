#include "Sml.h"
#include <math.h>
#include "Macros.h"

inline float smlVec2Direction(struct SmlVec2 const *p_vector) {
	return atan2f(p_vector->y, p_vector->x);
}

inline float smlVec2Magnitude(struct SmlVec2 const *p_vector) {
	return __builtin_sqrtf(smlVec2MagnitudeSquared(p_vector));
}

inline struct SmlVec2* smlVec2One(struct SmlVec2 *const p_vector) {
	p_vector->x = 1;
	p_vector->y = 1;
	return p_vector;
}

inline struct SmlVec2* smlVec2Zero(struct SmlVec2 *const p_vector) {
	p_vector->x = 0;
	p_vector->y = 0;
	return p_vector;
}

inline float smlVec2MagnitudeSquared(struct SmlVec2 const *p_vector) {
#define S(x) x * x
	return S(p_vector->x) + S(p_vector->y);
#undef S
}

inline struct SmlVec2* smlVec2FromAngle(float const p_angle, struct SmlVec2 *p_vector) {
	p_vector->x = cosf(p_angle);
	p_vector->y = sinf(p_angle);
	return p_vector;
}

inline float smlVec2Dot(struct SmlVec2 const *const p_first, struct SmlVec2 const *const p_second) {
	return p_first->x * p_second->x + p_first->y * p_second->y;
}

inline struct SmlVec2* smlVec2Set(struct SmlVec2 *const p_vector, float const p_x, float const p_y) {
	p_vector->x = p_x;
	p_vector->y = p_y;
	return p_vector;
}

inline struct SmlVec2* smlVec2Normalize(struct SmlVec2 const *p_vector, struct SmlVec2 *const p_destination) {
	float mag = smlVec2MagnitudeSquared(p_vector);
	mag = mag == 0.0 ? 1 : __builtin_sqrtf(mag);
	float const magInv = 1.0f / mag;
	p_destination->x = p_vector->x * magInv;
	p_destination->y = p_vector->y * magInv;
	return p_destination;
}

inline struct SmlVec2* smlVec2NormalizeUnchecked(struct SmlVec2 const *p_vector, struct SmlVec2 *const p_destination) {
	float const mag = smlVec2MagnitudeSquared(p_vector); // Are all compoents in registers? Dunno, so we cache this.
	float const magInv = 1.0f / mag;
	p_destination->x = p_vector->x * magInv;
	p_destination->y = p_vector->y * magInv;
	return p_destination;
}

inline struct SmlVec2* smlVec2Mult(struct SmlVec2 const *const p_vector, float const p_scalar, struct SmlVec2 *const p_destination) {
	p_destination->x = p_vector->x * p_scalar;
	p_destination->y = p_vector->y * p_scalar;
	return p_destination;
}

inline struct SmlVec2* smlVec2Scale(struct SmlVec2 const *const p_vector, float const p_scalar, struct SmlVec2 *const p_destination) {
	smlVec2Normalize(p_vector, p_destination);
	return smlVec2Mult(p_vector, p_scalar, p_destination);
}

inline struct SmlVec2* smlVec2ScaleUnchecked(struct SmlVec2 *const p_vector, float const p_scalar, struct SmlVec2 *const p_destination) {
	smlVec2NormalizeUnchecked(p_vector, p_destination);
	return smlVec2Mult(p_vector, p_scalar, p_destination);
}

inline struct SmlVec2* smlVec2Add(struct SmlVec2 const *const p_first, struct SmlVec2 const *const p_second, struct SmlVec2 *const p_destination) {
	p_destination->x = p_first->x + p_second->x;
	p_destination->y = p_first->y + p_second->y;
	return p_destination;
}

inline struct SmlVec2* smlVec2Sub(struct SmlVec2 const *const p_first, struct SmlVec2 const *const p_second, struct SmlVec2 *const p_destination) {
	p_destination->x = p_first->x - p_second->x;
	p_destination->y = p_first->y - p_second->y;
	return p_destination;
}

/* Remember, this always returns a 3D vector! */
inline struct SmlVec3* smlVec2Cross(struct SmlVec2 const *const p_first, struct SmlVec2 const *const p_second, struct SmlVec3 *const p_destination) {
	p_destination->x = p_destination->y = 0;
	p_destination->z = p_first->x * p_second->y - p_first->y * p_second->x;
	return p_destination;
}
