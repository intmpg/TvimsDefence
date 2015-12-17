#include "Bullet.h"

Bullet::Bullet(Image &image, String Name, float X, float Y, int W, int H, float tX, float tY)
	:Entity(image, X, Y, W, H, Name)//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
{
	x = X;
	y = Y;
	speed = 8.9;//�������� ����
	w = h = 16;
	life = true;
	m_target.x = tX;
	m_target.y = tY;
	distance = 0;
}

void Bullet::update(float time, Home &home){
	distance = sqrt((m_target.x - x)*(m_target.x - x) + (m_target.y - y)*(m_target.y - y));//������� ��������� (����� �� ����� � �� ����� �). ������� ����� �������

	if (distance> 5) {//���� �������� ������� �������� �� ����� �������� ������� �������
		x += speed*(m_target.x - x) / distance;
		y += speed*(m_target.y - y) / distance;
	}
	else { life = false; }

	sprite.setPosition(x + 26, y + 30);//�������� ������� ����
	//sprite.setPosition(x + 56/2, y + 66/2);//�������� ������� ����
}