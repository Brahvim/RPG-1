#pragma once

#pragma region Macros.
#define SML_PI 3.141592653589793
#define SML_TAU 6.283185307179586
#define SML_PI_HALF 1.5707963267948966
#define SML_PI_THIRD 1.0471975511965976
#define SML_PI_QUART 0.7853981633974483

#define SML_180_OVER_PI 57.29577951308232
#define SML_PI_OVER_180 0.017453292519943

// 12.5%
#define SML_PI_EIGHTH 0.39269908169872

// 6.25%
#define SML_PI_SIXTEENTH 0.19634954084936

// 66.666666%
#define SML_PI_TWO_THIRDS 2.09439510239319

// 75%
#define SML_PI_THREE_FOURTHS 2.35619449019234

#define SML_DEGREES(radians) SML_180_OVER_PI * (radians)
#define SML_RADIANS(degrees) SML_PI_OVER_180 * (degrees)
#pragma endregion

#pragma region Structures.
struct SmlVec2 {

	union {

		float data[2];
		struct { float x, y; };
		struct { float i, j; };
		struct { float u, v; };
		struct { float h, s; };

	};

};

struct SmlVec3 {

	union {

		float data[3];

		struct {

			union {

				struct SmlVec2 vec2;
				struct { float x, y; };
				struct { float i, j; };
				struct { float r, g; };
				struct { float h, s; };

			};

			union {

				float z;
				float k;
				float b;
				float v;

			};

		};

	};

};

struct SmlQuat {

	union {

		float data[4];

		struct {

			union {

				struct SmlVec3 vec3;

				union {

					struct {

						union {

							struct SmlVec2 vec2;
							struct { float x, y; };
							struct { float i, j; };
							struct { float r, g; };
							struct { float h, s; };

						};

						union {

							float z;
							float k;
							float b;
							float v;

						};

					};

				};

			};

			union { float a; float l; float w; };

		};


	};

};

// Matrices in **text** are row-major!: ***Rows*** are *stretched-out*!:

struct SmlMat22 {

	union {

		struct {

			struct SmlVec2 xy;
			struct SmlVec2 zw;

		};

		struct {

			union { struct SmlVec2 col1; struct { float c11, c21; }; };
			union { struct SmlVec2 col2; struct { float c12, c22; }; };

		};

		struct {

			union { struct SmlVec2 row1; struct { float x, y; }; struct { float r11, r12; }; };
			union { struct SmlVec2 row2; struct { float z, w; }; struct { float r21, r22; }; };

		};

		float one[4];

		float two[2][2];

		struct SmlQuat quat;

	};

};

struct SmlMat33 {

	union {

		struct {

			union { struct SmlVec3 col1; struct { float c11, c21, c31; }; };
			union { struct SmlVec3 col2; struct { float c12, c22, c32; }; };
			union { struct SmlVec3 col3; struct { float c13, c23, c33; }; };

		};

		struct {

			union { struct SmlVec3 row1; struct { float r11, r12, r13; }; };
			union { struct SmlVec3 row2; struct { float r21, r22, r23; }; };
			union { struct SmlVec3 row3; struct { float r31, r32, r33; }; };

		};

		float one[9];

		float two[3][3];

		struct SmlMat22 mat22;

	};

};

struct SmlMat44 {

	union {

		// Col-quats:
		struct { struct SmlQuat col1, col2, col3, col4; };

		// Row-quats:
		struct { struct SmlQuat row1, row2, row3, row4; };

		// Col-floats:
		struct {

			float c11, c21, c31, c41;
			float c12, c22, c32, c42;
			float c13, c23, c33, c43;
			float c14, c24, c34, c44;

		};

		// Row-floats:
		struct {

			float r11, r12, r13, r14;
			float r21, r22, r23, r24;
			float r31, r32, r33, r34;
			float r41, r42, r43, r44;

		};

		float one[16];

		float two[4][4];

		struct SmlMat33 mat33;

	};

};
#pragma endregion

#pragma region From-array.
// Copier functions!:
struct SmlVec2 smlVec2(float const *const array);
struct SmlVec3 smlVec3(float const *const array);
struct SmlQuat smlQuat(float const *const array);
struct SmlMat22 smlMat22(float const *const array);
struct SmlMat33 smlMat33(float const *const array);
struct SmlMat44 smlMat44(float const *const array);

char smlFloatCompareFltEpsilon(float const first, float const second);
char smlFloatCompare(float const first, float const second, float epsilon);
#pragma endregion

