#include "level.h"

Level::Level() {
	zombieQuantity = 3;//плотность создания зомби
	densityZombieWidth = 1200;//плотность появления зомби по ширине
	densityZombieHeight = 490;//по высоте
	wave = 1;// номер волны
	playerDamage = 1;
	zombieDamage = 5;
	tempGame = 800;
	score = 0; //количество убитых зомби
	attackDistance = 70;//дальность стрельбы игрока
	//superBulletWave = 11;//после какой волны пули станут сильнее
	superBulletWave = 1;//после какой волны пули станут сильнее
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
	Font font;//шрифт sfml
	font.loadFromFile("CyrilicOld.ttf");//загрузили файл шрифта
	Text text("", font, 20);//объявили текст сфмл и дали ему изначально пустую строку, затем дали шрифт и размер
	text.setColor(Color::Red);//цвет текста
	text.setStyle(Text::Bold);//жирный текст

	std::ostringstream statsString;
	statsString << "Волна: " << wave << "\n" << "Убито зомби: " << score;//то выводим счет игрока на экран
	text.setString(statsString.str());//закидываем тексту переменную счета
	text.setPosition(window.getSize().x - 180, window.getSize().y - 50);//позиция этого текста

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
		Font font;//шрифт sfml
		font.loadFromFile("CyrilicOld.ttf");//загрузили файл шрифта
		Text text("", font, 26);//объявили текст сфмл и дали ему изначально пустую строку, затем дали шрифт и размер
		text.setColor(Color::Yellow);//цвет текста
		text.setStyle(Text::Bold);//жирный текст
		text.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 300);
		showBonusTimer += time;
		std::ostringstream statsString;
		statsString << "Дальность стрельбы увеличена!";
		if (wave == 11) {
			statsString << "\n Ваши пули могут убивать больше врагов!";//
		}

		text.setString(statsString.str());//закидываем тексту переменную счета

		if (showBonusTimer < 3000) {
			text.move(-0.09*time, 0);
			window.draw(text);
		}
		else { showBonusTimer = 0; isShow = false; }
	}
}
void Level::startNextWave(RenderWindow &window, float &time) {//след волна

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