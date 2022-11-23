//
// Created by awilt on 21/11/22.
//
#ifndef NEUTRONENGINE_HELPER_H
#define NEUTRONENGINE_HELPER_H
#include "Drawable.h"

namespace Neutron {

    std::vector<int> generateIndexBuffer(std::vector<Vector2> vertices) {
        std::vector<int> indexBuffer = {};
        for (int i = 0; i < vertices.size() - 2; i++) {
            indexBuffer.push_back(0);
            indexBuffer.push_back(i+1);
            indexBuffer.push_back(i+2);
        }

        return indexBuffer;
    }
}


#endif //NEUTRONENGINE_HELPER_H
