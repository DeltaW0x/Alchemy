//
// Created by lucac on 27/05/2024.
//

#ifndef FLOAT4_H
#define FLOAT4_H
#include <stdafx.h>
using namespace DirectX;

namespace alchemy {
    class float4 : public XMFLOAT4A {
    public:
        float4() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->w = 0;
        }

        float4(XMVECTOR vec) {
            XMStoreFloat4A(this, vec);
        }

        float4(float v) {
            this->x = v;
            this->y = v;
            this->z = v;
            this->w = v;
        }

        float4(float x, float y, float z, float w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        float4 operator+(const float4 &rhs) {
            return float4(XMVectorAdd(XMLoadFloat4A(this), XMLoadFloat4A(&rhs)));
        }

        float4 operator-(const float4 &rhs) {
            return float4(XMVectorSubtract(XMLoadFloat4A(this), XMLoadFloat4A(&rhs)));
        }

        float4 operator*(const float4 &rhs) {
            return float4(XMVectorMultiply(XMLoadFloat4A(this), XMLoadFloat4A(&rhs)));
        }

        float4 operator/(const float4 &rhs) {
            return float4(XMVectorDivide(XMLoadFloat4A(this), XMLoadFloat4A(&rhs)));
        }

        float4 operator+(const float rhs) {
            return float4(XMVectorAdd(XMLoadFloat4A(this), XMVectorReplicate(rhs)));
        }

        float4 operator-(const float rhs) {
            return float4(XMVectorSubtract(XMLoadFloat4A(this), XMVectorReplicate(rhs)));
        }

        float4 operator*(const float rhs) {
            return float4(XMVectorMultiply(XMLoadFloat4A(this), XMVectorReplicate(rhs)));
        }

        float4 operator/(const float rhs) {
            return float4(XMVectorDivide(XMLoadFloat4A(this), XMVectorReplicate(rhs)));
        }

        float4 operator*(const XMMATRIX &mat) {
            return float4(AVX2::XMVector4Transform(XMLoadFloat4A(this), mat));
        }

        operator XMVECTOR() const noexcept { return XMLoadFloat4(this); }

    private:
        friend std::ostream &operator<<(std::ostream &os, const float4 &p) {
            return os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
        }
    };
}
#endif //FLOAT4_H
