#include "gameMath.h"
#include "Game.h"
#include <iostream>

void menu(RenderWindow & window){
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
	menu2.setPosition(500, 30);
	menu3.setPosition(900, 30);
	menuBg.setPosition(0, 0);

	//////////////////////////////ћ≈Ќё///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(500, 30, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(900, 30, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
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


struct objectImagesStruct //ќбъ€вили новую структуру objectImagesStruct.
{
	Image BulletImage;//изображение дл€ пули
	Image playerImage;//игрока
	Image enemyImage;//врага
	Image enemyBossImage;//сильный враг
	Image bonusImage;//бонусы
	Texture textureCursor; 
	Texture textureBonus;
	Sprite spriteCursor;
	Sprite bonusHealthSprite;
	Sprite bonusTimeSprite;
	int hideX;
	int hideY;
	
}; //ѕосле описани€ структуры став€т точку с зап€той

struct systemObjectStruct //ќбъ€вили новую структуру systemObjectStruct
{
	RenderWindow window;//окно
	View view;
	Clock clock;
	float time;
	float bonusTimer;
	int bonusClockTimer = 17000;//через сколько по€в€тс€ бонус 
	int timeForHide = 7000;//врем€ через которое бонус будет исчезать после по€влени€
}; 

struct gameObjectStruct //ќбъ€вили новую структуру gameObjectStruct
{
	LifeBar lifeBar;//экземпл€р класса полоски здоровь€
	std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты
	Level level;
	Map map;
	Home home;
}; 

void eventLoop(RenderWindow &window, Player &player, std::list<Entity*> & entities, Sprite &spriteCursor, Image &BulletImage){
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (player.isStay()) {//если игрок стоит, то будем его поворачивать и стрел€ть
			player.rotateSprite(spriteCursor.getPosition());//поворачиваем спрайт в сторону выстрела

			if ((event.type == Event::MouseButtonPressed) && (event.key.code == Mouse::Left) && (player.isShoot == true))//если нажата клавиша мыши //а именно лева€, то стрел€ем 
			{
				player.speed = 0;
				player.acceleration.x = 0;
				player.acceleration.y = 0;
				player.isShoot = false;
				entities.push_back(new Bullet(BulletImage, "Bullet", player.position, Vector2i(12, 12), spriteCursor.getPosition().x, spriteCursor.getPosition().y)); //если выстрелили, то по€вл€етс€ пул€	
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
		if (0 + rand() % 2 == 1){
			objectImages.bonusTimeSprite.setPosition(rangeXLeft + rand() % rangeXRight, rangeYTop + rand() % rangeYBottom);
		} else {
			objectImages.bonusHealthSprite.setPosition(rangeXLeft + rand() % rangeXRight, rangeYTop + rand() % rangeYBottom);
		}
		systemObjects.bonusTimer = 0;
	}
	if (systemObjects.bonusTimer > systemObjects.timeForHide){//скрыть бонусы через timeForhide 
		objectImages.bonusHealthSprite.setPosition(objectImages.hideX, objectImages.hideY);
		objectImages.bonusTimeSprite.setPosition(objectImages.hideX, objectImages.hideY);
	}
}

void interactionWithBonus(Player &player, objectImagesStruct &objectImages, gameObjectStruct &gameObjects) {
	int playerHealthBonus = 10;
	float slowEnemy = -0.005;

	if (FloatRect(player.sprite.getGlobalBounds()).intersects(FloatRect(objectImages.bonusHealthSprite.getGlobalBounds()))) {
		player.health += playerHealthBonus;
		objectImages.bonusHealthSprite.setPosition(objectImages.hideX, objectImages.hideY);
	}
	if (FloatRect(player.sprite.getGlobalBounds()).intersects(FloatRect(objectImages.bonusTimeSprite.getGlobalBounds()))) {
		
		for (auto& it : gameObjects.entities) {
			if ((it->name != "ZombieEnemy") && (it->name != "BearZombieEnemy"))
				continue;
			(it)->acceleration.x = slowEnemy;
		}
		objectImages.bonusTimeSprite.setPosition(objectImages.hideX, objectImages.hideY);
	}
}
void entitiesInteraction(gameObjectStruct &gameObjects, Player &player, objectImagesStruct &objectImages, systemObjectStruct &systemObject){
	for (auto& it : gameObjects.entities) {
		it->update(systemObject.time, gameObjects.home);

		if ((it->name != "ZombieEnemy")&&(it->name != "BearZombieEnemy"))
			continue;
		if (it->life == false) {
			gameObjects.level.score++;//если враг умер, то прибавл€ем очки игроку
		}
		
		if (it->getRect().intersects(player.getRect()) && (it->health>gameObjects.level.deathQuantityHealth)) {
			player.health -= gameObjects.level.playerDamage;
		}// игрок получает дамаг при контакте с зомби

		for (auto& it2 : gameObjects.entities)
		{
			if (!((it2->name == "Bullet") && (it->sprite.getGlobalBounds().intersects(it2->sprite.getGlobalBounds()) && (it->health > gameObjects.level.deathQuantityHealth))))

			//if (!((it2->name == "Bullet") && (it->getRect().intersects(it2->getRect()) && (it->health > gameObjects.level.deathQuantityHealth))))
				continue;
			if ((gameObjects.level.wave > gameObjects.level.superHardMode) && (it->name == "BearZombieEnemy")) {//после какой волны пул€ сможет убивать нескольких простых зомби сразу
				it2->life = false;
			}
			it->health -= gameObjects.level.zombieDamage;
			it->sprite.setColor(Color::Yellow);
			if (it->health <= gameObjects.level.deathQuantityHealth) {
				gameObjects.entities.push_back(new Enemy(objectImages.enemyImage, Vector2f(systemObject.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth), 50 + rand() % (gameObjects.level.densityZombieHeight)), Vector2i(25, 53), "ZombieEnemy", gameObjects.level.getZombieHealth(), gameObjects.level.getZombieSpeed()));
			}
			if ((it->health <= gameObjects.level.deathQuantityHealth) && (gameObjects.level.wave>gameObjects.level.superHardMode) && (0 + rand() % 2==1)) {
				gameObjects.entities.push_back(new Enemy(objectImages.enemyBossImage, Vector2f(systemObject.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth), 50 + rand() % (gameObjects.level.densityZombieHeight)), Vector2i(64, 66), "BearZombieEnemy", gameObjects.level.bearZombieHealth, gameObjects.level.bearZombieSpeed));
			}
		}
	}
	eventZombiDestroy(gameObjects.entities, gameObjects.level);
}

