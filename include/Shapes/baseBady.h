#pragma once
#include <Shapes/Colliders.h>

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

		void Step(float DT);
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

	private:
		BaseBady2D(collider::VirtualCollider* collider, bool isStatic, float density, float mass, float restition, float area);

		collider::VirtualCollider* ICollider;// ��������� ����������
		v2f LinearVelocity;					// �������� 

		v2f force;							// ������ ����
		bool isStatic;						// �����������
		float RotationVelocity;				// �������� ���������
		float Density;						// ���������
		float Mass;							// �����
		float Restitution;					// ���������
		float Area;							// �������
		size_t id;							// id �������
		static size_t CountCreatedObject;	// ����� � 4,294,967,295 �������� ����� ������
		static std::vector<size_t> freeId;			// ������ �� ��������� id ��������, ��� �������� ������� ������� ����� ������������� �� ����, � ����� ������ CountCreatedObject
	};


}