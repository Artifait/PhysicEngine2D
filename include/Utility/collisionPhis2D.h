#pragma once
#include <EnginePhis2D/Shapes/baseBady.h>
#include <StructData/v2f.h>
#include <float.h>

namespace phis2D
{
	//Один из модулей, отвечает за разрешение коллизий
	class Collision
	{
		// Проэкция полигона на ось, возращает самый макс и мин точки
	private: static void ProjectPolygons(const std::pair<const v2f* const&, size_t>& vertices, const v2f& axis, float& min, float& max);

		// Проекция круга на ось, возращает самый макс и мин точки
	public: static void ProjectCircle(collider::CircleCollider* circle, const v2f& axis, float& min, float& max);

		// Нахождние ближайшой точки из вершин до центра круга
	private: static int FindClosestPointOnPolygon(const v2f& circleCenter, const std::pair<const v2f* const&, size_t>& vertices);
		// Среднее арифмитическое 
	private: static v2f FindArithmeticMean(const std::pair<const v2f* const&, size_t>& vertices);

		// Функции для проверки на пересечение коллайдеров,
		// которая возращает нормаль(куда двинуть, направлен от A в B),
		// глубина(на сколько двинуть) чтобы разрешить колллизию
	//-------------------------------------------------------------------------------------------------------------------------------------------------

	private: static bool IntersectCircles(collider::CircleCollider* circleA, collider::CircleCollider* circleB, v2f& normal, float& depth);
	private: static bool IntersectCirclePolygon(collider::CircleCollider* circleA, collider::VirtualCollider* colliderB, v2f& normal, float& depth);
	private: static bool IntersectPolygons(collider::VirtualCollider* colliderA, collider::VirtualCollider* colliderB, v2f& normal, float& depth);
	public: static bool IntersectColliders(collider::VirtualCollider* colliderA, collider::VirtualCollider* colliderB, v2f& normal, float& depth);

	//-------------------------------------------------------------------------------------------------------------------------------------------------

	public: static void ResolverCollision(BaseBady2D* badyA, BaseBady2D* badyB, const v2f& normal, float depth);

	public:
		Collision() = default;
		~Collision() = default;
	};
}