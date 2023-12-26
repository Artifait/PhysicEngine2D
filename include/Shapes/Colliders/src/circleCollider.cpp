#include <Shapes/Colliders/circleCollider.h>
#include <SimulateData.h>


namespace phis2D
{
	namespace collider
	{
		//----------------Init-------------------

		CircleCollider::CircleCollider(const v2f& posCenter, float r)
			: Radius(r)
		{
			CenterPosition = posCenter;
		}

		//-------------Geters-------------

		const float& CircleCollider::GetRadius() { return Radius; }
		typeCollider CircleCollider::GetTypeCollider() { return phis2D::collider::Circle; }
		const vecV2f& phis2D::collider::CircleCollider::GetTransformedVertices() { return vecV2f(nullptr, 0); }
		v2fRect CircleCollider::GetRectCollider() { return v2fRect(CenterPosition - v2f(Radius, Radius), v2f(2.f * Radius, 2.f * Radius)); }


		//---------Creaters---------

		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider)
		{
			outCircleCollider = nullptr;
			float area = r * r * phis2D::PI;

			if (r > phis2D::worldPhysicConstant::maxRadius)
			{
				outMessage = "[CreateCircleCollider](--errore 'Big Value')\n {\n\tcircle with radius:" + std::to_string(r) + " maximum radius: " +
														std::to_string((int)phis2D::worldPhysicConstant::maxRadius) + "}.\n }\n";
				return false;
			}
			if (r < phis2D::worldPhysicConstant::minRadius)
			{
				outMessage = "[CreateCircleCollider](--errore 'Small Value')\n {\n\tcircle with radius:" + std::to_string(r) + " minimum radius: " +
					std::to_string((int)phis2D::worldPhysicConstant::maxRadius) + "}.\n }\n";
				return false;
			}
			if (area > phis2D::worldPhysicConstant::maxArea)
			{
				outMessage = "[CreateCircleCollider](--errore 'Big Value')\n {\n\tcircle with Area: " + std::to_string((int)area) + " maximum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::maxArea) + "}.\n }\n";
				return false;
			}
			if (area < phis2D::worldPhysicConstant::minArea)
			{
				outMessage = "[CreateCircleCollider](--errore 'Small Value')\n {\n\tcircle with Area: " + std::to_string((int)area) + " minimum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::minArea) + "}.\n }\n";
				return false;
			}

			outCircleCollider = new(std::nothrow) phis2D::collider::CircleCollider(posCenter, r);

			if (outCircleCollider == nullptr)
			{
				outMessage = "[CreateCircleCollider](--errore 'Memory'){ Memory allocation failed. }\n";
				return false;
			}

			outMessage = "[CreateCircleCollider](created)\n {\n\tCircle with CenterPosition: {" + std::to_string((int)posCenter.x) + ", " + std::to_string((int)posCenter.y) +
				"} and radius: " + std::to_string(r) + "}.\n }\n";
			return true;
		}

	}
}





