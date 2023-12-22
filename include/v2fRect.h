#pragma once

#include <v2f.h>


class v2fRect
{
public:
	v2fRect(float x, float y, float width, float height) : Position{ x, y }, Size{width, height}
	{
	}
	v2fRect() : v2fRect(0, 0, 0, 0)
	{

	}

	v2f GetSize()
	{
		return Size;
	}

	v2f GetPosition()
	{
		return Position;
	}

	void Move(const v2f& offset)
	{
		Position += offset;
	}

	
	~v2fRect()
	{
	}

private:
	v2f Position;
	v2f Size;
};
