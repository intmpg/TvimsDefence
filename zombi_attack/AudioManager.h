#ifndef AudioManager_HPP
#define AudioManager_HPP
#include <SFML\Audio.hpp>
#include "Player.h"
#include <list>
#include <iostream>

class AudioManager {
public:
	SoundBuffer bufferShoot;
	Sound playerShoot;
	SoundBuffer bufferPlayerStep;
	Sound playerStep;
	SoundBuffer bufferZombieDie;
	Sound zombieDie;
	SoundBuffer bufferZombieBearDie;
	Sound zombieBearDie;
	SoundBuffer bufferGunUpgraded;
	Sound gunUpgraded;
	bool isGunUpgraded;
	bool isGameOver;
	SoundBuffer bufferPlayerDeath;
	Sound playerDeath;
	SoundBuffer bufferGetPlayerDamage;
	Sound getPlayerDamage;
	SoundBuffer bufferPickupBonus;
	Sound pickupBonus;
	Music gameOver;
	Music gameTheme;
	Music menuMusic;

	AudioManager();

	void zombieDiePlay(std::list<Entity*> &entities);
	void update(Player &player);

};
#endif