#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Entity.h";
#include "map.h"
#include "home.h"
using namespace sf;

class Enemy :public Entity{
public:
	float deathAnimationTimer;
	Enemy(Image &image, float X, float Y, int W, int H, String Name, int Health, float Speed);
	void startAnimation(float &time);//анимация
	void attackHome(Home & home);//атака дома
	void update(float time, Home & home);//оживление врага 
	
};
#endif