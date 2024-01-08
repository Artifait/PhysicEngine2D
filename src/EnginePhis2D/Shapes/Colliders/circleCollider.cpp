#include <EnginePhis2D/Shapes/Colliders/circleCollider.h>

namespace phis2D::collider
{

#pragma region Defolt
	CircleCollider::CircleCollider(const v2f& posCenter, float r) : Radius(r)
	{
		CenterPosition = posCenter;
	}

	CircleCollider::CircleCollider(const CircleCollider& other)
		: VirtualCollider(other), Radius{ other.Radius } {}

	CircleCollider::CircleCollider(CircleCollider&& other) noexcept
		: VirtualCollider(std::move(other)), Radius{ other.Radius } {}

	CircleCollider& CircleCollider::operator=(const CircleCollider& other)
	{
		if (this != &other)
			VirtualCollider::operator=(other);
		return *this;
	}

	CircleCollider& CircleCollider::operator=(CircleCollider&& other) noexcept
	{
		if (this != &other)
			VirtualCollider::operator=(std::move(other));
		return *this;
	}

	void CircleCollider::SetTriangles() {}
	void CircleCollider::SetVertices() {}
#pragma endregion

#pragma region Getters
	float CircleCollider::GetArea() { return 3.141592f * Radius * Radius; }
	const float& CircleCollider::GetRadius() { return Radius; }
	typeCollider CircleCollider::GetTypeCollider() { return Circle; }
	vecV2f CircleCollider::GetTransformedVertices() { return vecV2f(nullptr, 0); }
	v2fRect CircleCollider::GetRectCollider() { return v2fRect(CenterPosition - v2f(Radius, Radius), v2f(2.f * Radius, 2.f * Radius)); }
#pragma endregion

}




