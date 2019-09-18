#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include "Shape.h"

class Square;
struct Grid;

class Circle : public Shape
{
public:
	Circle();
	Circle(float radius);
	Circle(const vec2& position);
	Circle(const vec2& position, float radius);
	Circle(const Circle& other);
	~Circle();

	Circle& operator=(const Circle& other);
	bool operator==(const Circle& other) const;

	float GetRadius() const;
	void SetRadius(float radius);

	bool Collides(const Circle& circle) const;
	bool Collides(const Square& square) const;
	
	// Inherited via Shape
	virtual unsigned int GetId() const override;
	virtual const std::string& GetShapeName() const override;
	virtual std::string GetShapeInfo() const override;
	virtual bool Collides(Shape& other) const override;
	virtual void ClampToGrid(const Grid& grid) override;

protected:
	float m_fRadius;

private:
	static const std::string m_sName;
	unsigned int m_id;
	static unsigned int m_idCounter;
};

#endif // CIRCLE_H
