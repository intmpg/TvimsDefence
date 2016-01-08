#ifndef GAMEMATH_HPP
#define GAMEMATH_HPP
#include <SFML\Graphics.hpp>

using namespace sf;

float lengthSqr(Vector2f dist){
	return (dist.x*dist.x + dist.y*dist.y);
}

void radiusAim(int attackDistance, Vector2f aimPosition, Vector2f playerPosition, Sprite &spriteCursor) {
	Vector2f dist = aimPosition;
	int offsetBulletX = 10;

	dist.x = aimPosition.x - playerPosition.x;
	dist.y = aimPosition.y - playerPosition.y;

	if (lengthSqr(dist) > attackDistance) {
		float angle = std::atan2(dist.y, dist.x);
		aimPosition.x = playerPosition.x + attackDistance * cos(angle);
		aimPosition.y = playerPosition.y + attackDistance * sin(angle);
	}
	spriteCursor.setPosition(aimPosition.x + offsetBulletX, aimPosition.y);
}
#endif