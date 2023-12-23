#pragma once
#include <Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		const size_t trianglesBox[6] = { 0, 1, 2, 0, 2, 3 };
		class BoxCollider : public VirtualCollider
		{
		public:

			phis2D::collider::typeCollider GetTypeCollider() override;
			sf::FloatRect GetRectCollider() override;
			const v2f& GetPosition() override;

			void Move(const v2f& offset) override;
			void MoveTo(const v2f& position) override;
			virtual const std::pair<const v2f* const&, size_t> GetTransformedVertices() override;
			const std::pair<const size_t* const&, size_t> GetTrinagles();//first индексы, second их колво

			const v2f& GetSize();
			~BoxCollider() = default;
			friend bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);

		private:
			BoxCollider(const v2f& pos, const v2f& size);
			void CreateBoxVertices();

			v2f Position;
			v2f Size;
		};
		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider);
	}
}