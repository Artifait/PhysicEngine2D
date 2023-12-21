#pragma once
#include <Shapes/Colliders/typeCollider.h>
#include <v2f.h>
#include <string>
#include <new>

namespace phis2D
{
	namespace collider
	{
		class VirtualCollider
		{
		public:
			VirtualCollider() = default;
			~VirtualCollider() = default;

			virtual phis2D::collider::typeCollider GetTypeCollider() = 0;
			virtual const v2f& GetPosition() = 0;
		};
	}
}