#pragma once
#include <Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		class CircleCollider : public VirtualCollider
		{
		public:
			phis2D::collider::typeCollider GetTypeCollider() override;
			const v2f& GetPosition() override;
			const float& GetRadius();

			~CircleCollider() = default;

			friend bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider* outCircleCollider);
		private:
			CircleCollider(const v2f& posCenter, float r);

			float Radius;
			v2f CenterPosition;
		};

		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider* outCircleCollider);
	}
}