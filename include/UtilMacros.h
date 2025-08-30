#pragma once

#define likely(p_condition) __builtin_expect((long) (p_condition), 1)
#define unlikely(p_condition) __builtin_expect((long) (p_condition), 0)
