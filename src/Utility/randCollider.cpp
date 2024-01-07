#include <Utility/randCollider.h>

namespace utility
{

    sf::Color getRandomColor()
    {
        return sf::Color(
            getRandomNumber(10, 255),
            getRandomNumber(10, 255),
            getRandomNumber(10, 255));
    }
    float getRandomNumber(float min, float max)
    {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }

    int getRandomNumber(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    void ColliderGenerator::GenerateRandBox(const v2f& pos, float minSide, float maxSide,
        std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider)
    {
        phis2D::collider::CreateBoxCollider(pos,
            v2f(getRandomNumber(minSide, maxSide),
                getRandomNumber(minSide, maxSide)),
            outMessage, outBoxCollider);
    }
    ::phis2D::collider::vecV2f utility::ColliderGenerator::GenerateRandVerticesPolygon(const v2f& posCenter, int n, float minLenght, float maxLenght)
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
            float deviation = dis(gen) * (360.f / n) - (360.f / n) / 2.f;
            float x = cos((angle + (360.f / n) * i + deviation) * (3.141592f / 180.f)) * length;
            float y = sin((angle + (360.f / n) * i + deviation) * (3.141592f / 180.f)) * length;
            vecVertics[i] = v2f(x + posCenter.x, y + posCenter.y);
        }

        return phis2D::collider::vecV2f(vecVertics, n);
    }
    ::phis2D::collider::vecV2f utility::ColliderGenerator::GenerateRandVerticesPolygon(const v2f& posCenter, int n)
    {
        return GenerateRandVerticesPolygon(posCenter, n, minPolygonSide, maxPolygonSide);
    }
    void ColliderGenerator::GenerateRandBox(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider)
    {
        ColliderGenerator::GenerateRandBox(pos, minSide, maxSide, outMessage, outBoxCollider);
    }

    void ColliderGenerator::GenerateRandCircle(const v2f& pos, float minRadius, float maxRadius, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider)
    {
        phis2D::collider::CreateCircleCollider(pos,
            getRandomNumber(minRadius, maxRadius),
            outMessage, outCircleCollider);
    }
    void ColliderGenerator::GenerateRandCircle(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider)
    {
        ColliderGenerator::GenerateRandCircle(pos, minRadius, maxRadius, outMessage, outCircleCollider);
    }

    void ColliderGenerator::GenerateRandPolygon(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider)
    {
        phis2D::collider::vecV2f vertics = GenerateRandVerticesPolygon(pos, n , minLenght, maxLenght);
        phis2D::collider::CreatePolygonCollider(vertics, outMessage, outPolygonCollider);
        outPolygonCollider->MoveTo(pos);
        delete[] vertics.first;
    }

    void ColliderGenerator::GenerateRandPolygon(const v2f& pos, int n, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider)
    {
        ColliderGenerator::GenerateRandPolygon(pos, n, minPolygonSide, maxPolygonSide, outMessage, outPolygonCollider);
    }

    void ColliderGenerator::GenerateRandCollider(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCollider)
    {
        //phis2D::collider::typeCollider typeColliderGenerate = phis2D::collider::Circle;
        //phis2D::collider::typeCollider typeColliderGenerate = (phis2D::collider::typeCollider)(rand() % 2);
        phis2D::collider::typeCollider typeColliderGenerate = (phis2D::collider::typeCollider)(rand() % (int)phis2D::collider::typeColliderCount);

        size_t cntVertices = getRandomNumber(3, 7);
        if (typeColliderGenerate == phis2D::collider::Box)
            ColliderGenerator::GenerateRandBox(pos, outMessage, outCollider);
        else if (typeColliderGenerate == phis2D::collider::Circle)
            ColliderGenerator::GenerateRandCircle(pos, outMessage, outCollider);
        else if (typeColliderGenerate == phis2D::collider::Polygon)
            ColliderGenerator::GenerateRandPolygon(pos, cntVertices, outMessage, outCollider);
    }



    void BadyGenerator::GenerateRandBoxStatic(const v2f& pos, float minSide, float maxSide, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        phis2D::BaseBady2D::CreateBoxBady(pos, v2f(getRandomNumber(minSide, maxSide), getRandomNumber(minSide, maxSide)),
            true, getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity), 1.f,
            outBady, outMessage);
    }
    void utility::BadyGenerator::GenerateRandBoxStatic(const v2f& pos, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        GenerateRandBoxStatic(pos, minSide, maxSide, outMessage, outBady);
    }

    void BadyGenerator::GenerateRandCircleStatic(const v2f& pos, float minRadius, float maxRadius, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        phis2D::BaseBady2D::CreateCircleBady(pos, getRandomNumber(minRadius, maxRadius),
            true, getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity), 1.f, 
            outBady, outMessage);
    }
    void utility::BadyGenerator::GenerateRandCircleStatic(const v2f& pos, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        GenerateRandCircleStatic(pos, minRadius, maxRadius, outMessage, outBady);
    }

    void BadyGenerator::GenerateRandPolygonStatic(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        auto vertices = ColliderGenerator::GenerateRandVerticesPolygon(pos, n, minLenght, maxLenght);
        phis2D::BaseBady2D::CreatePolygonBady(pos, vertices.first, vertices.second,
            true, getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity), 1.f,
            outBady, outMessage);
        delete[] vertices.first;
    }
    void utility::BadyGenerator::GenerateRandPolygonStatic(const v2f& pos, int n, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        GenerateRandPolygonStatic(pos, n, minPolygonSide, maxPolygonSide, outMessage, outBady);
    }
    void BadyGenerator::GenerateRandBady(const v2f& pos, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        phis2D::collider::VirtualCollider* collider = nullptr;
        ColliderGenerator::GenerateRandCollider(pos, outMessage, collider);
        if (collider == nullptr)
            return;
        
    }

    void utility::BadyGenerator::GenerateRandColliderStatic(phis2D::collider::VirtualCollider* collider, std::string& outMessage, phis2D::BaseBady2D*& outBady)
    {
        phis2D::BaseBady2D::CreateColliderBady(collider, true, 
            getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity), 1.f, 
            outBady, outMessage);
    }

    float BadyGenerator::minSide = phis2D::worldPhysicConstant::minSide;
    float BadyGenerator::maxSide = phis2D::worldPhysicConstant::maxSide;

    float BadyGenerator::minRadius = phis2D::worldPhysicConstant::minRadius;
    float BadyGenerator::maxRadius = phis2D::worldPhysicConstant::maxRadius;

    float BadyGenerator::minPolygonSide = 25.f;
    float BadyGenerator::maxPolygonSide = 50.f;


    float ColliderGenerator::minSide = phis2D::worldPhysicConstant::minSide;
    float ColliderGenerator::maxSide = phis2D::worldPhysicConstant::maxSide;

    float ColliderGenerator::minRadius = phis2D::worldPhysicConstant::minRadius;
    float ColliderGenerator::maxRadius = phis2D::worldPhysicConstant::maxRadius;

    float ColliderGenerator::minPolygonSide = 25.f;
    float ColliderGenerator::maxPolygonSide = 50.f;
}//utility