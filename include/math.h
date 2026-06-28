#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Math {
    struct Vector3 {
        float x, y, z;
        
        Vector3 operator+(const Vector3& v) const;
        Vector3 operator-(const Vector3& v) const;
        Vector3 operator*(float scalar) const;
        float dot(const Vector3& v) const;
        Vector3 cross(const Vector3& v) const;
        float length() const;
        Vector3 normalize() const;
    };
    
    struct Vector2 {
        float x, y;
        
        Vector2 operator+(const Vector2& v) const;
        Vector2 operator-(const Vector2& v) const;
        float distance(const Vector2& v) const;
    };
    
    // World to screen projection
    bool WorldToScreen(const Vector3& worldPos, Vector2& screenPos, 
                      const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
}
