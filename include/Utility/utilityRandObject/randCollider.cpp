#include <Utility/utilityRandObject/randCollider.h>

void utility::randCollider::GenerateRandBox(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider)
{
	phis2D::collider::CreateBoxCollider(pos,
		v2f(35 + rand() % 66, 35 + rand() % 66),
		outMessage, outBoxCollider);
}

void utility::randCollider::GenerateRandCircle(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider)
{
	phis2D::collider::CreateCircleCollider(pos,
		20.f + rand() % 31,
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
    float m = minLenght / (2 * sin((180 / n) * (3.141592f / 180)));
    float M = maxLenght / (2 * sin((180 / n) * (3.141592f / 180)));

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

void utility::randCollider::GenerateRandCollider(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCollider)
{
    phis2D::collider::typeCollider typeColliderGenerate = (phis2D::collider::typeCollider)(rand() % (int)phis2D::collider::countCollidersTypes);
    if (typeColliderGenerate == phis2D::collider::Box)
        GenerateRandBox(pos, outMessage, outCollider);
    else if (typeColliderGenerate == phis2D::collider::Circle)
        GenerateRandCircle(pos, outMessage, outCollider);
    else if (typeColliderGenerate == phis2D::collider::Polygon)
        GenerateRandPolygon(pos, 7, 50, 75, outMessage, outCollider);
}
