#include "level.h"

Level::Level() {
	zombieQuantity = 2;//��������� �������� �����
	densityZombieWidth = 1200;//��������� ��������� ����� �� ������
	densityZombieHeight = 490;//�� ������
	wave = 1;// ����� �����
	waveHelpPlayer = 22;//����� ����� ����� ����� �������� � ������ ������ �����
	playerDamage = 1;
	zombieDamage = 3;
	tempGame = 800;
	score = 0; //���������� ������ �����
	attackDistance = 70;//��������� �������� ������
	superHardMode = 1;//����� ����� ����� ���� ������ �������
	deathQuantityHealth = 0;
	zombieHealth = 1;
	bearZombieHealth = 5;
	zombieSpeed = -0.04;
	bearZombieSpeed = -0.03;
	showBonusTimer = 0;
	showBonusText = false;
	isHelpedPlayer = false;

	font.loadFromFile("CyrilicOld.ttf");//��������� ���� ������
	textStats.setFont(font);
	textStats.setString("");
	textStats.setCharacterSize(20);
	textStats.setColor(Color::Red);//���� ������
	textStats.setStyle(Text::Bold);//������ �����

	textBonus.setFont(font);
	textBonus.setString("");
	textBonus.setCharacterSize(26);
	textBonus.setColor(Color::Yellow);//���� ������
	textBonus.setStyle(Text::Bold);//������ �����

	BonusString << "��������� �������� ���������!";
	
}

bool Level::checkGameOver(RenderWindow  & window, Text &text, Player &player, Home &home) {
	if ((!player.life) || (!home.getLife())) {
		player.life = false;//���� ���� �������� ����� ����� � ������ , ����� �� �������� ������ � ��������, ������� ����
		gameOver(window, text);
		return true;
	}
	return false;
}

void Level::gameOver(RenderWindow  & window, Text &text) {
	std::ostringstream statsString;
	statsString << "�����: " << wave << "\n" << "����� �����: " << score;//�� ������� ���� ������ �� �����
	text.setString(gameOverString + statsString.str());//���������� ������ ���������� �����
	text.setPosition(window.getSize().x / 2 - 300, window.getSize().y / 2 - 200);//������� ����� ������
	window.draw(text);
}

void Level::drawStats(RenderWindow  & window, Player &player, Home &home) {
	
	std::ostringstream statsString;
	statsString << "�����: " << wave << "\n" << "����� �����: " << score;//�� ������� ���� ������ �� �����
	textStats.setString(statsString.str());//���������� ������ ���������� �����
	textStats.setPosition(window.getSize().x - 180, window.getSize().y - 50);//������� ����� ������

	checkGameOver(window, textStats, player, home);//print game over

	window.draw(textStats);
}

int Level::getZombieHealth() {
	return zombieHealth;
}

float Level::getZombieSpeed() {
	return zombieSpeed;
}

void Level::showBonusT(RenderWindow &window, float &time, bool &isShow) {
	if (isShow) {
		textBonus.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 300);
		showBonusTimer += time;
		//std::ostringstream statsString;
		
		if (wave == superHardMode) {
			BonusString << "\n ���� ���� ����� ������� ������ ������!";//
		}

		textBonus.setString(BonusString.str());//���������� ������ ���������� �����

		if (showBonusTimer < 3000) {
			textBonus.move(-0.09*time, 0);
			window.draw(textBonus);
		} else { 
			showBonusTimer = 0; isShow = false; 
		}
	}
}
void Level::startNextWave(RenderWindow &window, float &time) {//���� �����
	if (score > wave * 3) {
		wave++; zombieSpeed -= 0.001; zombieHealth += 0.05; bearZombieHealth += 1; attackDistance += 3;
		showBonusText = true;
	}
	showBonusT(window, time, showBonusText);
}

void Level::update(RenderWindow & window, Player &player, Home &home, float time) {
	drawStats(window, player, home);
	startNextWave(window, time);
}