void gameUpdate(systemObjectStruct &systemObjects, objectImagesStruct &objectImages, gameObjectStruct &gameObjects, Player &player){
	systemObjects.time = systemObjects.clock.getElapsedTime().asMicroseconds();
	systemObjects.clock.restart();
	systemObjects.time = systemObjects.time / gameObjects.level.tempGame;
	
	Vector2f pos = systemObjects.window.mapPixelToCoords(Mouse::getPosition(systemObjects.window));//забираем коорд курсора, переводим их в игровые (уходим от коорд окна)

	eventLoop(systemObjects.window, player, gameObjects.entities, objectImages.spriteCursor, objectImages.BulletImage);//while (window.pollEvent(event))

	player.update(systemObjects.time, gameObjects.home);
	radiusAim(gameObjects.level.attackDistance, pos, player.position, objectImages.spriteCursor);//прицел не дальше дистанции
	gameObjects.lifeBar.update(gameObjects.home.getHealth(), player.health, player.position);
	gameObjects.home.update();
	createBonus(gameObjects.level.wave, systemObjects, objectImages);//bonus create

	interactionWithBonus(player, objectImages, gameObjects);//взаимодействие с бонусами
	eventZombiDestroy(gameObjects.entities, gameObjects.level);

	entitiesInteraction(gameObjects, player, objectImages, systemObjects);

	
	
	systemObjects.window.setView(systemObjects.view);
	systemObjects.window.clear();
	systemObjects.window.draw(gameObjects.map.getSprite());//рисуем карту
	systemObjects.window.draw(gameObjects.home.getSprite());//рисуем дом
	gameObjects.level.update(systemObjects.window, player, gameObjects.home, systemObjects.time);//обновление уровн€ и рисование статистики
	for (auto& it : gameObjects.entities) {
		systemObjects.window.draw(it->sprite);
	} //рисуем entities объекты (сейчас это пули и враги)
	systemObjects.window.draw(player.sprite);
	systemObjects.window.draw(objectImages.spriteCursor);
	systemObjects.window.draw(objectImages.bonusHealthSprite);
	systemObjects.window.draw(objectImages.bonusTimeSprite);
	gameObjects.lifeBar.draw(systemObjects.window);

	systemObjects.window.display();
}

