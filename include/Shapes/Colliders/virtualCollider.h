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
		//ps: const int *pa - это Указатели на константы	// нельзя менять переменную
		//			int *const pa - Константный указатель	// нельязя менять адресс 
		//
		//часто встречаямые конструкции означает стаический массив, size_t отвечает за хранение кол-ва обьектов
		//std::pair<const size_t* const&, size_t>
		//std::pair<const v2f* const&, size_t>
		// 
		// что означает это кострукция: const size_t* const&.
		// то что у нас есть константная ссылка(что избавляет нас от лищнего копирования) на const size_t*, что в свою очередь означает хранение не изменяемых данных

		//----const Array----
		typedef std::pair<const size_t* const&, size_t> vecIndex;
		//----const Array----
		typedef std::pair<const v2f* const&, size_t> vecV2f;

		//Интерфейс для коллайдеров
		class VirtualCollider
		{
		public:
			//=========base===========
			VirtualCollider() = default;
			~VirtualCollider() { delete[] transformedVertices; delete[] vertices; delete[] triangleIndex; };
			//========================


			//==========Движение==========
			virtual void Move(const v2f& offset)
			{
				CenterPosition += offset;
				transformUpdateRequired = true;
			}
			//==========Пермещение========
			virtual void MoveTo(const v2f& position)
			{
				CenterPosition = position;
				transformUpdateRequired = true;
			}
			//==========Вращение==========
			virtual void Rotate(float amount) {
				rotation += amount;
				if (rotation > 2.f * PI)
					rotation -= 2.f * PI;
				if (rotation < -2.f * PI)
					rotation += 2.f * PI;
				transformUpdateRequired = true;
			};
			//============================
			
			
			//--------------Обьявление основных методов для работы с коллайдерами--------------

			//Для работы с !кругами а вообще отдает коорды всеx вершины, у кругов нужно переопределить 
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
			

			//Каждые три индекса описывают треугольник, в итоги получаем триугольники для рисования всей фигуры
			virtual vecIndex GetTriangles() { return vecIndex(triangleIndex, countTriangleIndex); };

			//Квадрат описанный около фигиру его стороны паралельны абцисе и ординате, у кругов нужно переопределить 
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

			//угол в радианах
			const float& GetRotation() { return rotation; };

			//Отдает для большинства фигур позицею его центра
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
			//угол поворота на данный момент
			float rotation = 0.f;

			v2f CenterPosition;

			//true значит в масиве transformedVertices лtжат устаревшии вершнины и при вызове GetTransformedVertices будут обновляны значения массива
			bool transformUpdateRequired = true;

			//количество вершин
			size_t countVertices = 0;
			size_t countTriangleIndex = 0;
			// абсолютное положение вершин коллайдера
			v2f* transformedVertices = nullptr;
			size_t* triangleIndex = nullptr;

			// положение точек коллайдера вокруг центральной точки (0, 0) 
			v2f* vertices = nullptr;

		};

	}
}