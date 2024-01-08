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

	::phis2D::collider::vecV2f GenerateRandVerticesPolygon(const v2f& posCenter, int n, float minLenght, float maxLenght);
	::phis2D::collider::vecV2f GenerateRandVerticesPolygon(const v2f& posCenter, int n);

}