#include <Utility/randCollider.h>

namespace utility
{
    sf::Color getRandomColor()
    {
        return sf::Color(
            getRandomNumber(10, 150),
            getRandomNumber(10, 150),
            getRandomNumber(10, 150));
    }
    float getRandomNumber(float min, float max)
    {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }

    int getRandomNumber(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    ::phis2D::collider::vecV2f GenerateRandVerticesPolygon(const v2f& posCenter, int n, float minLenght, float maxLenght)
    {
        v2f* vecVertics = new v2f[n];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        // 1. Генерация угла первой точки
        float angle = (float)dis(gen) * 360.f;

        // 1б. Расчет параметров m и M
        float m = minLenght / (2.f * sin((180.f / n) * (3.141592f / 180.f)));
        float M = maxLenght / (2.f * sin((180.f / n) * (3.141592f / 180.f)));

        // 1в. Выбор расстояния от центра
        float length = (float)(dis(gen) * (M - m) + m);

        // 2. Вычисление координат для остальных точек
        for (int i = 0; i < n; ++i) {
            float deviation = (float)dis(gen) * (360.f / n) - (360.f / n) / 2.f;
            float x = cos((angle + (360.f / n) * i + deviation) * (3.141592f / 180.f)) * length;
            float y = sin((angle + (360.f / n) * i + deviation) * (3.141592f / 180.f)) * length;
            vecVertics[i] = v2f(x + posCenter.x, y + posCenter.y);
        }

        return phis2D::collider::vecV2f(vecVertics, n);
    }
    ::phis2D::collider::vecV2f GenerateRandVerticesPolygon(const v2f& posCenter, int n)
    {
        return GenerateRandVerticesPolygon(posCenter, n, 10.f, 30.f);
    }

}// namespace utility