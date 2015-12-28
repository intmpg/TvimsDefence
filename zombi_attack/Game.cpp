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

	//////////////////////////////МЕНЮ///////////////////
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



void eventLoop(RenderWindow &window, Player &player, std::list<Entity*> & entities, Sprite &spriteCursor, Image &BulletImage){
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (player.isStay()) {//если игрок стоит, то будем его поворачивать и стрелять
			player.rotateSprite(spriteCursor.getPosition());//поворачиваем спрайт в сторону выстрела

			if ((event.type == Event::MouseButtonPressed) && (event.key.code == Mouse::Left) && (player.isShoot == true))//если нажата клавиша мыши //а именно левая, то стреляем 
			{
				player.speed = 0;
				player.acceleration.x = 0;
				player.acceleration.y = 0;
				player.isShoot = false;
				entities.push_back(new Bullet(BulletImage, "Bullet", player.position, Vector2i(12, 12), spriteCursor.getPosition().x, spriteCursor.getPosition().y)); //если выстрелили, то появляется пуля	
			}
		}
	}
}

void entitiesInteraction(std::list<Entity*> & entities, float &time, Home &home, Level &level, Player &player, Image &enemyImage, RenderWindow &window){
	for (auto& it : entities) {
		it->update(time, home);

		if (it->name != "ZombieEnemy")
			continue;
		if (it->life == false) {
			level.score++;//если враг умер, то прибавляем очки игроку
		}

		if (it->getRect().intersects(player.getRect()) && (it->health>level.deathQuantityHealth)) {
			player.health -= level.playerDamage;
		}// игрок получает дамаг при контакте с зомби

		for (auto& it2 : entities)
		{
			if (!((it2->name == "Bullet") && (it->getRect().intersects(it2->getRect()) && (it->health > level.deathQuantityHealth))))
				continue;
			if (level.wave < level.superBulletWave) {//после 11 волны пуля сможет убивать нескольких
				it2->life = false;
			}
			it->health -= level.zombieDamage;
			it->sprite.setColor(Color::Yellow);
			if (it->health <= level.deathQuantityHealth) {
				entities.push_back(new Enemy(enemyImage, Vector2f(window.getSize().x + rand() % (level.densityZombieWidth), 50 + rand() % (level.densityZombieHeight)), Vector2i(25, 53), "ZombieEnemy", level.getZombieHealth(), level.getZombieSpeed()));
			}
		}
	}
	eventZombiDestroy(entities, level);
}

void gameUpdate(RenderWindow &window, LifeBar &lifeBar, View &view, Texture &textureCursor, Sprite &spriteCursor, Clock & clock, Image &BulletImage, Image &enemyImage, Level &level, Player &player, Map &map, Home &home, std::list<Entity*> & entities){
	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / level.tempGame;
	
	Vector2f pos = window.mapPixelToCoords(Mouse::getPosition(window));//забираем коорд курсора, переводим их в игровые (уходим от коорд окна)

	eventLoop(window, player, entities,spriteCursor,BulletImage);//while (window.pollEvent(event))

	player.update(time, home);
	radiusAim(level.attackDistance, pos, player.position, spriteCursor);//прицел не дальше дистанции
	lifeBar.update(home.getHealth(), player.health, player.position);
	home.update();
	
	entitiesInteraction(entities, time, home, level, player,enemyImage,window);

	//удаление эл-тов из списка
	

	window.setView(view);
	window.clear();

	window.draw(map.getSprite());//рисуем карту
	window.draw(home.getSprite());//рисуем дом
	level.update(window, player, home, time);//обновление уровня и рисование статистики
	for (auto& it : entities) {
		window.draw(it->sprite);
	} //рисуем entities объекты (сейчас это пули и враги)
	window.draw(player.sprite);
	window.draw(spriteCursor);
	lifeBar.draw(window);

	window.display();
}

bool startGame(RenderWindow &window, LifeBar &lifeBar, View &view, Texture &textureCursor, Sprite &spriteCursor, Clock & clock, Image &BulletImage, Image &enemyImage, Level &level, Player &player, Map &map, Home &home, std::list<Entity*> & entities) {//функция начинает игру

	//menu(window);//вызов меню

	while (window.isOpen())
	{
		gameUpdate(window, lifeBar, view, textureCursor, spriteCursor, clock, BulletImage,  enemyImage, level, player, map, home, entities);
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
	RenderWindow window(sf::VideoMode(1276, 668), "Ataka zombi!");
	LifeBar lifeBar;//экземпляр класса полоски здоровья
	window.setMouseCursorVisible(false); // скрывает курсор

	View view = window.getView(); //фиксированная камера для прицела

	std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты
	Texture textureCursor;
	textureCursor.loadFromFile("images/cursor.png");
	Sprite spriteCursor(textureCursor);

	Clock clock;

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету
	Image playerImage;
	playerImage.loadFromFile("images/hero.png");
	playerImage.createMaskFromColor(Color(255, 255, 255));

	Image enemyImage;
	enemyImage.loadFromFile("images/Monster-zombie.png");

	Level level;

	Player player(playerImage, Vector2f(150, 150), Vector2i(55, 65), "Player1");
	Map map;
	Home home;

	/////////////////////////////Создание зомби в зависимости от плотности////////////////////
	for (int i = 0; i < level.zombieQuantity; i++) {//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(enemyImage, Vector2f(window.getSize().x + rand() % (level.densityZombieWidth), 50 + rand() % (level.densityZombieHeight)*i), Vector2i(25, 53), "ZombieEnemy", level.getZombieHealth(), level.getZombieSpeed()));//генерим врагов по высоте
		for (int j = 0; j < level.zombieQuantity; j++) {
			entities.push_back(new Enemy(enemyImage, Vector2f(window.getSize().x + rand() % (level.densityZombieWidth)*j, 50 + rand() % (level.densityZombieHeight)), Vector2i(25, 53), "ZombieEnemy", 1 + rand() % level.getZombieHealth(), level.getZombieSpeed()));//по ширине
		}
	}
	///////////////////////////////////////////////////////////////

	return startGame(window, lifeBar, view, textureCursor, spriteCursor, clock, BulletImage, enemyImage, level, player, map, home, entities);
	
}

void gameRunning(){//ф-ция перезагружает игру , если это необходимо
	if (createGameObject()) { gameRunning(); }////если createGameObject() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
}

void eventZombiDestroy(std::list<Entity*> &entities, Level &level){

	auto is_crash = [](Entity *entities) {
		return !(entities->life);
	};

	entities.erase(std::remove_if(entities.begin(), entities.end(), is_crash), entities.end());//удаляем все элементы со значением life=false
}