bool startGame(systemObjectStruct &systemObjects, objectImagesStruct &objectImages, gameObjectStruct &gameObjects, Player &player) {//функци€ начинает игру

	//menu(window);//вызов меню

	while (systemObjects.window.isOpen())
	{
		gameUpdate(systemObjects, objectImages, gameObjects, player);
		if (Keyboard::isKeyPressed(Keyboard::Tab)) {
			return true;
		}//если таб, то перезагружаем игру
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return false;
		}//если эскейп, то выходим из игры
	}
	return false;
}

bool createGameObject(){

	systemObjectStruct systemObjects;
	systemObjects.window.create(sf::VideoMode(1276, 668), "Ataka zombi!");
	systemObjects.window.setMouseCursorVisible(false); // скрывает курсор
	systemObjects.view = systemObjects.window.getView(); //фиксированна€ камера дл€ прицела
	
	objectImagesStruct objectImages;
	objectImages.hideX = 0;
	objectImages.hideY = 2200;
	objectImages.BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображени€
	objectImages.BulletImage.createMaskFromColor(Color(0, 0, 0));//маска дл€ пули по черному цвету
	objectImages.playerImage.loadFromFile("images/hero.png");
	objectImages.playerImage.createMaskFromColor(Color(255, 255, 255));
	objectImages.enemyImage.loadFromFile("images/Monster-zombie.png");
	objectImages.enemyBossImage.loadFromFile("images/zombiebear.png");
	objectImages.textureCursor.loadFromFile("images/cursor.png");
	objectImages.textureBonus.loadFromFile("images/bonus.png");
	objectImages.bonusTimeSprite.setTextureRect(IntRect(0, 0, 32,32));
	objectImages.bonusTimeSprite.setTexture(objectImages.textureBonus);
	objectImages.bonusTimeSprite.setPosition(objectImages.hideX, objectImages.hideY);
	objectImages.bonusHealthSprite.setTexture(objectImages.textureBonus);
	objectImages.bonusHealthSprite.setTextureRect(IntRect(32, 0, 32, 32));
	objectImages.bonusHealthSprite.setPosition(objectImages.hideX, objectImages.hideY);
	
	objectImages.spriteCursor.setTexture(objectImages.textureCursor);
	
	gameObjectStruct gameObjects;
	Player player(objectImages.playerImage, Vector2f(150, 150), Vector2i(55, 65), "Player1");
	systemObjects.bonusTimer = 0;
	/////////////////////////////—оздание зомби в зависимости от плотности////////////////////
	for (int i = 0; i < gameObjects.level.zombieQuantity; i++) {//проходимс€ по элементам этого вектора(а именно по врагам)
		gameObjects.entities.push_back(new Enemy(objectImages.enemyImage, Vector2f(systemObjects.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth), 50 + rand() % (gameObjects.level.densityZombieHeight)*i), Vector2i(25, 53), "ZombieEnemy", gameObjects.level.getZombieHealth(), gameObjects.level.getZombieSpeed()));//генерим врагов по высоте
		for (int j = 0; j < gameObjects.level.zombieQuantity; j++) {
			gameObjects.entities.push_back(new Enemy(objectImages.enemyImage, Vector2f(systemObjects.window.getSize().x + rand() % (gameObjects.level.densityZombieWidth)*j, 50 + rand() % (gameObjects.level.densityZombieHeight)), Vector2i(25, 53), "ZombieEnemy", 1 + rand() % gameObjects.level.getZombieHealth(), gameObjects.level.getZombieSpeed()));//по ширине
		}
	}
	///////////////////////////////////////////////////////////////

	return startGame(systemObjects, objectImages, gameObjects, player);
	
}

void gameRunning(){//ф-ци€ перезагружает игру , если это необходимо
	if (createGameObject()) { gameRunning(); }////если createGameObject() == true, то вызываем занова ф-цию isGameRunning, котора€ в свою очередь оп€ть вызывает startGame() 
}

void eventZombiDestroy(std::list<Entity*> &entities, Level &level){

	auto is_crash = [](Entity *entities) {
		return !(entities->life);
	};

	entities.erase(std::remove_if(entities.begin(), entities.end(), is_crash), entities.end());//удал€ем все элементы со значением life=false
}