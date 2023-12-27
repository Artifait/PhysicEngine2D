#include <Shapes/baseBady.h>
#include <SimulateData.h>

namespace phis2D
{
	BaseBady2D::BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area)
		  : ICollider{ collider }, isStatic{ isStatic },
			RotationVelocity{0.f}, LinearVelocity{0.f, 0.f}, Density{density},
		Mass{ mass }, Restitution{ restition }, Area{ area } 
	{
		if(freeId.empty())
		{
			CountCreatedObject++;
			id = CountCreatedObject;
		}
		else
		{
			id = freeId[0];
			freeId.erase(freeId.begin());
		}
	}

	BaseBady2D::~BaseBady2D() { delete ICollider; freeId.push_back(id); }
	void phis2D::BaseBady2D::ApplyForce(const v2f& amount) { force = amount; }
	void phis2D::BaseBady2D::Step(float DT)
	{
		LinearVelocity += force * DT;
		ICollider->Move(LinearVelocity * DT);
		ICollider->Rotate(RotationVelocity * DT);
		force = v2f();
	}

	void phis2D::BaseBady2D::Move(const v2f& offset) { ICollider->Move(offset); }
	void phis2D::BaseBady2D::MoveTo(const v2f& position) { ICollider->MoveTo(position); }
	void phis2D::BaseBady2D::Rotate(float amount) { ICollider->Rotate(amount); }

	//Getters
	const v2f& phis2D::BaseBady2D::GetLinearVelocity() const { return LinearVelocity; }
	const float& phis2D::BaseBady2D::GetArea() const { return Area; }
	const float& phis2D::BaseBady2D::GetMass() const { return Mass; }
	const float& phis2D::BaseBady2D::GetDensity() const { return Density; }
	const float& phis2D::BaseBady2D::GetRestitution() const { return Restitution; }
	const bool& phis2D::BaseBady2D::IsStatic() const { return this->isStatic; }

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

		//Может глючить изза нее нужно для polygonov по другому расчитывать площадь
		float area = collider->GetTypeCollider() == phis2D::collider::Circle ?
			std::pow(static_cast<phis2D::collider::CircleCollider*>(collider)->GetRadius(), 2.f) * PI
			: collider->GetRectCollider().GetSize().x * collider->GetRectCollider().GetSize().y;

		outBady = new(std::nothrow) phis2D::BaseBady2D(collider, isStatic, density, mass, restition, area);
		if (outBady == nullptr)
		{
			outMessage = "[CreateColliderBady](--errore 'Memory'){ Memory allocation failed. }\n";
			return false;
		}
		outMessage = "[CreateColliderBady](created){ Bse Norm. }\n";
		return true;
	}

	bool BaseBady2D::CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
		float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
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

		collider::VirtualCollider* boxCollider;
		std::string outMsg;
		if (!collider::CreateCircleCollider(posCenter, r, outMsg, boxCollider))
		{
			outMessage = "[CreateCircleCollider](error 'CreateCircleCollider'){\n\t" + outMsg + "}\n";
			return false;
		}
		return true;
	}

	bool BaseBady2D::CreateBoxBady(const v2f& position, const v2f& size, bool isStatic, 
		float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
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

		collider::VirtualCollider* boxCollider;
		std::string outMsg;
		if (!collider::CreateBoxCollider(position, size, outMsg, boxCollider))
		{
			outMessage = "[CreateColliderBady](error 'CreateBoxCollider'){\n\t" + outMsg + "}\n";
			return false;
		}
		
		float area = size.x * size.y;

		outBady = new(std::nothrow) phis2D::BaseBady2D(boxCollider, isStatic, density, mass, restition, area);
		if (outBady == nullptr)
		{
			outMessage = "[CreateColliderBady](--errore 'Memory'){ Memory allocation failed. }\n";
			return false;
		}
		outMessage = "[CreateColliderBady](created){ Bse Norm. }\n";
		return true;
	}
	size_t BaseBady2D::CountCreatedObject = 0;
	std::vector<size_t> BaseBady2D::freeId;
}