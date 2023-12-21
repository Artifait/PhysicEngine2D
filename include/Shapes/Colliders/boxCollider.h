#pragma once
#include <Shapes/Colliders/virtualCollider.h>

namespace phis2D
{
	namespace collider
	{
		class BoxCollider : public VirtualCollider
		{
		public:
			phis2D::collider::typeCollider GetTypeCollider() override;
			const v2f& GetPosition() override;
			const v2f& GetSize();

			~BoxCollider() = default;

			friend bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider* outBoxCollider);
		private:
			BoxCollider(const v2f& pos, const v2f& size);

			v2f Position;
			v2f Size;
		};
		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider* outBoxCollider);
	}
}