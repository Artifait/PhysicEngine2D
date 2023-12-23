#pragma once
#include <Shapes/Colliders.h>

namespace phis2D
{
	class BaseBady2D
	{
	public:
		static bool CreateColliderBady(collider::VirtualCollider* collider, bool isStatic,
			float density, float mass, float restition, BaseBady2D* outBady, std::string& outMessage);

		static bool CreateCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float mass, float restition, BaseBady2D* outBady, std::string& outMessage);

		static bool CreateBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float mass, float restition, BaseBady2D* outBady, std::string& outMessage);
		~BaseBady2D();

	private:
		BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area);

		collider::VirtualCollider* ICollider;	// интерфейс коллайдера
		v2f LinearVelocity;			// скорость 

		bool IsStatic;				// статический
		float rotationVelocity;		// скорость вращаения
		float Density;				// плотность
		float Mass;					// масса
		float Restitution;			// упрогость
		float Area;					// площадь
	};


}