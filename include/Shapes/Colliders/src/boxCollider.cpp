#include <Shapes/Colliders/boxCollider.h>
#include <SimulateData.h>
#include <TransformPhis2D.h>

namespace phis2D
{
	namespace collider
	{
		const v2f& BoxCollider::GetPosition()
		{
			return Position;
		}
		const v2f& BoxCollider::GetSize()
		{
			return Size;
		}

		typeCollider BoxCollider::GetTypeCollider()
		{
			return phis2D::collider::Box;
		}
		sf::FloatRect BoxCollider::GetRectCollider()
		{
			return sf::FloatRect(Position, Size);
		}
		void BoxCollider::Move(const v2f& offset)
		{ 
			Position += offset;
			transformUpdateRequired = true;
		}
		void phis2D::collider::BoxCollider::MoveTo(const v2f& position)
		{
			Position = position;
			transformUpdateRequired = true;
		}

		BoxCollider::BoxCollider(const v2f& pos, const v2f& size)
			: Position(pos), Size(size)
		{
			transformedVertices = new v2f[4];
			vertices = new v2f[4];

			CreateBoxVertices();
			countVertices = 4;
			transformUpdateRequired = true;
		}
		const std::pair<const v2f* const&, size_t> phis2D::collider::BoxCollider::GetTransformedVertices()
		{
			if (transformUpdateRequired)
			{
				Transform2D transform(Position, rotation);
				for (int i = 0; i < countVertices; i++)
				{
					transformedVertices[i] = Transform2D::Transform(vertices[i], transform);
				}
			}
			transformUpdateRequired = false;
			return std::pair<v2f*&, size_t>(transformedVertices, countVertices);
		}
		const std::pair<const size_t* const&, size_t> phis2D::collider::BoxCollider::GetTrinagles()
		{
			return std::pair<const size_t* const&, size_t>(trianglesBox, 6);
		}
		void BoxCollider::CreateBoxVertices()
		{
			float left, right, bottom, top;

			left = -Size.x / 2.f;
			right = left + Size.x;
			bottom = -Size.y / 2.f;
			top = bottom + Size.y;

			vertices[0] = v2f(left, top);
			vertices[1] = v2f(right, top);
			vertices[2] = v2f(right, bottom);
			vertices[3] = v2f(left, bottom);

			transformedVertices[0] = v2f(left, top);
			transformedVertices[1] = v2f(right, top);
			transformedVertices[2] = v2f(right, bottom);
			transformedVertices[3] = v2f(left, bottom);
		}


		bool CreateBoxCollider(const v2f& pos, const v2f& size, std::string& outMessage, VirtualCollider*& outBoxCollider)
		{
			outBoxCollider = nullptr;
			float area = size.x * size.y;

			if (size.x > phis2D::worldPhysicConstant::maxSide || size.y > phis2D::worldPhysicConstant::maxSide)
			{
				outMessage = "[CreateBoxCollider](--errore 'Big Value')\n {\n\tbox with sides : {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
					"} maximum side: " + std::to_string((int)phis2D::worldPhysicConstant::maxSide) + ".\n }\n";
				return false;
			}
			if (size.x < phis2D::worldPhysicConstant::minSide || size.y < phis2D::worldPhysicConstant::minSide)
			{
				outMessage = "[CreateBoxCollider](--errore 'Min Value')\n {\n\tbox with sides: {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
					"} minimum side: " + std::to_string((int)phis2D::worldPhysicConstant::minSide) + ".\n }\n";
				return false;
			}

			if (area > phis2D::worldPhysicConstant::maxArea)
			{
				outMessage = "[CreateBoxCollider](--errore 'Big Value')\n {\n\tbox with Area: " + std::to_string(area) + " maximum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::maxArea) + ".\n }\n";
				return false;
			}
			if (area < phis2D::worldPhysicConstant::minArea)
			{
				outMessage = "[CreateBoxCollider](--errore 'Min Value')\n {\n\tbox with Area: " + std::to_string(area) + " minimum Area: " +
					std::to_string((int)phis2D::worldPhysicConstant::minArea) + ".\n }\n";
				return false;
			}

			outBoxCollider = new(std::nothrow) phis2D::collider::BoxCollider(pos, size);
			if (outBoxCollider == nullptr)
			{
				outMessage = "[CreateBoxCollider](--errore 'Memory'){ Memory allocation failed. }\n";
				return false;
			}
			outMessage = "[CreateBoxCollider](created)\n {\n\tBox with size: {" + std::to_string((int)size.x) + ", " + std::to_string((int)size.y) +
				"} and pos: {" + std::to_string((int)pos.x) + ", " + std::to_string((int)pos.y) + "}.\n }\n";
			return true;
		}

	}
}





