#include "Tractor.h"

using namespace sf;

Tractor::Tractor() {
	startPosition = (Vector2f(-17, 0));
	position = startPosition;
	
	spriteSizeHorizontal = (Vector2i(127, 80));
	spriteSizeVertical = (Vector2i(59, 124));

	spriteOffsetRight = (Vector2i(136, 23));
	spriteOffsetLeft = (Vector2i(132, 157));
	spriteOffsetUp = (Vector2i(36, 8));
	spriteOffsetDown = (Vector2i(38, 131));

	acceleration = (Vector2f(0, 0));
	tractorImage.loadFromFile("images/tractor.png");
	texture.loadFromImage(tractorImage);
	sprite.setTexture(texture);
	sprite.setOrigin(spriteSizeHorizontal.x / 2, spriteSizeHorizontal.y / 2);
	sprite.setTextureRect(IntRect(136, 23, spriteSizeHorizontal.x, spriteSizeHorizontal.y));
	isMove = false;
	moveTimer = 0;
	startTimer = 0;
	speed = 0.2;
	startTime = 3000;//через какое время выедет трактор
	moveTime = 30000;//время, которое трактор должен ездить прежде чем вернется на базу
	state = right;
}

Tractor::~Tractor(){}

void Tractor::checkCollisionWithHome(Home &home, Player &player) {//столкновение с домом
	if (home.getRect().intersects(getRect()) && (player.acceleration.x<0))  {
		position.x = home.getSprite().getTextureRect().width - 2;
	}
};

void Tractor::control(float &time, Player &player) {
	player.position = position;
	acceleration = (Vector2f(0, 0));
	if (player.acceleration.x < 0) { //left
		acceleration = (Vector2f(-speed, 0));
		state = left;
	}
	if (player.acceleration.x > 0) {//right
		acceleration = (Vector2f(speed, 0));
		state = right;
	}
	if (player.acceleration.y < 0) {//up
		acceleration = (Vector2f(0, -speed));
		state = up;
	}
	if (player.acceleration.y > 0) {//down
		acceleration = (Vector2f(0, speed));
		state = down;
	}
}

FloatRect Tractor::getRect() {//получить область прямоугольника спрайта
	if ((state == right) || (state == left)){
		return FloatRect(position.x, position.y, spriteSizeHorizontal.x, spriteSizeHorizontal.y);
	}
	if ((state == up) || (state == down)){
		return FloatRect(position.x, position.y, spriteSizeVertical.x, spriteSizeVertical.y);
	}
}

void Tractor::interactionWithPlayer(float &time, Player &player) {
	if ((player.getRect().intersects(getRect())&&(isMove))) {
		player.isDrive = true;
		control(time, player);
	}
}

void Tractor::startMove() {
	acceleration.x = speed;
	acceleration.y = 0;
	isMove = true;
}

void Tractor::setSpriteRect(Player &player) {
	switch (state)//меняем направление
	{
		case right:sprite.setTextureRect(IntRect(spriteOffsetRight.x, spriteOffsetRight.y, spriteSizeHorizontal.x, spriteSizeHorizontal.y)); break;
		case left:sprite.setTextureRect(IntRect(spriteOffsetLeft.x, spriteOffsetLeft.y, spriteSizeHorizontal.x, spriteSizeHorizontal.y)); break;
		case down:sprite.setTextureRect(IntRect(spriteOffsetDown.x, spriteOffsetDown.y, spriteSizeVertical.x, spriteSizeVertical.y)); break;
		case up:sprite.setTextureRect(IntRect(spriteOffsetUp.x, spriteOffsetUp.y, spriteSizeVertical.x, spriteSizeVertical.y));	break;
	}
}

void Tractor::rotateInHome() {
	state = right;
}

void Tractor::update(float &time,Player &player, Home &home) {
	startTimer += time;
	setSpriteRect(player);
	if (startTimer > startTime) {
		
		interactionWithPlayer(time, player);
		position.x += acceleration.x*time;
		position.y += acceleration.y*time;
		startMove();
		checkCollisionWithHome(home, player);
		moveTimer += time;
		if (moveTimer > moveTime) {
			rotateInHome();
			isMove = false;
			position = startPosition;
			moveTimer = 0;
			startTimer = 0;
			acceleration.x = 0;
			acceleration.y = 0;
			player.isDrive = false;
		}
	}
	sprite.setPosition(position.x + spriteSizeHorizontal.x / 2, position.y + spriteSizeHorizontal.y / 2);
};