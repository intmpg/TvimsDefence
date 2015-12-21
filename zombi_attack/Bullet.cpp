#include "Bullet.h"

Bullet::Bullet(Image &image, String Name, Vector2f startPosition, Vector2i spriteObjectSize, float tX, float tY)
:Entity(image, startPosition, spriteObjectSize, Name)
{
	position = startPosition;
	speed = 8.9;//скорость пули
	spriteSize.x = spriteSize.y = 16;
	life = true;
	m_target.x = tX;
	m_target.y = tY;
	distance = 0;
}

void Bullet::update(float time, Home &home){
	distance = sqrt((m_target.x - position.x)*(m_target.x - position.x) + (m_target.y - position.y)*(m_target.y - position.y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

	if (distance> 5) {//этим условием убираем дергание во время конечной позиции спрайта
		position.x += speed*(m_target.x - position.x) / distance;
		position.y += speed*(m_target.y - position.y) / distance;
	}
	else { 
		life = false; 
	}
	sprite.setPosition(position.x + 26, position.y + 30);//задается позицию пуле
}