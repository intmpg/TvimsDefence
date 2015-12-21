#ifndef BULLET_HPP
#define BULLET_HPP
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "home.h"

using namespace sf;

class Bullet :public Entity{//����� ����
public:
	Vector2f m_target;//���� ����
	Vector2f m_direction;//�����������
	float distance;//���������

	Bullet(Image &image, String Name, Vector2f startPosition, Vector2i spriteObjectSize, float tX, float tY);//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	void update(float time, Home &home);
	
};
#endif