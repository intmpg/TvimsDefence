#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML\Graphics.hpp>
#include "Entity.h"
using namespace sf;

class Player: public Entity {
public:
	enum { left, right, up, down, left_down, left_up, right_down, right_up,stay } state;
	int frequencyAttack;
	int playerMaxHealth;
	bool isShoot;
	bool isDrive;
	bool isShooted;
	bool isSuperBullet;
	float attackTimer;
	Player(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name);

	bool isStay();
	void rotateSprite(Vector2f pos);
	void startAnimation(float &time);
	void frequencyShoot(float &time);
	void isShootAlive();
	void control(float &time);
	void update(float time, Home & home);
};
#endif