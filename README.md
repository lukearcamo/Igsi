# Igsi
A rudimentary C++ OpenGL library, inspired by Three.js, OGL.js, and TWGL.js

In my native tongue, igsi means "short" or "shortness", and this is the philosophy behind this library. It is that it is meant to make code less verbose by shortening various common interactions with OpenGL, while still giving you the freedom to do it yourself (due to the lack of heavy abstraction). src/helpers.h is used for interacting with OpenGL, and everything else is merely a container for data, accompanied by various functions for manipulating this data. Despite there being other libraries, I made this because I wanted a library that wasn't too far abstracted from the original low-level OpenGL.

## Consists of:
- Helpers for creating & managing OpenGL objects
- Classes for just vec3, vec4, and mat4 (meant to be used kinda like in glsl, but with no swizzling because I don't have enough braincells to figure that out)
- A simple scene graph system
- Simple geometry data generation & transformation

## Missing/planned features:
- Creating OpenGL contexts or windows — Use other libraries like GLFW
- Loading images to use for textures — Use other libraries like stb_image or lodepng (I did include picopng, but *do not use that for serious projects* — see the note at the top of the pico_load.h file)
- Support for more data types other than floats (for the vectors, attributes, uniforms, etc.), but some I don't really plan on supporting (like the elusive `bvec4`)
- More math functions for vectors (right now there is only `floor()` and `abs()`)
- Swizzling vectors
- More geometry generation functions (cylinder/cone, torus, etc.)

As of right now, there is no documentation, but the code should be fairly intuitive so feel free to explore it (especially the header files, which give a great overview), or even modify this for your own project, etc. There is an example but it is very messy. Maybe if this gets larger I'll write something.
