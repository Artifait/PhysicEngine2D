#include <Shapes/Colliders/boxCollider.h>
#include <SimulateData.h>

namespace phis2D
{
	namespace collider
	{
		const v2f& BoxCollider::GetPosition()
		{
			return Position;
		}
		const v2f& BoxCollider::GetSize()
		{
			return Size;
		}

		typeCollider BoxCollider::GetTypeCollider()
		{
			return phis2D::collider::Circle;
		}

		BoxCollider::BoxCollider(const v2f& pos, const v2f& size)
			: Position(pos), Size(size)
		{
		}

		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider* outBoxCollider)
		{
			outBoxCollider = nullptr;
			float area = size.x * size.y;

			if (size.x > phis2D::worldPhysicConstant::maxSide || size.y > phis2D::worldPhysicConstant::maxSide)
			{
				outMessage = "[CreateBoxCollider](--errore 'Big Value')\n {\n\tbox with sides : {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
					"} maximum side: " + std::to_string((int)phis2D::worldPhysicConstant::maxSide) + ".\n }\n";
				return false;
			}
			if (size.x < phis2D::worldPhysicConstant::minSide || size.y < phis2D::worldPhysicConstant::minSide)
			{
				outMessage = "[CreateBoxCollider](--errore 'Min Value')\n {\n\tbox with sides: {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
					"} minimum side: " + std::to_string((int)phis2D::worldPhysicConstant::minSide) + ".\n }\n";
				return false;
			}

			if (area > phis2D::worldPhysicConstant::maxArea)
			{
				outMessage = "[CreateBoxCollider](--errore 'Big Value')\n {\n\tbox with Area: " + std::to_string(area) + " maximum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::maxArea) + ".\n }\n";
				return false;
			}
			if (area < phis2D::worldPhysicConstant::minArea)
			{
				outMessage = "[CreateBoxCollider](--errore 'Min Value')\n {\n\tbox with Area: " + std::to_string(area) + " minimum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::minArea) + ".\n }\n";
				return false;
			}

			outBoxCollider = new(std::nothrow) phis2D::collider::BoxCollider(pos, size);
			if (outBoxCollider == nullptr)
			{
				outMessage = "[CreateBoxCollider](--errore 'Memory'){ Memory allocation failed. }\n";
				return false;
			}
			outMessage = "[CreateBoxCollider](created)\n {\n\tBox with size: {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
				"} and pos: {" + std::to_string((int)pos.x) + ", " + std::to_string((int)pos.y) + "}.\n }\n";
			return true;
		}

	}
}





