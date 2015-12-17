#include "Enemy.h"

Enemy::Enemy(Image &image, float X, float Y, int W, int H, String Name, int Health, float Speed)
	:Entity(image, X, Y, W, H, Name)
{
	if (name == "ZombieEnemy") {
		sprite.setTextureRect(IntRect(0, h, w, h));//���� � ��������
		dx = Speed;//���� ��������.���� ������ ������ ���������
		health = Health;//��������
		deathAnimationTimer = 0;//������ ������ �������� ������
	}
}

void Enemy::startAnimation(float &time){//��������
	sprite.setTextureRect(IntRect(w * int(getCurrentFrame(time)), 0, w, h));//�������� ������
	if (health <= 0) {  // ��� �������� �������� ������
		deathAnimationTimer += time;
		sprite.setTextureRect(IntRect(37 * int(getCurrentFrame(time)), h + 1, 37, h + 1));//�������� ������
		if (deathAnimationTimer > 600) { life = false; deathAnimationTimer = 0; }//���������� �������� � ������� �����
	}
}

void Enemy::attackHome(Home & home){//����� ����
	if (getRect().intersects(home.getRect())) { home.setDamage(); } // ���� ����� ����������� � ����� , �� �������
}

void Enemy::update(float time, Home & home){//��������� ����� 
	if (name == "ZombieEnemy") {//��� ��������� � ����� ������ ������ ����� �����
		x += dx*time;//���� ��������
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		startAnimation(time);//�������� ��������
		checkDeath(); // �������� �� ������
		attackHome(home);//����� ����
		checkCollisionWithHome(home);//�������� ������������ � �����
	}
}