#pragma once


#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		class PolygonCollider : public VirtualCollider
		{
		public:

			//==========base==========
			~PolygonCollider() = default;
			//========================
			PolygonCollider(const PolygonCollider& other)
				: VirtualCollider(other) {}
			PolygonCollider(PolygonCollider&& other) noexcept
				: VirtualCollider(std::move(other)) {}

			PolygonCollider& operator=(const PolygonCollider& other)
			{
				if (this != &other)
					VirtualCollider::operator=(other);
				return *this;
			}

			PolygonCollider& operator=(PolygonCollider&& other) noexcept
			{
				if (this != &other)
					VirtualCollider::operator=(std::move(other));
				return *this;
			}

			phis2D::collider::typeCollider GetTypeCollider() override;
			vecV2f GetTransformedVertices()
			{
				if (transformUpdateRequired)
				{
					Transform2D transform(CenterPosition, rotation);
					for (int i = 0; i < countVertices; i++)
					{
						transformedVertices[i] = Transform2D::Transform(vertices[i], transform);
					}
					transformedVertices[countVertices] = CenterPosition;
				}
				transformUpdateRequired = false;
				return vecV2f(transformedVertices, countVertices);

			}

			//=================out_Fabric=================
			friend bool CreatePolygonCollider(const vecV2f& virts, std::string& outMessage, VirtualCollider*& outPolygonCollider);
			//=================out_Fabric=================
		private:
			static v2f GetCenter(const vecV2f& virts)
			{
				v2f sum;
				for (int i = 0; i < virts.second; i++)  sum += virts.first[i]; 
				return sum / virts.second;
			}

			void SetTriangles() override;
			void SetVertices() override {}
			void SetVertices(const vecV2f& virts);
			//выделяться будет + 1 тк на последнем индексе храниться центр
			void CreateVertices(size_t countVrt = 0) override;
			PolygonCollider(const vecV2f& virts);
		};

		//=================out_Fabric=================
		bool CreatePolygonCollider(const vecV2f& virts, std::string& outMessage, VirtualCollider*& outPolygonCollider);
		//=================out_Fabric=================
	}
}
