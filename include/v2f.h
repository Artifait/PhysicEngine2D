#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

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

    // Методы доступа к координатам
    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
    void setX(float x) {
        this->x = x;
    }
    void setY(float y) {
        this->y = y;
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
    static float dot(const v2f& v1, const v2f& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static float cross(const v2f& v1, const v2f& v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }
    static v2f lerp(const v2f& v1, const v2f& v2, float t) {
        return v1 * (1.f - t) + v2 * t;
    }

    static v2f RotateVector(const v2f& v, double angl)//только нормализованый вектор
    {
        float currentAngl = std::atan2(v.y, v.x);
        float newAngl = currentAngl + angl;
        return v2f(std::cos(newAngl), std::sin(newAngl));
    }

    float x, y;
};