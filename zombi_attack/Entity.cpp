#include "Entity.h"


Entity::Entity(Image &image, Vector2f startPosition, Vector2i spriteObjectSize, String Name){
	position = startPosition;
	spriteSize = spriteObjectSize;
	name = Name;
	currentFrame = 0;
	currentFrameDeath = 3;
	speed = 0;
	health = 100;
	acceleration.x = 0;
	acceleration.y = 0;
	life = true;
	startShowDecomposition = false;//не показывать разложение 
	isTractorKiller = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
}

void Entity::checkDeath() {
	
	if ( (name != "ZombieEnemy") && (name != "BearZombieEnemy") && (health <= 0) ) {
			life = false; 
			speed = 0; 
			acceleration.x = 0; 
			acceleration.y = 0; 
		//убиваем и останавливаем
	}

	if ((name == "ZombieEnemy") || (name == "BearZombieEnemy")) {
		if (health <= 0) { 
			speed = 0; acceleration.x = 0; acceleration.y = 0; 
		}//сразу не убиваем из-за анимации смерти
	}
}

float Entity::getCurrentFrameDeath(float &time) {
	currentFrameDeath += 0.00009*time;//скорость разложения
	if (currentFrameDeath > 8) {
		life = false;
	}
	return currentFrameDeath;//возвращаем текущий кадр
}

float Entity::getCurrentFrame(float &time){//получить текущий кадр анимации
	if ( (name == "ZombieEnemy") || (name == "BearZombieEnemy") ) {
		if (health > 0) { 
			currentFrame += 0.005*time;
			if (currentFrame > 8) {
				currentFrame = 0;
			}
		} else { 
			currentFrame += 0.001*time;
			if (currentFrame > 3) {
				currentFrame = 0;
			}
		}
	} //проходимся по тайлам в тайлсете
	if (name == "Player1") {
		currentFrame += 0.009*time; 
		if (currentFrame > 8) {
			currentFrame = 0;
		}
	}//аналогично
	return currentFrame;//возвращаем текущий кадр
}

void Entity::setCurrentFrame(int currentFRAME){
	currentFrame = currentFRAME;
}

FloatRect Entity::getRect(){//получить область прямоугольника спрайта
	return FloatRect(position.x, position.y, spriteSize.x, spriteSize.y);
}

void Entity::checkCollisionWithHome(Home &home) {//столкновение с домом
	if ((home.getRect().intersects(getRect())) && (acceleration.x<0)) { // если столкнулись то выталкиваем объекты назад
		speed = 0;
		acceleration.x = 0;
		position.x = home.getSprite().getTextureRect().width - 1;
	}
}