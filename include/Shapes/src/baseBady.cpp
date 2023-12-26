#include <Shapes/baseBady.h>
#include <SimulateData.h>

namespace phis2D
{
	BaseBady2D::BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area)
		  : ICollider{ collider }, IsStatic{ isStatic },  
			rotationVelocity{0.f}, LinearVelocity{0.f, 0.f}, Density{density},
			Mass{ mass }, Restitution{ restition }, Area{area}   {			}

	BaseBady2D::~BaseBady2D()
	{
		delete ICollider;
	}

	bool BaseBady2D::CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
		float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
		if (collider == nullptr)
		{
			outMessage = "[CreateColliderBady](--error 'Memory')\n {\n\tnullptr collider}\n";
			return false;
		}
		if (density > worldPhysicConstant::MaxDensity)
		{
			outMessage = "[CreateColliderBady](--error 'Big Value')\n {\n\tMax density: " + std::to_string(worldPhysicConstant::MaxDensity) + 
				", you density: " + std::to_string(density) + ".\n}\n";
			return false;
		}
		if (density < worldPhysicConstant::MinDensity)
		{
			outMessage = "[CreateColliderBady](error 'Small Value')\n {\n\tMin density: " + std::to_string(worldPhysicConstant::MinDensity) +
				", you density: " + std::to_string(density) + ".\n}\n";
			return false;
		}
		float area = collider->GetTypeCollider() == phis2D::collider::Circle ?
			std::pow(static_cast<phis2D::collider::CircleCollider*>(collider)->GetRadius(), 2.f) * PI
			: collider->GetRectCollider().GetSize().x * collider->GetRectCollider().GetSize().y;

		outBady = new(std::nothrow) phis2D::BaseBady2D(collider, isStatic, density, mass, restition, area);
		if (outBady == nullptr)
		{
			outMessage = "[CreateColliderBady](--errore 'Memory'){ Memory allocation failed. }\n";
			return false;
		}
		return true;
	}

	bool BaseBady2D::CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
		float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
		
		return true;
	}

	bool BaseBady2D::CreateBoxBady(const v2f& position, const v2f& size, bool isStatic, 
		float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{

		return true;
	}
}