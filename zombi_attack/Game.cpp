#include "gameMath.h"
#include "Game.h"
#include <iostream>

void menu(RenderWindow & window){
	Music music;
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/menubg.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(60, 100);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);
	//audioManager.menuMusic.play();
	music.openFromFile("sounds/MenuMusic.wav");
	music.play();

	//////////////////////////////����///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(60, 100, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(100, 170, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}


struct objectImagesStruct //�������� ����� ��������� objectImagesStruct.
{
	Image BulletImage;//����������� ��� ����
	Image playerImage;//������
	Image enemyImage;//�����
	Image enemyBossImage;//������� ����
	Image bonusImage;//������
	Texture textureCursor; 
	Texture textureBonus;
	Sprite spriteCursor;
	Sprite bonusHealthSprite;
	Sprite bonusTimeSprite;
	Sprite bonusBombSprite;
	int hideX;
	int hideY;
	
}; //����� �������� ��������� ������ ����� � �������



struct systemObjectStruct //�������� ����� ��������� systemObjectStruct
{
	RenderWindow window;//����
	View view;
	Clock clock;
	float time;
	float bonusTimer;
	int bonusClockTimer = 7000;//����� ������� �������� ����� 
	int timeForHide = 17000;//����� ����� ������� ����� ����� �������� ����� ���������
	Event event;
	Vector2f pos;
	AudioManager audioManager;
}; 

struct gameObjectStruct //�������� ����� ��������� gameObjectStruct
{
	LifeBar lifeBar;//��������� ������ ������� ��������
	std::list<Entity*>  entities;//������ ������, ���� ���� ������ �������
	Level level;
	Map map;
	Home home;
	Tractor tractor;
}; 



void eventLoop(systemObjectStruct &systemObjects, Player &player, std::list<Entity*> & entities, Sprite &spriteCursor, Image &BulletImage){
	
	while (systemObjects.window.pollEvent(systemObjects.event))
	{
		if (systemObjects.event.type == sf::Event::Closed)
			systemObjects.window.close();
		if (player.isStay()) {//���� ����� �����, �� ����� ��� ������������ � ��������
			player.rotateSprite(spriteCursor.getPosition());//������������ ������ � ������� ��������

			if ((systemObjects.event.type == Event::MouseButtonPressed) && (systemObjects.event.key.code == Mouse::Left) && (player.isShoot == true))//���� ������ ������� ���� //� ������ �����, �� �������� 
			{
				player.speed = 0;
				player.isShooted = true;
				player.acceleration.x = 0;
				player.acceleration.y = 0;
				player.isShoot = false;
				entities.push_back(new Bullet(BulletImage, "Bullet", player.position, Vector2i(12, 12), spriteCursor.getPosition().x, spriteCursor.getPosition().y)); //���� ����������, �� ���������� ����	
			}
		}
	}
}

void createBonus(int &wave, systemObjectStruct &systemObjects, objectImagesStruct &objectImages) {
	int rangeXLeft = 150;
	int rangeXRight = 900;
	int rangeYTop = 10;
	int rangeYBottom = 640;
	systemObjects.bonusTimer += systemObjects.time;
	if (systemObjects.bonusTimer>systemObjects.bonusClockTimer) {
		if (0 + rand() % 2 == 1) {
			objectImages.bonusTimeSprite.setPosition(float(rangeXLeft + rand() % rangeXRight), float(rangeYTop + rand() % rangeYBottom));
		} else {
			objectImages.bonusHealthSprite.setPosition(float(rangeXLeft + rand() % rangeXRight), float(rangeYTop + rand() % rangeYBottom));
			if (0 + rand() % 10 == 7) {//���� ������ �����
				objectImages.bonusBombSprite.setPosition(float(rangeXLeft + rand() % rangeXRight), float(rangeYTop + rand() % rangeYBottom));
			}
		}
		systemObjects.bonusTimer = 0;
	}
	if (systemObjects.bonusTimer > systemObjects.timeForHide){//������ ������ ����� timeForhide 
		objectImages.bonusHealthSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
		objectImages.bonusTimeSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
		objectImages.bonusBombSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
	}
}

