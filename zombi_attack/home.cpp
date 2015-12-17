#include "home.h"

Home::Home(){
	image.loadFromFile("images/home.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	health = 15000;//здоровье базы
	life = true;
}
FloatRect Home::getRect() {
	return FloatRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getTextureRect().width, sprite.getTextureRect().height);
}

Sprite Home::getSprite() {
	return sprite;
}

void Home::setHealth(int H) {
	health = H;
}

int Home::getHealth() {
	return health;
}

void Home::setDamage() {
	health--;
}

void Home::checkDeath() {
	if (health <= 0){ life = false; }
}

bool Home::getLife() {
	return life;
}

void Home::update() {

	checkDeath();

}

