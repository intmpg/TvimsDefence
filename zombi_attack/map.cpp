#include "map.h"

Map::Map() {
	image.loadFromFile("images/map.jpg");//��������
	texture.loadFromImage(image);//��������� �������� ���������
	sprite.setTexture(texture);//��������� � ������ ��������
}

Sprite Map::getSprite(){
	return sprite;
}
