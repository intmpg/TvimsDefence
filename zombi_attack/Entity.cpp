#include "Entity.h"


Entity::Entity(Image &image, float X, float Y, int W, int H, String Name){
	x = X;
	y = Y;
	w = W;
	h = H;
	name = Name;
	currentFrame = 0;
	speed = 0;
	health = 100;
	dx = 0;
	dy = 0;
	life = true;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

void Entity::checkDeath(){
	if (name != "ZombieEnemy") {
		if (health <= 0) { life = false; speed = 0; dx = 0; dy = 0; }//убиваем и останавливаем
	}

	if (name == "ZombieEnemy") {
		if (health <= 0) { speed = 0; dx = 0; dy = 0; }//сразу не убиваем из-за анимации смерти
	}
}

float Entity::getCurrentFrame(float time){//получить текущий кадр анимации
	if (name == "ZombieEnemy") {
		currentFrame += 0.005*time; if (currentFrame > 9) currentFrame = 0;
	} //проходимся по тайлам в тайлсете
	if (name == "Player1") { currentFrame += 0.009*time; if (currentFrame > 8) currentFrame = 0; }//аналогично
	return currentFrame;//возвращаем текущий кадр
}

void Entity::setCurrentFrame(int cF){
	currentFrame = cF;
}

FloatRect Entity::getRect(){//получить область прямоугольника спрайта
	return FloatRect(x, y, w, h);
}

void Entity::checkCollisionWithHome(Home &home) {//столкновение с домом

	if ((home.getRect().intersects(getRect())) && (dx<0)) { // если столкнулись то выталкиваем объекты назад
		speed = 0;
		dx = 0;
		x = home.getSprite().getTextureRect().width - 1;
	}
}