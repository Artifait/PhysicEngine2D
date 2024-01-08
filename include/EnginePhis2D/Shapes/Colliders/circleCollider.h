#pragma once
#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>

namespace phis2D::collider
{
	//Коллайдер для Круга
	class CircleCollider : public VirtualCollider
	{
	public:
#pragma region Defolt
		~CircleCollider() = default;
		CircleCollider(const CircleCollider& other);
		CircleCollider(CircleCollider&& other) noexcept;
		CircleCollider& operator=(const CircleCollider& other);
		CircleCollider& operator=(CircleCollider&& other) noexcept;
#pragma endregion

#pragma region Getters
		typeCollider GetTypeCollider() override;
		vecV2f GetTransformedVertices() override;
		v2fRect GetRectCollider() override;
		float GetArea() override;
		const float& GetRadius();
#pragma endregion

	private:
		friend class AdderBody;

		void SetTriangles() override;
		void SetVertices() override;

		CircleCollider(const v2f& posCenter, float r);
		float Radius;
	};

}