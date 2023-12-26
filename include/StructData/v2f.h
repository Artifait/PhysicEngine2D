#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

class v2f {
public:
    // Конструкторы
    v2f() : x(0.f), y(0.f) {}
    v2f(float x, float y) : x(x), y(y) {}
    v2f(const sf::Vector2f& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}
    v2f(const sf::Vector2i& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

    // Операторы базовых математических операций
    v2f operator+(const v2f& other) const {
        return v2f(x + other.x, y + other.y);
    }
    v2f operator-(const v2f& other) const {
        return v2f(x - other.x, y - other.y);
    }
    v2f operator-()
    {
        return v2f(-x, -y);
    }
    v2f operator*(float scalar) const {
        return v2f(x * scalar, y * scalar);
    }
    v2f operator*(const v2f& other) const {
        return v2f(x * other.x, y * other.y);
    }
    v2f operator/(float scalar) const {
        return v2f(x / scalar, y / scalar);
    }
    v2f operator/(v2f scalar) const {
        return v2f(x / scalar.x, y / scalar.y);
    }

    // Операторы присваивания
    v2f& operator=(const v2f& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    v2f& operator=(const sf::Vector2f& v) {
        x = static_cast<float>(v.x);
        y = static_cast<float>(v.y);
        return *this;
    }
    v2f& operator=(const sf::Vector2i& v) {
        x = static_cast<float>(v.x);
        y = static_cast<float>(v.y);
        return *this;
    }
    v2f& operator+=(const v2f& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    v2f& operator-=(const v2f& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    v2f& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    v2f& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const v2f& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const v2f& other) const {
        return !(*this == other);
    }
    // Перегрузка оператора <
    bool operator<(const v2f& other) const
    {
        if (x < other.x)
            return true;
        else if (x == other.x && y < other.y)
            return true;
        else
            return false;
    }

    // Перегрузка оператора >
    bool operator>(const v2f& other) const
    {
        if (x > other.x)
            return true;
        else if (x == other.x && y > other.y)
            return true;
        else
            return false;
    }

    // Методы для работы с вектором
    float getLength() const {
        return std::sqrt(x * x + y * y);
    }
    float getLengthSquared() const {
        return x * x + y * y;
    }
    void normalize() {
        float length = getLength();
        if (length != 0.f) {
            x /= length;
            y /= length;
        }
    }

    v2f getNormalized() const {
        v2f result(x, y);
        result.normalize();
        return result;
    }

    // Методы для конвертации
    operator sf::Vector2f() const {
        return sf::Vector2f(x, y);
    }

    // Статические методы для работы с векторами
    static v2f v2fMax() { return v2f(3.4E+38f, 3.4E+38f); }
    static v2f v2fMin() { return v2f(-3.4E+38f, -3.4E+38f); }


    static float dot(const v2f& v1, const v2f& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static float cross(const v2f& v1, const v2f& v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }
    static v2f lerp(const v2f& v1, const v2f& v2, float t) {
        return v1 * (1.f - t) + v2 * t;
    }

    static inline float Length(const v2f& v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    static inline float LengthSquere(const v2f& v) {
        return v.x * v.x + v.y * v.y;
    }

    static inline float Distance(const v2f& v0, const v2f& v1) {
        return v2f::Length(v0 - v1);
    }

    static inline float DistanceSquere(const v2f& v0, const v2f& v1) {
        return v2f::LengthSquere(v0 - v1);
    }


    static v2f Normalize(const v2f& v) {
        float length = Length(v);

        return length ? v / length : v2f();
    }

    static v2f RotateVector(const v2f& v, float angl)//только нормализованый вектор
    {
        float currentAngl = std::atan2(v.y, v.x);
        float newAngl = currentAngl + angl;
        return v2f(std::cos(newAngl), std::sin(newAngl));
    }

    float x, y;
    friend std::ostream& operator<<(std::ostream& os, const v2f& vec) {
        os << "v2f(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};
