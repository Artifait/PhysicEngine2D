#include <EnginePhis2D/Shapes/baseBady.h>
#include <EnginePhis2D/SimulateData.h>

namespace phis2D
{
	BaseBady2D::BaseBady2D(const BaseBady2D& other) :
		ICollider(other.ICollider), LinearVelocity(other.LinearVelocity), spaceCollisionTesting(other.spaceCollisionTesting),
		spaceUpdateRequired(other.spaceUpdateRequired), force(other.force), isStatic(other.isStatic),
		RotationVelocity(other.RotationVelocity), Density(other.Density), Mass(other.Mass),
		Restitution(other.Restitution), Area(other.Area), id(other.id), InvMass{ other.InvMass } {}

	BaseBady2D::BaseBady2D(BaseBady2D* other) :
		ICollider(other->ICollider), LinearVelocity(other->LinearVelocity), spaceCollisionTesting(other->spaceCollisionTesting),
		spaceUpdateRequired(other->spaceUpdateRequired), force(other->force), isStatic(other->isStatic),
		RotationVelocity(other->RotationVelocity), Density(other->Density), Mass(other->Mass),
		Restitution(other->Restitution), Area(other->Area), id(other->id), InvMass{ other->InvMass } {}
	BaseBady2D::BaseBady2D(BaseBady2D&& other) noexcept
	{
		// Переносим данные класса
		ICollider = other.ICollider;
		LinearVelocity = std::move(other.LinearVelocity);
		spaceCollisionTesting = std::move(other.spaceCollisionTesting);
		spaceUpdateRequired = other.spaceUpdateRequired;
		force = std::move(other.force);
		isStatic = other.isStatic;
		RotationVelocity = other.RotationVelocity;
		Density = other.Density;
		Mass = other.Mass;
		InvMass = other.InvMass;
		Restitution = other.Restitution;
		Area = other.Area;
		id = other.id;

		// Обнуляем данные оригинального объекта
		other.ICollider = nullptr;
		other.spaceUpdateRequired = true;
		other.isStatic = false;
		other.RotationVelocity = 0.0f;
		other.Density = 0.0f;
		other.Mass = 0.0f;
		other.Restitution = 0.0f;
		other.Area = 0.0f;
		other.id = 0;
	}

	BaseBady2D& BaseBady2D::operator=(BaseBady2D&& other) noexcept
	{
		if (this == &other)  // Проверка на самоприсваивание
			return *this;

		// Переносим данные класса
		ICollider = other.ICollider;
		LinearVelocity = std::move(other.LinearVelocity);
		spaceCollisionTesting = std::move(other.spaceCollisionTesting);
		spaceUpdateRequired = other.spaceUpdateRequired;
		force = std::move(other.force);
		isStatic = other.isStatic;
		RotationVelocity = other.RotationVelocity;
		Density = other.Density;
		Mass = other.Mass;
		Restitution = other.Restitution;
		Area = other.Area;
		id = other.id;

		// Обнуляем данные оригинального объекта
		other.ICollider = nullptr;
		other.spaceUpdateRequired = true;
		other.isStatic = false;
		other.RotationVelocity = 0.0f;
		other.Density = 0.0f;
		other.Mass = 0.0f;
		other.Restitution = 0.0f;
		other.Area = 0.0f;
		other.id = 0;

		return *this;
	}
	const v2f& phis2D::BaseBady2D::GetPosition() const
	{
		return ICollider->GetCenterPosition();
	}
	v2fRect BaseBady2D::GetRectPossibilityCollision(float DT) {
		if (spaceUpdateRequired)
		{
			v2f minPast, maxPast, minFuture, maxFuture;
			v2fRect pastRect(ICollider->GetRectCollider());
			minPast = pastRect.GetMinCorner();
			maxPast = pastRect.GetMaxCorner();
			pastRect.Move(LinearVelocity * DT);
			minFuture = pastRect.GetMinCorner();
			maxFuture = pastRect.GetMaxCorner();

			v2f minPos(std::min({ minPast.x, maxPast.x, minFuture.x, maxFuture.x }), std::min({ minPast.y, maxPast.y, minFuture.y, maxFuture.y }));
			v2f maxPos(std::max({ minPast.x, maxPast.x, minFuture.x, maxFuture.x }), std::max({ minPast.y, maxPast.y, minFuture.y, maxFuture.y }));
			spaceCollisionTesting = v2fRect(minPos, maxPos - minPos);
			spaceUpdateRequired = false;
		}

		return spaceCollisionTesting;

	}
	
