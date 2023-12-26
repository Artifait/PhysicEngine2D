#pragma once
#include <Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		class BoxCollider : public VirtualCollider
		{
		public:

			//==========base==========
			~BoxCollider() = default;
			const v2f& GetSize();
			//========================

			//--------------------------РВМ часть--------------------------
			//================Реализация Виртуальных Методов===============

			phis2D::collider::typeCollider GetTypeCollider() override;

			//=================out_Fabric=================
			friend bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);
			//=================out_Fabric=================

		private:
			void SetTriangles() override;
			void SetVertices() override;

			//==========base==========
			BoxCollider(const v2f& posCenter, const v2f& size);

			v2f Size;

			//-----------------------
		};

		//=================out_Fabric=================
		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);
		//=================out_Fabric=================

	}
}