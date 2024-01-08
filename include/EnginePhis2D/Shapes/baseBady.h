#pragma once
#include <EnginePhis2D/Shapes/Colliders.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#pragma region defined
namespace phis2D
{
	class BaseBady2D;
	class Scena;
}

namespace utility::draw
{
	void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider,
		bool filled, bool boundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
	void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary,
		bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
}
#pragma endregion

namespace phis2D
{
	// ���������� ����
	class BaseBady2D
	{
	public:
#pragma region Defolt
		BaseBady2D(const BaseBady2D& other);
		BaseBady2D(BaseBady2D&& other) noexcept;

		BaseBady2D& operator=(const BaseBady2D& other);
		BaseBady2D& operator=(BaseBady2D&& other) noexcept;

		~BaseBady2D();
#pragma endregion

#pragma region Manipulation
		void Move(const v2f& offset);
		void MoveTo(const v2f& position);
		void Rotate(float amount);
		void ApplyForce(const v2f& amount);
#pragma endregion

#pragma region Getters
		const v2f& GetLinearVelocity() const;
		const float& GetArea() const;
		const float& GetMass() const;
		const float& GetDensity() const;
		const float& GetRestitution() const;
		const v2f& GetPosition() const;
		const bool& IsStatic() const;
#pragma endregion

#pragma region Collision
		v2f GetMinCorner() const; 
		v2f GetMaxCorner() const;
		v2fRect GetRectPossibilityCollision();
#pragma endregion

	private:
		friend class Collision;
		friend class Scena;
		friend class AdderBody;

		friend 	void utility::draw::DrawBady(sf::RenderWindow& win, BaseBady2D* bady, bool filled, bool boundary,
			bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);

		BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area);

		v2fRect GetRectPossibilityCollision(float DT);
		void Step(float DT, const v2f& gravity);

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

