#ifndef LIFEBAR_HPP
#define LIFEBAR_HPP
#include <SFML\Graphics.hpp>
using namespace sf;

class LifeBar
{
public:
	Image image;
	Image entitiesBar;
	Texture t;
	Texture entitiesTexture;
	Sprite s;
	Sprite bar2;
	int maxHomeHealth;
	int barOffset;
	RectangleShape bar;//прямоугольник которым будем покрывать нашу картинку
	Vector2i playerHealthSize;
	Vector2i playerHealthOffset;
	Vector2i offsetBarHome;
	
	LifeBar();
	void update(int homeHealth, int playerHealth, Vector2f PlayerPosition);
	void draw(RenderWindow &window);
};
#endif