#ifndef HOME_HPP
#define HOME_HPP
#include <SFML\Graphics.hpp>
using namespace sf;

class Home {
private:
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	int health;
	bool life;
public:
	Home();
	FloatRect getRect();
	Sprite getSprite();
	void setHealth(int H);
	int getHealth();
	void setDamage();
	void checkDeath();
	bool getLife();
	void update();
};
#endif