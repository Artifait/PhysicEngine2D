#include <EnginePhis2D/Shapes/Colliders/boxCollider.h>
#include <EnginePhis2D/SimulateData.h>
#include <StructData/TransformPhis2D.h>

namespace phis2D
{
	namespace collider
	{

		phis2D::collider::BoxCollider::BoxCollider(const BoxCollider& other)
			: VirtualCollider(other) {}
		phis2D::collider::BoxCollider::BoxCollider(BoxCollider&& other) noexcept
			: VirtualCollider(std::move(other)) {}
		BoxCollider& phis2D::collider::BoxCollider::operator=(const BoxCollider& other)
		{
			if (this != &other)
				VirtualCollider::operator=(other);
			return *this;
		}

		BoxCollider& phis2D::collider::BoxCollider::operator=(BoxCollider&& other) noexcept
		{
			if (this != &other)
				VirtualCollider::operator=(std::move(other));
			return *this;
		}
		BoxCollider::BoxCollider(const v2f& posCenter, const v2f& size)
			: Size(size)
		{
			CenterPosition = posCenter;
			CreateTriangles(6);
			CreateVertices(4);
			SetVertices();
			SetTriangles();
		}

		//-------------Geters-------------

		const v2f& BoxCollider::GetSize() { return Size; }
		typeCollider BoxCollider::GetTypeCollider() { return phis2D::collider::Box; }


		//---------Creaters---------

		void phis2D::collider::BoxCollider::SetTriangles()
		{
			if (countTriangleIndex != 6) CreateTriangles(6);
			triangleIndex[0] = 0;
			triangleIndex[1] = 1;
			triangleIndex[2] = 2;
			triangleIndex[3] = 0;
			triangleIndex[4] = 2;
			triangleIndex[5] = 3;
		}
		void phis2D::collider::BoxCollider::SetVertices()
		{
			float left, right, bottom, top;

			left = -Size.x / 2.f;
			right = left + Size.x;
			bottom = -Size.y / 2.f;
			top = bottom + Size.y;

			vertices[0] = v2f(left, top);
			vertices[1] = v2f(right, top);
			vertices[2] = v2f(right, bottom);
			vertices[3] = v2f(left, bottom);

			transformUpdateRequired = true;
		}
		float phis2D::collider::BoxCollider::GetArea()
		{
			return Size.x * Size.y;
		}

	}
}





