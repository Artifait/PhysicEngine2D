#pragma once
#include <Shapes/Colliders/typeCollider.h>
#include <structData.h>
#include <string>
#include <new>
#include <SimulateData.h>

namespace phis2D
{
	namespace collider
	{
		//ps: const int *pa - ��� ��������� �� ���������	// ������ ������ ����������
		//			int *const pa - ����������� ���������	// ������� ������ ������ 
		//
		//����� ����������� ����������� �������� ���������� ������, size_t �������� �� �������� ���-�� ��������
		//std::pair<const size_t* const&, size_t>
		//std::pair<const v2f* const&, size_t>
		// 
		// ��� �������� ��� ����������: const size_t* const&.
		// �� ��� � ��� ���� ����������� ������(��� ��������� ��� �� ������� �����������) �� const size_t*, ��� � ���� ������� �������� �������� �� ���������� ������

		//----const Array----
		typedef std::pair<const size_t* const&, size_t> vecIndex;
		//----const Array----
		typedef std::pair<const v2f* const&, size_t> vecV2f;

		//��������� ��� �����������
		class VirtualCollider
		{
		public:
			//=========base===========
			VirtualCollider() = default;
			~VirtualCollider() { delete[] transformedVertices; delete[] vertices; delete[] triangleIndex; };
			//========================


			//==========��������==========
			virtual void Move(const v2f& offset)
			{
				CenterPosition += offset;
				transformUpdateRequired = true;
			}
			//==========����������========
			virtual void MoveTo(const v2f& position)
			{
				CenterPosition = position;
				transformUpdateRequired = true;
			}
			//==========��������==========
			virtual void Rotate(float amount) {
				rotation += amount;
				if (rotation > 2.f * PI)
					rotation -= 2.f * PI;
				if (rotation < -2.f * PI)
					rotation += 2.f * PI;
				transformUpdateRequired = true;
			};
			//============================
			
			
			//--------------���������� �������� ������� ��� ������ � ������������--------------

			//��� ������ � !������� � ������ ������ ������ ���x �������, � ������ ����� �������������� 
			virtual vecV2f GetTransformedVertices() 
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
			

			//������ ��� ������� ��������� �����������, � ����� �������� ������������ ��� ��������� ���� ������
			virtual vecIndex GetTriangles() { return vecIndex(triangleIndex, countTriangleIndex); };

			//������� ��������� ����� ������ ��� ������� ���������� ������ � ��������, � ������ ����� �������������� 
			virtual v2fRect GetRectCollider() {
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
			};

			//���� � ��������
			const float& GetRotation() { return rotation; };

			//������ ��� ����������� ����� ������� ��� ������
			virtual const v2f& GetCenterPosition() { return CenterPosition; };
			virtual v2f GetPosition() { return CenterPosition; };
			virtual phis2D::collider::typeCollider GetTypeCollider() = 0;

			//---------------------------------------------------------------------------------
		protected:
			virtual void SetTriangles() = 0;
			virtual void SetVertices() = 0;

			virtual void CreateVertices(size_t countVrt = 0) 
			{
				if (transformedVertices != nullptr) delete[] transformedVertices;
				if (vertices != nullptr) delete[] vertices;

				countVertices = countVrt;
				transformedVertices = new v2f[countVertices];
				vertices = new v2f[countVertices];
			};
			virtual void CreateTriangles(size_t countInd = 0) 
			{
				if (triangleIndex != nullptr) delete[] triangleIndex;
				countTriangleIndex = countInd;
				triangleIndex = new size_t[countTriangleIndex];
			};
			//���� �������� �� ������ ������
			float rotation = 0.f;

			v2f CenterPosition;

			//true ������ � ������ transformedVertices �t��� ���������� �������� � ��� ������ GetTransformedVertices ����� ��������� �������� �������
			bool transformUpdateRequired = true;

			//���������� ������
			size_t countVertices = 0;
			size_t countTriangleIndex = 0;
			// ���������� ��������� ������ ����������
			v2f* transformedVertices = nullptr;
			size_t* triangleIndex = nullptr;

			// ��������� ����� ���������� ������ ����������� ����� (0, 0) 
			v2f* vertices = nullptr;

		};

	}
}