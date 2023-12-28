#include <Shapes/Colliders/boxCollider.h>
#include <SimulateData.h>
#include <StructData/TransformPhis2D.h>

namespace phis2D
{
	namespace collider
	{


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

		bool phis2D::collider::BoxCollider::CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider)
		{
			outBoxCollider = new(std::nothrow) phis2D::collider::BoxCollider(pos, size);
			if (outBoxCollider != nullptr) return true;
			return false;
		}
		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider)
		{
			outBoxCollider = nullptr;
			float area = size.x * size.y;

			if (size.x > phis2D::worldPhysicConstant::maxSide || size.y > phis2D::worldPhysicConstant::maxSide)
			{
				outMessage = "[CreateBoxCollider](--errore 'Big Value'){ Box with sides : {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
					"} maximum side: " + std::to_string((int)phis2D::worldPhysicConstant::maxSide) + ". }\n";
				return false;
			}
			if (size.x < phis2D::worldPhysicConstant::minSide || size.y < phis2D::worldPhysicConstant::minSide)
			{
				outMessage = "[CreateBoxCollider](--errore 'Small Value'){ Box with sides: {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
					"} minimum side: " + std::to_string((int)phis2D::worldPhysicConstant::minSide) + ". }\n";
				return false;
			}

			if (area > phis2D::worldPhysicConstant::maxArea)
			{
				outMessage = "[CreateBoxCollider](--errore 'Big Value'){ Box with Area: " + std::to_string(area) + " maximum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::maxArea) + ". }\n";
				return false;
			}
			if (area < phis2D::worldPhysicConstant::minArea)
			{
				outMessage = "[CreateBoxCollider](--errore 'Small Value'){ Box with Area: " + std::to_string(area) + " minimum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::minArea) + ". }\n";
				return false;
			}

			outBoxCollider = new(std::nothrow) phis2D::collider::BoxCollider(pos, size);
			if (outBoxCollider == nullptr)
			{
				outMessage = "[CreateBoxCollider](--errore 'Memory'){ Memory allocation failed. }\n";
				return false;
			}
			outMessage = "[CreateBoxCollider](created){Box with size: {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
				"} and pos: {" + std::to_string((int)pos.x) + ", " + std::to_string((int)pos.y) + "}. }\n";
			return true;
		}

	}
}





