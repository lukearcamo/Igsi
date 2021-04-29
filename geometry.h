#ifndef IGSI_GEOMETRY_H
#define IGSI_GEOMETRY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

#include "mathematics.h"

/*
TODO:
Add cylinder/cone or other types of geometry
Perhaps perform these functions on the actual opengl buffer rather than a vector?
*/

namespace Igsi {
    void nonIndexed(std::vector<float> &buffer, std::vector<unsigned int> &indices, int itemSize) {
        std::vector<float> newBuffer;
        newBuffer.reserve(indices.size() * itemSize);
        for (int i = 0; i < indices.size(); i++) {
            int idx = indices[i] * itemSize;
            for (int j = 0; j < itemSize; j++) {
                newBuffer.push_back(buffer.at(idx + j)); // .at throws exception if OOB
            }
        }
        buffer.swap(newBuffer);
    }

    // Note that this doesnt multiply idx by 3 first, so it assumes that idx is an array position, not the index of the vector
    void setXYZ(std::vector<float> &buffer, int idx, vec3 value) {
        buffer[idx] = value.x;
        buffer[idx + 1] = value.y;
        buffer[idx + 2] = value.z;
    }
    vec3 getXYZ(std::vector<float> &buffer, int idx) {
        return vec3(buffer[idx], buffer[idx + 1], buffer[idx + 2]);
    }
    void transform(mat4 matrix, std::vector<float> &vertices, std::vector<float> &normals) {
        mat4 normalMatrix = matrix;
        normalMatrix.invert().transpose(); // assumes that elements 3, 7, and 11 are 0, which should be true if using the regular matrix transformations defined in matrix class
        for (int i = 0; i < vertices.size(); i += 3) {
            vec4 pos = matrix * vec4(getXYZ(vertices, i), 1);
            vec4 nml = normalMatrix * vec4(getXYZ(normals, i), 0);
            setXYZ(vertices, i, vec3(pos.x, pos.y, pos.z));
            setXYZ(normals, i, vec3(nml.x, nml.y, nml.z));
        }
    }
    void computeNormals(std::vector<float> &vertices, std::vector<float> &normals) {
        normals.assign(vertices.size(), 0);
        for (int i = 0; i < vertices.size(); i += 9) { // Iterates thru triangles, not points
            vec3 pA = getXYZ(vertices, i);
            vec3 pB = getXYZ(vertices, i + 3);
            vec3 pC = getXYZ(vertices, i + 6);
            vec3 nml = normalize(cross(pC - pB, pA - pB));
            setXYZ(normals, i, nml);
            setXYZ(normals, i + 3, nml);
            setXYZ(normals, i + 6, nml);
        }
    }
    void computeNormals(std::vector<float> &vertices, std::vector<float> &normals, std::vector<unsigned int> &indices) {
        normals.assign(vertices.size(), 0);
        for (int i = 0; i < indices.size(); i += 3) { // Iterates thru triangles, not points
            vec3 index = vec3(indices[i], indices[i + 1], indices[i + 2]);
            index *= 3;
            vec3 pA = getXYZ(vertices, index.x);
            vec3 pB = getXYZ(vertices, index.y);
            vec3 pC = getXYZ(vertices, index.z);
            vec3 nml = cross(pC - pB, pA - pB);
            setXYZ(normals, index.x, getXYZ(normals, index.x) + nml);
            setXYZ(normals, index.y, getXYZ(normals, index.y) + nml);
            setXYZ(normals, index.z, getXYZ(normals, index.z) + nml);
        }
        for (int i = 0; i < normals.size(); i += 3) {
            setXYZ(normals, i, normalize(getXYZ(normals, i)));
        }
    }

