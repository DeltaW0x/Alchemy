//
// Created by lucac on 27/05/2024.
//

#ifndef FLOAT3_H
#define FLOAT3_H

#include <stdafx.h>
using namespace DirectX;

namespace alchemy {
    class float3 : public XMFLOAT3A {
    public:
        float3() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }

        float3(XMVECTOR vec) {
            XMStoreFloat3A(this, vec);
        }

        float3(float v) {
            this->x = v;
            this->y = v;
            this->z = v;
        }

        float3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        float3 operator+(const float3 &rhs) {
            return float3(XMVectorAdd(XMLoadFloat3A(this), XMLoadFloat3A(&rhs)));
        }

        float3 operator-(const float3 &rhs) {
            return float3(XMVectorSubtract(XMLoadFloat3A(this), XMLoadFloat3A(&rhs)));
        }

        float3 operator*(const float3 &rhs) {
            return float3(XMVectorMultiply(XMLoadFloat3A(this), XMLoadFloat3A(&rhs)));
        }

        float3 operator/(const float3 &rhs) {
            return float3(XMVectorDivide(XMLoadFloat3A(this), XMLoadFloat3A(&rhs)));
        }

        float3 operator+(const float rhs) {
            return float3(XMVectorAdd(XMLoadFloat3A(this), XMVectorReplicate(rhs)));
        }

        float3 operator-(const float rhs) {
            return float3(XMVectorSubtract(XMLoadFloat3A(this), XMVectorReplicate(rhs)));
        }

        float3 operator*(const float rhs) {
            return float3(XMVectorMultiply(XMLoadFloat3A(this), XMVectorReplicate(rhs)));
        }

        float3 operator/(const float rhs) {
            return float3(XMVectorDivide(XMLoadFloat3A(this), XMVectorReplicate(rhs)));
        }

        operator XMVECTOR() const noexcept { return XMLoadFloat3(this); }

    private:
        friend std::ostream &operator<<(std::ostream &os, const float3 &p) {
            return os << "(" << p.x << "," << p.y << "," << p.z << ")";
        }
    };
}
#endif //FLOAT3_H
