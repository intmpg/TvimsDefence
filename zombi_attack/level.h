#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "home.h"
#include <sstream>
using namespace sf;

class Level {
public:
	int zombieQuantity;//��������� �������� ����� ��� ������ ����
	int densityZombieWidth;//��������� ��������� ����� �� ������ ��� ������
	int densityZombieHeight;//��������� ��������� �� ������
	int wave;//����� �����
	int score;//���-�� �����
	int attackDistance;//��������� �����
	int zombieHealth;//�������� �����
	int bearZombieHealth;//������� �����
	int playerDamage;//���� �� ������
	int zombieDamage;//���� �� �����
	int tempGame;//���� ����
	int superHardMode;//����� ����� ����� ���� ����� �������
	int deathQuantityHealth;//���������� �� ����������� ��� ������
	bool showBonusText;//���������� ��� ��� ����� ������ ������
	float zombieSpeed;//�������� �����
	float bearZombieSpeed;//�������� �����
	float showBonusTimer;//����� ������ ������ � �������
	
	String gameOverString = "���� ��������. ������� ���, ����� ������ ������. ��� ���� : \n";
	Level();
	bool checkGameOver(RenderWindow  & window, Text &text, Player &player, Home &home);
	void gameOver(RenderWindow  & window, Text &text);
	void drawStats(RenderWindow  & window, Player &player, Home &home);
	int getZombieHealth();
	float getZombieSpeed();
	void showBonusT(RenderWindow &window, float &time, bool &isShow);
	void startNextWave(RenderWindow &window, float &time);
	void update(RenderWindow & window, Player &player, Home &home, float time);
};
#endif