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

<<<<<<< HEAD
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
=======
			CircleCollider(const CircleCollider& other)
				: VirtualCollider(other), Radius{other.Radius} {}
			CircleCollider(CircleCollider&& other) noexcept
				: VirtualCollider(std::move(other)), Radius{ other.Radius } {}

			CircleCollider& operator=(const CircleCollider& other)
			{
				if (this != &other)
					VirtualCollider::operator=(other);
				return *this;
			}

			CircleCollider& operator=(CircleCollider&& other) noexcept
			{
				if (this != &other)
					VirtualCollider::operator=(std::move(other));
				return *this;
			}


			//--------------------------РВМ часть--------------------------
			//================Реализация Виртуальных Методов===============

			vecV2f GetTransformedVertices() override;
			phis2D::collider::typeCollider GetTypeCollider() override;
			v2fRect GetRectCollider() override;

			//=============================================================


			//=================out_Fabric=================
			friend bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);
			//=================out_Fabric=================
		private:
			void SetTriangles() override {};
			void SetVertices() override {};
			//==========base==========
			CircleCollider(const v2f& posCenter, float r);
			//========================


			//----BaseEtoZnatNado----
			float Radius;
			//-----------------------
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
		};

		//=================out_Fabric=================
		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);
<<<<<<< HEAD
=======
		//=================out_Fabric=================

>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
	}
}