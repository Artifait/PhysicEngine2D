#pragma once
#include <EnginePhis2D/Shapes/Colliders/typeCollider.h>
#include <structData.h>
#include <string>
#include <new>
#include <EnginePhis2D/SimulateData.h>

namespace phis2D
{
	class World2D;
	class AdderBody;

	namespace collider
	{
		//ps: const int *pa - это Указатели на константы	// нельзя менять переменную
		//			int *const pa - Константный указатель	// нельязя менять адресс 

		//----const Array----
		typedef std::pair<const size_t* const&, size_t> vecIndex;
		//----const Array----
		typedef std::pair<const v2f* const&, size_t> vecV2f;

		//Интерфейс для коллайдеров
		class VirtualCollider
		{
		public:
			//=========base==========
			VirtualCollider() = default;
			~VirtualCollider() { delete[] transformedVertices; delete[] vertices; delete[] triangleIndex; };
			//=======================

			//==NO=====base======NO==
			VirtualCollider(const VirtualCollider& other);
			VirtualCollider(VirtualCollider* other);
			VirtualCollider(VirtualCollider&& other) noexcept;

			VirtualCollider& operator=(const VirtualCollider& other);
			VirtualCollider& operator=(VirtualCollider&& other) noexcept;

			virtual float GetArea() = 0;

			//--------------Обьявление основных методов для работы с коллайдерами--------------

			virtual void Move(const v2f& offset);
			virtual void MoveTo(const v2f& position);
			virtual void Rotate(float amount);

			virtual vecV2f GetTransformedVertices();
			virtual vecIndex GetTriangles(); 

			virtual const v2f& GetCenterPosition();
			virtual v2fRect GetRectCollider();	
			const float& GetRotation();
			virtual v2f GetPosition(); 

			virtual phis2D::collider::typeCollider GetTypeCollider() = 0;
			//---------------------------------------------------------------------------------
		protected:
			//-------заполнение массивов-------

			virtual void SetTriangles() = 0;
			virtual void SetVertices() = 0;
			//---выделение памяти под массивы---

			virtual void CreateVertices(size_t countVrt = 0);
			virtual void CreateTriangles(size_t countInd = 0);

			bool transformUpdateRequired = true;
			float rotation = 0.f;
			v2f CenterPosition;

			size_t countTriangleIndex = 0;
			size_t countVertices = 0;

			v2f* transformedVertices = nullptr;
			size_t* triangleIndex = nullptr;
			v2f* vertices = nullptr;

			friend class World2D;
			friend class AdderBody;
		};

	}
}