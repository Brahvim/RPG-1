#pragma once

// The syntax for `foru()` sucks because you have to use `,`s over `;`s!
// Can't make loops with multiple variable declarations that way...!
// This is "solved" with the Espressif-style macros below!

#define switchl(p_condition, p_likelyBranch) switch (__builtin_expect((long) (p_condition), p_likelyBranch))

// Espressif-style!:

#define unlikely(p_condition) (__builtin_expect((long) (p_condition), 0))
#define likely(p_condition) (__builtin_expect((long) (p_condition), 0))

#define whileu(p_condition) while (unlikely(p_condition))
#define whilel(p_condition) while (likely(p_condition))

#define ifu(p_condition) if (unlikely(p_condition))
#define ifl(p_condition) if (likely(p_condition))
