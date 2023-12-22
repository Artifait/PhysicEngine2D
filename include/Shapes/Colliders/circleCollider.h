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
			sf::FloatRect GetRectCollider() override;

			void Move(const v2f& offset) override;
			const float& GetRadius();

			friend bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);
			~CircleCollider() = default;
		private:
			CircleCollider(const v2f& posCenter, float r);

			float Radius;
			v2f CenterPosition;
		};

		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);
	}
}