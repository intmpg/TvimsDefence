
#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
using namespace sf;
class Map { //класс карты
private:
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
public:
	Map();
	Sprite getSprite();

};
#endif