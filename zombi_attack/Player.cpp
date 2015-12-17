#include "Player.h"

Player::Player(Image &image, float X, float Y, int W, int H, String Name)
	:Entity(image, X, Y, W, H, Name)
{
	isShoot = false;
	attackTimer = 0;
	frequencyAttack = 500;//скорость атаки игрока
	sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Player::setStay(){

}

bool Player::isStay(){//если игрок стоит, то вернем true
	if (state == stay){ return true; }
	return false;
}

void Player::rotateSprite(Vector2f pos) {
	float rotation = (atan2(pos.y - y, pos.x - x)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
	if (state == stay) {
		if ((rotation > -180.0) && (rotation<-135.0)) { sprite.setTextureRect(IntRect(w, h * 4, w, h)); }
		if ((rotation > -135.0) && (rotation<-105.0)) { sprite.setTextureRect(IntRect(w, 0, w, h)); }
		if ((rotation > -105.0) && (rotation<-45.0)) { sprite.setTextureRect(IntRect(w, h, w, h)); }
		if ((rotation > -45.0) && (rotation<-25.0)) { sprite.setTextureRect(IntRect(w, h * 2, w, h)); }
		if ((rotation < 25.0) && (rotation>-25.0)) { sprite.setTextureRect(IntRect(w, h * 3, w, h)); }
		if ((rotation < 45.0) && (rotation>25.0)) { sprite.setTextureRect(IntRect(w, h * 7, w, h)); }
		if ((rotation < 90.0) && (rotation>45.0)) { sprite.setTextureRect(IntRect(w, h * 6, w, h)); }
		if ((rotation > 90.0) && (rotation<135.0)) { sprite.setTextureRect(IntRect(w, h * 5, w, h)); }
		if ((rotation > 135.0) && (rotation<180.0)) { sprite.setTextureRect(IntRect(w, h * 4, w, h)); }
	}
}

void Player::startAnimation(float &time) { //анимация
	switch (state)//для каждого состояния своя анимация
	{
	case down: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h * 6, w, h)); break;
	case left: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h * 4, w, h)); break;
	case right: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h * 3, w, h)); break;
	case left_down: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h * 5, w, h)); break;
	case right_down: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h * 7, w, h)); break;
	case up: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h, w, h)); break;
	case left_up: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), 0, w, h)); break;
	case right_up: sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), h * 2, w, h)); break;
	}
}

void Player::frequencyShoot(float &time) { //можем стрелять только не чаще чем раз в frequence сек
	attackTimer += time;
	if ((attackTimer > frequencyAttack) && (isShoot == false) && (state == stay)) { //если перезарядилось и стоим, то можем стрельнуть
		isShoot = true;
		attackTimer = 0;
	}
}

void Player::isShootAlive(){
	if (life == false) { isShoot = false; }
}

void Player::control(float &time) {
	if (life) {//убираем игрока движение после смерти
		if ((!Keyboard::isKeyPressed(Keyboard::Left) && (!Keyboard::isKeyPressed(Keyboard::Right)
			&& (!Keyboard::isKeyPressed(Keyboard::Down) && (!Keyboard::isKeyPressed(Keyboard::Up)
			&& (!Keyboard::isKeyPressed(Keyboard::A) && (!Keyboard::isKeyPressed(Keyboard::S)
			&& (!Keyboard::isKeyPressed(Keyboard::D) && (!Keyboard::isKeyPressed(Keyboard::W)))))))))) {
			state = stay;//если ничего не нажали, то состояние "стоим"
		}

		if (state != stay) {
			startAnimation(time);//если что то нажали - играем анимацию
		}


		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			speed = 0.1;
			state = left;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			speed = 0.1;
			state = right;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			speed = 0.1;
			state = up;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			speed = 0.1;
			state = down;
		}

		if ((Keyboard::isKeyPressed(Keyboard::W) && (Keyboard::isKeyPressed(Keyboard::A)) && (state != left))) {

			state = left_up;
		}

		if ((Keyboard::isKeyPressed(Keyboard::W) && (Keyboard::isKeyPressed(Keyboard::D)))) {
			speed = 0.1;
			state = right_up;
		}

		if ((Keyboard::isKeyPressed(Keyboard::A) && (Keyboard::isKeyPressed(Keyboard::S)))) {
			speed = 0.1;
			state = left_down;
		}

		if ((Keyboard::isKeyPressed(Keyboard::D) && (Keyboard::isKeyPressed(Keyboard::S)))) {
			speed = 0.1;
			state = right_down;
		}
	}
}

void Player::update(float time, Home & home)
{
	control(time);//управление
	checkCollisionWithHome(home);//столкновение с домом
	checkDeath();//проверка на смерть игрока
	frequencyShoot(time);//частота выстрела
	isShootAlive();// стреляет пока жив
	switch (state)//меняем направление
	{
	case right: dx = speed; dy = 0; break;
	case left: dx = -speed; dy = 0; break;
	case down: dx = 0; dy = speed; break;
	case up: dx = 0; dy = -speed; break;
	case left_up: dx = -speed / 2; dy = -speed / 2; break;
	case left_down: dx = -speed / 2; dy = speed / 2; break;
	case right_up: dx = speed / 2; dy = -speed / 2; break;
	case right_down: dx = speed / 2; dy = speed / 2; break;
	case stay:dx = 0; dy = 0; speed = 0; break;
	}

	x += dx*time;
	y += dy*time;

	speed = 0;
	sprite.setPosition(x + w / 2, y + h / 2);
}