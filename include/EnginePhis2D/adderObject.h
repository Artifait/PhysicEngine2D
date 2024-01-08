#pragma once

#include <EnginePhis2D/scenaPhis2D.h>
#include <Utility/randCollider.h>

#include <algorithm>
namespace phis2D
{
	class AdderBody
	{
	public:
		AdderBody(Scena* s, std::vector<std::string>& logs) : scena(s), logs_(logs) {}

		bool AddCollider(phis2D::collider::VirtualCollider* collider, float density, float restitution, bool Static)
		{
			std::string outMsg;
			if (!CheckProperty(collider, density, outMsg))
			{
				logs_.push_back(outMsg);
				return false;
			}
			//c++17
			restitution = std::clamp(restitution, 0.f, 1.f);
			float area = collider->GetArea();
			float mass = area * density / phis2D::worldPhysicConstant::scale;

			phis2D::BaseBady2D* body = new phis2D::BaseBady2D(collider, Static, density, mass, restitution, area);
			scena->AddBady(body);
			return false;
		}
		bool AddCircle(const v2f& position, float radius, float density, float restitution, bool Static)
		{
			std::string outMsg;
			if (!CheckProperty(density, radius, outMsg))
			{
				logs_.push_back(outMsg);
				return false;
			}
			phis2D::collider::VirtualCollider* collider = new phis2D::collider::CircleCollider(position, radius);
			return AddCollider(collider, density, restitution, Static);
		}
		bool AddBox(const v2f& position, const v2f& size, float density, float restitution, bool Static)
		{
			std::string outMsg;
			if (!CheckProperty(density, size, outMsg))
			{
				logs_.push_back(outMsg);
				return false;
			}
			phis2D::collider::VirtualCollider* collider = new phis2D::collider::BoxCollider(position, size);
			return AddCollider(collider, density, restitution, Static);
		}
		bool AddPolygon(const v2f& position, const v2f* vertices, size_t cntVertices, float density, float restitution, bool Static)
		{
			std::string outMsg;
			if (!CheckProperty(vertices, cntVertices, outMsg))
			{
				logs_.push_back(outMsg);
				return false;
			}
			phis2D::collider::VirtualCollider* collider = new phis2D::collider::PolygonCollider(phis2D::collider::vecV2f(vertices, cntVertices));
			return AddCollider(collider, density, restitution, Static);
		}


		bool AddRandomCircle(const v2f& pos, bool Static)
		{
			float radius = utility::getRandomNumber(phis2D::worldPhysicConstant::minRadius, phis2D::worldPhysicConstant::maxRadius);

			float density = utility::getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity);
			float restitution = utility::getRandomNumber(0.f, 1.f);

			return AddCircle(pos, radius, density, restitution, Static);
		}
		bool AddRandomBox(const v2f& pos, bool Static)
		{
			float width = utility::getRandomNumber(phis2D::worldPhysicConstant::minSide, phis2D::worldPhysicConstant::maxSide);
			float height = utility::getRandomNumber(phis2D::worldPhysicConstant::minSide, phis2D::worldPhysicConstant::maxSide);

			float density = utility::getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity);
			float restitution = utility::getRandomNumber(0.f, 1.f);

			return AddBox(pos, v2f(width, height), density, restitution, Static);
		}
		bool AddRandomPolygon(const v2f& pos, bool Static)
		{
			int n = utility::getRandomNumber(3, 7);
			auto vertices = utility::GenerateRandVerticesPolygon(pos, n);

			float density = utility::getRandomNumber(phis2D::worldPhysicConstant::MinDensity, phis2D::worldPhysicConstant::MaxDensity);
			float restitution = utility::getRandomNumber(0.f, 1.f);

			bool result = AddPolygon(pos, vertices.first, n, density, restitution, Static);
			delete vertices.first;

			return result;
		}

		bool AddRandom(const v2f& pos, bool Static)
		{
			phis2D::collider::typeCollider randomType = (phis2D::collider::typeCollider)(rand() % phis2D::collider::typeColliderCount);
			if (randomType == phis2D::collider::Box)
				return AddRandomBox(pos, Static);
			else if (randomType == phis2D::collider::Circle)
				return AddRandomCircle(pos, Static);
			else if (randomType == phis2D::collider::Polygon)
				return AddRandomPolygon(pos, Static);
			else
				logs_.push_back("[AddRandom](--errore 'unidentified type'){ NoName type }");
			return false;
		}
		~AdderBody() = default;

	private:
		Scena* scena;
		std::vector<std::string>& logs_;

		static bool CheckProperty(float density, std::string& outMsg)
		{
			if (density < phis2D::worldPhysicConstant::MinDensity)
			{
				outMsg = "[CheckProperty](--error 'Small Value')\n{ density: " + std::to_string(density) + " }\n";
				return false;
			}
			else if (density > phis2D::worldPhysicConstant::MaxDensity)
			{
				outMsg = "[CheckProperty](--error 'Big Value')\n{ density: " + std::to_string(density) + " }\n";
				return false;
			}
			return true;
		}
		static bool CheckProperty(float density, float radius, std::string& outMsg)
		{
			if (!CheckProperty(density, outMsg)) return false;

			if (radius < phis2D::worldPhysicConstant::minRadius)
			{
				outMsg = "[CheckProperty](--error 'Small Value')\n{ radius: " + std::to_string(radius) + " }\n";
				return false;
			}
			else if (radius > phis2D::worldPhysicConstant::maxRadius)
			{
				outMsg = "[CheckProperty](--error 'Big Value')\n{ radius: " + std::to_string(radius) + " }\n";
				return false;
			}
			return true;
		}
		static bool CheckProperty(float density, float width, float height, std::string& outMsg)
		{
			if (!CheckProperty(density, outMsg)) return false;

			if (width < phis2D::worldPhysicConstant::minSide || height < phis2D::worldPhysicConstant::minSide)
			{
				outMsg = "[CheckProperty](--error 'Small Value')\n{ width: " + std::to_string(width) + ", height: " + std::to_string(height) + " }\n";
				return false;
			}
			else if (width > phis2D::worldPhysicConstant::maxSide || height > phis2D::worldPhysicConstant::maxSide)
			{
				outMsg = "[CheckProperty](--error 'Big Value')\n{ width: " + std::to_string(width) + ", height: " + std::to_string(height) + " }\n";
				return false;
			}
			return true;
		}

		static bool CheckProperty(float density, const v2f& size, std::string& outMsg)
		{
			return CheckProperty(density, size.x, size.y, outMsg);
		}


		static bool CheckProperty(const v2f* vertices, size_t cntVertices, std::string& outMsg)
		{
			if (vertices == nullptr)
			{
				outMsg = "[CheckProperty](--error 'nullptr')\n{ vertices is nullptr }";
				return false;
			}
			if (cntVertices <= 2)
			{
				outMsg = "[CheckProperty](--error 'Vertices')\n{ count vertices: " + std::to_string(cntVertices) + ", give >= 3 }\n";
				return false;
			}
			return true;
		}
		static bool CheckProperty(phis2D::collider::VirtualCollider* collider, std::string& outMsg)
		{
			if (collider == nullptr)
			{
				outMsg = "[CheckProperty](--error 'nullptr')\n{ collider is nullptr }";
				return false;
			}
			return true;
		}
		static bool CheckProperty(phis2D::collider::VirtualCollider* collider, float density, std::string& outMsg)
		{
			if (!CheckProperty(collider, outMsg)) return false;
			if (!CheckProperty(density, outMsg))  return false;

			return true;
		}
		
	};

}