#pragma once
#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		class BoxCollider : public VirtualCollider
		{
		public:

			//==========base==========
			~BoxCollider() = default;
<<<<<<< HEAD

			BoxCollider(const BoxCollider& other);
			BoxCollider(BoxCollider&& other) noexcept;
			BoxCollider& operator=(const BoxCollider& other);
			BoxCollider& operator=(BoxCollider&& other) noexcept;

			phis2D::collider::typeCollider GetTypeCollider() override;
			float GetArea() override;
			const v2f& GetSize();

			friend bool CreateBoxCollider(const v2f& pos, const v2f& size, 
				std::string& outMessage, VirtualCollider*& outBoxCollider);
		private:
			friend class World2D;
			friend class AdderBody;
			//----------------------------without limits---------------------------
			static bool CreateBoxCollider(const v2f& pos, const v2f& size, 
				std::string& outMessage, VirtualCollider*& outBoxCollider);

			void SetTriangles() override;
			void SetVertices() override;

			//==========base==========
			BoxCollider(const v2f& posCenter, const v2f& size);
			v2f Size;
=======
			const v2f& GetSize();
			//========================

			BoxCollider(const BoxCollider& other)
				: VirtualCollider(other) {}
			BoxCollider(BoxCollider&& other) noexcept
				: VirtualCollider(std::move(other)) {}
			BoxCollider& operator=(const BoxCollider& other)
			{
				if (this != &other)
					VirtualCollider::operator=(other);
				return *this;
			}
			BoxCollider& operator=(BoxCollider&& other) noexcept
			{
				if (this != &other)
					VirtualCollider::operator=(std::move(other));
				return *this;
			}


			//--------------------------РВМ часть--------------------------
			//================Реализация Виртуальных Методов===============

			phis2D::collider::typeCollider GetTypeCollider() override;

			//=================out_Public_Fabric=================
			friend bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);
			//=================out_Public_Fabric=================
		private:
			friend class World2D;
			//---------------------------------without limits--------------------------------
			//=================inner_Private_Fabric=================
			static bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);
			//=================inner_Private_Fabric=================
			void SetTriangles() override;
			void SetVertices() override;
			//==========base==========
			BoxCollider(const v2f& posCenter, const v2f& size);

			v2f Size;

>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
			//-----------------------
		};

		//=================out_Fabric=================
<<<<<<< HEAD
		bool CreateBoxCollider(const v2f& pos, const v2f& size, 
			std::string& outMessage, VirtualCollider*& outBoxCollider);
=======
		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
		//=================out_Fabric=================

	}
}