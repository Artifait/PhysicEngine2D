#pragma once
#include <Shapes/Colliders/typeCollider.h>
#include <SFML/Graphics/Rect.hpp>
#include <v2f.h>
#include <string>
#include <new>
#include <SimulateData.h>

namespace phis2D
{
	namespace collider
	{
		class VirtualCollider
		{
		public:
			VirtualCollider() = default;
			~VirtualCollider() = default;

			virtual phis2D::collider::typeCollider GetTypeCollider() = 0;
			virtual const std::pair<const v2f* const&, size_t> GetTransformedVertices() = 0;
			virtual sf::FloatRect GetRectCollider() = 0;
			virtual const v2f& GetPosition() = 0;
			const float& GetRotation() { return rotation; };
			virtual const std::pair<const size_t* const&, size_t> GetTrinagles() = 0;//first индексы, second их колво
			virtual void Move(const v2f& offset) = 0;
			virtual void MoveTo(const v2f& position) = 0;
			virtual void Rotate(float amount) {
				rotation += amount;
				if (rotation > 2.f * PI)
					rotation -= 2.f * PI;
				if (rotation < -2.f * PI)
					rotation += 2.f * PI;
				transformUpdateRequired = true;
			};
		protected:
			float rotation = 0.f;
			bool transformUpdateRequired = true;
			size_t countVertices = 0;
			v2f* transformedVertices = nullptr;
			v2f* vertices = nullptr;
		};
	}
}