#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name, int Health, float Speed)
:Entity(image, startPosition, spriteObjectSize, Name)
{
		sprite.setTextureRect(IntRect(0, spriteSize.y, spriteSize.x, spriteSize.y));//тайл в тайлсете
		acceleration.x = Speed;//даем скорость.этот объект всегда двигается
		health = Health;//здоровье
		deathAnimationTimer = 0;//таймер показа анимации смерти
		showDecomposition = false;//не показывать разложение 
}

void Enemy::startAnimation(float &time) {//анимация
	sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), 0, spriteSize.x, spriteSize.y));//анимация ходьбы

	if (health <= 0) {  // для создания анимации смерти
		deathAnimationTimer += time;
		if (name == "ZombieEnemy") {//для персонажа с таким именем логика анимации смерти будет такой
			if (isTractorKiller) {
				sprite.setTextureRect(IntRect(88 * int(getCurrentFrame(time)), spriteSize.y, 88, 57));//анимация смерти первого зомби от трактора
			} else {
				sprite.setTextureRect(IntRect(61 * int(getCurrentFrame(time)), 135, 61, 93));//анимация смерти первого зомби от пули
			}
		}
		if (name == "BearZombieEnemy") {//для персонажа с таким именем логика анимации смерти будет такой
			sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y, spriteSize.x, spriteSize.y + 1));//анимация смерти
		}
		if (deathAnimationTimer > 800) {
			deathAnimationTimer = 0;
			showDecomposition = true;//начать показывать разложение
		}//показываем анимацию и убиваем врага

		if (showDecomposition) {
			if (name == "ZombieEnemy") {//для персонажа с таким именем логика разложения будет такой
				if (isTractorKiller) {
					sprite.setTextureRect(IntRect(88 * int(getCurrentFrameDeath(time)), spriteSize.y, 88, 57));//анимация разложения от трактора
				} else {
					sprite.setTextureRect(IntRect(61 * int(getCurrentFrameDeath(time)), 135, 61, 93));//анимация разложения от пули
				}
			}
			if (name == "BearZombieEnemy") {//для персонажа с таким именем логика разложения будет такой
				if (isTractorKiller) {
					sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 2, spriteSize.x, spriteSize.y + 1));//анимация смерти
				} else {
					sprite.setTextureRect(IntRect(74 * int(getCurrentFrameDeath(time)), 135, 74, 68));//анимация разложения от пули
				}
			}
		}
	}
}

void Enemy::attackHome(Home & home){//атака дома
	if (getRect().intersects(home.getRect())) { 
		home.setDamage(); 
	} // если зомби столкнулись с домом , то атакуют
}

void Enemy::update(float time, Home & home){//оживление врага 
	if (health > 0) {
		position.x += acceleration.x*time;//само движение
		sprite.setPosition(position.x + spriteSize.x / 2, position.y + spriteSize.y / 2); //задаем позицию спрайта в место его центра
		attackHome(home);//атака дома
		checkCollisionWithHome(home);//проверка столкновения с домом
	} else {
		checkDeath(); // проверка на смерть
	}
	startAnimation(time);//анимация движений
}