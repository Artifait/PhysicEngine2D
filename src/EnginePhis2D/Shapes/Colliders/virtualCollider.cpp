#include <EnginePhis2D/Shapes/Colliders/virtualCollider.h>

#pragma region CreateMehanism


phis2D::collider::VirtualCollider::VirtualCollider(const phis2D::collider::VirtualCollider& other)
	: rotation(other.rotation),
	CenterPosition(other.CenterPosition),
	transformUpdateRequired(other.transformUpdateRequired),
	countVertices(other.countVertices),
	countTriangleIndex(other.countTriangleIndex) {
	// Выделение памяти и копирование значений transformedVertices
	transformedVertices = new v2f[countVertices];
	for (size_t i = 0; i < countVertices; ++i) {
		transformedVertices[i] = other.transformedVertices[i];
	}

	// Выделение памяти и копирование значений triangleIndex
	triangleIndex = new size_t[countTriangleIndex];
	for (size_t i = 0; i < countTriangleIndex; ++i) {
		triangleIndex[i] = other.triangleIndex[i];
	}

	// Выделение памяти и копирование значений vertices
	vertices = new v2f[countVertices];
	for (size_t i = 0; i < countVertices; ++i) {
		vertices[i] = other.vertices[i];
	}
}
phis2D::collider::VirtualCollider::VirtualCollider(phis2D::collider::VirtualCollider* other)
	: rotation(other->rotation),
	CenterPosition(other->CenterPosition),
	transformUpdateRequired(other->transformUpdateRequired),
	countVertices(other->countVertices),
	countTriangleIndex(other->countTriangleIndex) {
	// Выделение памяти и копирование значений transformedVertices
	transformedVertices = new v2f[countVertices];
	for (size_t i = 0; i < countVertices; ++i) {
		transformedVertices[i] = other->transformedVertices[i];
	}

	// Выделение памяти и копирование значений triangleIndex
	triangleIndex = new size_t[countTriangleIndex];
	for (size_t i = 0; i < countTriangleIndex; ++i) {
		triangleIndex[i] = other->triangleIndex[i];
	}

	// Выделение памяти и копирование значений vertices
	vertices = new v2f[countVertices];
	for (size_t i = 0; i < countVertices; ++i) {
		vertices[i] = other->vertices[i];
	}
}
phis2D::collider::VirtualCollider::VirtualCollider(VirtualCollider&& other) noexcept
	: rotation(other.rotation),
	CenterPosition(std::move(other.CenterPosition)),
	transformUpdateRequired(other.transformUpdateRequired),
	countVertices(other.countVertices),
	countTriangleIndex(other.countTriangleIndex) {
	transformedVertices = other.transformedVertices;
	other.transformedVertices = nullptr;

	triangleIndex = other.triangleIndex;
	other.triangleIndex = nullptr;

	vertices = other.vertices;
	other.vertices = nullptr;
}

phis2D::collider::VirtualCollider& phis2D::collider::VirtualCollider::operator=(const phis2D::collider::VirtualCollider& other)
{
	if (this != &other)
	{
		rotation = other.rotation;
		CenterPosition = other.CenterPosition;
		transformUpdateRequired = other.transformUpdateRequired;
		countVertices = other.countVertices;
		countTriangleIndex = other.countTriangleIndex;

		// Освобождение старой памяти
		delete[] transformedVertices;
		delete[] triangleIndex;
		delete[] vertices;

		// Выделение новой памяти и копирование значений
		transformedVertices = new v2f[countVertices];
		for (size_t i = 0; i < countVertices; ++i) {
			transformedVertices[i] = other.transformedVertices[i];
		}

		triangleIndex = new size_t[countTriangleIndex];
		for (size_t i = 0; i < countTriangleIndex; ++i) {
			triangleIndex[i] = other.triangleIndex[i];
		}

		vertices = new v2f[countVertices];
		for (size_t i = 0; i < countVertices; ++i) {
			vertices[i] = other.vertices[i];
		}
	}
	return *this;
}
phis2D::collider::VirtualCollider& phis2D::collider::VirtualCollider::operator=(phis2D::collider::VirtualCollider&& other) noexcept
{
	if (this != &other)
	{
		rotation = other.rotation;
		CenterPosition = std::move(other.CenterPosition);
		transformUpdateRequired = other.transformUpdateRequired;
		countVertices = other.countVertices;
		countTriangleIndex = other.countTriangleIndex;

		// Освобождение старой памяти
		delete[] transformedVertices;
		delete[] triangleIndex;
		delete[] vertices;

		// Перемещение указателей на новую память
		transformedVertices = other.transformedVertices;
		other.transformedVertices = nullptr;

		triangleIndex = other.triangleIndex;
		other.triangleIndex = nullptr;

		vertices = other.vertices;
		other.vertices = nullptr;
	}
	return *this;
}

