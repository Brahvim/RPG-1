#pragma once
#define ifu(x) if (__builtin_expect((long) (x), 0))
#define ifl(x) if (__builtin_expect((long) (x), 1))

// Nope!:
// #define caseu(x) case __builtin_expect((long) (x), 0):
// #define casel(x) case __builtin_expect((long) (x), 1):

#define whileu(x) while (__builtin_expect((long) (x), 0))
#define whilel(x) while (__builtin_expect((long) (x), 1))

#define foru(a, b, c) for (a; __builtin_expect((long) (b), 0); c)
#define forl(a, b, c) for (a; __builtin_expect((long) (b), 1); c)
