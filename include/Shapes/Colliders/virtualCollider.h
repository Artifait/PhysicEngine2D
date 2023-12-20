#pragma once
#include <Shapes/Colliders/typeCollider.h>
#include <v2f.h>
#include <string>
#include <new>

class VirtualCollider
{
public:
	VirtualCollider() = default;
	~VirtualCollider() = default;

	virtual phis2D::typeCollider GetTypeCollider() = 0;
	virtual const v2f& GetPosition() = 0;
};
