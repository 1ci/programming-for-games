#ifndef COLLISION_H
#define COLLISION_H

class Circle;
class Square;

bool Collide(const Circle& first, const Circle& second);
bool Collide(const Square& first, const Square& second);
bool Collide(const Circle& circle, const Square& square);
bool Collide(const Square& square, const Circle& circle);

#endif // COLLISION_H
