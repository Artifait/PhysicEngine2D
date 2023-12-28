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
        World2D(sf::RenderWindow& window);
		size_t AddColliderBady(collider::VirtualCollider* collider, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);
		FloatRect GetRamkaWindow();
		size_t AddCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		size_t AddBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		size_t AddRandomBady(bool isStatic = false);
		size_t AddRandomBady(const v2f& Pos, bool isStatic = false);

		bool IsEmptyWorld();
		void HandleEvent(float DT);
		void RemoveByIdBady(size_t id);
		bool GetBadyById(size_t id, BaseBady2D*& outBady);
		bool GetBadyByIndex(size_t index, BaseBady2D*& outBady);
		const BaseBady2D* const& GetBadyInPos(v2f position);
		void Render(bool debug = false);
		void Step(float DT);
		~World2D();

	private:
		sf::RenderWindow& win;
        vector<BaseBady2D*> BadyInWorld;
		vector<sf::Color> outlineColors;
		phis2D::BaseBady2D* player;
		sf::FloatRect ramkaWindow;
		bool ramkaUpdateRequired = true;
		v2f gravity;
		sf::Vector2f MsCoord;
		void WrapScreen();
		void WrapSpaceObj(const sf::FloatRect& ramka, cld::VirtualCollider* coll);

		bool pressLeft, pressRight;
	};

}


