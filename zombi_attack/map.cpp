#include "map.h"

Map::Map() {
	image.loadFromFile("images/map.jpg");//картинка
	texture.loadFromImage(image);//загружаем текстуру картинкой
	sprite.setTexture(texture);//загружаем в спрайт текстуру
}

Sprite Map::getSprite(){
	return sprite;
}
