#pragma once
#include <EnginePhis2D/Shapes/Colliders.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

<<<<<<< HEAD
class App;
namespace phis2D
{
	class BaseBady2D;
	class Scena;
}

=======
namespace phis2D
{
	// Физическое тело
	class BaseBady2D;
}
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider,
<<<<<<< HEAD
			bool filled, bool boundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
		void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary,
			bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
	}

}


=======
			bool filled = true, bool boundary = false, const sf::Color& col = sf::Color(34, 109, 224));
		void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled = true, bool boundary = false,
			bool possibilityBoundary = false, const sf::Color& col = sf::Color(34, 109, 224));
	}
}



>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
namespace phis2D
{
	// Физическое тело
	class BaseBady2D
	{
	public:
		static bool CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
<<<<<<< HEAD
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

=======
			float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage);

		static bool CreateBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float mass, float restition, BaseBady2D*& outBady, std::string& outMessage);
		// Конструктор копирования
		BaseBady2D(const BaseBady2D& other) :
			ICollider(other.ICollider), LinearVelocity(other.LinearVelocity), spaceCollisionTesting(other.spaceCollisionTesting),
			spaceUpdateRequired(other.spaceUpdateRequired), force(other.force), isStatic(other.isStatic),
			RotationVelocity(other.RotationVelocity), Density(other.Density), Mass(other.Mass),
			Restitution(other.Restitution), Area(other.Area), id(other.id), InvMass{other.InvMass} {}
		BaseBady2D(BaseBady2D* other) :
			ICollider(other->ICollider), LinearVelocity(other->LinearVelocity), spaceCollisionTesting(other->spaceCollisionTesting),
			spaceUpdateRequired(other->spaceUpdateRequired), force(other->force), isStatic(other->isStatic),
			RotationVelocity(other->RotationVelocity), Density(other->Density), Mass(other->Mass),
			Restitution(other->Restitution), Area(other->Area), id(other->id), InvMass{ other->InvMass } {}
		// Конструктор переноса
		BaseBady2D(BaseBady2D&& other) noexcept
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

		// Оператор присваивания
		BaseBady2D& operator=(const BaseBady2D& other)
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

		// Оператор перемещения
		BaseBady2D& operator=(BaseBady2D&& other) noexcept
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
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
		void Move(const v2f& offset);
		void MoveTo(const v2f& position);
		void Rotate(float amount);
		void ApplyForce(const v2f& amount);

		const v2f& GetLinearVelocity() const;
		const float& GetArea() const;
		const float& GetMass() const;
		const float& GetDensity() const;
		const float& GetRestitution() const;
<<<<<<< HEAD
		const v2f& GetPosition() const;
		const bool& IsStatic() const;

=======
		const bool& IsStatic() const;

		friend class World2D;
		friend class Collision;

>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
		~BaseBady2D();


		//for Collision
		v2f GetMinCorner() const { return spaceCollisionTesting.GetMinCorner(); }
		v2f GetMaxCorner() const { return spaceCollisionTesting.GetMaxCorner(); }
<<<<<<< HEAD
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



=======
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
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2

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
<<<<<<< HEAD
=======

BOOST_GEOMETRY_REGISTER_BOX(phis2D::BaseBady2D, v2f, GetMinCorner(), GetMaxCorner())
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
