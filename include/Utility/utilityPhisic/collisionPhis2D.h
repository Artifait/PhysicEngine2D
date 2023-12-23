#pragma once
#include <Shapes/Colliders.h>
#include <v2f.h>
#include <float.h>

namespace phis2D
{
	class Collision
	{
	public:
		Collision() = default;
		~Collision() = default;
	private: static void ProjectPolygons(const std::pair<const v2f* const&, size_t>& vertices, const v2f& axis, float& min, float& max) //����� ����
	{
		min = 3.4E+38;
		max = -3.4E+38;
		for (int i = 0; i < vertices.second; i++)
		{
			float proj = v2f::dot(vertices.first[i], axis);
			if (proj > max) max = proj;
			if (proj < min) min = proj;
		}
	}
	public: static void ProjectCircle(collider::CircleCollider* circle, const v2f& axis, float& min, float& max)// ����� ����
	{
		v2f normAxis = v2f::Normalize(axis);
		v2f axisAndRadius = normAxis * circle->GetRadius();

		v2f p1 = circle->GetPosition() + axisAndRadius;
		v2f p2 = circle->GetPosition() - axisAndRadius;

		min = v2f::dot(p1, normAxis);
		max = v2f::dot(p2, normAxis);
		if (min > max) std::swap(min, max);
	}

	private: static int FindClosestPointOnPolygon(const v2f& circleCenter, const std::pair<const v2f* const&, size_t>& vertices)//����� ����
	{
		int result = -1;
		float minDist = 3.4E+38;
		for (int i = 0; i < vertices.second; i++)
		{
			float dist = v2f::Distance(circleCenter, vertices.first[i]);
			if (minDist > dist) 
			{
				result = i;
				minDist = dist;
			}
		}
		
		return result;
	
	}
	private: static v2f FindArithmeticMean(const std::pair<const v2f* const&, size_t>& vertices)//����� ����
	{
		v2f sum;
		for (int i = 0; i < vertices.second; i++)
		{
			sum += vertices.first[i];
		}
		return sum / (float)vertices.second;
	}
	private: static bool IntersectCircles(collider::CircleCollider* circleA, collider::CircleCollider* circleB, v2f& normal, float& depth)//����� ����
		{
			normal = v2f();
			depth = 0.f;

			v2f distVec = circleB->GetPosition() - circleA->GetPosition();// ������ ����������� �� A � B ������ ���� ����� �������� B ��� ��������
			float distance = v2f::Length(distVec);
			float radii = circleA->GetRadius() + circleB->GetRadius();

			if (distance >= radii)
				return false;

			depth = radii - distance;
			normal = v2f::Normalize(distVec);
			return true;
		}
	private: static bool IntersectCirclePolygon(collider::CircleCollider* circleA, collider::VirtualCollider* colliderB, v2f& normal, float& depth)
		{
			auto vertixB = colliderB->GetTransformedVertices();
			depth = 3.4E+38;
			float minA, minB, maxA, maxB;
			float axisDepth = 0.f;
			v2f axis;
			for (int i = 0; i < vertixB.second; i++)
			{
				v2f edge = vertixB.first[(i + 1) % vertixB.second] - vertixB.first[i];//�����
				axis = v2f(-edge.y, edge.x);//������� �� �����
				axis.normalize();
				ProjectPolygons(vertixB, axis, minB, maxB);
				ProjectCircle(circleA, axis, minA, maxA);
				if (minA >= maxB || minB >= maxA)
					return false;
				axisDepth = std::min(maxB - minA, maxA - minB);
				if (axisDepth < depth)
				{
					normal = axis;
					depth = axisDepth;
				}
			}
			int cpIndex = FindClosestPointOnPolygon(circleA->GetPosition(), vertixB);
			axis = vertixB.first[cpIndex] - circleA->GetPosition();
			axis.normalize();
			ProjectPolygons(vertixB, axis, minB, maxB);
			ProjectCircle(circleA, axis, minA, maxA);
			if (minA >= maxB || minB >= maxA)
				return false;
			axisDepth = std::min(maxB - minA, maxA - minB);
			if (axisDepth < depth)
			{
				normal = axis;
				depth = axisDepth;
			}

			v2f centerA(circleA->GetPosition());
			v2f centerB(FindArithmeticMean(vertixB));

			v2f dir = centerA - centerB;

			if (v2f::dot(dir, normal) > 0.f)
			{
				normal = -normal;
			}
			return true;
		}
	private: static bool IntersectPolygons(collider::VirtualCollider* colliderA, collider::VirtualCollider* colliderB, v2f& normal, float& depth)//����� ����
		{
			auto vertixA = colliderA->GetTransformedVertices();
			auto vertixB = colliderB->GetTransformedVertices();
			depth = 3.4E+38;
			for (int i = 0; i < vertixA.second; i++)
			{
				v2f edge = vertixA.first[(i + 1) % vertixA.second] - vertixA.first[i];//�����
				v2f axis = v2f(-edge.y, edge.x);//������� �� �����
				axis.normalize();
				float minA, minB, maxA, maxB;
				ProjectPolygons(vertixA, axis, minA, maxA);
				ProjectPolygons(vertixB, axis, minB, maxB);

				if (minA >= maxB || minB >= maxA)
					return false;
				float axisDepth = std::min(maxB - minA, maxA - minB);
				if (axisDepth < depth) 
				{
					normal = axis;
					depth = axisDepth;
				}
			}
			for (int i = 0; i < vertixB.second; i++)
			{
				v2f edge = vertixB.first[(i + 1) % vertixB.second] - vertixB.first[i];//�����
				v2f axis = v2f(-edge.y, edge.x);//������� �� �����
				axis.normalize();
				float minA, minB, maxA, maxB;
				ProjectPolygons(vertixA, axis, minA, maxA);
				ProjectPolygons(vertixB, axis, minB, maxB);

				if (minA >= maxB || minB >= maxA)
					return false;
				float axisDepth = std::min(maxB - minA, maxA - minB);
				if (axisDepth < depth)
				{
					normal = axis;
					depth = axisDepth;
				}
			}

			v2f centerA(FindArithmeticMean(vertixA));
			v2f centerB(FindArithmeticMean(vertixB));

			v2f dir = centerB - centerA;

			if (v2f::dot(dir, normal) < 0.f)
			{
				normal = -normal;
			}

			return true;
		}
	public: static bool IntersectColliders(collider::VirtualCollider* colliderA, collider::VirtualCollider* colliderB, v2f& normal, float& depth)
	{
		collider::typeCollider typeA = colliderA->GetTypeCollider();
		collider::typeCollider typeB = colliderB->GetTypeCollider();

		normal = v2f();
		depth = 0.f;
		bool result = false;

		if (typeA == collider::Circle)
		{
			if (typeB == collider::Circle)
				result = IntersectCircles(static_cast<collider::CircleCollider*>(colliderA), static_cast<collider::CircleCollider*>(colliderB), normal, depth);
			else if(typeB == collider::Box)
			{
				result = IntersectCirclePolygon(static_cast<collider::CircleCollider*>(colliderA), colliderB, normal, depth);
			}
		}
		else if (typeA == collider::Box)
		{
			if (typeB == collider::Circle)
			{
				result = IntersectCirclePolygon(static_cast<collider::CircleCollider*>(colliderB), colliderA, normal, depth);
				normal = -normal;
			}
			else if (typeB == collider::Box)
			{
				result = IntersectPolygons(colliderA, colliderB, normal, depth);
			}
		}
		return result;

	}
	private:

	};
}