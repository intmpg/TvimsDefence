#ifndef GAME_HPP
#define GAME_HPP
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "LifeBar.h"
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>
#include "map.h"
#include "level.h"
#include "Player.h"
#include "Tractor.h"
#include "AudioManager.h"

using namespace sf;

void menu(RenderWindow & window);

void gameUpdate(RenderWindow &window, LifeBar &lifeBar, View &view, Texture &textureCursor, Sprite &spriteCursor, Clock & clock, Image &BulletImage, Image &playerImage, Image &enemyImage, Level &level, Player &player, Map &map, Home &home, std::list<Entity*> & entities);

bool startGame(RenderWindow &window, LifeBar &lifeBar, View &view, Texture &textureCursor, Sprite &spriteCursor, Clock & clock, Image &BulletImage, Image &playerImage, Image &enemyImage, Level &level, Player &player, Map &map, Home &home, std::list<Entity*> & entities);

bool createGameObject();

void gameRunning();

void eventZombiDestroy(std::list<Entity*> &entities, Level &level);


#endif
