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
		if (health <= 0) { life = false; speed = 0; dx = 0; dy = 0; }//������� � �������������
	}

	if (name == "ZombieEnemy") {
		if (health <= 0) { speed = 0; dx = 0; dy = 0; }//����� �� ������� ��-�� �������� ������
	}
}

float Entity::getCurrentFrame(float time){//�������� ������� ���� ��������
	if (name == "ZombieEnemy") {
		currentFrame += 0.005*time; if (currentFrame > 9) currentFrame = 0;
	} //���������� �� ������ � ��������
	if (name == "Player1") { currentFrame += 0.009*time; if (currentFrame > 8) currentFrame = 0; }//����������
	return currentFrame;//���������� ������� ����
}

void Entity::setCurrentFrame(int cF){
	currentFrame = cF;
}

FloatRect Entity::getRect(){//�������� ������� �������������� �������
	return FloatRect(x, y, w, h);
}

void Entity::checkCollisionWithHome(Home &home) {//������������ � �����

	if ((home.getRect().intersects(getRect())) && (dx<0)) { // ���� ����������� �� ����������� ������� �����
		speed = 0;
		dx = 0;
		x = home.getSprite().getTextureRect().width - 1;
	}
}