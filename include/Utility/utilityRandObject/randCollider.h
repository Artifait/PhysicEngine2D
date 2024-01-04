#pragma once
#include <EnginePhis2D/Shapes/Colliders.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <SFML/Graphics/Color.hpp>

namespace utility
{
	sf::Color getRandomColor();
	namespace randNumber
	{
        float getRandomNumber(float min, float max);
        int getRandomNumber(int min, int max); 
	}

	namespace randCollider
	{
        void GenerateRandBox(const v2f& pos, float minSide, float maxSide, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider);


        void GenerateRandCircle(const v2f& pos, float minRadius, float maxRadius, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider);

        void GenerateRandPolygon(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider);

		void GenerateRandCollider(const v2f& pos, float scaleSize, std::string& outMessage, phis2D::collider::VirtualCollider*& outCollider);
	}
}