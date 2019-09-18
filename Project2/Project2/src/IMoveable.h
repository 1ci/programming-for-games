#ifndef IMOVEABLE_H
#define IMOVEABLE_H

struct vec2;

class IMoveable
{
public:
	virtual void Move(const vec2& velocity) = 0;
};

#endif // IMOVEABLE_H
