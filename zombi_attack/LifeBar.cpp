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

	bar.setFillColor(Color(0, 0, 0));//черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья

	maxHomeHealth = 15000;//макс значение хп дома

	playerHealthSize.x = 20;
	playerHealthSize.y = 7;

	playerHealthOffset.x = 60;
	playerHealthOffset.y = 40;

	offsetBarHome.x = 10;
	offsetBarHome.y = 70;

	barOffset = 4;	
}

void LifeBar::update(int homeHealth, int playerHealth, Vector2f PlayerPosition)//homeHealth,playerHealth,p.x,p.y
{
	if ((homeHealth>0) && (homeHealth < maxHomeHealth)) {
		bar.setSize(Vector2f(offsetBarHome.x, (maxHomeHealth - homeHealth) * offsetBarHome.y / maxHomeHealth));//если не отрицательно и при этом меньше максимума, то устанавливаем новое значение (новый размер) для черного прямоугольника
	}

	if (playerHealth >= 0) {
		bar2.setTextureRect(IntRect(0, 0, playerHealthSize.x + playerHealth, playerHealthSize.y));
	}
	else { bar2.setTextureRect(IntRect(0, 0, playerHealthSize.x, playerHealthSize.y)); }

	bar2.setPosition(PlayerPosition.x - playerHealthOffset.x, PlayerPosition.y - playerHealthOffset.y);
}

void LifeBar::draw(RenderWindow &window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / 2, center.y - size.y / 2 );//позиция на экране
	bar.setPosition(center.x - size.x / 2 + barOffset, center.y - size.y / 2 + barOffset);


	window.draw(s);//сначала рисуем полоску здоровья
	window.draw(bar);//поверх неё уже черный прямоугольник, он как бы покрывает её
	window.draw(bar2);
}