    void planeGeometry(std::vector<float> &vertices, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indices, vec2 dims=vec2(1), vec2 segments=vec2(1)) {
        vec2 halfDims = dims / 2;
		vec2 grid = floor(segments);
		vec2 grid1 = grid + 1;
		vec2 segmentSize = dims / grid;
        
        int numVerts = grid1.x * grid1.y;
        int numIdcs = grid.x * grid.y * 6;
        int pastSize = vertices.size();        
        vertices.reserve(pastSize + numVerts * 3);
        normals.reserve(pastSize + numVerts * 3);
        uvs.reserve(pastSize + numVerts * 2);
        indices.reserve(indices.size() + numIdcs);

		for (int iy = 0; iy < grid1.y; iy++) {
			float y = iy * segmentSize.y - halfDims.y;
			for (int ix = 0; ix < grid1.x; ix++) {
				float x = ix * segmentSize.x - halfDims.x;
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(0);

				normals.push_back(0);
				normals.push_back(0);
				normals.push_back(1);
                
                uvs.push_back(ix / grid.x);
				uvs.push_back(iy / grid.y);
			}
		}
		for (int iy = 0; iy < grid.y; iy++) {
			for (int ix = 0; ix < grid.x; ix++) {
                unsigned int a = grid1.x * iy + ix + pastSize;
				unsigned int b = grid1.x * (iy + 1) + ix + pastSize;
				unsigned int c = grid1.x * iy + (ix + 1) + pastSize;
				unsigned int d = grid1.x * (iy + 1) + (ix + 1) + pastSize;
                
				indices.push_back(a);
				indices.push_back(d);
				indices.push_back(b);
				indices.push_back(a);
				indices.push_back(c);
				indices.push_back(d);
			}
		}
    }
    // Credit to THREE.js BoxGeometry
    void boxGeometry(std::vector<float> &vertices, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indices, vec3 dims=vec3(1), vec3 segments=vec3(1)) {
        vec3 halfDims = dims / 2;

        int pastSize = vertices.size() / 3;

        auto face = [&](int u, int v, int w, int udir, int vdir, vec3 relDims) {
            vec2 grid = floor(vec2(segments[u], segments[v]));
            vec2 grid1 = grid + 1;
            vec2 segmentSize = vec2(dims[u], dims[v]) / grid;

            vec3 tmp;
            
            // knowing my math, these numbers may not be correct lol but its fine bc vector will not throw an error it'll just reallocate mem
            int numVerts = grid1.y * grid1.x;
            int numIdcs = grid.y * grid.x * 6;
            vertices.reserve(pastSize + numVerts * 3);
            normals.reserve(pastSize + numVerts * 3);
            uvs.reserve(pastSize + numVerts * 2);
            indices.reserve(indices.size() + numIdcs);

            for (int iy = 0; iy < grid1.y; iy++) {
                float y = iy * segmentSize.y - relDims.y;
                for (int ix = 0; ix < grid1.x; ix++) {
                    float x = ix * segmentSize.x - relDims.x;

                    tmp[u] = x * udir;
                    tmp[v] = y * vdir;
                    tmp[w] = relDims.z;
                    
                    vertices.push_back(tmp.x);
                    vertices.push_back(tmp.y);
                    vertices.push_back(tmp.z);

                    tmp[u] = 0;
                    tmp[v] = 0;
                    tmp[w] = relDims.z > 0 ? 1 : -1;

                    normals.push_back(tmp.x);
                    normals.push_back(tmp.y);
                    normals.push_back(tmp.z);
                    
                    uvs.push_back(ix / grid.x);
                    uvs.push_back(iy / grid.y); // THREE.js: (1.0 - (iy / grid.y))
                }
            }
            for (int iy = 0; iy < grid.y; iy++) {
                for (int ix = 0; ix < grid.x; ix++) {
                    unsigned int a = grid1.x * iy + ix + pastSize;
                    unsigned int b = grid1.x * iy + (ix + 1) + pastSize;
                    unsigned int c = grid1.x * (iy + 1) + ix + pastSize;
                    unsigned int d = grid1.x * (iy + 1) + (ix + 1) + pastSize;
                    
                    indices.push_back(a);
                    indices.push_back(c);
                    indices.push_back(b);
                    indices.push_back(c);
                    indices.push_back(d);
                    indices.push_back(b);
                }
            }

            pastSize += numVerts;
        };

        face(2, 1, 0, -1, -1, vec3(halfDims.z, halfDims.y, halfDims.x)); // px
		face(2, 1, 0, 1, -1, vec3(halfDims.z, halfDims.y, -halfDims.x)); // nx
		face(0, 2, 1, 1, 1, vec3(halfDims.x, halfDims.z, halfDims.y)); // py
		face(0, 2, 1, 1, -1, vec3(halfDims.x, halfDims.z, -halfDims.y)); // ny
		face(0, 1, 2, 1, -1, vec3(halfDims.x, halfDims.y, halfDims.z)); // pz
		face(0, 1, 2, -1, -1, vec3(halfDims.x, halfDims.y, -halfDims.z)); // nz
    }

    // void LatheGeometry(std::vector<float> &vertices, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indices, std::vector<vec2> points) {

    // }
    // Based on Song Ho's article on OpenGL Spheres and THREE.js SphereBufferGeometry (But without phi/theta start/length)
    void sphereGeometry(std::vector<float> &vertices, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indices, float radius=1.0, vec2 segments=vec2(8, 6)) {
        int pastSize = vertices.size() / 3;

        // knowing my math, these numbers may not be correct lol but its fine bc vector will not throw an error it'll just reallocate mem
        int numVerts = (segments.y + 1) * (segments.x + 1);
        int numIdcs = segments.y * segments.x * 6 - segments.x * 2;
        vertices.reserve(pastSize + numVerts * 3);
        normals.reserve(pastSize + numVerts * 3);
        uvs.reserve(pastSize + numVerts * 2);
        indices.reserve(indices.size() + numIdcs);

        for (int iy = 0; iy <= segments.y; iy++) {
            float v = iy / segments.y;
            float phi = v * M_PI;
            for (int ix = 0; ix <= segments.x; ix++) {
                float u = ix / segments.x;
                float theta = u * M_PI * 2;

                vec3 point = vec3(
                    -radius * std::cos(theta) * std::sin(phi),
				    radius * std::cos(phi),
				    radius * std::sin(theta) * std::sin(phi)
                );
				vertices.push_back(point.x);
                vertices.push_back(point.y);
                vertices.push_back(point.z);

                normals.push_back(point.x / radius); // Normalize the vertex
                normals.push_back(point.y / radius);
                normals.push_back(point.z / radius);

                uvs.push_back(u);
                uvs.push_back(v);
            }
        }
        for (int iy = 0; iy < segments.y; iy++) {
			for (int ix = 0; ix < segments.x; ix++) {
                unsigned int a = (segments.x + 1) * iy + ix + pastSize;
                unsigned int b = (segments.x + 1) * iy + (ix + 1) + pastSize;
                unsigned int c = (segments.x + 1) * (iy + 1) + ix + pastSize;
                unsigned int d = (segments.x + 1) * (iy + 1) + (ix + 1) + pastSize;

                if (iy != 0) {
                    indices.push_back(a);
                    indices.push_back(c);
                    indices.push_back(b);
                }
                if (iy != segments.y - 1) {
                    indices.push_back(c);
                    indices.push_back(d);
                    indices.push_back(b);
                }
			}
		}
    }
}

#endif