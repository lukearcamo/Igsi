#include "pico_load.h"
#include "picopng.h"
#include "../core/vec2.h"

#include <vector>
#include <iostream>
#include <fstream>

// DO NOT USE PICOPNG IN A SERIOUS PROJECT
// I only used picopng because it's simple and tiny
// According to https://lodev.org/lodepng/, which is where I got it from,
// it is "less well maintained than LodePNG, has less features, and may be less efficient."

namespace Igsi {
    vec2 loadImage(std::vector<unsigned char> &imageData, const char* imagePath) {
        std::ifstream file(imagePath, std::ios::in | std::ios::binary | std::ios::ate);
        std::vector<unsigned char> buffer;

        // Get filesize
        std::streamsize size = 0;
        if (file.seekg(0, std::ios::end).good()) size = file.tellg();
        if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

        // Read contents of the file into the vector
        if (size > 0) {
            buffer.resize(size);
            file.read((char*)buffer.data(), size);
        }
        else buffer.clear();

        unsigned long w = 0;
        unsigned long h = 0;
        int error = picopng::decodePNG(imageData, w, h, buffer.empty() ? 0 : buffer.data(), buffer.size());
        if (error) std::cout << "Image failed to load: " << error << std::endl;
        return vec2(w, h);
    }
}