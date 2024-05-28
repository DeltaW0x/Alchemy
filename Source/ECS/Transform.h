//
// Created by lucac on 28/05/2024.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <stdafx.h>
#include "../Math/Float3.h"
#include "../Math/Float4.h"

namespace alchemy {
    struct LocalTransform {
        float3 position;
        float4 rotation;
        float3 scale;
    };
}

#endif //TRANSFORMCOMPONENT_H
