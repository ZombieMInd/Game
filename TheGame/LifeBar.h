#pragma once

using namespace sf;

class LifeBar{
private:
	Image image;
	Texture texture;
	Sprite sprite;
	int max;
	RectangleShape bar;
public:
	

	LifeBar();

	void update(int);

	void draw(RenderWindow&);

};


LifeBar::LifeBar() {
	image.loadFromFile("assets/life.png");
	image.createMaskFromColor(Color(50, 96, 166));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(783, 2, 15, 84));
	sprite.setScale(2.0f, 2.0f);

	bar.setFillColor(Color(0, 0, 0));//������ ������������� ������������� ������ � ���������� ������ ���������� ��������
	max = 100;
}

void LifeBar::update(int currentHp){
	if (currentHp > 0) {
		if (currentHp < max) {
			bar.setSize(Vector2f(26, (max - currentHp) * 140 / max));//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� �������� (����� ������) ��� ������� ��������������
		}		
	}	
}

void LifeBar::draw(RenderWindow &window){

	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	sprite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//������� �� ������
	bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

	window.draw(sprite);//������� ������ ������� ��������
	window.draw(bar);//������ �� ��� ������ �������������, �� ��� �� ��������� �
}