#include "level.h"

Level::Level() {
	zombieQuantity = 3;//��������� �������� �����
	densityZombieWidth = 1200;//��������� ��������� ����� �� ������
	densityZombieHeight = 490;//�� ������
	wave = 1;// ����� �����
	playerDamage = 1;
	zombieDamage = 5;
	tempGame = 800;
	score = 0; //���������� ������ �����
	attackDistance = 70;//��������� �������� ������
	//superBulletWave = 11;//����� ����� ����� ���� ������ �������
	superBulletWave = 1;//����� ����� ����� ���� ������ �������
	deathQuantityHealth = 0;
	zombieHealth = 4;
	bearZombieHealth = 5;
	zombieSpeed = -0.08;
	bearZombieSpeed = -0.05;
	showBonusTimer = 0;
	showBonusText = false;
}

bool Level::checkGameOver(RenderWindow  & window, Text &text, Player &player, Home &home){
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
	Font font;//����� sfml
	font.loadFromFile("CyrilicOld.ttf");//��������� ���� ������
	Text text("", font, 20);//�������� ����� ���� � ���� ��� ���������� ������ ������, ����� ���� ����� � ������
	text.setColor(Color::Red);//���� ������
	text.setStyle(Text::Bold);//������ �����

	std::ostringstream statsString;
	statsString << "�����: " << wave << "\n" << "����� �����: " << score;//�� ������� ���� ������ �� �����
	text.setString(statsString.str());//���������� ������ ���������� �����
	text.setPosition(window.getSize().x - 180, window.getSize().y - 50);//������� ����� ������

	checkGameOver(window, text, player, home);//print game over

	window.draw(text);
}

int Level::getZombieHealth(){
	return zombieHealth;
}

float Level::getZombieSpeed(){
	return zombieSpeed;
}

void Level::showBonusT(RenderWindow &window, float &time, bool &isShow){

	if (isShow) {
		Font font;//����� sfml
		font.loadFromFile("CyrilicOld.ttf");//��������� ���� ������
		Text text("", font, 26);//�������� ����� ���� � ���� ��� ���������� ������ ������, ����� ���� ����� � ������
		text.setColor(Color::Yellow);//���� ������
		text.setStyle(Text::Bold);//������ �����
		text.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 300);
		showBonusTimer += time;
		std::ostringstream statsString;
		statsString << "��������� �������� ���������!";
		if (wave == 11) {
			statsString << "\n ���� ���� ����� ������� ������ ������!";//
		}

		text.setString(statsString.str());//���������� ������ ���������� �����

		if (showBonusTimer < 3000) {
			text.move(-0.09*time, 0);
			window.draw(text);
		}
		else { showBonusTimer = 0; isShow = false; }
	}
}
void Level::startNextWave(RenderWindow &window, float &time) {//���� �����

	if (score > wave * 3) {
		wave++; zombieSpeed -= 0.004; zombieHealth += 3; bearZombieHealth += 2; attackDistance += 5;
		showBonusText = true;
	}
	showBonusT(window, time, showBonusText);


}

void Level::update(RenderWindow & window, Player &player, Home &home, float time){
	drawStats(window, player, home);
	startNextWave(window, time);
}