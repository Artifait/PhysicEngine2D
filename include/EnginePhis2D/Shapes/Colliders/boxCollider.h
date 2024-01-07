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

			//-----------------------
		};

		//=================out_Fabric=================
		bool CreateBoxCollider(const v2f& pos, const v2f& size, 
			std::string& outMessage, VirtualCollider*& outBoxCollider);
		//=================out_Fabric=================

	}
}