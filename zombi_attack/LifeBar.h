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
	const int maxHomeHealth = 15000;
	const int barOffset=4;
	const int halfScreen=2;
	const int playerHealthSizeX = 20;
	const int playerHealthSizeY = 7;
	const int playerHealthOffsetX = 60;
	const int playerHealthOffsetY = 40;
	const int offsetBarHomeX = 10;
	const int offsetBarHomeY = 70;
	RectangleShape bar;//прямоугольник которым будем покрывать нашу картинку
	
	LifeBar();
	void update(int homeHealth, int playerHealth, Vector2f PlayerPosition);
	void draw(RenderWindow &window);
};
#endif