#include "math.h"
#include <cmath>

namespace Math {
    Vector3 Vector3::operator+(const Vector3& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }
    
    Vector3 Vector3::operator-(const Vector3& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }
    
    Vector3 Vector3::operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
    
    float Vector3::dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    Vector3 Vector3::cross(const Vector3& v) const {
        return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        };
    }
    
    float Vector3::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    Vector3 Vector3::normalize() const {
        float len = length();
        if (len > 0) {
            return {x / len, y / len, z / len};
        }
        return {0, 0, 0};
    }
    
    Vector2 Vector2::operator+(const Vector2& v) const {
        return {x + v.x, y + v.y};
    }
    
    Vector2 Vector2::operator-(const Vector2& v) const {
        return {x - v.x, y - v.y};
    }
    
    float Vector2::distance(const Vector2& v) const {
        float dx = x - v.x;
        float dy = y - v.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    bool WorldToScreen(const Vector3& worldPos, Vector2& screenPos,
                      const glm::mat4& viewMatrix, const glm::mat4& projMatrix) {
        glm::vec4 worldVec = glm::vec4(worldPos.x, worldPos.y, worldPos.z, 1.0f);
        glm::vec4 viewVec = viewMatrix * worldVec;
        glm::vec4 projVec = projMatrix * viewVec;
        
        if (projVec.w <= 0.0f) {
            return false;
        }
        
        screenPos.x = (projVec.x / projVec.w + 1.0f) * 0.5f;
        screenPos.y = (1.0f - projVec.y / projVec.w) * 0.5f;
        
        return true;
    }
}
