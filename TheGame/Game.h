#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
//#include "Messages.h"
#include <string>
#include <sstream>
#include "Chest.h"
#include "PassiveItem.h"
#include "Weapon.h"
#include "LifeBar.h"

using namespace sf;

class Game{
private:
	//string state;
	bool isRestarted = false;
	bool playing;
	int gameLevel;
	int levelOfComplexity; // easy, medium, hard. depends on amount of enemy, weapons etc
	std::list<Entity*> entities;
	std::list<Chest*> chests;
	void generatingObjectsOnMap(Player&);
	void drawMap(RenderWindow&);
	void updateEntities(Player&, float&);
	void updateChests(Player&, RenderWindow&);
	void updateItems(Player&, RenderWindow&);
	void updateWeapons(Player&, RenderWindow&);
	void menu(RenderWindow&);
	bool showMissionText = true;////////
	bool isPlayerWin();
	void win(RenderWindow&);

	std::list<Weapon*> weapons;
	std::list<PassiveItem*> items;
	
	
protected:
	Clock clock;
	Image map_image;
	Image quest_image;
	Texture quest_texture;
	Sprite s_quest;
	Texture map;
	Sprite s_map;
	Font font;
	Text text;
public:
	
	Game();
	Game(int, int);
	void init();
	bool play();
	
	void restartGame();
	bool isPlaying();

	int getCurrentMission(int);
	std::string getTextMission(int);
};

Game::Game() {
	playing = true;
	gameLevel = 1;
	levelOfComplexity = 1;
}

bool Game::isPlaying() {
	return playing;
}
bool Game::isPlayerWin() {
	return entities.size() < 1;
}
Game::Game(int gameLevel, int levelOfComplexity) {
	this->gameLevel = gameLevel;
	this->levelOfComplexity = levelOfComplexity;
}

void Game::init() {
	map_image.loadFromFile("assets/G_v06.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);
	font.loadFromFile("assets/CyrilicOld.ttf");
	text.setFont(font);
	text.setCharacterSize(38);
	text.setPosition(view.getCenter());
	quest_image.loadFromFile("assets/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	quest_texture.loadFromImage(quest_image);
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));
	//s_quest.setScale(0.6f, 0.6f);
	
	playing = false;
}

void Game::updateItems(Player &player, RenderWindow& window) {
	for (std::list<PassiveItem*>::iterator itemIter = items.begin(); itemIter != items.end();) {
		PassiveItem* item = *itemIter;
		item->interaction(player.getPos());
		if (item->isPickedUp) {
			player.pickUpItem(item);
			itemIter = items.erase(itemIter);
			delete item;
		}
		else {
			window.draw(item->text);
			itemIter++;
		}
	}
}

void Game::updateWeapons(Player &player, RenderWindow& window) {
	for (std::list<Weapon*>::iterator wepIter = weapons.begin(); wepIter != weapons.end();) {
		Weapon* wep = *wepIter;
		wep->interaction(player.getPos());
		if (wep->isPickedUp) {
			player.pickUpWeapon(wep);
			wepIter = weapons.erase(wepIter);
			delete wep;
		}
		else {
			window.draw(wep->text);
			wepIter++;
		}
	}
}

int Game::getCurrentMission(int x) {

	int mission = 0;

	if ((x > 0) && (x < 600)) {
		mission = 0;
	}
	if (x > 400) {
		mission = 1;
	}

	return mission;
}


std::string Game::getTextMission(int currentMission) {

	std::string missionText = "";

	switch (currentMission) {

	case 0:
		missionText = "\tВозьмите оружие\n\t чтобы вы могли\n\t\t атаковать\n\t\t противников";
		break;
	case 1:
		missionText = "\t\tУбейте всех\n\t\tЗлых собак\n\tчтобы победить!\n\t\tЖелаем удачи!";
		break;
	}

	return missionText;
};

void Game::win(RenderWindow& window) {
	Texture winTexture;
	winTexture.loadFromFile("assets/win.jpg");
	Sprite winSprite(winTexture);

	winSprite.setScale(window.getSize().x / winSprite.getLocalBounds().width,
		window.getSize().y / winSprite.getLocalBounds().height);

	bool isWin = true;
	
	window.clear();

	text.setCharacterSize(60);
	text.setString("HOORAY you won!\nit was hard battle..\nbut you did it\ncongrats!");
	text.setPosition(view.getCenter());

	while (isWin) {
		sf::Event event;
		window.clear(Color(129, 181, 221));

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				isWin = false;
			}
		}

		
		window.draw(text);
			
		
		window.draw(winSprite);

		window.display();
	}

}

void Game::menu(RenderWindow& window) {
	Texture menuTextureNewGame, menuTextureAbout, menuTextureExit,
		aboutTexture, menuTextureBackground;
	menuTextureNewGame.loadFromFile("assets/newGame.png");
	menuTextureAbout.loadFromFile("assets/about.png");
	menuTextureExit.loadFromFile("assets/exit.png");
	aboutTexture.loadFromFile("assets/cave.jpg");
	menuTextureBackground.loadFromFile("assets/cave.jpg");
	
	Sprite menuNewGame(menuTextureNewGame), menuAbout(menuTextureAbout), menuExit(menuTextureExit),
		aboutWindow(aboutTexture), menuBackground(menuTextureBackground);

	menuBackground.setScale(window.getSize().x / menuBackground.getLocalBounds().width,
		window.getSize().y / menuBackground.getLocalBounds().height);
	aboutWindow.setScale(window.getSize().x / aboutWindow.getLocalBounds().width,
		window.getSize().y / aboutWindow.getLocalBounds().height);
	bool isMenu = true;
	int menuFlag = 0;
	menuNewGame.setPosition(100, 30);
	menuAbout.setPosition(100, 90);
	menuExit.setPosition(100, 150);
	menuBackground.setPosition(0, 0);

	while (isMenu){
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				isMenu = false;
			}
		}

		menuNewGame.setColor(Color::White);
		menuAbout.setColor(Color::White);
		menuExit.setColor(Color::White);
		menuFlag = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) {
			menuNewGame.setColor(Color::Blue);
			menuFlag = 1;
		}
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) {
			menuAbout.setColor(Color::Blue);
			menuFlag = 2;
		}
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) {
			menuExit.setColor(Color::Blue);
			menuFlag = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left)){

			if (menuFlag == 1) {
				isMenu = false;
			}  
			if (menuFlag == 2) {
				window.draw(aboutWindow);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuFlag == 3) {
				window.close();
				isMenu = false;
			}

		}

		window.draw(menuBackground);
		window.draw(menuNewGame);
		window.draw(menuAbout);
		window.draw(menuExit);

		window.display();
	}
}

