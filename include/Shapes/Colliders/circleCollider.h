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
			sf::FloatRect GetRectCollider() override;
			const v2f& GetPosition() override;

			void Move(const v2f& offset) override;
			void MoveTo(const v2f& position) override;

			virtual const std::pair<const size_t* const&, size_t> GetTrinagles();//first индексы, second их колво
			virtual const std::pair<const v2f* const&, size_t> GetTransformedVertices();

			const float& GetRadius();
			~CircleCollider() = default;
			friend bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);

		private:
			CircleCollider(const v2f& posCenter, float r);

			float Radius;
			v2f CenterPosition;
		};

		bool CreateCircleCollider(const v2f& posCenter, float r, std::string& outMessage, VirtualCollider*& outCircleCollider);
	}
}