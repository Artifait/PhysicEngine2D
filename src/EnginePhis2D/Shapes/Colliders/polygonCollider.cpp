#include <EnginePhis2D/Shapes/Colliders/polygonCollider.h>
#include <StructData/TransformPhis2D.h>

namespace phis2D::collider
{

#pragma region Defolt
	PolygonCollider::PolygonCollider(const vecV2f& virts)
	{
		CreateTriangles(virts.second * 3);
		CreateVertices(virts.second);

		SetTriangles();
		SetVertices(virts);
	}

	PolygonCollider::PolygonCollider(const PolygonCollider& other)
		: VirtualCollider(other) {}

	PolygonCollider::PolygonCollider(PolygonCollider&& other) noexcept
		: VirtualCollider(std::move(other)) {}

	PolygonCollider& PolygonCollider::operator=(const PolygonCollider& other)
	{
		if (this != &other)
			VirtualCollider::operator=(other);
		return *this;
	}

	PolygonCollider& PolygonCollider::operator=(PolygonCollider&& other) noexcept
	{
		if (this != &other)
			VirtualCollider::operator=(std::move(other));
		return *this;
	}
#pragma endregion

#pragma region Collision
	vecV2f PolygonCollider::GetTransformedVertices()
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
	void PolygonCollider::SetVertices()
	{
	}
	void PolygonCollider::SetTriangles()
	{
		for (int i = 0; i < countVertices; i++)
		{
			triangleIndex[i * 3] = countVertices;
			triangleIndex[i * 3 + 1] = i;
			triangleIndex[i * 3 + 2] = (i + 1) % countVertices;
		}
	}
	void PolygonCollider::SetVertices(const vecV2f& virts)
	{
		if (countVertices != virts.second) CreateVertices(virts.second);
		v2f cntPos = PolygonCollider::GetCenter(virts);
		for (int i = 0; i < virts.second; i++)
		{
			vertices[i] = virts.first[i] - cntPos;
		}
		vertices[countVertices] = CenterPosition;
	}
	void PolygonCollider::CreateVertices(size_t countVrt)
	{
		if (transformedVertices != nullptr) delete[] transformedVertices;
		if (vertices != nullptr) delete[] vertices;

		countVertices = countVrt;

		transformedVertices = new v2f[countVertices + 1];
		vertices = new v2f[countVertices + 1];
	}
	typeCollider PolygonCollider::GetTypeCollider() { return Polygon; }
#pragma endregion

#pragma region Getters
	float PolygonCollider::GetArea()
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

	v2f PolygonCollider::GetCenter(const vecV2f& virts)
	{
		v2f sum;
		for (int i = 0; i < virts.second; i++)  sum += virts.first[i];
		return sum / (float)virts.second;
	}
#pragma endregion

}
