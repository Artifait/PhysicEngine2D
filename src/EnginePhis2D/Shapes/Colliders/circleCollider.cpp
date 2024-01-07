#include <EnginePhis2D/Shapes/Colliders/circleCollider.h>
#include <EnginePhis2D/SimulateData.h>


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
		phis2D::collider::CircleCollider::CircleCollider(const CircleCollider& other)
			: VirtualCollider(other), Radius{ other.Radius } {}
		phis2D::collider::CircleCollider::CircleCollider(CircleCollider&& other) noexcept
			: VirtualCollider(std::move(other)), Radius{ other.Radius } {}
		CircleCollider& phis2D::collider::CircleCollider::operator=(const CircleCollider& other)
		{
			if (this != &other)
				VirtualCollider::operator=(other);
			return *this;
		}
		CircleCollider& phis2D::collider::CircleCollider::operator=(CircleCollider&& other) noexcept
		{
			if (this != &other)
				VirtualCollider::operator=(std::move(other));
			return *this;
		}
		//-------------Geters-------------
		float phis2D::collider::CircleCollider::GetArea()
		{
			return phis2D::PI * Radius * Radius;
		}
		const float& CircleCollider::GetRadius() { return Radius; }
		typeCollider CircleCollider::GetTypeCollider() { return phis2D::collider::Circle; }
		vecV2f phis2D::collider::CircleCollider::GetTransformedVertices() { return vecV2f(nullptr, 0); }
		v2fRect CircleCollider::GetRectCollider() { return v2fRect(CenterPosition - v2f(Radius, Radius), v2f(2.f * Radius, 2.f * Radius)); }


		//---------Creaters---------

		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider)
		{
			outCircleCollider = nullptr;
			float area = r * r * phis2D::PI;

			if (r > phis2D::worldPhysicConstant::maxRadius)
			{
				outMessage = "[CreateCircleCollider](--errore 'Big Value'){ Ñircle with radius:" + std::to_string(r) + " maximum radius: " +
														std::to_string((int)phis2D::worldPhysicConstant::maxRadius) + "}. }\n";
				return false;
			}
			if (r < phis2D::worldPhysicConstant::minRadius)
			{
				outMessage = "[CreateCircleCollider](--errore 'Small Value'){ Ñircle with radius:" + std::to_string(r) + " minimum radius: " +
					std::to_string((int)phis2D::worldPhysicConstant::maxRadius) + "}. }\n";
				return false;
			}


			outCircleCollider = new(std::nothrow) phis2D::collider::CircleCollider(posCenter, r);

			if (outCircleCollider == nullptr)
			{
				outMessage = "[CreateCircleCollider](--errore 'Memory'){ Memory allocation failed. }\n";
				return false;
			}

			outMessage = "[CreateCircleCollider](created){ Circle with CenterPosition: {" + std::to_string((int)posCenter.x) + ", " + std::to_string((int)posCenter.y) +
				"} and radius: " + std::to_string(r) + "}. }\n";
			return true;
		}

	}
}





