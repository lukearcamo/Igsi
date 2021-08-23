#ifndef IGSI_PICO_LOAD_H
#define IGSI_PICO_LOAD_H

#include <vector>

// DO NOT USE PICOPNG IN A SERIOUS PROJECT
// I only used picopng because it's simple and tiny
// According to https://lodev.org/lodepng/, which is where I got it from,
// it is "less well maintained than LodePNG, has less features, and may be less efficient."

namespace Igsi {
    class vec2;
    
    vec2 loadImage(std::vector<unsigned char> &imageData, const char* imagePath);
}

#endif