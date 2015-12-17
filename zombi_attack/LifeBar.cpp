#include "LifeBar.h"

LifeBar::LifeBar(){
	image.loadFromFile("images/life.png");
	image.createMaskFromColor(Color(50, 96, 166));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(783, 2, 15, 71));

	entitiesBar.loadFromFile("images/heal_bar.jpg");
	entitiesTexture.loadFromImage(entitiesBar);
	bar2.setTexture(entitiesTexture);

	bar.setFillColor(Color(0, 0, 0));//������ ������������� ������������� ������ � ���������� ������ ���������� ��������


	max = 15000;
}

void LifeBar::update(int hH, int pH, float pX, float pY)//homeHealth,playerHealth,p.x,p.y

{

	if ((hH>0) && (hH < max)) {
		bar.setSize(Vector2f(10, (max - hH) * 70 / max));//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� �������� (����� ������) ��� ������� ��������������
	}

	if (pH >= 0) {
		bar2.setTextureRect(IntRect(0, 0, 20 + pH, 7));
	}
	else { bar2.setTextureRect(IntRect(0, 0, 20, 7)); }


	bar2.setPosition(pX - 60, pY - 40);

}

void LifeBar::draw(RenderWindow &window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 0);//������� �� ������
	bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 4);


	window.draw(s);//������� ������ ������� ��������
	window.draw(bar);//������ �� ��� ������ �������������, �� ��� �� ��������� �
	window.draw(bar2);
}
