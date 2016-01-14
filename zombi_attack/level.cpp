#include "level.h"

Level::Level() {
	zombieQuantity = 2;//��������� �������� �����
	densityZombieWidth = 1200;//��������� ��������� ����� �� ������
	densityZombieHeight = 490;//�� ������
	wave = 1;// ����� �����
	waveHelpPlayer = 20;//����� ����� ����� ����� �������� � ������ ������ �����
	playerDamage = 1;
	zombieDamage = 3;
	tempGame = 800;
	score = 0; //���������� ������ �����
	attackDistance = 70;//��������� �������� ������
	superHardMode = 30;//����� ����� ����� ���� ������ �������
	deathQuantityHealth = 0;
	zombieHealth = 1;
	bearZombieHealth = 5;
	zombieSpeed = -0.05f;
	bearZombieSpeed = -0.02f;
	showBonusTimer = 0;
	showBonusText = false;
	isHelpedPlayer = false;

	font.loadFromFile("CyrilicOld.ttf");//��������� ���� ������
	textStats.setFont(font);
	textStats.setString("");
	textStats.setCharacterSize(20);
	textStats.setColor(Color::Yellow);//���� ������
	textStats.setStyle(Text::Bold);//������ �����


	textBonus.setFont(font);
	textBonus.setString("");
	textBonus.setCharacterSize(26);
	textBonus.setColor(Color::Black);//���� ������
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
	text.setPosition(float(window.getSize().x / 2 - 300), float(window.getSize().y / 2 - 200));//������� ����� ������
	window.draw(text);
}

void Level::drawStats(RenderWindow  & window, Player &player, Home &home) {
	
	std::ostringstream statsString;
	statsString << "�����: " << wave << "\n" << "����� �����: " << score;//�� ������� ���� ������ �� �����
	textStats.setString(statsString.str());//���������� ������ ���������� �����
	textStats.setPosition(float(window.getSize().x - 180), float(window.getSize().y - 50));//������� ����� ������

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
		textBonus.setPosition(float(window.getSize().x / 2 - 150), float(window.getSize().y / 2 - 300));
		showBonusTimer += time;
		//std::ostringstream statsString;
		
		textBonus.setString(BonusString.str());//���������� ������ ���������� �����

		if (showBonusTimer < 3000) {
			textBonus.move(-0.09f * time, 0);
			window.draw(textBonus);
		} else { 
			showBonusTimer = 0; isShow = false; 
		}
	}
}
void Level::startNextWave(RenderWindow &window, float &time) {//���� �����
	if (score > wave * 3) {
		wave++; zombieSpeed -= 0.0005f; zombieHealth += 0.5f; bearZombieHealth += 0.8f; attackDistance += 0.9f; zombieQuantity += 0.01f;
		showBonusText = true;
	}
	showBonusT(window, time, showBonusText);
}

void Level::update(RenderWindow & window, Player &player, Home &home, float time) {
	drawStats(window, player, home);
	startNextWave(window, time);
}