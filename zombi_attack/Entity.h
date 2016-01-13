#ifndef ENITY_HPP
#define ENITY_HPP
#include <SFML\Graphics.hpp>
#include "home.h"
using namespace sf;

class Entity {
public:
	Vector2f position;
	Vector2f acceleration;
	Vector2i spriteSize;
	float speed;
	float currentFrame;//�������� ���������� ����� ����
	float currentFrameDeath;
	int health;
	bool life;
	bool startShowDecomposition;//���������� ����� ������
	bool isTractorKiller;//������� �� � ������ �������
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, Vector2f startPosition, Vector2i spriteObjectSize, String Name);
	void checkDeath();//�������� �� ������ �������
	float getCurrentFrame(float &time); //�������� ������� ���� ��������
	float getCurrentFrameDeath(float &time);//����� ������ ���������� �����
	void setCurrentFrame(int currentFRAME);
	FloatRect getRect();//�������� ������� �������������� �������
	void checkCollisionWithHome(Home &home);//������������ � �����
	virtual void update(float time, Home &home) = 0;
	virtual ~Entity() {};
};
#endif