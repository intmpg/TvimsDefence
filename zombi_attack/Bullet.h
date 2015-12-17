#ifndef BULLET_HPP
#define BULLET_HPP
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "home.h"

using namespace sf;

class Bullet :public Entity{//класс пули
public:
	Vector2f m_target;//цель пули
	Vector2f m_direction;//направление
	float distance;//дистанция

	Bullet(Image &image, String Name, float X, float Y, int W, int H, float tX, float tY);//всё так же, только взяли в конце состояние игрока (int dir)
	void update(float time, Home &home);
	
};
#endif