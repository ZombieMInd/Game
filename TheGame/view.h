#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;
void GetPlayerCoordinateForView(float x, float y) { 
	float tempX = x; float tempY = y;
	if (x < 540) tempX = 540;//������� �� ���� ����� �������
	if (y < 500) tempY = 500;//������� �������
	if (y > 1750) tempY = 1850;//������ �������	
	if (x > 3100) tempX = 3250; // ������ �������
	// � �������� �� ������ ����� ��� ����� �� �����
	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 

}


