# RPG-1
A small game I'm working on in more of an engine style. Made some libraries for it:  
- [Simple-Math-Library](https://github.com/Brahvim/Simple-Math-Library) (That's what [`include/sml.h`](https://github.com/Brahvim/RPG-1/blob/main/include/) and [`libs/libSimpleMathLibrary.so`](https://github.com/Brahvim/RPG-1/blob/main/libs/) and are!)
- [Simple-Physics-Engine](https://github.com/Brahvim/Simple-Physics-Engine) (Currently unused and *honestly, **not** very ready*)

Building is in the usual CMake style. Make sure to get GLFW3 and OpenAL development and library packages!  
I dev-and-build on Debian, using packages was the easiest method for me.

Designing with data a lot. Code is mostly "procedural", and also somewhat "functional" - for transforms only, really.  
Functions you can call anytime you want, on any thread you want, to do the work *you want*.  

Currently only *rendering **quads*** - for 2D sprites. Will soon bring texture atlas *packing* (in the algorithmic sense, yes - as in, the engine will assemble a texture atlas from multiple files instead of us specifying coordinates and packing textures in squares, not just parsing - I might instead choose parsing if I find a more consumer-friendly method to *MAKE* atlasses in the first place).  

Also, OpenAL! I wish to use 3D audio in this game even if it plays top-down. That, and fade-transitions between "floors".  
