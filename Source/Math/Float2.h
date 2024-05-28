//
// Created by lucac on 27/05/2024.
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdafx.h>
using namespace DirectX;

namespace alchemy {
    class float2 : public XMFLOAT2 {
        float2() {
            this->x = 0;
            this->y = 0;
        }

        float2(DirectX::XMVECTOR vec) {
            XMStoreFloat2A(this, vec);
        }

        float2(float v) {
            this->x = v;
            this->y = v;
        }

        float2(float x, float y) {
            this->x = x;
            this->y = y;
        }

        float2 operator+(const float2 &rhs) {
            return float2(XMVectorAdd(XMLoadFloat2A(this), XMLoadFloat2A(&rhs)));
        }

        float2 operator-(const float2 &rhs) {
            return float2(XMVectorSubtract(XMLoadFloat2A(this), XMLoadFloat2A(&rhs)));
        }

        float2 operator*(const float2 &rhs) {
            return float2(XMVectorMultiply(XMLoadFloat2A(this), XMLoadFloat2A(&rhs)));
        }

        float2 operator/(const float2 &rhs) {
            return float2(XMVectorDivide(XMLoadFloat2A(this), XMLoadFloat2A(&rhs)));
        }

        float2 operator+(const float rhs) {
            return float2(XMVectorAdd(XMLoadFloat2A(this), XMVectorReplicate(rhs)));
        }

        float2 operator-(const float rhs) {
            return float2(XMVectorSubtract(XMLoadFloat2A(this), XMVectorReplicate(rhs)));
        }

        float2 operator*(const float rhs) {
            return float2(XMVectorMultiply(XMLoadFloat2A(this), XMVectorReplicate(rhs)));
        }

        float2 operator/(const float rhs) {
            return float2(XMVectorDivide(XMLoadFloat2A(this), XMVectorReplicate(rhs)));
        }

    private:
        friend std::ostream &operator<<(std::ostream &os, const float2 &p) {
            return os << "(" << p.x << "," << p.y << ")";
        }
    };
}
#endif //VECTOR2_H