void interactionWithBonus(Player &player, objectImagesStruct &objectImages, gameObjectStruct &gameObjects, AudioManager &audioManager) {
	int playerHealthBonus = 30;
	float slowEnemy = -0.005f;

	if ((FloatRect(player.sprite.getGlobalBounds()).intersects(FloatRect(objectImages.bonusHealthSprite.getGlobalBounds())))&&(player.health<player.playerMaxHealth)) {
		player.health += playerHealthBonus;
		audioManager.pickupBonus.play(); 
		objectImages.bonusHealthSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
	}
	if ( (FloatRect(player.sprite.getGlobalBounds()).intersects(FloatRect(objectImages.bonusBombSprite.getGlobalBounds()))) ) {
		objectImages.bonusBombSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
		audioManager.pickupBonus.play();
		gameObjects.level.waveHelpPlayer = gameObjects.level.wave;
		gameObjects.level.isHelpedPlayer = false;
	}
	if (FloatRect(player.sprite.getGlobalBounds()).intersects(FloatRect(objectImages.bonusTimeSprite.getGlobalBounds()))) {
		for (auto& it : gameObjects.entities) {
			if ((it->name != "ZombieEnemy") && (it->name != "BearZombieEnemy"))
				continue;
			(it)->acceleration.x = slowEnemy;
		}
		audioManager.pickupBonus.play();
		objectImages.bonusTimeSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
	}
}
void entitiesInteraction(gameObjectStruct &gameObjects, Player &player, objectImagesStruct &objectImages, systemObjectStruct &systemObject){
	for (auto& it : gameObjects.entities) {
		it->update(systemObject.time, gameObjects.home);
		
		if ( (it->name != "ZombieEnemy")&&(it->name != "BearZombieEnemy") )
			continue;
		systemObject.audioManager.zombieDiePlay(gameObjects.entities);//���� ������
		
		if (it->getRect().intersects(player.getRect()) && (it->health>gameObjects.level.deathQuantityHealth) && (!player.isDrive)) {
			player.health -= gameObjects.level.playerDamage;
			if (!systemObject.audioManager.getPlayerDamage.getStatus() && (player.life)) {
				systemObject.audioManager.getPlayerDamage.play(); 
			}
		}// ����� �������� ����� ��� �������� � �����

	
		if ( (!it->startShowDecomposition) && (it->health<=0) ) {
			gameObjects.level.score++;//���� ���� ����, �� ���������� ���� ������
			it->startShowDecomposition = true;
			if (0 + rand() % 3 != 2) {
				gameObjects.entities.push_back(new Enemy(objectImages.enemyImage, Vector2f(float(systemObject.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth)), float(50 + rand() % (gameObjects.level.densityZombieHeight))), Vector2i(34, 77), "ZombieEnemy", gameObjects.level.getZombieHealth(), gameObjects.level.getZombieSpeed()));
			}
			else {
				gameObjects.entities.push_back(new Enemy(objectImages.enemyBossImage, Vector2f(float(systemObject.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth)), float(50 + rand() % (gameObjects.level.densityZombieHeight))), Vector2i(40, 75), "BearZombieEnemy", gameObjects.level.bearZombieHealth, gameObjects.level.bearZombieSpeed));
			}
		}

		if (it->getRect().intersects(gameObjects.tractor.getRect()) && (it->health>gameObjects.level.deathQuantityHealth)) {//����� ����� ���������
			it->health -= gameObjects.level.zombieDamage;
			it->isTractorKiller = true;
		}// ����� �������� ����� ��� �������� � ���������
		
		if ((gameObjects.level.wave == gameObjects.level.waveHelpPlayer) && (!gameObjects.level.isHelpedPlayer)) {
			for (auto& it : gameObjects.entities) {
				it->health = 0;
			}
			gameObjects.level.isHelpedPlayer = true;
		}

		for (auto& it2 : gameObjects.entities)
		{
			if (!((it2->name == "Bullet") && (it->sprite.getGlobalBounds().intersects(it2->sprite.getGlobalBounds()) && (it->health > gameObjects.level.deathQuantityHealth))))
				continue;
			if ((gameObjects.level.wave > gameObjects.level.superHardMode) && (it->name == "BearZombieEnemy")) {//����� ����� ����� ���� ������ ������� ���������� ������� ����� �����
				it2->life = false;
			} else {
					player.isSuperBullet = true;
			}
			it->health -= gameObjects.level.zombieDamage;
		}
	}
	eventZombiDestroy(gameObjects.entities, gameObjects.level);
}

void gameUpdate(systemObjectStruct &systemObjects, objectImagesStruct &objectImages, gameObjectStruct &gameObjects, Player &player){
	systemObjects.time = float(systemObjects.clock.getElapsedTime().asMicroseconds());
	systemObjects.clock.restart();
	systemObjects.time = systemObjects.time / gameObjects.level.tempGame;
	
	systemObjects.pos = systemObjects.window.mapPixelToCoords(Mouse::getPosition(systemObjects.window));//�������� ����� �������, ��������� �� � ������� (������ �� ����� ����)

	eventLoop(systemObjects, player, gameObjects.entities, objectImages.spriteCursor, objectImages.BulletImage);//while (window.pollEvent(event))

	player.update(systemObjects.time, gameObjects.home);
	radiusAim(gameObjects.level.attackDistance, systemObjects.pos, player.position, objectImages.spriteCursor);//������ �� ������ ���������
	gameObjects.lifeBar.update(gameObjects.home.getHealth(), player.health, player.position);
	gameObjects.home.update();
	createBonus(gameObjects.level.wave, systemObjects, objectImages);//bonus create

	interactionWithBonus(player, objectImages, gameObjects, systemObjects.audioManager);//�������������� � ��������
	eventZombiDestroy(gameObjects.entities, gameObjects.level);

	entitiesInteraction(gameObjects, player, objectImages, systemObjects);
	
	gameObjects.tractor.update(systemObjects.time, player,gameObjects.home);//tractor update
	systemObjects.audioManager.update(player);
	
	systemObjects.window.setView(systemObjects.view);
	systemObjects.window.clear();
	
	systemObjects.window.draw(gameObjects.map.getSprite());//������ �����
	systemObjects.window.draw(gameObjects.home.getSprite());//������ ���
	for (auto& it : gameObjects.entities) {
		systemObjects.window.draw(it->sprite);
	} //������ entities ������� (������ ��� ���� � �����)
	gameObjects.level.update(systemObjects.window, player, gameObjects.home, systemObjects.time);//���������� ������ � ��������� ����������

	if (!player.isDrive) {
		systemObjects.window.draw(player.sprite);
		systemObjects.window.draw(objectImages.spriteCursor);
	}
	systemObjects.window.draw(gameObjects.tractor.sprite); //������ �������
	systemObjects.window.draw(objectImages.bonusHealthSprite);
	systemObjects.window.draw(objectImages.bonusTimeSprite);
	systemObjects.window.draw(objectImages.bonusBombSprite);
	gameObjects.lifeBar.draw(systemObjects.window);

	systemObjects.window.display();
}

