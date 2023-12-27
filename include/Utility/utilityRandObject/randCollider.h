#pragma once
#include <Shapes/Colliders.h>
#include <algorithm>
#include <iostream>
#include <random>

namespace utility
{
	namespace randCollider
	{
        void GenerateRandBox(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider);


        void GenerateRandCircle(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider);

        void GenerateRandPolygon(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider);

		void GenerateRandCollider(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCollider);
	}
}