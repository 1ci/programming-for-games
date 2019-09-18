#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "Shape.h"

class Circle;
struct Grid;

class Square : public Shape
{
public:
	Square();
	Square(float side);
	Square(const vec2& position);
	Square(const vec2& position, float side);
	Square(const Square& other);
	~Square();

	Square& operator=(const Square& other);
	bool operator==(const Square& other) const;

	float GetSide() const;
	void SetSide(float side);

	bool Collides(const Circle& circle) const;
	bool Collides(const Square& square) const;
	
	// Inherited via Shape
	virtual unsigned int GetId() const override;
	virtual const std::string& GetShapeName() const override;
	virtual std::string GetShapeInfo() const override;
	virtual bool Collides(Shape& other) const override;
	virtual void ClampToGrid(const Grid& grid);

protected:
	float m_fSide;

private:
	static const std::string m_sName;
	unsigned int m_id;
	static unsigned int m_idCounter;
};

#endif // SQUARE_H
