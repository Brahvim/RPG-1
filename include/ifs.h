#pragma once
#define ifu(x) if (__builtin_expect((long) (x), 0))
#define ifl(x) if (__builtin_expect((long) (x), 1))

#define switchl(p_condition, p_likelyBranch) switch (__builtin_expect((long) (p_condition), p_likelyBranch))

#define whileu(x) while (__builtin_expect((long) (x), 0))
#define whilel(x) while (__builtin_expect((long) (x), 1))

// The syntax for `foru()` sucks because you have to use `,`s over `;`s and don't get initialize multiple variables that way!
