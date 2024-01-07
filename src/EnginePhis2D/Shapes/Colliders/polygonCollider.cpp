#include <EnginePhis2D/Shapes/Colliders/polygonCollider.h>
#include <EnginePhis2D/SimulateData.h>
#include <StructData/TransformPhis2D.h>

namespace phis2D
{
	namespace collider
	{
		phis2D::collider::typeCollider phis2D::collider::PolygonCollider::GetTypeCollider() { return phis2D::collider::Polygon; }

		phis2D::collider::PolygonCollider::PolygonCollider(const PolygonCollider& other)
			: VirtualCollider(other) {}
		phis2D::collider::PolygonCollider::PolygonCollider(PolygonCollider&& other) noexcept
			: VirtualCollider(std::move(other)) {}
		PolygonCollider& phis2D::collider::PolygonCollider::operator=(const PolygonCollider& other)
		{
			if (this != &other)
				VirtualCollider::operator=(other);
			return *this;
		}
		PolygonCollider& phis2D::collider::PolygonCollider::operator=(PolygonCollider&& other) noexcept
		{
			if (this != &other)
				VirtualCollider::operator=(std::move(other));
			return *this;
		}
		vecV2f phis2D::collider::PolygonCollider::GetTransformedVertices()
		{
			if (transformUpdateRequired)
			{
				Transform2D transform(CenterPosition, rotation);
				for (int i = 0; i < countVertices; i++)
				{
					transformedVertices[i] = Transform2D::Transform(vertices[i], transform);
				}
				transformedVertices[countVertices] = CenterPosition;
			}
			transformUpdateRequired = false;
			return vecV2f(transformedVertices, countVertices);

		}
		float phis2D::collider::PolygonCollider::GetArea()
		{
			float S = 0.f;
			for (size_t i = 0; i < countVertices; ++i)
			{
				if (i != countVertices - 1)
					S += (vertices[i].x * vertices[i + 1].y - vertices[i].y * vertices[i + 1].x);
				else
					S += (vertices[i].x * vertices[0].y - vertices[i].y * vertices[0].x);
			}
			return abs(S) * 0.5f;
		}
		PolygonCollider::PolygonCollider(const vecV2f& virts)
		{
			CreateTriangles(virts.second * 3);
			CreateVertices(virts.second);

			SetTriangles();
			SetVertices(virts);
		}
		void phis2D::collider::PolygonCollider::SetTriangles()
		{
			for (int i = 0; i < countVertices; i++)
			{
				triangleIndex[i * 3] = countVertices;
				triangleIndex[i * 3 + 1] = i;
				triangleIndex[i * 3 + 2] = (i + 1) % countVertices;				
			}
		}
		v2f phis2D::collider::PolygonCollider::GetCenter(const vecV2f& virts)
		{
			v2f sum;
			for (int i = 0; i < virts.second; i++)  sum += virts.first[i];
			return sum / virts.second;
		}
		void phis2D::collider::PolygonCollider::SetVertices(const vecV2f& virts)
		{
			if (countVertices != virts.second) CreateVertices(virts.second);
			v2f cntPos = PolygonCollider::GetCenter(virts);
			for (int i = 0; i < virts.second; i++)
			{
				vertices[i] = virts.first[i] - cntPos;
			}
			vertices[countVertices] = CenterPosition;
		}
		void phis2D::collider::PolygonCollider::CreateVertices(size_t countVrt)
		{
			if (transformedVertices != nullptr) delete[] transformedVertices;
			if (vertices != nullptr) delete[] vertices;

			countVertices = countVrt;

			transformedVertices = new v2f[countVertices + 1];
			vertices = new v2f[countVertices + 1];
		}
		bool phis2D::collider::CreatePolygonCollider(const vecV2f& virts, std::string& outMessage, VirtualCollider*& outBoxCollider)
		{
			if (virts.second <= 2)
			{
				outMessage = "[CreatePolygonCollider](--errore 'Vertices'){ You give me " + std::to_string(virts.second) + " vertices, pls give >= 3. }\n";
				return false;
			}

			outBoxCollider = new(std::nothrow) phis2D::collider::PolygonCollider(virts);
			if (outBoxCollider == nullptr)
			{
				outMessage = "[CreatePolygonCollider](--errore 'Memory'){ Memory allocation failed. }\n";
				return false;
			}
			outMessage = "[CreatePolygonCollider](created){ Bse Norm. }\n";
			return true;
		}

	}
}
