#include "Enemy.h"

Enemy::Enemy(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name, int Health, float Speed)
:Entity(image, startPosition, spriteObjectSize, Name)
{
	if (name == "ZombieEnemy") {
		sprite.setTextureRect(IntRect(0, spriteSize.y, spriteSize.x, spriteSize.y));//тайл в тайлсете
		acceleration.x = Speed;//даем скорость.этот объект всегда двигается
		health = Health;//здоровье
		deathAnimationTimer = 0;//таймер показа анимации смерти
	}
}

void Enemy::startAnimation(float &time){//анимация
	sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), 0, spriteSize.x, spriteSize.y));//анимация ходьбы
	if (health <= 0) {  // для создания анимации смерти
		deathAnimationTimer += time;
		sprite.setTextureRect(IntRect(37 * int(getCurrentFrame(time)), spriteSize.y + 1, 37, spriteSize.y + 1));//анимация смерти
		if (deathAnimationTimer > 600) { 
			life = false; deathAnimationTimer = 0; 
		}//показываем анимацию и убиваем врага
	}
}

void Enemy::attackHome(Home & home){//атака дома
	if (getRect().intersects(home.getRect())) { 
		home.setDamage(); 
	} // если зомби столкнулись с домом , то атакуют
}

void Enemy::update(float time, Home & home){//оживление врага 
	if (name == "ZombieEnemy") {//для персонажа с таким именем логика будет такой
		position.x += acceleration.x*time;//само движение
		sprite.setPosition(position.x + spriteSize.x / 2, position.y + spriteSize.y / 2); //задаем позицию спрайта в место его центра
		startAnimation(time);//анимация движений
		checkDeath(); // проверка на смерть
		attackHome(home);//атака дома
		checkCollisionWithHome(home);//проверка столкновения с домом
	}
}