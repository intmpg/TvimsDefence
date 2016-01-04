#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "home.h"
#include <sstream>
using namespace sf;

class Level {
public:
	int zombieQuantity;//плотность создания зомби при старте игры
	int densityZombieWidth;//плотность появление зомби по ширине при старте
	int densityZombieHeight;//плотность появление по высоте
	int wave;//номер волны
	int score;//кол-во очков
	int attackDistance;//дистанция атаки
	int zombieHealth;//здоровье зомби
	int bearZombieHealth;//медведь зомби
	int playerDamage;//урон по игроку
	int zombieDamage;//урон по зомби
	int tempGame;//темп игры
	int superHardMode;//после какой волны пули будут сильнее
	int deathQuantityHealth;//количество хп необходимое для смерти
	bool showBonusText;//показывать или нет текст нового бонуса
	float zombieSpeed;//скорость зомби
	float bearZombieSpeed;//скорость зомби
	float showBonusTimer;//время показа текста о бонусах
	
	String gameOverString = "Игра окончена. Нажмите ТАБ, чтобы начать заново. Ваш счет : \n";
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