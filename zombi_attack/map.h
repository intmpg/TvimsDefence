
#ifndef MAP_HPP
#define MAP_HPP
#include <SFML/Graphics.hpp>
using namespace sf;
class Map { //����� �����
private:
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
public:
	Map();
	Sprite getSprite();

};
#endif