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

}

void LifeBar::update(int homeHealth, int playerHealth, Vector2f PlayerPosition)//homeHealth,playerHealth,p.x,p.y
{
	if ((homeHealth>0) && (homeHealth < maxHomeHealth)) {
		bar.setSize(Vector2f(offsetBarHomeX, (maxHomeHealth - homeHealth) * offsetBarHomeY / maxHomeHealth));//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� �������� (����� ������) ��� ������� ��������������
	}

	if (playerHealth >= 0) {
		bar2.setTextureRect(IntRect(0, 0, playerHealthSizeX + playerHealth, playerHealthSizeY));
	} else { 
		bar2.setTextureRect(IntRect(0, 0, playerHealthSizeX, playerHealthSizeY));
		}

	bar2.setPosition(PlayerPosition.x - playerHealthOffsetX, PlayerPosition.y - playerHealthOffsetY);
}

void LifeBar::draw(RenderWindow &window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / halfScreen, center.y - size.y / halfScreen);//������� �� ������
	bar.setPosition(center.x - size.x / halfScreen + barOffset, center.y - size.y / halfScreen + barOffset);

	window.draw(s);//������� ������ ������� ��������
	window.draw(bar);//������ �� ��� ������ �������������, �� ��� �� ��������� �
	window.draw(bar2);
}
