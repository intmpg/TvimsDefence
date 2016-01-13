#ifndef ENITY_HPP
#define ENITY_HPP
#include <SFML\Graphics.hpp>
#include "home.h"
using namespace sf;

class Entity {
public:
	Vector2f position;
	Vector2f acceleration;
	Vector2i spriteSize;
	float speed;
	float currentFrame;//добавили переменную текущ кадр
	float currentFrameDeath;
	int health;
	bool life;
	bool startShowDecomposition;//разложение после смерти
	bool isTractorKiller;//виноват ли в смерти трактор
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, Vector2f startPosition, Vector2i spriteObjectSize, String Name);
	void checkDeath();//проверка на смерть объекта
	float getCurrentFrame(float &time); //получить текущий кадр анимации
	float getCurrentFrameDeath(float &time);//после смерти разложение зомби
	void setCurrentFrame(int currentFRAME);
	FloatRect getRect();//получить область прямоугольника спрайта
	void checkCollisionWithHome(Home &home);//столкновение с домом
	virtual void update(float time, Home &home) = 0;
	virtual ~Entity() {};
};
#endif