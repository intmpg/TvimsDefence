#include "level.h"

Level::Level() {
	zombieQuantity = 2;//плотность создания зомби
	densityZombieWidth = 1200;//плотность появления зомби по ширине
	densityZombieHeight = 490;//по высоте
	wave = 1;// номер волны
	waveHelpPlayer = 22;//после какой волны зомби подохнут и игроку станет легче
	playerDamage = 1;
	zombieDamage = 3;
	tempGame = 800;
	score = 0; //количество убитых зомби
	attackDistance = 70;//дальность стрельбы игрока
	superHardMode = 1;//после какой волны пули станут сильнее
	deathQuantityHealth = 0;
	zombieHealth = 1;
	bearZombieHealth = 5;
	zombieSpeed = -0.04;
	bearZombieSpeed = -0.03;
	showBonusTimer = 0;
	showBonusText = false;
	isHelpedPlayer = false;

	font.loadFromFile("CyrilicOld.ttf");//загрузили файл шрифта
	textStats.setFont(font);
	textStats.setString("");
	textStats.setCharacterSize(20);
	textStats.setColor(Color::Red);//цвет текста
	textStats.setStyle(Text::Bold);//жирный текст

	textBonus.setFont(font);
	textBonus.setString("");
	textBonus.setCharacterSize(26);
	textBonus.setColor(Color::Yellow);//цвет текста
	textBonus.setStyle(Text::Bold);//жирный текст

	BonusString << "Дальность стрельбы увеличена!";
	
}

bool Level::checkGameOver(RenderWindow  & window, Text &text, Player &player, Home &home) {
	if ((!player.life) || (!home.getLife())) {
		player.life = false;//если база погибнет нужно убить и игрока , чтобы он перестал ходить и стрелять, набивая очки
		gameOver(window, text);
		return true;
	}
	return false;
}

void Level::gameOver(RenderWindow  & window, Text &text) {
	std::ostringstream statsString;
	statsString << "Волна: " << wave << "\n" << "Убито зомби: " << score;//то выводим счет игрока на экран
	text.setString(gameOverString + statsString.str());//закидываем тексту переменную счета
	text.setPosition(window.getSize().x / 2 - 300, window.getSize().y / 2 - 200);//позиция этого текста
	window.draw(text);
}

void Level::drawStats(RenderWindow  & window, Player &player, Home &home) {
	
	std::ostringstream statsString;
	statsString << "Волна: " << wave << "\n" << "Убито зомби: " << score;//то выводим счет игрока на экран
	textStats.setString(statsString.str());//закидываем тексту переменную счета
	textStats.setPosition(window.getSize().x - 180, window.getSize().y - 50);//позиция этого текста

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
			BonusString << "\n Ваши пули могут убивать больше врагов!";//
		}

		textBonus.setString(BonusString.str());//закидываем тексту переменную счета

		if (showBonusTimer < 3000) {
			textBonus.move(-0.09*time, 0);
			window.draw(textBonus);
		} else { 
			showBonusTimer = 0; isShow = false; 
		}
	}
}
void Level::startNextWave(RenderWindow &window, float &time) {//след волна
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