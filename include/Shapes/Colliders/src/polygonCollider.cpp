#include <Shapes/Colliders/polygonCollider.h>
#include <SimulateData.h>
#include <StructData/TransformPhis2D.h>

namespace phis2D
{
	namespace collider
	{
		phis2D::collider::typeCollider phis2D::collider::PolygonCollider::GetTypeCollider() { return phis2D::collider::Polygon; }

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
