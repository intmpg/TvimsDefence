#ifndef TRACTOR_HPP
#define TRACTOR_HPP
#include <SFML\Graphics.hpp>
#include "Player.h"

using namespace sf;

class Tractor {
public:
	Vector2f position;
	Vector2f startPosition;
	Vector2f acceleration;
	Vector2i spriteSizeHorizontal;
	Vector2i spriteSizeVertical;
	Vector2i spriteOffsetRight;
	Vector2i spriteOffsetLeft;
	Vector2i spriteOffsetUp;
	Vector2i spriteOffsetDown;
	Image tractorImage;
	Texture texture; 
	Sprite sprite;
	bool isMove;
	float moveTimer;
	float startTimer;
	float speed;
	int startTime;
	int moveTime;
	enum { left, right, up, down } state;
	
	Tractor();
	~Tractor();
	
	
	void update(float &time, Player &player, Home &home);
	void interactionWithPlayer(float &time, Player &player);
	void setSpriteRect(Player &player);
	void control(float &time, Player &player);
	void startMove();
	void rotateInHome();
	void checkCollisionWithHome(Home &home, Player & player);//столкновение с домом
	FloatRect getRect();//получить область прямоугольника спрайта
};
#endif