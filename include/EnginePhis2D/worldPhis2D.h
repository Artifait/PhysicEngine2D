#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include <Shapes/baseBady.h>

#include <Utility/utilityDraw/utilityDrawCollider.h>
#include <Utility/utilityPhisic/collisionPhis2D.h>
#include <Utility/utilityRandObject/randCollider.h>

using namespace sf;
using namespace std;
namespace cld = phis2D::collider;

namespace phis2D
{
	class World2D
	{
	public:
        World2D();
		
		size_t AddColliderBady(collider::VirtualCollider* collider, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		size_t AddCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		size_t AddBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		bool IsEmptyWorld();

		void RemoveByIdBady(size_t id);
		bool GetBadyById(size_t id, BaseBady2D*& outBady);
		bool GetBadyByIndex(size_t index, BaseBady2D*& outBady);
		const BaseBady2D* const& GetBadyInPos(v2f position);
		void Render(RenderWindow& win);
		void Step(float DT);
		~World2D() = default;

	private:
        vector<BaseBady2D*> BadyInWorld;
		v2f gravity;
	};

}


