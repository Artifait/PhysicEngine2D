#include <Shapes/baseBady.h>
#include <SimulateData.h>

namespace phis2D
{
	BaseBady2D::BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area)
		  : ICollider{ collider }, IsStatic{ isStatic }, rotation{ 0.f }, 
			rotationVelocity{0.f}, LinearVelocity{0.f, 0.f}, Density{density},
			Mass{ mass }, Restitution{ restition }, Area{area}   {			}

	BaseBady2D::~BaseBady2D()
	{
		delete ICollider;
	}

	bool BaseBady2D::CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
		float density, float mass, float restition, BaseBady2D* outBady, std::string& outMessage)
	{
		if (collider == nullptr)
		{
			outMessage = "[CreateColliderBady](error){ nullptr collider}\n";
		}
		return true;
	}

	bool BaseBady2D::CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
		float density, float mass, float restition, BaseBady2D* outBady, std::string& outMessage)
	{
		
		return true;
	}

	bool BaseBady2D::CreateBoxBady(const v2f& position, const v2f& size, bool isStatic, 
		float density, float mass, float restition, BaseBady2D* outBady, std::string& outMessage)
	{

		return true;
	}
}