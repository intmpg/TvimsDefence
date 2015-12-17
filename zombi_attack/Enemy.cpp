#include "Enemy.h"

Enemy::Enemy(Image &image, float X, float Y, int W, int H, String Name, int Health, float Speed)
	:Entity(image, X, Y, W, H, Name)
{
	if (name == "ZombieEnemy") {
		sprite.setTextureRect(IntRect(0, h, w, h));//тайл в тайлсете
		dx = Speed;//даем скорость.этот объект всегда двигается
		health = Health;//здоровье
		deathAnimationTimer = 0;//таймер показа анимации смерти
	}
}

void Enemy::startAnimation(float &time){//анимация
	sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), 0, w, h));//анимация ходьбы
	if (health <= 0) {  // для создания анимации смерти
		deathAnimationTimer += time;
		sprite.setTextureRect(IntRect(37 * int(getCurrentFrame(time)), h + 1, 37, h + 1));//анимация смерти
		if (deathAnimationTimer > 600) { life = false; deathAnimationTimer = 0; }//показываем анимацию и убиваем врага
	}
}

void Enemy::attackHome(Home & home){//атака дома
	if (getRect().intersects(home.getRect())) { home.setDamage(); } // если зомби столкнулись с домом , то атакуют
}

void Enemy::update(float time, Home & home){//оживление врага 
	if (name == "ZombieEnemy") {//для персонажа с таким именем логика будет такой
		x += dx*time;//само движение
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		startAnimation(time);//анимация движений
		checkDeath(); // проверка на смерть
		attackHome(home);//атака дома
		checkCollisionWithHome(home);//проверка столкновения с домом
	}
}