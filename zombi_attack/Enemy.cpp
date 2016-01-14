#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name, int Health, float Speed)
:Entity(image, startPosition, spriteObjectSize, Name)
{
		sprite.setTextureRect(IntRect(0, spriteSize.y, spriteSize.x, spriteSize.y));//���� � ��������
		acceleration.x = Speed;//���� ��������.���� ������ ������ ���������
		health = Health;//��������
		deathAnimationTimer = 0;//������ ������ �������� ������
		showDecomposition = false;//�� ���������� ���������� 
}

void Enemy::startAnimation(float &time) {//��������
	sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), 0, spriteSize.x, spriteSize.y));//�������� ������

	if (health <= 0) {  // ��� �������� �������� ������
		deathAnimationTimer += time;
		if (name == "ZombieEnemy") {//��� ��������� � ����� ������ ������ �������� ������ ����� �����
			if (isTractorKiller) {
				sprite.setTextureRect(IntRect(88 * int(getCurrentFrame(time)), spriteSize.y, 88, 57));//�������� ������ ������� ����� �� ��������
			} else {
				sprite.setTextureRect(IntRect(92 * int(getCurrentFrame(time)), 135, 92, 67));//�������� ������ ������� ����� �� ����
			}
		}
		if (name == "BearZombieEnemy") {//��� ��������� � ����� ������ ������ �������� ������ ����� �����
			sprite.setTextureRect(IntRect(88 * int(getCurrentFrame(time)), spriteSize.y, 88, 66));//�������� ������
		}
		else {
			sprite.setTextureRect(IntRect(61 * int(getCurrentFrame(time)), 135, 61, 93)); // �� ����
		}
		if (deathAnimationTimer > 800) {
			deathAnimationTimer = 0;
			showDecomposition = true;//������ ���������� ����������
		}//���������� �������� � ������� �����

		if (showDecomposition) {
			if (name == "ZombieEnemy") {//��� ��������� � ����� ������ ������ ���������� ����� �����
				if (isTractorKiller) {
					sprite.setTextureRect(IntRect(88 * int(getCurrentFrameDeath(time)), spriteSize.y, 88, 57));//�������� ���������� �� ��������
				} else {
					sprite.setTextureRect(IntRect(93 * int(getCurrentFrameDeath(time)), 135, 93, 61));//�������� ���������� �� ����
				}
			}
			if (name == "BearZombieEnemy") {//��� ��������� � ����� ������ ������ ���������� ����� �����
				if (isTractorKiller) {
					sprite.setTextureRect(IntRect(88 * int(getCurrentFrameDeath(time)), spriteSize.y, 88, 66));//�������� ���������� �� ��������
				} else {
					sprite.setTextureRect(IntRect(86 * int(getCurrentFrameDeath(time)), 140, 86, 78));//�������� ���������� �� ����
				}
			}
		}
	}
}

void Enemy::attackHome(Home & home){//����� ����
	if (getRect().intersects(home.getRect())) { 
		home.setDamage(); 
	} // ���� ����� ����������� � ����� , �� �������
}

void Enemy::update(float time, Home & home){//��������� ����� 
	if (health > 0) {
		position.x += acceleration.x*time;//���� ��������
		sprite.setPosition(position.x + spriteSize.x / 2, position.y + spriteSize.y / 2); //������ ������� ������� � ����� ��� ������
		attackHome(home);//����� ����
		checkCollisionWithHome(home);//�������� ������������ � �����
	} else {
		checkDeath(); // �������� �� ������
	}
	startAnimation(time);//�������� ��������
}