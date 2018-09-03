/*
 * linmath_test.h
 *
 *  Created on: Apr 9, 2017
 *      Author: dizcza
 */

#ifndef LINMATH_H_LINMATH_TEST_H_
#define LINMATH_H_LINMATH_TEST_H_

#include "linmath.h"

#ifndef assert_expr
#define assert_expr(expr) ((expr) ? (void)0U : assert_expr_failed((uint8_t *)__FILE__, __LINE__))
void assert_expr_failed(uint8_t* file, uint32_t line);
#endif /* assert_expr */

#define LINMATH_TEST_M(n) \
static inline uint8_t vec##n##_equal(vec##n const a, vec##n const b) { \
	uint8_t i, equal = 1U; \
	for(i = 0; i < n; ++i) \
		equal &= (fabsf(a[i] - b[i]) < LINMATH_EPS); \
	return equal; \
} \
static inline uint8_t mat##n##x##n##_equal(mat##n##x##n const M, mat##n##x##n const N) { \
	uint8_t i, equal = 1U; \
	for (i = 0; i < n; ++i) \
		equal &= vec##n##_equal(M[i], N[i]); \
	return equal; \
}

LINMATH_TEST_M(3);
LINMATH_TEST_M(4);

static inline void Linmath_TestQuatMat4() {
	quat q;
	vec3 axis = { 0, 1, 0 };
	float degrees = 15;
	quat_rotate(q, LINMATH_DEGREES_TO_RADS(degrees), axis);
	mat4x4 m_ident, m_rotated, m;
	mat4x4_identity(m_ident);
	mat4x4o_mul_quat(m_rotated, m_ident, q);
	quat_rotate(q, LINMATH_DEGREES_TO_RADS(-degrees), axis);
	mat4x4o_mul_quat(m, m_rotated, q);
	uint8_t eq = mat4x4_equal(m_ident, m);
	assert_expr(eq);
}

static inline void Linmath_TestQuatVec3() {
	quat q;
	vec3 axis = { 1, 1, -1 };
	float degrees = 139.27f;
	quat_rotate(q, LINMATH_DEGREES_TO_RADS(degrees), axis);
	const vec3 v_ref = { 23.12f, 0.89f, -6.23f };
	vec3 v;
	vec3_dup(v, v_ref);
	quat_mul_vec3(v, q, v);
	quat_rotate(q, LINMATH_DEGREES_TO_RADS(-degrees), axis);
	quat_mul_vec3(v, q, v);
	uint8_t eq = vec3_equal(v_ref, v);
	assert_expr(eq);
}

static inline void Linmath_RunTests() {
	Linmath_TestQuatVec3();
}

#endif /* LINMATH_H_LINMATH_TEST_H_ */
