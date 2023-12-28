#pragma once
#include <Shapes/Colliders.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace phis2D
{
	// ���������� ����
	class BaseBady2D;
}
namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider,
			bool filled = true, bool boundary = false, const sf::Color& col = sf::Color(34, 109, 224));
		void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled = true, bool boundary = false,
			bool possibilityBoundary = false, const sf::Color& col = sf::Color(34, 109, 224));
	}
}



namespace phis2D
{
	// ���������� ����
	class BaseBady2D
	{
	public:
		static bool CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
			float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreateBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage);
		// ����������� �����������
		BaseBady2D(const BaseBady2D& other) :
			ICollider(other.ICollider), LinearVelocity(other.LinearVelocity), spaceCollisionTesting(other.spaceCollisionTesting),
			spaceUpdateRequired(other.spaceUpdateRequired), force(other.force), isStatic(other.isStatic),
			RotationVelocity(other.RotationVelocity), Density(other.Density), Mass(other.Mass),
			Restitution(other.Restitution), Area(other.Area), id(other.id) {}
		BaseBady2D(BaseBady2D* other) :
			ICollider(other->ICollider), LinearVelocity(other->LinearVelocity), spaceCollisionTesting(other->spaceCollisionTesting),
			spaceUpdateRequired(other->spaceUpdateRequired), force(other->force), isStatic(other->isStatic),
			RotationVelocity(other->RotationVelocity), Density(other->Density), Mass(other->Mass),
			Restitution(other->Restitution), Area(other->Area), id(other->id) {}
		// ����������� ��������
		BaseBady2D(BaseBady2D&& other) noexcept
		{
			// ��������� ������ ������
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

			// �������� ������ ������������� �������
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

		// �������� ������������
		BaseBady2D& operator=(const BaseBady2D& other)
		{
			if (this == &other)  // �������� �� ����������������
				return *this;

			// �������� ������ ������
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

		// �������� �����������
		BaseBady2D& operator=(BaseBady2D&& other) noexcept
		{
			if (this == &other)  // �������� �� ����������������
				return *this;

			// ��������� ������ ������
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

			// �������� ������ ������������� �������
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
		void Move(const v2f& offset);
		void MoveTo(const v2f& position);
		void Rotate(float amount);
		void ApplyForce(const v2f& amount);

		const v2f& GetLinearVelocity() const;
		const float& GetArea() const;
		const float& GetMass() const;
		const float& GetDensity() const;
		const float& GetRestitution() const;
		const bool& IsStatic() const;

		friend class World2D;
		friend class Collision;

		~BaseBady2D();


		//for Collision
		v2f GetMinCorner() const { return spaceCollisionTesting.GetMinCorner(); }
		v2f GetMaxCorner() const { return spaceCollisionTesting.GetMaxCorner(); }
		v2fRect GetRectPossibilityCollision() { 
			if(spaceUpdateRequired)
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

	private:
		void Step(float DT, const v2f& gravity);
		friend 	void utility::draw::DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary,
			bool possibilityBoundary, const sf::Color& col);

		BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area);

		v2fRect GetRectPossibilityCollision(float DT) {
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

		collider::VirtualCollider* ICollider;// ��������� ����������
		v2f LinearVelocity;					// �������� 
		v2fRect spaceCollisionTesting;		// ������� � ������� �� ����� ������ ������� ��� �������� �� ��������
		bool spaceUpdateRequired = true;	// ���� �� ��������?
		v2f force;							// ������ ����
		bool isStatic;						// �����������
		float RotationVelocity;				// �������� ���������
		float Density;						// ���������
		float Mass;							// �����
		float InvMass;						// �������� �����
		float Restitution;					// ���������
		float Area;							// �������
		size_t id;							// id �������
		static size_t CountCreatedObject;	// ����� � 4,294,967,295 �������� ����� ������
		static std::vector<size_t> freeId;	// ������ �� ��������� id ��������, ��� �������� ������� ������� ����� ������������� �� ����, � ����� ������ CountCreatedObject
	};
}

BOOST_GEOMETRY_REGISTER_BOX(phis2D::BaseBady2D, v2f, GetMinCorner(), GetMaxCorner())
