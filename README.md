# Igsi
A rudimentary C++ OpenGL library, inspired by Three.js, OGL.js, and TWGL.js

In my native tongue, igsi means "short" or "shortness", and this is the philosophy behind this library. It is that it is meant to make code less verbose by shortening various common interactions with OpenGL, while still giving you the freedom to do it yourself (due to the lack of heavy abstraction). src/helpers.h is used for interacting with OpenGL, and everything else is merely a container for data, accompanied by various functions for manipulating this data. Despite there being other libraries, I made this because I wanted a library that wasn't too far abstracted from the original low-level OpenGL, and also because this project was kind of like coding practice, helping me better understand OpenGL.

## This library consists of:
- Helpers for creating & managing OpenGL objects
- Classes for just vec3, vec4, and mat4 (meant to be used kinda like in glsl, but with no swizzling because I don't have enough braincells to figure that out)
- A simple scene graph system
- Simple geometry data generation & transformation

## Missing features:
- Creating OpenGL contexts or windows — Use other libraries like GLFW
- Loading images to use for textures — Use other libraries like stb_image or lodepng (I did include picopng, but see the note at the top of the pico_load.h file)
- Mostly only supports float data type for the math classes, attributes, uniforms, etc. I plan on changing this later but this is a big change. Some may still not be supported (just think, when was the last time you used a uniform bvec4?)
- There are todo comments at the top of some files, check them to see what missing features there are because I'm probably forgetting some here

As of right now, there is no documentation, but the code should be fairly intuitive so feel free to explore it, modify it for your project, etc. Maybe if this gets larger I'll write some.
