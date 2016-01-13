#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Entity.h"
#include "map.h"
#include "home.h"
using namespace sf;

class Enemy :public Entity{
public:
	float deathAnimationTimer;
	bool showDecomposition;//���������� ����� ������
	Enemy(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name, int Health, float Speed);
	void startAnimation(float &time);//��������
	void deathAnimation();//�������� ����� ������
	void attackHome(Home & home);//����� ����
	void update(float time, Home & home);//��������� ����� 
	
};
#endif