#ifndef IGSI_TRANSFORM_H
#define IGSI_TRANSFORM_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "mathematics.h"
#include "helpers.h"

namespace Igsi {
    class Transform {
    public:
        mat4 matrix;
        mat4 worldMatrix;
        mat4 inverseWorldMatrix;
        mat4 normalMatrix;

        std::vector<Transform*> children;
        Transform* parent = nullptr;

        vec3 position;
        vec3 rotation;
        const char* rotationOrder = "XYZ";
        vec3 scale = vec3(1);

        bool dynamic = true;

        ~Transform() {
            clear();
            if (parent) parent->remove(this);
        }

        Transform& add(Transform* child) {
            if (child == this) {
                std::cerr << "Transform::add: Transform cannot be child of itself" << std::endl;
                return *this;
            }
            if (child->parent == this) {
                std::cerr << "Transform::add: Already child of Transform" << std::endl;
                return *this;
            }
            children.push_back(child);
            if (child->parent != nullptr) child->parent->remove(child);
            child->parent = this;
            return *this;
        }
        Transform& remove(Transform* child) {
            std::vector<Transform*>::iterator idx = std::find(children.begin(), children.end(), child);
            if (idx != children.end()) {
                child->parent = nullptr;
                children.erase(idx);
            }
            return *this;
        }
        void clear() {
            std::vector<Transform*>::iterator ptr;
            for (ptr = children.begin(); ptr < children.end(); ptr++) {
                (*ptr)->parent = nullptr;
            }
            children.clear();
        }

        virtual void updateMatrices() {
            matrix.scale(scale);
            matrix *= mat4().rotationEuler(rotation, rotationOrder);
            matrix.setTranslation(position);

            if (parent) worldMatrix = matrix * parent->worldMatrix;
            else worldMatrix = matrix;

            inverseWorldMatrix = worldMatrix;
            inverseWorldMatrix.invert();
            
            normalMatrix = inverseWorldMatrix;
            normalMatrix.transpose();
        }
        void updateChildrenMatrices() {
            if (dynamic) updateMatrices();
            std::vector<Transform*>::iterator ptr;
            for (ptr = children.begin(); ptr < children.end(); ptr++) {
                (*ptr)->updateChildrenMatrices();
            }
        }

        vec4 localToWorld(vec4 a) {
            if (dynamic) updateMatrices();
            return worldMatrix * a;
        }
        vec4 worldToLocal(vec4 a) {
            if (dynamic) updateMatrices();
            return inverseWorldMatrix * a;
        }
        vec3 getWorldPosition() {
            if (dynamic) updateMatrices();
            return vec3(worldMatrix.elements[12], worldMatrix.elements[13], worldMatrix.elements[14]);
        }
        virtual vec3 getWorldDirection() { // https://community.khronos.org/t/get-direction-from-transformation-matrix-or-quat/65502/2
            if (dynamic) updateMatrices();
            return vec3(
                worldMatrix.elements[8],
                worldMatrix.elements[9],
                worldMatrix.elements[10]
            );
        }

        void setDefaultUniforms(Transform* camera, mat4 projectionMatrix) {
            setUniform("projectionMatrix", projectionMatrix);
            setUniform("worldMatrix", worldMatrix);
            setUniform("normalMatrix", normalMatrix);
            setUniform("viewMatrix", camera->inverseWorldMatrix);
            setUniform("cameraPosition", camera->position);
        }
    };
}

#endif
