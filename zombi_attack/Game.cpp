#include "Game.h"

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

	//////////////////////////////����///////////////////
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

void radiusAim(int attackDistance, Vector2f pos, float playerX, float playerY, Sprite &spriteCursor) {
	float dX = pos.x - 500;
	float dY = pos.y - 500;

	if (dX*dX + dY*dY > attackDistance) {
		float angle = std::atan2(dY, dX);
		pos.x = playerX + attackDistance * cos(angle);
		pos.y = playerY + attackDistance * sin(angle);
	}
	spriteCursor.setPosition(pos.x + 10, pos.y);

}

void gameUpdate(RenderWindow &window, LifeBar &lifeBar, View &view, Texture &textureCursor, Sprite &spriteCursor, Clock & clock, Image &BulletImage, Image &playerImage, Image &enemyImage, Level &level, Player &player, Map &map, Home &home, std::list<Entity*> & entities){
	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / 800;
	Event event;
	Vector2f pos = window.mapPixelToCoords(Mouse::getPosition(window));//�������� ����� �������, ��������� �� � ������� (������ �� ����� ����)

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (player.isStay()) {//���� ����� �����, �� ����� ��� ������������ � ��������
			player.rotateSprite(spriteCursor.getPosition());//������������ ������ � ������� ��������

			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left) //� ������ �����, �� �������� 
				{

					if (player.isShoot == true) {
						player.speed = 0; player.dx = 0; player.dy = 0;
						player.isShoot = false;
						entities.push_back(new Bullet(BulletImage, "Bullet", player.x, player.y, 12, 12, spriteCursor.getPosition().x, spriteCursor.getPosition().y));
					} //���� ����������, �� ���������� ����
				}
		}
	}



	player.update(time, home);
	radiusAim(level.attackDistance, pos, player.x, player.y, spriteCursor);//������ �� ������ ���������
	lifeBar.update(home.getHealth(), player.health, player.x, player.y);
	home.update();

	for (auto& it : entities) {
		it->update(time, home);

		if (it->name == "ZombieEnemy") {
			if (it->getRect().intersects(player.getRect()) && (it->health>0)){ player.health -= 1; }// ����� �������� ����� ��� �������� � �����
			for (auto& it2 : entities)
			{
				if (it2->name == "Bullet") {
					if ((it->getRect().intersects(it2->getRect()) && (it->health>0)))
					{
						if (level.wave < 11){//����� 15 ����� ���� ������ ������� ����������
							it2->life = false;
						}
						else { it->sprite.setColor(Color::Yellow); }
						it->health -= 5;
						it->sprite.setColor(Color::Yellow);
						if (it->health <= 0) {
							entities.push_back(new Enemy(enemyImage, window.getSize().x + rand() % (level.densityZombieWidth), 50 + rand() % (level.densityZombieHeight), 25, 53, "ZombieEnemy", level.getZombieHealth(), level.getZombieSpeed()));
						}
					}
				}
			}
		}
	}

	/*
	for (auto& it : entities) {
	if (it->life == false)	{
	if (it->name == "ZombieEnemy") { level.score++; } //���� ������� �����, �� ���������� ���� ������
	it=entities.erase(it);//��� �� ���� ��� ������� ������� �� ������
	}
	else   it++;
	}*/

	//�������� ��-��� �� ������
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();)
	{
		if ((*it)->life == false)	{
			if ((*it)->name == "ZombieEnemy") { level.score++; } //���� ������� �����, �� ���������� ���� ������
			it = entities.erase(it);
		}
		else   it++;
	}

	window.setView(view);
	window.clear();

	window.draw(map.getSprite());//������ �����
	window.draw(home.getSprite());//������ ���
	level.update(window, player, home, time);//���������� ������ � ��������� ����������
	for (auto& it : entities) { window.draw(it->sprite); } //������ entities ������� (������ ��� ���� � �����)
	window.draw(player.sprite);
	window.draw(spriteCursor);
	lifeBar.draw(window);

	window.display();
}

bool startGame(RenderWindow &window, LifeBar &lifeBar, View &view, Texture &textureCursor, Sprite &spriteCursor, Clock & clock, Image &BulletImage, Image &playerImage, Image &enemyImage, Level &level, Player &player, Map &map, Home &home, std::list<Entity*> & entities) {//������� �������� ����

	menu(window);//����� ����

	while (window.isOpen())
	{
		gameUpdate(window, lifeBar, view, textureCursor, spriteCursor, clock, BulletImage, playerImage, enemyImage, level, player, map, home, entities);
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }//���� ���, �� ������������� ����
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//���� ������, �� ������� �� ����
	}
	return false;
}

bool createGameObject(){
	RenderWindow window(sf::VideoMode(1276, 668), "Ataka zombi!");
	LifeBar lifeBar;//��������� ������ ������� ��������
	window.setMouseCursorVisible(false); // �������� ������

	View view = window.getView(); //������������� ������ ��� �������

	std::list<Entity*>  entities;//������ ������, ���� ���� ������ �������
	Texture textureCursor;
	textureCursor.loadFromFile("images/cursor.png");
	Sprite spriteCursor(textureCursor);

	Clock clock;

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����
	Image playerImage;
	playerImage.loadFromFile("images/hero.png");
	playerImage.createMaskFromColor(Color(255, 255, 255));

	Image enemyImage;
	enemyImage.loadFromFile("images/Monster-zombie.png");

	Level level;

	Player player(playerImage, 150, 150, 55.55, 65.5, "Player1");
	Map map;
	Home home;


	/////////////////////////////�������� ����� � ����������� �� ���������////////////////////
	for (int i = 0; i < level.zombieQuantity; i++) {//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(enemyImage, window.getSize().x + rand() % (level.densityZombieWidth), 50 + rand() % (level.densityZombieHeight)*i, 25, 53, "ZombieEnemy", level.getZombieHealth(), level.getZombieSpeed()));//������� ������ �� ������
		for (int j = 0; j < level.zombieQuantity; j++) {
			entities.push_back(new Enemy(enemyImage, window.getSize().x + rand() % (level.densityZombieWidth)*j, 50 + rand() % (level.densityZombieHeight), 25, 53, "ZombieEnemy", 1 + rand() % level.getZombieHealth(), level.getZombieSpeed()));//�� ������
		}
	}
	///////////////////////////////////////////////////////////////

	return startGame(window, lifeBar, view, textureCursor, spriteCursor, clock, BulletImage, playerImage, enemyImage, level, player, map, home, entities);
}

void gameRunning(){//�-��� ������������� ���� , ���� ��� ����������
	if (createGameObject()) { gameRunning(); }////���� createGameObject() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
}