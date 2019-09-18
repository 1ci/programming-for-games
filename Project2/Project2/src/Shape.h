#ifndef SHAPE_H
#define SHAPE_H

#include "vec2.h"
#include <string>
#include "IMoveable.h"

struct Grid;

class Shape : public IMoveable
{
protected:
	Shape();
	Shape(const vec2& position);
	Shape(const Shape& other);

public:
	virtual ~Shape();
	vec2 GetPosition() const;
	void SetPosition(const vec2& position);

	// Inherited via IMoveable
	virtual void Move(const vec2& velocity) override;

	virtual unsigned int GetId() const = 0;
	virtual const std::string& GetShapeName() const = 0;
	virtual std::string GetShapeInfo() const = 0;
	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& stream, const Shape& shape);

	virtual bool Collides(Shape& other) const = 0;
	virtual void ClampToGrid(const Grid& grid) = 0;

protected:
	vec2 m_vecPosition;
};

#endif // SHAPE_H
