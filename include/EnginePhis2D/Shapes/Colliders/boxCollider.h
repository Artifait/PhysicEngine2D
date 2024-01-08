#pragma once
#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>



namespace phis2D::collider
{
	class BoxCollider : public VirtualCollider
	{
	public:
#pragma region Defolt
		~BoxCollider() = default;

		BoxCollider(const BoxCollider& other);
		BoxCollider(BoxCollider&& other) noexcept;
		BoxCollider& operator=(const BoxCollider& other);
		BoxCollider& operator=(BoxCollider&& other) noexcept;
#pragma endregion

#pragma region Getters
		typeCollider GetTypeCollider() override;
		float GetArea() override;
		const v2f& GetSize();
#pragma endregion

	private:
		friend class AdderBody;

		void SetTriangles() override;
		void SetVertices() override;

		//==========base==========
		BoxCollider(const v2f& posCenter, const v2f& size);
		v2f Size;

		//-----------------------
	};
}