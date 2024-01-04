#include <Utility/utilityRandObject/randCollider.h>


sf::Color utility::getRandomColor()
{
    return sf::Color(utility::randNumber::getRandomNumber(10, 255), utility::randNumber::getRandomNumber(10, 255), utility::randNumber::getRandomNumber(10, 255));
}
float utility::randNumber::getRandomNumber(float min, float max)
{
    float random = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    return random;
}

int utility::randNumber::getRandomNumber(int min, int max)
{
    int random = rand() % (max - min + 1) + min;
    return random;
}

void utility::randCollider::GenerateRandBox(const v2f& pos, float minSide, float maxSide, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider)
{
	phis2D::collider::CreateBoxCollider(pos,
		v2f(utility::randNumber::getRandomNumber(minSide, maxSide),
            utility::randNumber::getRandomNumber(minSide, maxSide)),
		outMessage, outBoxCollider);
}

void utility::randCollider::GenerateRandCircle(const v2f& pos, float minRadius, float maxRadius, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider)
{
	phis2D::collider::CreateCircleCollider(pos,
		utility::randNumber::getRandomNumber(minRadius, maxRadius),
		outMessage, outCircleCollider);
}

void utility::randCollider::GenerateRandPolygon(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider)
{
    v2f* vecVertics = new v2f[n];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    // 1. Генерация угла первой точки
    float angle = dis(gen) * 360;

    // 1б. Расчет параметров m и M
    float m = minLenght / (2.f * sin((180.f / n) * (3.141592f / 180.f)));
    float M = maxLenght / (2.f * sin((180.f / n) * (3.141592f / 180.f)));

    // 1в. Выбор расстояния от центра
    float length = dis(gen) * (M - m) + m;

    // 2. Вычисление координат для остальных точек
    for (int i = 0; i < n; ++i) {
        float deviation = dis(gen) * (360 / n) - (360 / n) / 2;
        float x = cos((angle + (360 / n) * i + deviation) * (3.141592f / 180)) * length;
        float y = sin((angle + (360 / n) * i + deviation) * (3.141592f / 180)) * length;
        vecVertics[i] = v2f(x + pos.x, y + pos.y);
    }
    phis2D::collider::vecV2f vertics(vecVertics, n);
    phis2D::collider::CreatePolygonCollider(vertics, outMessage, outPolygonCollider);
    outPolygonCollider->MoveTo(pos);
    delete[] vecVertics;
}

void utility::randCollider::GenerateRandCollider(const v2f& pos, float scaleSize, std::string& outMessage, phis2D::collider::VirtualCollider*& outCollider)
{
    //phis2D::collider::typeCollider typeColliderGenerate = (phis2D::collider::typeCollider)(rand() % (int)phis2D::collider::countCollidersTypes);
    //phis2D::collider::typeCollider typeColliderGenerate = (phis2D::collider::typeCollider)(rand() % 2);
    phis2D::collider::typeCollider typeColliderGenerate = phis2D::collider::Circle;
    float minSize = 10 * scaleSize, maxSize = 20 * scaleSize;
    size_t cntVertices = 7;
    if (typeColliderGenerate == phis2D::collider::Box)
        GenerateRandBox(pos, minSize, maxSize, outMessage, outCollider);
    else if (typeColliderGenerate == phis2D::collider::Circle)
        GenerateRandCircle(pos, minSize, maxSize, outMessage, outCollider);
    else if (typeColliderGenerate == phis2D::collider::Polygon)
        GenerateRandPolygon(pos, cntVertices, minSize, maxSize, outMessage, outCollider);
}