	v2fRect BaseBady2D::GetRectPossibilityCollision() {
		if (spaceUpdateRequired)
		{
			v2f minPast, maxPast, minFuture, maxFuture;
			v2fRect pastRect(ICollider->GetRectCollider());
			minPast = pastRect.GetMinCorner();
			maxPast = pastRect.GetMaxCorner();
			pastRect.Move(LinearVelocity);
			minFuture = pastRect.GetMinCorner();
			maxFuture = pastRect.GetMaxCorner();

			v2f minPos(std::min({ minPast.x, maxPast.x, minFuture.x, maxFuture.x }), std::min({ minPast.y, maxPast.y, minFuture.y, maxFuture.y }));
			v2f maxPos(std::max({ minPast.x, maxPast.x, minFuture.x, maxFuture.x }), std::max({ minPast.y, maxPast.y, minFuture.y, maxFuture.y }));
			spaceCollisionTesting = v2fRect(minPos, maxPos - minPos);
			spaceUpdateRequired = false;
		}
		return spaceCollisionTesting;
	}

	BaseBady2D& BaseBady2D::operator=(const BaseBady2D& other)
	{
		if (this == &other)  // Проверка на самоприсваивание
			return *this;

		// Копируем данные класса
		ICollider = other.ICollider;
		LinearVelocity = other.LinearVelocity;
		spaceCollisionTesting = other.spaceCollisionTesting;
		spaceUpdateRequired = other.spaceUpdateRequired;
		force = other.force;
		isStatic = other.isStatic;
		RotationVelocity = other.RotationVelocity;
		Density = other.Density;
		Mass = other.Mass;
		Restitution = other.Restitution;
		Area = other.Area;
		id = other.id;

		return *this;
	}