void Game::generatingObjectsOnMap(Player &player) {
	int chestCount = 0;
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if ((TileMap[i][j] == 'e')) {
				Enemy *enemy = new Enemy(Vector2f((j - 0.5) * BLOCK_SIZE, (i - 0.5) * BLOCK_SIZE), 100, " ");
				enemy->setPlayer(&player);
				entities.push_back(enemy);
			}
			if (TileMap[i][j] == 'b') {
				chests.push_back(new Chest(Vector2f((j + 0.5) * BLOCK_SIZE, (i + 0.5) * BLOCK_SIZE)));
				chestCount++;
			}
		}
	}
	for (auto chest : chests) {
		chest->setChestSize(chestCount);
	}
}

void Game::restartGame() {
	this->entities.clear();
	this->chests.clear();
}

void Game::drawMap(RenderWindow &window) {
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if (TileMap[i][j] == ' ') {
				this->s_map.setTextureRect(IntRect(890, 65, 94, 94));
			}
			if (TileMap[i][j] == 't') {
				this->s_map.setTextureRect(IntRect(890, 430, 94, 94));
			}
			if ((TileMap[i][j] == '0')) {
				this->s_map.setTextureRect(IntRect(890, 180, 94, 209));
			}
			this->s_map.setPosition(j * 94, i * 94);
			window.draw(this->s_map);
		}
	}
}

void Game::updateChests(Player& player, RenderWindow &window) {
	for (std::list<Chest*>::iterator chestIter = chests.begin(); chestIter != chests.end();) {
		Chest* chest = *chestIter;
		chest->update(player.getPos());
		if (chest->checkOfOpened() == 1) {
			weapons.push_back(chest->weaponGain());
		}
		else if (chest->checkOfOpened() == 2) {
			items.push_back(chest->passiveItemGain());
		}
		window.draw(chest->text);
		chestIter++;
	}
}

void Game::updateEntities(Player& player, float& time) {
	for (std::list<Entity*>::iterator iter = entities.begin(); iter != entities.end();) {
		Entity *enemy = *iter;
		enemy->update(time, player.getPos());
		if (enemy->getHP() <= 0) {
			iter = entities.erase(iter);
			delete enemy;
		}
		else iter++;
	}
}

bool Game::play() {
	RenderWindow window(sf::VideoMode(800, 600), "Kill all bad dogs 2");
	if (!isRestarted) {
		menu(window);
	}
	Player player(sf::Vector2f(200, 200), 100);

	LifeBar lifeBar;
	

	generatingObjectsOnMap(player);
	player.setEntities(entities);
	float time;
	while (window.isOpen()) {

		sf::Event event;


		if (isPlayerWin()) {
			break;
		}

		//для плавности и контроля игрока
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600;
		//sf::sleep(sf::milliseconds(2));

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				playing = false;
				return false;
			}
			if (event.type == Event::KeyPressed) {
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

						case true: {
							std::ostringstream playerHealthString;//строка здоровья игрока
							playerHealthString << player.getHP(); //заносим в строку здоровье 
							std::ostringstream task;//строка текста миссии
							task << getTextMission(getCurrentMission(player.getPos().x));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
							text.setString("\n	Здоровье: " + playerHealthString.str() + "\n\n" + task.str());//задаем
							text.setFillColor(sf::Color::Black);
							text.setPosition(view.getCenter().x - 450, view.getCenter().y - 450);//позиция всего этого текстового блока
							s_quest.setPosition(view.getCenter().x - 450, view.getCenter().y - 450);//позиция фона для блока
							showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
							break;//выходим , чтобы не выполнить условие "false" (которое ниже)
						}
						case false: {
							text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
							showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
							break;
						}
					}
					
				}

			}
		}
		
		window.clear();

		drawMap(window);

		for (auto chest : chests) {
			window.draw(chest->sprite);
		}
		for (auto item : items) {
			window.draw(item->sprite);
		}
		for (auto wep : weapons) {
			window.draw(wep->sprite);
		}

		window.setView(view);

		if (player.isAlive()) {

			player.update(time, pos);
			window.draw(player.sprite);

			updateEntities(player, time);

			updateChests(player, window);

			updateWeapons(player, window);

			updateItems(player, window);

			if (!showMissionText) {
				window.draw(s_quest);
				window.draw(text);
			}
		}
		else {
			text.setString("GAME OVER! press r to restart");
			text.setPosition(view.getCenter());
			window.draw(text);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				std::cout << "Restart ";
				isRestarted = true;
				playing = true;
				return true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				playing = false;
				return false;
			}

		}

		lifeBar.update(player.getHP());
		lifeBar.draw(window);

		for (auto ent : entities) {
			window.draw(ent->sprite);
		}


		window.display();
	}

	if (isPlayerWin()) {
		win(window);
	}
	
}