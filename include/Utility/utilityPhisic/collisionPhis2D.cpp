#pragma once
#include <Utility/utilityPhisic/collisionPhis2D.h>

namespace phis2D
{

	void Collision::ProjectPolygons(const std::pair<const v2f* const&, size_t>& vertices, const v2f& axis, float& min, float& max) //точно норм
	{
		min = 3.4E+38f;
		max = -3.4E+38f;
		for (int i = 0; i < vertices.second; i++)
		{
			float proj = v2f::dot(vertices.first[i], axis);
			if (proj > max) max = proj;
			if (proj < min) min = proj;
		}
	}
	void Collision::ProjectCircle(collider::CircleCollider* circle, const v2f& axis, float& min, float& max)// точно норм
	{
		v2f normAxis = v2f::Normalize(axis);
		v2f axisAndRadius = normAxis * circle->GetRadius();

		v2f p1 = circle->GetPosition() + axisAndRadius;
		v2f p2 = circle->GetPosition() - axisAndRadius;

		min = v2f::dot(p1, normAxis);
		max = v2f::dot(p2, normAxis);
		if (min > max) std::swap(min, max);
	}

	int Collision::FindClosestPointOnPolygon(const v2f& circleCenter, const std::pair<const v2f* const&, size_t>& vertices)
	{
		int result = -1;
		float minDist = 3.4E+38f;
		for (int i = 0; i < vertices.second; i++)
		{
			float dist = v2f::DistanceSquere(circleCenter, vertices.first[i]);
			if (minDist > dist)
			{
				result = i;
				minDist = dist;
			}
		}

		return result;

	}

	v2f Collision::FindArithmeticMean(const std::pair<const v2f* const&, size_t>& vertices)//точно норм
	{
		v2f sum;
		for (int i = 0; i < vertices.second; i++)
		{
			sum += vertices.first[i];
		}
		return sum / (float)vertices.second;
	}

	bool Collision::IntersectCircles(collider::CircleCollider* circleA, collider::CircleCollider* circleB, v2f& normal, float& depth)//точнр норм
	{
		normal = v2f();
		depth = 0.f;

		v2f distVec = circleB->GetPosition() - circleA->GetPosition();// вектор направлений из A в B тоесть куда нужно сдвинуть B при коллизии
		float distance = v2f::Length(distVec);
		float radii = circleA->GetRadius() + circleB->GetRadius();

		if (distance >= radii)
			return false;

		depth = radii - distance;
		normal = v2f::Normalize(distVec);
		return true;
	}

	bool Collision::IntersectCirclePolygon(collider::CircleCollider* circleA, collider::VirtualCollider* colliderB, v2f& normal, float& depth)
	{
		auto vertixB = colliderB->GetTransformedVertices();
		depth = 3.4E+38f;
		float minA, minB, maxA, maxB;
		float axisDepth = 0.f;
		v2f axis;
		for (int i = 0; i < vertixB.second; i++)
		{
			v2f edge = vertixB.first[(i + 1) % vertixB.second] - vertixB.first[i];//грань
			axis = v2f(-edge.y, edge.x);//нормаль от грани
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

	bool Collision::IntersectPolygons(collider::VirtualCollider* colliderA, collider::VirtualCollider* colliderB, v2f& normal, float& depth)//точно норм
	{
		auto vertixA = colliderA->GetTransformedVertices();
		auto vertixB = colliderB->GetTransformedVertices();
		depth = 3.4E+38;
		for (int i = 0; i < vertixA.second; i++)
		{
			v2f edge = vertixA.first[(i + 1) % vertixA.second] - vertixA.first[i];//грань
			v2f axis = v2f(-edge.y, edge.x);//нормаль от грани
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
			v2f edge = vertixB.first[(i + 1) % vertixB.second] - vertixB.first[i];//грань
			v2f axis = v2f(-edge.y, edge.x);//нормаль от грани
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

	bool Collision::IntersectColliders(collider::VirtualCollider* colliderA, collider::VirtualCollider* colliderB, v2f& normal, float& depth)
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
			else if (typeB == collider::Box || typeB == collider::Polygon)
				result = IntersectCirclePolygon(static_cast<collider::CircleCollider*>(colliderA), colliderB, normal, depth);

		}
		else if (typeA == collider::Box || typeA == collider::Polygon)
		{
			if (typeB == collider::Circle)
			{
				result = IntersectCirclePolygon(static_cast<collider::CircleCollider*>(colliderB), colliderA, normal, depth);
				normal = -normal;
			}
			else if (typeB == collider::Box || typeB == collider::Polygon)
				result = IntersectPolygons(colliderA, colliderB, normal, depth);
		}
		return result;

	}

	void phis2D::Collision::ResolverCollision(BaseBady2D* badyA, BaseBady2D* badyB, const v2f& normal, float depth)
	{
		v2f relativeVelocity = badyB->LinearVelocity - badyA->LinearVelocity;
		float e = std::min(badyA->Restitution, badyB->Restitution);
		float j = -(1.f + e) * v2f::dot(relativeVelocity, normal);
		j /= (1.f / badyA->Mass + 1.f / badyB->Mass);
		badyA->LinearVelocity -= j / badyA->Mass * normal;
		badyB->LinearVelocity += j / badyA->Mass * normal;

	}
}