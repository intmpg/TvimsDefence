#ifndef ENITY_HPP
#define ENITY_HPP
#include <SFML\Graphics.hpp>
#include "home.h"
using namespace sf;

class Entity {
public:
	float dx;
	float dy; 
	float x; 
	float y;
	float speed;
	float currentFrame;//�������� ���������� ������ ��� ������� �����
	int w;
	int h;
	int health;
	bool life;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, float X, float Y, int W, int H, String Name);
	void checkDeath();//�������� �� ������ �������
	float getCurrentFrame(float time); //�������� ������� ���� ��������
	void setCurrentFrame(int cF);
	FloatRect getRect();//�������� ������� �������������� �������
	void checkCollisionWithHome(Home &home);//������������ � �����
	virtual void update(float time, Home &home) = 0;
};
#endif