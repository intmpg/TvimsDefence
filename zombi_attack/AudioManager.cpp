#include "AudioManager.h"

using namespace sf;

AudioManager::AudioManager() {
	bufferShoot.loadFromFile("sounds/shoot.wav");// גûסענוכ
	playerShoot.setBuffer(bufferShoot);
	bufferPlayerStep.loadFromFile("sounds/player_step.wav");//ראדט
	playerStep.setBuffer(bufferPlayerStep);

	bufferZombieDie.loadFromFile("sounds/zombie__FireDie.wav");// ןנמסעמי חמלבט סלונעü
	zombieDie.setBuffer(bufferZombieDie);

	bufferZombieBearDie.loadFromFile("sounds/zombiebearDie.wav");// bear חמלבט סלונעü
	zombieBearDie.setBuffer(bufferZombieBearDie);

	bufferGunUpgraded.loadFromFile("sounds/GunUpgraded.wav"); //get power gun
	gunUpgraded.setBuffer(bufferGunUpgraded);
	isGunUpgraded = false;
	isGameOver = false;

	bufferPlayerDeath.loadFromFile("sounds/die.wav"); //death player
	playerDeath.setBuffer(bufferPlayerDeath);
	gameOver.openFromFile("sounds/game_over.wav");//game over

	bufferGetPlayerDamage.loadFromFile("sounds/get_damage.wav"); //damage player
	getPlayerDamage.setBuffer(bufferGetPlayerDamage);

	bufferPickupBonus.loadFromFile("sounds/pickup_bonus.wav"); //bonus;
	pickupBonus.setBuffer(bufferPickupBonus);

	gameTheme.openFromFile("sounds/FightMusic.wav"); //main music;
}

void AudioManager::zombieDiePlay(std::list<Entity*> &entities){
	for (auto& it : entities) {
		if ((it->name == "ZombieEnemy") && (it->health <= 0) && (!zombieDie.getStatus())){ zombieDie.play(); }
		if ((it->name == "BearZombieEnemy") && (it->health <= 0) && (!zombieBearDie.getStatus())) { zombieBearDie.play(); }
	}
}
void AudioManager::update(Player &player) {
	if (!gameTheme.getStatus() && (player.life)) {
		gameTheme.play();
	}
	if ((!player.life) && (!playerDeath.getStatus()) && (!isGameOver)) {
		playerDeath.play();
		gameTheme.stop();
		gameOver.play();
		isGameOver = true;
	}
	if (player.isShooted) {
		playerShoot.play();
		player.isShooted = false;
	}
	if ((player.isStay() == false) && (!playerStep.getStatus()) && (!player.isDrive)) {
		playerStep.play(); 
	}
	
	if ((player.isSuperBullet) && (!isGunUpgraded)) {
		gunUpgraded.play();
		isGunUpgraded = true;
	}

	
	


}
