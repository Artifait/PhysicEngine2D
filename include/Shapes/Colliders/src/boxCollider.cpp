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
			return phis2D::Circle;
		}

		BoxCollider::BoxCollider(const v2f& pos, const v2f& size)
			: Position(pos), Size(size)
		{
		}

		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, BoxCollider* outBoxCollider)
		{
			outBoxCollider = nullptr;
			float area = size.x * size.y;

			if (size.x > phis2D::worldPhysicConstant::maxSide || size.y > phis2D::worldPhysicConstant::maxSide)
			{
				outMessage = "\nCreating a box with sides: {" + std::to_string(size.x) + ", " + std::to_string(size.y) + "} greater than the maximum lenght side: " +
					std::to_string(phis2D::worldPhysicConstant::maxSide) + ".\n";
				return false;
			}
			if (size.x < phis2D::worldPhysicConstant::minSide || size.y < phis2D::worldPhysicConstant::minSide)
			{
				outMessage = "\nCreating a box with sides: {" + std::to_string(size.x) + ", " + std::to_string(size.y) + "} less than the minimum lenght side: " +
					std::to_string(phis2D::worldPhysicConstant::minSide) + ".\n";
				return false;
			}

			if (area > phis2D::worldPhysicConstant::maxArea)
			{
				outMessage = "\nCreating a box with Area: " + std::to_string(area) + " greater than the maximum Area: " +
					std::to_string(phis2D::worldPhysicConstant::maxArea) + ".\n";
				return false;
			}
			if (area < phis2D::worldPhysicConstant::minArea)
			{
				outMessage = "\nCreating a box with Area: " + std::to_string(area) + " less than the minimum Area: " +
					std::to_string(phis2D::worldPhysicConstant::minArea) + ".\n";
				return false;
			}

			outBoxCollider = new(std::nothrow) phis2D::collider::BoxCollider(pos, size);
			if (outBoxCollider == nullptr)
			{
				outMessage = "\nMemory allocation failed.\n";
				return false;
			}
			outMessage = "\nBox with size: {" + std::to_string(size.x) + ", " + std::to_string(size.y) +
				"}\n and position: {" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + "} was successfully created.\n";
			return true;
		}

	}
}





