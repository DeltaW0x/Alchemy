//
// Created by lucac on 27/05/2024.
//

#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <stdafx.h>
#include "Float3.h"
#include "Float4.h"

using namespace DirectX;

namespace alchemy {
    inline XMMATRIX CalculateWorldTransform(float3 scale, float4 rotation, float3 position) {
        return XMMatrixTransformation(XMVectorZero(),
                                      XMQuaternionIdentity(),
                                      scale,
                                      XMVectorZero(),
                                      rotation,
                                      position);
    }

    inline XMMATRIX CalculateWorldTransformFromParent(XMMATRIX transform,
                                                      XMMATRIX parent) {
        return XMMatrixMultiply(parent,transform);

    }


    float3 QuaternionToAngleVector(float4 quaternion) {

        float3 angles;
        float4 q(quaternion);

        double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
        double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
        double sinp = 2 * (q.w * q.y - q.z * q.x);

        angles.x = (float)std::atan2(sinr_cosp, cosr_cosp);

        if (std::abs(sinp) >= 1)
        {
            angles.y = (float)std::copysign(3.141592653589793f / 2, sinp);
        }
        else
        {
            angles.y = (float)std::asin(sinp);
        }
        double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
        angles.z = (float)std::atan2(siny_cosp, cosy_cosp);
        return angles;
    }
}


#endif //MATRIXMATH_H
