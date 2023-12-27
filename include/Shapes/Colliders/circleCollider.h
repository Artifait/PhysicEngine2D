#pragma once
#include <Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		//��������� ��� �����
		class CircleCollider : public VirtualCollider
		{
		public: 

			//==========base==========
			~CircleCollider() = default;
			const float& GetRadius();
			//========================
			

			//--------------------------��� �����--------------------------
			//================���������� ����������� �������===============

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
		};

		//=================out_Fabric=================
		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);
		//=================out_Fabric=================

	}
}