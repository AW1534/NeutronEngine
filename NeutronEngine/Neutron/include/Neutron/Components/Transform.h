//
// Created by aw1lt on 07/12/22.
//

#ifndef NEUTRONEXAMPLEC_TRANSFORM_H
#define NEUTRONEXAMPLEC_TRANSFORM_H

#include "BaseComponent.h"
#include "Neutron/Math/Vector2.h"

namespace Neutron {

    class Transform : public BaseComponent {
    public:
        Math::Vector2 position = Math::Vector2(0, 0);
        Math::Vector2 rotation = Math::Vector2(0, 0);
        Math::Vector2 scale = Math::Vector2(1, 1);
    };

} // Neutron

#endif //NEUTRONEXAMPLEC_TRANSFORM_H
