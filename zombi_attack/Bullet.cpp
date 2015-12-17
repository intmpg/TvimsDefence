#include "Bullet.h"

Bullet::Bullet(Image &image, String Name, float X, float Y, int W, int H, float tX, float tY)
	:Entity(image, X, Y, W, H, Name)//всё так же, только взяли в конце состояние игрока (int dir)
{
	x = X;
	y = Y;
	speed = 8.9;//скорость пули
	w = h = 16;
	life = true;
	m_target.x = tX;
	m_target.y = tY;
	distance = 0;
}

void Bullet::update(float time, Home &home){
	distance = sqrt((m_target.x - x)*(m_target.x - x) + (m_target.y - y)*(m_target.y - y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

	if (distance> 5) {//этим условием убираем дергание во время конечной позиции спрайта
		x += speed*(m_target.x - x) / distance;
		y += speed*(m_target.y - y) / distance;
	}
	else { life = false; }

	sprite.setPosition(x + 26, y + 30);//задается позицию пуле
	//sprite.setPosition(x + 56/2, y + 66/2);//задается позицию пуле
}