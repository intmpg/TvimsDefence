#include "Player.h"

Player::Player(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name)
:Entity(image, startPosition, spriteObjectSize, Name)
{
	position = startPosition;
	isShoot = false;
	attackTimer = 0;
	frequencyAttack = 500;//скорость атаки игрока
	sprite.setTextureRect(IntRect(0, 0, spriteSize.x, spriteSize.y));
}

bool Player::isStay(){//если игрок стоит, то вернем true
	if (state == stay){ 
		return true; 
	}
	return false;
}

void Player::rotateSprite(Vector2f pos) {
	float rotation = (atan2(pos.y - position.y, pos.x - position.x)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
	if (state == stay) {
		if ((rotation > -180.0) && (rotation<-135.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 4, spriteSize.x, spriteSize.y));
		}
		if ((rotation > -135.0) && (rotation<-105.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, 0, spriteSize.x, spriteSize.y)); 
		}
		if ((rotation > -105.0) && (rotation<-45.0)) {
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y, spriteSize.x, spriteSize.y)); 
		}
		if ((rotation > -45.0) && (rotation<-25.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 2, spriteSize.x, spriteSize.y)); 
		}
		if ((rotation < 25.0) && (rotation>-25.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 3, spriteSize.x, spriteSize.y)); 
		}
		if ((rotation < 45.0) && (rotation>25.0)) {
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 7, spriteSize.x, spriteSize.y)); 
		}
		if ((rotation < 90.0) && (rotation>45.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 6, spriteSize.x, spriteSize.y));
		}
		if ((rotation > 90.0) && (rotation<135.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 5, spriteSize.x, spriteSize.y)); 
		}
		if ((rotation > 135.0) && (rotation<180.0)) { 
			sprite.setTextureRect(IntRect(spriteSize.x, spriteSize.y * 4, spriteSize.x, spriteSize.y)); 
		}
	}
}

void Player::startAnimation(float &time) { //анимация
	switch (state)//для каждого состояния своя анимация
	{
		case down: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 6, spriteSize.x, spriteSize.y)); break;
		case left: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 4, spriteSize.x, spriteSize.y)); break;
		case right: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 3, spriteSize.x, spriteSize.y)); break;
		case left_down: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 5, spriteSize.x, spriteSize.y)); break;
		case right_down: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 7, spriteSize.x, spriteSize.y)); break;
		case up: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y, spriteSize.x, spriteSize.y)); break;
		case left_up: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), 0, spriteSize.x, spriteSize.y)); break;
		case right_up: sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y * 2, spriteSize.x, spriteSize.y)); break;
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
		case right: acceleration.x = speed; acceleration.y = 0; break;
		case left: acceleration.x = -speed; acceleration.y = 0; break;
		case down: acceleration.x = 0; acceleration.y = speed; break;
		case up: acceleration.x = 0; acceleration.y = -speed; break;
		case left_up: acceleration.x = -speed / 2; acceleration.y = -speed / 2; break;
		case left_down: acceleration.x = -speed / 2; acceleration.y = speed / 2; break;
		case right_up: acceleration.x = speed / 2; acceleration.y = -speed / 2; break;
		case right_down: acceleration.x = speed / 2; acceleration.y = speed / 2; break;
		case stay:acceleration.x = 0; acceleration.y = 0; speed = 0; break;
	}

	position.x += acceleration.x*time;
	position.y += acceleration.y*time;

	speed = 0;
	sprite.setPosition(position.x + spriteSize.x / 2, position.y + spriteSize.y / 2);
}