#pragma region 2 * 2 Matrices.
#define smlMat22Val(...) ((struct SmlMat22) { __VA_ARGS__ })
#define smlMat22Ptr(...) ((struct SmlMat22*) { __VA_ARGS__ })

float smlMat22Determinant(struct SmlMat22 const *const matrix);
struct SmlMat22* smlMat22AdjugateSame(struct SmlMat22 *const matrix);
struct SmlMat22* smlMat22SwapMajority(struct SmlMat22 *const matrix);
struct SmlMat22* smlMat22Identity(struct SmlMat22 *const destination);
float smlMat22Invert(struct SmlMat22 const *const matrix, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22Adjugate(struct SmlMat22 *const matrix, struct SmlMat22 *const destination);
float smlMat22InvertUnchecked(struct SmlMat22 const *const matrix, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22Copy(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination);
struct SmlMat22* smlMat22Cofactors(struct SmlMat22 const* const matrix, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22SwapMajorityToNew(struct SmlMat22 *const matrix, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22AddScalar(struct SmlMat22 const *const matrix, float const scalar, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22DivScalar(struct SmlMat22 const *const matrix, float const scalar, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22SubScalar(struct SmlMat22 const *const matrix, float const scalar, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22MultScalar(struct SmlMat22 const *const matrix, float const scalar, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22Add(struct SmlMat22 const *const first, struct SmlMat22 const *const second, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22Sub(struct SmlMat22 const *const first, struct SmlMat22 const *const second, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22Mult(struct SmlMat22 const *const first, struct SmlMat22 const *const second, struct SmlMat22 *const destination);
struct SmlVec2* smlMat22MultVec2(struct SmlMat22 const *const matrix, struct SmlVec2 const *const vector2, struct SmlVec2 *const destination);
struct SmlMat22* smlMat22DivMembers(struct SmlMat22 const *const first, struct SmlMat22 const *const second, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22MultMembers(struct SmlMat22 const *const first, struct SmlMat22 const *const second, struct SmlMat22 *const destination);
struct SmlMat22* smlMat22InvertGivenInvertedDeterminant(struct SmlMat22 const *const matrix, struct SmlMat22 *const destination, float invertedDeterminant);
#pragma endregion

#pragma region 3 * 3 Matrices.
#define smlMat33Val(...) ((struct SmlMat33) { __VA_ARGS__ })
#define smlMat33Ptr(...) ((struct SmlMat33*) { __VA_ARGS__ })

float smlMat33Determinant(struct SmlMat33 const *const matrix);
struct SmlMat33* smlMat33AdjugateSame(struct SmlMat33 *const matrix);
struct SmlMat33* smlMat33SwapMajority(struct SmlMat33 *const matrix);
struct SmlMat33* smlMat33Identity(struct SmlMat33 *const destination);
struct SmlMat33* smlMat33ShearXY(struct SmlMat33 *const matrix, float const shear);
struct SmlMat33* smlMat33ShearXZ(struct SmlMat33 *const matrix, float const shear);
struct SmlMat33* smlMat33ShearYZ(struct SmlMat33 *const matrix, float const shear);
struct SmlMat33* smlMat33RotateX(struct SmlMat33 *const matrix, float const angle);
struct SmlMat33* smlMat33RotateY(struct SmlMat33 *const matrix, float const angle);
struct SmlMat33* smlMat33RotateZ(struct SmlMat33 *const matrix, float const angle);
float smlMat33Invert(struct SmlMat33 const *const matrix, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33Adjugate(struct SmlMat33 *const matrix, struct SmlMat33 *const destination);
float smlMat33InvertUnchecked(struct SmlMat33 const *const matrix, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33Copy(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination);
struct SmlMat33* smlMat33Cofactors(struct SmlMat33 const* const matrix, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33SwapMajorityToNew(struct SmlMat33 *const matrix, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33AddScalar(struct SmlMat33 const *const matrix, float const scalar, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33DivScalar(struct SmlMat33 const *const matrix, float const scalar, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33SubScalar(struct SmlMat33 const *const matrix, float const scalar, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33MultScalar(struct SmlMat33 const *const matrix, float const scalar, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33Sub(struct SmlMat33 const *const first, struct SmlMat33 const *const second, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33Add(struct SmlMat33 const *const first, struct SmlMat33 const *const second, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33Mult(struct SmlMat33 const *const first, struct SmlMat33 const *const second, struct SmlMat33 *const destination);
struct SmlVec3* smlMat33MultVec3(struct SmlMat33 const *const matrix, struct SmlVec3 const *const vector3, struct SmlVec3 *const destination);
struct SmlMat33* smlMat33DivMembers(struct SmlMat33 const *const first, struct SmlMat33 const *const second, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33MultMembers(struct SmlMat33 const *const first, struct SmlMat33 const *const second, struct SmlMat33 *const destination);
struct SmlMat33* smlMat33InvertGivenInvertedDeterminant(struct SmlMat33 const *const matrix, struct SmlMat33 *const destination, float invertedDeterminant);
#pragma endregion

#pragma region 4 * 4 Matrices.
#define smlMat44Val(...) ((struct SmlMat44) { __VA_ARGS__ })
#define smlMat44Ptr(...) ((struct SmlMat44*) { __VA_ARGS__ })

float smlMat44Determinant(struct SmlMat44 const *const matrix);
struct SmlMat44* smlMat44AdjugateSame(struct SmlMat44 *const matrix);
struct SmlMat44* smlMat44SwapMajority(struct SmlMat44 *const matrix);
struct SmlMat44* smlMat44Identity(struct SmlMat44 *const destination);
float smlMat44Invert(struct SmlMat44 const *const matrix, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44RotateQuat(struct SmlMat44 const *const matrix, struct SmlQuat *const quat);
struct SmlMat44* smlMat44Adjugate(struct SmlMat44 *const matrix, struct SmlMat44 *const destination);
float smlMat44InvertUnchecked(struct SmlMat44 const *const matrix, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44Copy(struct SmlMat44 const *const p_matrix, struct SmlMat44 *const p_destination);
struct SmlMat44* smlMat44Cofactors(struct SmlMat44 const* const matrix, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44SwapMajorityToNew(struct SmlMat44 *const matrix, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44AddScalar(struct SmlMat44 const *const matrix, float const scalar, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44DivScalar(struct SmlMat44 const *const matrix, float const scalar, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44SubScalar(struct SmlMat44 const *const matrix, float const scalar, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44MultScalar(struct SmlMat44 const *const matrix, float const scalar, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44Add(struct SmlMat44 const *const first, struct SmlMat44 const *const second, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44Sub(struct SmlMat44 const *const first, struct SmlMat44 const *const second, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44Mult(struct SmlMat44 const *const first, struct SmlMat44 const *const second, struct SmlMat44 *const destination);
struct SmlQuat* smlMat44MultVec4(struct SmlMat44 const *const matrix, struct SmlQuat const *const vector4, struct SmlQuat *const destination);
struct SmlMat44* smlMat44DivMembers(struct SmlMat44 const *const first, struct SmlMat44 const *const second, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44MultMembers(struct SmlMat44 const *const first, struct SmlMat44 const *const second, struct SmlMat44 *const destination);
struct SmlMat44* smlMat44InvertGivenInvertedDeterminant(struct SmlMat44 const *const matrix, struct SmlMat44 *const destination, float invertedDeterminant);
#pragma endregion

#pragma region Two-dimensional vectors.
#define smlVec2Val(...) ((struct SmlVec2) { __VA_ARGS__ })
#define smlVec2Ptr(...) ((struct SmlVec2*) { __VA_ARGS__ })

float smlVec2Direction(struct SmlVec2 const *vector);
float smlVec2Magnitude(struct SmlVec2 const *vector);
struct SmlVec2* smlVec2One(struct SmlVec2 *const vector);
struct SmlVec2* smlVec2Zero(struct SmlVec2 *const vector);
float smlVec2MagnitudeSquared(struct SmlVec2 const *vector);
struct SmlVec2* smlVec2Set(struct SmlVec2 *const vector, float x, float y);
struct SmlVec2* smlVec2FromAngle(float const angle, struct SmlVec2 *vector);
float smlVec2Dot(struct SmlVec2 const *const first, struct SmlVec2 const *const second);
struct SmlVec2* smlVec2Normalize(struct SmlVec2 const *vector, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2NormalizeUnchecked(struct SmlVec2 const *vector, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Mult(struct SmlVec2 const *const vector, float const scalar, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Scale(struct SmlVec2 const *const vector, float const scalar, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2ScaleUnchecked(struct SmlVec2 *const vector, float const scalar, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Add(struct SmlVec2 const *const first, struct SmlVec2 const *const second, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Sub(struct SmlVec2 const *const first, struct SmlVec2 const *const second, struct SmlVec2 *const destination);
struct SmlVec3* smlVec2Cross(struct SmlVec2 const *const first, struct SmlVec2 const *const second, struct SmlVec3 *const destination);
#pragma endregion

#pragma region Three-dimensional vectors.
#define smlVec3Val(...) ((struct SmlVec3) { __VA_ARGS__ })
#define smlVec3Ptr(...) ((struct SmlVec3*) { __VA_ARGS__ })

float smlVec3Direction2d(struct SmlVec3* vector);
float smlVec3Magnitude(struct SmlVec3 const *vector);
struct SmlVec3* smlVec3One(struct SmlVec3 *const vector);
struct SmlVec3* smlVec3Zero(struct SmlVec3 *const vector);
float smlVec3MagnitudeSquared(struct SmlVec3 const *vector);
struct SmlVec3* smlVec3FromAngle2d(struct SmlVec3 *const vector, float const angle);
float smlVec3Dot(struct SmlVec3 const *const first, struct SmlVec3 const *const second);
struct SmlVec3* smlVec3Normalize(struct SmlVec3 const *vector, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Set(struct SmlVec3 *const vector, float const x, float const y, float const z);
struct SmlVec3* smlVec3NormalizeUnchecked(struct SmlVec3 const *vector, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Scale(struct SmlVec3 *const vector, float const scalar, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3FromAngle3d(float const x, float const y, float const z, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3ScaleUnchecked(struct SmlVec3 *const vector, float scalar, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Mult(struct SmlVec3 const *const vector, float const scalar, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Add(struct SmlVec3 const *const first, struct SmlVec3 const *const second, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Sub(struct SmlVec3 const *const first, struct SmlVec3 const *const second, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Cross(struct SmlVec3 const *const first, struct SmlVec3 const *const second, struct SmlVec3 *const destination);
#pragma endregion

#pragma region Quaternions (four-dimensional vectors!).
#define smlQuatVal(...) ((struct SmlQuat) { __VA_ARGS__ })
#define smlQuatPtr(...) ((struct SmlQuat*) { __VA_ARGS__ })

float smlQuatMagnitude(struct SmlQuat const *const quaternion);
struct SmlQuat* smlQuatIdentity(struct SmlQuat *const destination);
float smlQuatMagnitudeSquared(struct SmlQuat const *const quaternion);
float smlQuatDot(struct SmlQuat const *const first, struct SmlQuat const *const second);
struct SmlQuat* smlQuatInvert(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlVec3* smlQuatToEuler(struct SmlQuat const *const quaternion, struct SmlVec3 * const destination);
struct SmlMat33* smlQuatToMatrix33(struct SmlQuat const *const source, struct SmlMat33 *const destination); // Rotation only!
struct SmlMat44* smlQuatToMatrix44(struct SmlQuat const *const source, struct SmlMat44 *const destination); // Complete transforms only!
struct SmlQuat* smlQuatConjugate(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlQuat* smlQuatNormalize(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlQuat* smlQuatNormalizeUnchecked(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlQuat* smlQuatSet(struct SmlQuat *const quaternion, float const x, float const y, float const z, float const w);
struct SmlQuat* smlQuatScale(struct SmlQuat const *const quaternion, float const scalar, struct SmlQuat *const destination);
struct SmlQuat* smlQuatMultScalar(struct SmlQuat const *const first, float const scalar, struct SmlQuat *const destination);
struct SmlQuat* smlQuatFromAxisAngle(struct SmlVec3 const *const axisVector, float const angle, struct SmlQuat *const destination);
struct SmlQuat* smlQuatScaleUnchecked(struct SmlQuat const *const quaternion, float const scalar, struct SmlQuat *const destination);
struct SmlQuat* smlQuatAdd(struct SmlQuat const *const first, struct SmlQuat const *const second, struct SmlQuat *const destination);
struct SmlQuat* smlQuatSub(struct SmlQuat const *const first, struct SmlQuat const *const second, struct SmlQuat *const destination);
struct SmlQuat* smlQuatMult(struct SmlQuat const *const first, struct SmlQuat const *const second, struct SmlQuat *const destination);
struct SmlVec3* smlQuatRotateVector3d(struct SmlQuat const *const quaternion, struct SmlVec3 *const vector, struct SmlVec3 *const destination);
struct SmlVec2* smlQuatRotateVector2d(struct SmlQuat const *const quaternion, struct SmlVec2 *const vector, struct SmlVec2 *const destination); // ???
struct SmlQuat* smlQuatLerp(struct SmlQuat const *const source, struct SmlQuat const *const target, float const amount, struct SmlQuat *const destination);
struct SmlQuat* smlQuatSlerp(struct SmlQuat const *const source, struct SmlQuat const *const target, float const amount, struct SmlQuat *const destination);
struct SmlQuat* smlQuatNlerp(struct SmlQuat const *const source, struct SmlQuat const *const target, float const amount, struct SmlQuat *const destination);
#pragma endregion
