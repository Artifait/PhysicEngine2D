#pragma once
#include <EnginePhis2D/Shapes/Colliders.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class App;
namespace phis2D
{
	class BaseBady2D;
	class Scena;
}

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider,
			bool filled, bool boundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
		void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary,
			bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
	}

}

namespace phis2D
{
	// Физическое тело
	class BaseBady2D
	{
	public:
		static bool CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
			float density, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreateBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreatePolygonBady(const v2f& posCenter, const v2f* vertices, size_t cntVertices, bool isStatic,
			float density, float restition, BaseBady2D*& outBady, std::string& outMessage);
		BaseBady2D(const BaseBady2D& other);
		BaseBady2D(BaseBady2D* other); 
		BaseBady2D(BaseBady2D&& other) noexcept;

		BaseBady2D& operator=(const BaseBady2D& other);
		BaseBady2D& operator=(BaseBady2D&& other) noexcept;

		void Move(const v2f& offset);
		void MoveTo(const v2f& position);
		void Rotate(float amount);
		void ApplyForce(const v2f& amount);

		const v2f& GetLinearVelocity() const;
		const float& GetArea() const;
		const float& GetMass() const;
		const float& GetDensity() const;
		const float& GetRestitution() const;
		const v2f& GetPosition() const;
		const bool& IsStatic() const;


		~BaseBady2D();


		//for Collision
		v2f GetMinCorner() const { return spaceCollisionTesting.GetMinCorner(); }
		v2f GetMaxCorner() const { return spaceCollisionTesting.GetMaxCorner(); }
		v2fRect GetRectPossibilityCollision();

	private:
		friend class World2D;
		friend class Collision;
		friend class App;
		friend class Scena;
		friend class AdderBody;
		friend 	void utility::draw::DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary,
			bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);

		BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area);

		v2fRect GetRectPossibilityCollision(float DT);
		void Step(float DT, const v2f& gravity);


		collider::VirtualCollider* ICollider;// интерфейс коллайдера
		v2f LinearVelocity;					// скорость 
		v2fRect spaceCollisionTesting;		// область в которой мы будем искать обьекты для проверки на коллизии
		bool spaceUpdateRequired = true;	// пора ее обновить?
		v2f force;							// вектор силы
		bool isStatic;						// статический
		float RotationVelocity;				// скорость вращаения
		float Density;						// плотность
		float Mass;							// масса
		float InvMass;						// обратная масса
		float Restitution;					// упрогость
		float Area;							// площадь
		size_t id;							// id объекта
		static size_t CountCreatedObject;	// запас в 4,294,967,295 объектов думаю хватит
		static std::vector<size_t> freeId;	// массив из удаленных id обьектов, при создании обьекта сначала будут присваиваться от сюда, а потом только CountCreatedObject
	};
}

