#pragma once
#include <EnginePhis2D/Shapes/baseBady.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <SFML/Graphics/Color.hpp>

namespace utility
{
	sf::Color getRandomColor();

	float getRandomNumber(float min, float max);
	int getRandomNumber(int min, int max);

	class ColliderGenerator
	{
	public:
		ColliderGenerator() = default;
		~ColliderGenerator() = default;

		friend class BadyGenerator;
		friend class ::phis2D::World2D;
		friend class ::phis2D::AdderBody;
	private:
		static void GenerateRandBox(const v2f& pos, float minSide, float maxSide, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider);
		static void GenerateRandBox(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outBoxCollider);

		static void GenerateRandCircle(const v2f& pos, float minRadius, float maxRadius, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider);
		static void GenerateRandCircle(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCircleCollider);

		static ::phis2D::collider::vecV2f GenerateRandVerticesPolygon(const v2f& posCenter, int n, float minLenght, float maxLenght);
		static ::phis2D::collider::vecV2f GenerateRandVerticesPolygon(const v2f& posCenter, int n);

		static void GenerateRandPolygon(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider);
		static void GenerateRandPolygon(const v2f& pos, int n, std::string& outMessage, phis2D::collider::VirtualCollider*& outPolygonCollider);

		static void GenerateRandCollider(const v2f& pos, std::string& outMessage, phis2D::collider::VirtualCollider*& outCollider);


		static float minSide;
		static float maxSide;

		static float minRadius;
		static float maxRadius;

		static float minPolygonSide;
		static float maxPolygonSide;
	};

	class BadyGenerator
	{
	public:
		BadyGenerator() = default;
		~BadyGenerator() = default;

		friend class ::phis2D::World2D;
		friend class ::phis2D::AdderBody;
	private:
		static void GenerateRandBoxStatic(const v2f& pos, float minSide, float maxSide, std::string& outMessage, phis2D::BaseBady2D*& outBady);
		static void GenerateRandBoxStatic(const v2f& pos, std::string& outMessage, phis2D::BaseBady2D*& outBady);

		static void GenerateRandCircleStatic(const v2f& pos, float minRadius, float maxRadius, std::string& outMessage, phis2D::BaseBady2D*& outBady);
		static void GenerateRandCircleStatic(const v2f& pos, std::string& outMessage, phis2D::BaseBady2D*& outBady);

		static void GenerateRandPolygonStatic(const v2f& pos, int n, float minLenght, float maxLenght, std::string& outMessage, phis2D::BaseBady2D*& outBady);
		static void GenerateRandPolygonStatic(const v2f& pos, int n, std::string& outMessage, phis2D::BaseBady2D*& outBady);

		static void GenerateRandColliderStatic(phis2D::collider::VirtualCollider* collider, std::string& outMessage, phis2D::BaseBady2D*& outBady);

		static void GenerateRandBady(const v2f& pos, std::string& outMessage, phis2D::BaseBady2D*& outBady);

		static float minSide;
		static float maxSide;

		static float minRadius;
		static float maxRadius;

		static float minPolygonSide;
		static float maxPolygonSide;
	};

}