bool startGame(systemObjectStruct &systemObjects, objectImagesStruct &objectImages, gameObjectStruct &gameObjects, Player &player) {//������� �������� ����

	menu(systemObjects.window);//����� ����

	systemObjects.window.setMouseCursorVisible(false); // �������� ������a

	while (systemObjects.window.isOpen())
	{
		gameUpdate(systemObjects, objectImages, gameObjects, player);
		if (Keyboard::isKeyPressed(Keyboard::Tab)) {
			return true;
		}//���� ���, �� ������������� ����
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return false;
		}//���� ������, �� ������� �� ����
	}
	return false;
}

bool createGameObject(){

	systemObjectStruct systemObjects;
	systemObjects.window.create(sf::VideoMode(1366, 768), "Ataka zombi!", sf::Style::Fullscreen);
	systemObjects.view = systemObjects.window.getView(); //������������� ������ ��� �������
	objectImagesStruct objectImages;
	objectImages.hideY = 2200;
	objectImages.BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	objectImages.BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����
	objectImages.playerImage.loadFromFile("images/hero.png");
	objectImages.playerImage.createMaskFromColor(Color(255, 255, 255));
	objectImages.enemyImage.loadFromFile("images/Monster-zombie.png");
	objectImages.enemyBossImage.loadFromFile("images/zombiebear.png");
	objectImages.textureCursor.loadFromFile("images/cursor.png");
	objectImages.textureBonus.loadFromFile("images/bonus.png");
	objectImages.bonusTimeSprite.setTextureRect(IntRect(0, 0, 32,32));
	objectImages.bonusTimeSprite.setTexture(objectImages.textureBonus);
	objectImages.bonusTimeSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
	objectImages.bonusHealthSprite.setTexture(objectImages.textureBonus);
	objectImages.bonusHealthSprite.setTextureRect(IntRect(32, 0, 32, 32));
	objectImages.bonusHealthSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
	objectImages.bonusBombSprite.setTexture(objectImages.textureBonus);
	objectImages.bonusBombSprite.setTextureRect(IntRect(64, 0, 32, 32));
	objectImages.bonusBombSprite.setPosition(float(objectImages.hideX), float(objectImages.hideY));
	
	objectImages.spriteCursor.setTexture(objectImages.textureCursor);
	
	gameObjectStruct gameObjects;
	Player player(objectImages.playerImage, Vector2f(150, 150), Vector2i(55, 65), "Player1");
	systemObjects.bonusTimer = 0;
	/////////////////////////////�������� ����� � ����������� �� ���������////////////////////
	for (int i = 0; i < gameObjects.level.zombieQuantity; i++) {//���������� �� ��������� ����� �������(� ������ �� ������)
		gameObjects.entities.push_back(new Enemy(objectImages.enemyImage, Vector2f(float(systemObjects.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth)), float(50 + rand() % (gameObjects.level.densityZombieHeight)*i)), Vector2i(34, 77), "ZombieEnemy", gameObjects.level.getZombieHealth(), gameObjects.level.getZombieSpeed()));//������� ������ �� ������
		for (int j = 0; j < gameObjects.level.zombieQuantity; j++) {
			gameObjects.entities.push_back(new Enemy(objectImages.enemyImage, Vector2f(systemObjects.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth)*j, 50 + rand() % (gameObjects.level.densityZombieHeight)), Vector2i(34, 77), "ZombieEnemy", 1 + rand() % gameObjects.level.getZombieHealth(), float(gameObjects.level.getZombieSpeed())));//�� ������
		}
	}
	///////////////////////////////////////////////////////////////

	return startGame(systemObjects, objectImages, gameObjects, player);
	
}

void gameRunning(){//�-��� ������������� ���� , ���� ��� ����������
	if (createGameObject()) { gameRunning(); }////���� createGameObject() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
}

void eventZombiDestroy(std::list<Entity*> &entities, Level &level){

	auto is_crash = [](Entity *entities) {
		return !(entities->life);
	};

	entities.erase(std::remove_if(entities.begin(), entities.end(), is_crash), entities.end());//������� ��� �������� �� ��������� life=false
}