	BaseBady2D::BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area)
		: ICollider{ collider }, isStatic{ isStatic },
		RotationVelocity{ 0.f }, LinearVelocity{ 0.f, 0.f }, Density{ density },
		Mass{ mass }, Restitution{ restition }, Area{ area }
	{
		if (freeId.empty())
		{
			CountCreatedObject++;
			id = CountCreatedObject;
		}
		else
		{
			id = freeId[0];
			freeId.erase(freeId.begin());
		}
		isStatic ? InvMass = 0.f : InvMass = 1.f / Mass;
	}

	BaseBady2D::~BaseBady2D() { delete ICollider; freeId.push_back(id); }
	void phis2D::BaseBady2D::ApplyForce(const v2f& amount) { force = amount; }
	void phis2D::BaseBady2D::Step(float DT, const v2f& gravity)
	{
		v2f acceleration = force / Mass;
		LinearVelocity += acceleration * DT;
		LinearVelocity += gravity * DT;
		ICollider->Move(LinearVelocity * DT);
		ICollider->Rotate(RotationVelocity * DT);
		force = v2f();
		spaceUpdateRequired = true;
		GetRectPossibilityCollision(DT);
	}

	void phis2D::BaseBady2D::Move(const v2f& offset) { ICollider->Move(offset); spaceUpdateRequired = true; }
	void phis2D::BaseBady2D::MoveTo(const v2f& position) { ICollider->MoveTo(position); spaceUpdateRequired = true; }
	void phis2D::BaseBady2D::Rotate(float amount) { ICollider->Rotate(amount); spaceUpdateRequired = true; }

	//Getters
	const v2f& phis2D::BaseBady2D::GetLinearVelocity() const { return LinearVelocity; }
	const float& phis2D::BaseBady2D::GetArea() const { return Area; }
	const float& phis2D::BaseBady2D::GetMass() const { return Mass; }
	const float& phis2D::BaseBady2D::GetDensity() const { return Density; }
	const float& phis2D::BaseBady2D::GetRestitution() const { return Restitution; }
	const bool& phis2D::BaseBady2D::IsStatic() const { return this->isStatic; }

	bool BaseBady2D::CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
		float density, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
		if (collider == nullptr)
		{
			outMessage = "[CreateColliderBady](--error 'Memory'){ nullptr collider }\n";
			return false;
		}
		if (density > worldPhysicConstant::MaxDensity)
		{
			outMessage = "[CreateColliderBady](--error 'Big Value'){ Max density: " + std::to_string(worldPhysicConstant::MaxDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}
		if (density < worldPhysicConstant::MinDensity)
		{
			outMessage = "[CreateColliderBady](error 'Small Value'){ Min density: " + std::to_string(worldPhysicConstant::MinDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}

		//Может глючить изза нее нужно для polygonov по другому расчитывать площадь
		float area = collider->GetArea();
		float mass = area * density * 10.f / phis2D::worldPhysicConstant::scale; //10 тк перевод из м^2 в см^2(тоесть умножить на 10000)и гр в кг(тоесть разделить на 1000)
		//mass = area * density;

		outBady = new(std::nothrow) phis2D::BaseBady2D(collider, isStatic, density, mass, restition, area);
		if (outBady == nullptr)
		{
			outMessage = "[CreateColliderBady](--errore 'Memory'){ Memory allocation failed. }\n";
			return false;
		}
		outMessage = "[CreateColliderBady](created){ Bse Norm. }\n";
		return true;
	}
	bool phis2D::BaseBady2D::CreatePolygonBady(const v2f& posCenter, const v2f* vertices, size_t cntVertices, bool isStatic, float density, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
		if (density > worldPhysicConstant::MaxDensity)
		{
			outMessage = "[CreatePolygonBady](--error 'Big Value'){ Max density: " + std::to_string(worldPhysicConstant::MaxDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}
		if (density < worldPhysicConstant::MinDensity)
		{
			outMessage = "[CreatePolygonBady](error 'Small Value'){ Min density: " + std::to_string(worldPhysicConstant::MinDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}
		collider::VirtualCollider* polygonCollider;
		std::string outMsg;
		if (!collider::CreatePolygonCollider(phis2D::collider::vecV2f(vertices, cntVertices), outMsg, polygonCollider))
		{
			outMessage = "[CreatePolygonBady](error 'CreateCircleCollider'){\n\t" + outMsg + "}\n";
			return false;
		}
		polygonCollider->MoveTo(posCenter);
		float area = polygonCollider->GetArea();
		float mass = area * density * 10.f / phis2D::worldPhysicConstant::scale; //10 тк перевод из м^2 в см^2(тоесть умножить на 10000)и гр в кг(тоесть разделить на 1000)
		outBady = new(std::nothrow) phis2D::BaseBady2D(polygonCollider, isStatic, density, mass, restition, area);
		if (outBady == nullptr)
		{
			outMessage = "[CreatePolygonBady](--errore 'Memory'){ Memory allocation failed. }\n";
			return false;
		}
		outMessage = "[CreatePolygonBady](created){ Bse Norm. }\n";
		return true;
	}
	bool BaseBady2D::CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
		float density, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
		if (density > worldPhysicConstant::MaxDensity)
		{
			outMessage = "[CreateColliderBady](--error 'Big Value'){ Max density: " + std::to_string(worldPhysicConstant::MaxDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}
		if (density < worldPhysicConstant::MinDensity)
		{
			outMessage = "[CreateColliderBady](error 'Small Value'){ Min density: " + std::to_string(worldPhysicConstant::MinDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}

		collider::VirtualCollider* circleCollider;
		std::string outMsg;
		if (!collider::CreateCircleCollider(posCenter, r, outMsg, circleCollider))
		{
			outMessage = "[CreateCircleCollider](error 'CreateCircleCollider'){\n\t" + outMsg + "}\n";
			return false;
		}

		float area = circleCollider->GetArea();
		float mass = area * density * 10.f / phis2D::worldPhysicConstant::scale; //10 тк перевод из м^2 в см^2(тоесть умножить на 10000)и гр в кг(тоесть разделить на 1000)

		outBady = new(std::nothrow) phis2D::BaseBady2D(circleCollider, isStatic, density, mass, restition, area);
		if (outBady == nullptr)
		{
			outMessage = "[CreateColliderBady](--errore 'Memory'){ Memory allocation failed. }\n";
			return false;
		}
		outMessage = "[CreateColliderBady](created){ Bse Norm. }\n";

		return true;
	}

	bool BaseBady2D::CreateBoxBady(const v2f& position, const v2f& size, bool isStatic,
		float density, float restition, BaseBady2D*& outBady, std::string& outMessage)
	{
		if (density > worldPhysicConstant::MaxDensity)
		{
			outMessage = "[CreateColliderBady](--error 'Big Value'){ Max density: " + std::to_string(worldPhysicConstant::MaxDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}
		if (density < worldPhysicConstant::MinDensity)
		{
			outMessage = "[CreateColliderBady](error 'Small Value'){ Min density: " + std::to_string(worldPhysicConstant::MinDensity) +
				", you density: " + std::to_string(density) + ". }\n";
			return false;
		}


		collider::VirtualCollider* boxCollider;
		std::string outMsg;
		if (!collider::CreateBoxCollider(position, size, outMsg, boxCollider))
		{
			outMessage = "[CreateColliderBady](error 'CreateBoxCollider'){\n\t" + outMsg + "}\n";
			return false;
		}

		float area = boxCollider->GetArea();
		float mass = area * density * 10.f / phis2D::worldPhysicConstant::scale; //10 тк перевод из м^2 в см^2(тоесть умножить на 10000)и гр в кг(тоесть разделить на 1000)

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