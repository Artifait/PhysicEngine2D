#pragma once
#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		//Коллайдер для Круга
		class CircleCollider : public VirtualCollider
		{
		public: 

			//==========base==========
			~CircleCollider() = default;
			const float& GetRadius();
			//========================

			CircleCollider(const CircleCollider& other);
			CircleCollider(CircleCollider&& other) noexcept;
			CircleCollider& operator=(const CircleCollider& other);
			CircleCollider& operator=(CircleCollider&& other) noexcept;

			phis2D::collider::typeCollider GetTypeCollider() override;
			vecV2f GetTransformedVertices() override;
			v2fRect GetRectCollider() override;
			float GetArea() override;
			friend bool CreateCircleCollider(const v2f& posCenter, float r, 
				std::string& outMessage, VirtualCollider*& outCircleCollider);
		private:
			friend class AdderBody;

			void SetTriangles() override {};
			void SetVertices() override {};

			CircleCollider(const v2f& posCenter, float r);
			float Radius;

		};

		//=================out_Fabric=================
		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);

	}
}