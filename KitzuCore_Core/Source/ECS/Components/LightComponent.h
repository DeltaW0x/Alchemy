//
// Created by lucac on 08/06/2024.
//

#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

struct LightShadowCaster {};

enum class LightType {
    Point,
    Spotlight,
    Directional,
    Area
};

class LightComponent {
    LightType type;

    float color[3];
    float direction[3];
    float intensity;
    float radius;
    float angle;
};

#endif //LIGHTCOMPONENT_H
