#pragma once

#include <StructData/v2f.h>


class v2fRect
{
public:
	v2fRect(float x, float y, float width, float height) : Position{ x, y }, Size{ width, height } {}
	v2fRect(const v2f& pos, const v2f& size) : Position{ pos }, Size{ size } {}
	v2fRect() : v2fRect(0, 0, 0, 0) {}

	const v2f& GetSize() const { return Size; }
	const v2f& GetPosition() const { return Position; }

	const v2f& GetMinCorner() const { return GetPosition(); }
	v2f GetMaxCorner() const { return GetPosition() + GetSize(); }
	void Move(const v2f& offset) { Position += offset; }
	void MoveTo(const v2f& newPosition) { Position = newPosition; }

	~v2fRect() = default;
private:
	v2f Position;
	v2f Size;
};
