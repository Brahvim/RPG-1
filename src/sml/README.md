# Simple-Math-Library
A "simple" math library for rendering operations - "simple" for cross-platform speed.  
Vectors, matrices, and quaternions. For now.  
It has many functions, but I'll *definitely* be adding MANY more. Check [`include/library/sml.h`](https://github.com/Brahvim/Simple-Math-Library/tree/main/include/library/sml.h).  

**Lots** of `union`-abuse to support syntax like GLSL's "swizzles".  
Code is as simple as possible for API granularity reasons as well as "**general**" platform-specific optimization reasons (may or may not use platform-specific SIMD intrinsics till I have the time to).  
For now, I *really do* rely on "simple code" and compiler auto-vectorization.  

All functions take memory addresses to the data structure[s] to perform an operation on, and a destination. Lots of `const`-correctness on those. Hopefully the compiler optimizes those, but I cannot give guarantees.  

Should also provide batch-operation functions!... I do *not* have those right now!!!  
Library does not handle allocation - might offer allocation pools some day, use IDs instead of pointers, maybe have more *speed* that way. That day iiis... *not today!*  