#pragma endregion

#pragma region MovingMehanism
void phis2D::collider::VirtualCollider::Move(const v2f& offset)
{
	CenterPosition += offset;
	transformUpdateRequired = true;
}
void phis2D::collider::VirtualCollider::MoveTo(const v2f& position)
{
	CenterPosition = position;
	transformUpdateRequired = true;
}

void phis2D::collider::VirtualCollider::Rotate(float amount)
{
	rotation += amount;
	if (rotation > 2.f * PI)
		rotation -= 2.f * PI;
	if (rotation < -2.f * PI)
		rotation += 2.f * PI;
	transformUpdateRequired = true;
}
#pragma endregion

#pragma region CollisionMehanism

void phis2D::collider::VirtualCollider::CreateVertices(size_t countVrt)
{
	if (transformedVertices != nullptr) delete[] transformedVertices;
	if (vertices != nullptr) delete[] vertices;

	countVertices = countVrt;
	transformedVertices = new v2f[countVertices];
	vertices = new v2f[countVertices];
}

void phis2D::collider::VirtualCollider::CreateTriangles(size_t countInd)
{
	if (triangleIndex != nullptr) delete[] triangleIndex;
	countTriangleIndex = countInd;
	triangleIndex = new size_t[countTriangleIndex];
}

phis2D::collider::vecV2f phis2D::collider::VirtualCollider::GetTransformedVertices()
{
	if (transformUpdateRequired)
	{
		Transform2D transform(CenterPosition, rotation);
		for (int i = 0; i < countVertices; i++)
		{
			transformedVertices[i] = Transform2D::Transform(vertices[i], transform);
		}
	}
	transformUpdateRequired = false;
	return vecV2f(transformedVertices, countVertices);
}

phis2D::collider::vecIndex phis2D::collider::VirtualCollider::GetTriangles()
{
	return vecIndex(triangleIndex, countTriangleIndex);
}

const float& phis2D::collider::VirtualCollider::GetRotation()
{
	return rotation;
}

const v2f& phis2D::collider::VirtualCollider::GetCenterPosition()
{
	return CenterPosition;
}
v2f phis2D::collider::VirtualCollider::GetPosition()
{
	return CenterPosition;
}
v2fRect phis2D::collider::VirtualCollider::GetRectCollider()
{
	v2f minPos(v2f::v2fMax()), maxPos(v2f::v2fMin());
	auto vert = GetTransformedVertices();
	for (int i = 0; i < countVertices; i++)
	{
		v2f nowVert(vert.first[i]);

		if (minPos.x > nowVert.x)
			minPos.x = nowVert.x;
		if (minPos.y > nowVert.y)
			minPos.y = nowVert.y;

		if (maxPos.x < nowVert.x)
			maxPos.x = nowVert.x;
		if (maxPos.y < nowVert.y)
			maxPos.y = nowVert.y;
	}
	return v2fRect(minPos, maxPos - minPos);
}
#pragma endregion
