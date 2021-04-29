# Igsi
A rudimentary C++ OpenGL library, remotely based off of THREE.js

In my native tongue, *igsi* means "short" or "shortness", and I named it that not only because this library is tiny & very lightweight, but also that's exactly what this library is supposed to help with: shortening OpenGL code and making it less verbose (meaning this is *not* an OpenGL abstraction). I also named it that because it's my library and I can do what I want :)
Why did you make this? There are other libr— Because I wanted to stay true to the original low-level OpenGL so I didn't want to use any abstraction libraries, and also coding practice, and also because I can, and also because I usually make things harder for myself

## This library consists of:
- Helpers for creating & managing OpenGL objects
..- This library is *not* object-oriented; more freedom for you to do other stuff, with other OpenGL objects
- Classes for just vec3, vec4, and mat4 (it's meant to be kinda like glsl, but with no swizzling because I don't have enough braincells to figure that out)
- A scene graph system, which does not use any OpenGL, so it's up to you what to do with all the matrices
- Functions to generate and modify geometry data in C++ vectors

## Missing features:
- Creating OpenGL contexts or windows — Use other libraries like GLFW
- Loading images to use for textures — Use other libraries like stb_image or lodepng
- Many of the functions that deal with VBOs and uniforms only support floats, I plan on changing those later, but just think, when was the last time you used a bvec4?
- On a similar note, there are some todo comments at the top of the header files, check them to see what missing features there are

As of right now, there is no documentation, but the code should be intuitive so feel free to explore it, modify it for your project, etc. Maybe if this gets larger I will write documentation, and maybe some examples.
