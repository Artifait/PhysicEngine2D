#include <EnginePhis2D/Shapes/baseBady.h>

namespace phis2D
{
#pragma region Defolt
	BaseBady2D::BaseBady2D(const BaseBady2D& other) :
		ICollider(other.ICollider), LinearVelocity(other.LinearVelocity), spaceCollisionTesting(other.spaceCollisionTesting),
		spaceUpdateRequired(other.spaceUpdateRequired), force(other.force), isStatic(other.isStatic),
		RotationVelocity(other.RotationVelocity), Density(other.Density), Mass(other.Mass),
		Restitution(other.Restitution), Area(other.Area), id(other.id), InvMass{ other.InvMass } {}

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
#pragma endregion

#pragma region Collision
	v2f phis2D::BaseBady2D::GetMinCorner() const { return spaceCollisionTesting.GetMinCorner(); }
	v2f phis2D::BaseBady2D::GetMaxCorner() const { return spaceCollisionTesting.GetMaxCorner(); }

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
#pragma endregion

#pragma region Manipulation
	void phis2D::BaseBady2D::Move(const v2f& offset) { ICollider->Move(offset); spaceUpdateRequired = true; }
	void phis2D::BaseBady2D::MoveTo(const v2f& position) { ICollider->MoveTo(position); spaceUpdateRequired = true; }
	void phis2D::BaseBady2D::Rotate(float amount) { ICollider->Rotate(amount); spaceUpdateRequired = true; }
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
#pragma endregion

#pragma region Getters
	const v2f& phis2D::BaseBady2D::GetLinearVelocity() const { return LinearVelocity; }
	const float& phis2D::BaseBady2D::GetArea() const { return Area; }
	const float& phis2D::BaseBady2D::GetMass() const { return Mass; }
	const float& phis2D::BaseBady2D::GetDensity() const { return Density; }
	const float& phis2D::BaseBady2D::GetRestitution() const { return Restitution; }
	const bool& phis2D::BaseBady2D::IsStatic() const { return this->isStatic; }
	const v2f& phis2D::BaseBady2D::GetPosition() const { return ICollider->GetCenterPosition(); }
#pragma endregion

	size_t BaseBady2D::CountCreatedObject = 0;
	std::vector<size_t> BaseBady2D::freeId;
}