//
// Created by aw1lt on 03/12/22.
//

#ifndef NEUTRONENGINE_CONCEPTS_H
#define NEUTRONENGINE_CONCEPTS_H

#include <concepts>

namespace Neutron {
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;
}

#endif //NEUTRONENGINE_CONCEPTS_H
