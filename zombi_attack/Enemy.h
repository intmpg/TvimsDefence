#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Entity.h"
#include "map.h"
#include "home.h"
using namespace sf;

class Enemy :public Entity{
public:
	float deathAnimationTimer;
	bool showDecomposition;//разложение после смерти
	Enemy(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name, int Health, float Speed);
	void startAnimation(float &time);//анимация
	void deathAnimation();//анимация после смерти
	void attackHome(Home & home);//атака дома
	void update(float time, Home & home);//оживление врага 
	
};
#endif