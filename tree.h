#ifndef IGSI_OBJ_H
#define IGSI_OBJ_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "mathematics.h"

namespace Igsi {
    class Object3D {
    public:
        mat4 matrix;
        mat4 matrixWorld;
        mat4 matrixWorldInverse; // Normally not used except for cameras and b) worldToLocal() method
        mat4 normalMatrix;

        std::vector<Object3D*> children;
        Object3D* parent = nullptr;

        vec3 position;
        vec3 rotation;
        EulerOrder rotationOrder = XYZ;
        vec3 scale = vec3(1);

        bool dynamic = true;

        ~Object3D() {
            clear();
            if (parent) parent->remove(this);
        }

        Object3D& add(Object3D* child) {
            if (child == this) {
                std::cerr << "Object3D.add: Object3D cannot be child of itself" << std::endl;
                return *this;
            }
            if (child->parent == this) {
                std::cerr << "Object3D.add: Already child of Object3D" << std::endl;
                return *this;
            }
            children.push_back(child);
            if (child->parent != nullptr) child->parent->remove(child);
            child->parent = this;
            return *this;
        }
        Object3D& remove(Object3D* child) {
            std::vector<Object3D*>::iterator idx = std::find(children.begin(), children.end(), child);
            if (idx != children.end()) {
                child->parent = nullptr;
                children.erase(idx);
            }
            return *this;
        }
        void clear() {
            std::vector<Object3D*>::iterator ptr;
            for (ptr = children.begin(); ptr < children.end(); ptr++) {
                (*ptr)->parent = nullptr;
            }
            children.clear();
        }

        virtual void updateMatrices() {
            matrix.scale(scale);
            matrix *= mat4().rotationEuler(rotation, rotationOrder);
            matrix.setTranslation(position);

            if (parent) matrixWorld = matrix * parent->matrixWorld;
            else matrixWorld = matrix;

            matrixWorldInverse = matrixWorld;
            matrixWorldInverse.invert();
            
            normalMatrix = matrixWorldInverse;
            normalMatrix.transpose();
        }
        void updateChildrenMatrices() {
            if (dynamic) updateMatrices();
            std::vector<Object3D*>::iterator ptr;
            for (ptr = children.begin(); ptr < children.end(); ptr++) {
                (*ptr)->updateChildrenMatrices();
            }
        }

        vec4 localToWorld(vec4 a) {
            if (dynamic) updateMatrices();
            return matrixWorld * a;
        }
        vec4 worldToLocal(vec4 a) {
            if (dynamic) updateMatrices();
            return matrixWorldInverse * a;
        }
        vec3 getWorldPosition() {
            if (dynamic) updateMatrices();
            return vec3(matrixWorld.elements[12], matrixWorld.elements[13], matrixWorld.elements[14]);
        }
        virtual vec3 getWorldDirection() { // https://community.khronos.org/t/get-direction-from-transformation-matrix-or-quat/65502/2
            if (dynamic) updateMatrices();
            return vec3(
                matrixWorld.elements[8],
                matrixWorld.elements[9],
                matrixWorld.elements[10]
            );
        }
    };
}

#endif