#include <Shapes/Colliders/circleCollider.h>
#include <SimulateData.h>


namespace phis2D
{
	namespace collider
	{
		const v2f& CircleCollider::GetPosition()
		{
			return CenterPosition;
		}
		const float& CircleCollider::GetRadius()
		{
			return Radius;
		}

		typeCollider CircleCollider::GetTypeCollider()
		{
			return phis2D::Circle;
		}

		CircleCollider::CircleCollider(const v2f& posCenter, float r)
			: Radius(r), CenterPosition(posCenter)
		{
		}

		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, CircleCollider* outCircleCollider)
		{
			outCircleCollider = nullptr;
			float area = r * r * phis2D::PI;

			if (r > phis2D::worldPhysicConstant::maxRadius)
			{
				outMessage = "\nCreating a circle with radius:" + std::to_string(r) + " greater than the maximum radius: " +
														std::to_string(phis2D::worldPhysicConstant::maxRadius) + ".\n";
				return false;
			}
			if (r < phis2D::worldPhysicConstant::minRadius)
			{
				outMessage = "\nCreating a circle with radius:" + std::to_string(r) + " less than the minimum radius: " +
					std::to_string(phis2D::worldPhysicConstant::maxRadius) + ".\n";
				return false;
			}
			if (area > phis2D::worldPhysicConstant::maxArea)
			{
				outMessage = "\nCreating a circle with Area: " + std::to_string(area) + " greater than the maximum Area: " +
					std::to_string(phis2D::worldPhysicConstant::maxArea) + ".\n";
				return false;
			}
			if (area < phis2D::worldPhysicConstant::minArea)
			{
				outMessage = "\nCreating a circle with Area: " + std::to_string(area) + " less than the minimum Area: " +
					std::to_string(phis2D::worldPhysicConstant::minArea) + ".\n";
				return false;
			}

			outCircleCollider = new(std::nothrow) phis2D::collider::CircleCollider(posCenter, r);
			if (outCircleCollider == nullptr)
			{
				outMessage = "\nMemory allocation failed.\n";
				return false;
			}

			outMessage = "\nCircle with CenterPosition: {" + std::to_string(posCenter.x) + ", " + std::to_string(posCenter.y) +
				"}\n and radius: " + std::to_string(r) + " was successfully created.\n";
			return true;
		}

	}
}





