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
	int max;
	RectangleShape bar;//прямоугольник которым будем покрывать нашу картинку
	
	LifeBar();
	void update(int hH, int pH, float pX, float pY);
	void draw(RenderWindow &window);
};
#endif