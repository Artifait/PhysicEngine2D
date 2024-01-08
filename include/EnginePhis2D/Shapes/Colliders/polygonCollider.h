#pragma once
#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		class PolygonCollider : public VirtualCollider
		{
		public:
#pragma region Defolt
			~PolygonCollider() = default;
			PolygonCollider(const PolygonCollider& other);
			PolygonCollider(PolygonCollider&& other) noexcept;
			PolygonCollider& operator=(const PolygonCollider& other);
			PolygonCollider& operator=(PolygonCollider&& other) noexcept;
#pragma endregion

#pragma region Getters
			float GetArea() override;
			phis2D::collider::typeCollider GetTypeCollider() override;
			static v2f GetCenter(const vecV2f& virts);
			vecV2f GetTransformedVertices();
#pragma endregion

		private:
			friend class AdderBody;

			void SetTriangles() override;
			void SetVertices() override;
			void SetVertices(const vecV2f& virts);

			//выделяться будет + 1 тк на последнем индексе храниться центр
			void CreateVertices(size_t countVrt = 0) override;
			PolygonCollider(const vecV2f& virts);
		};

	}
}
