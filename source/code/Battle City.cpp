﻿#include "pch.h"
#include <SFML/Graphics.hpp>
#include "entity.h"
#include <list>
#include "leveling.h"
#include "collision.h"

using namespace sf;

int main() {
	srand(time(NULL));
	int wx = 624, wy = 624;
	sf::Clock clock;
	RenderWindow window(VideoMode(wx, wy), "Battle City");
	window.setFramerateLimit(20);
	Image sprite;
	sprite.loadFromFile("source/img/sprites.png");
	sprite.createMaskFromColor(sf::Color::Color(0, 0, 1), 0);

	LevelManager lm(sprite);
	lm.ReadMap(1);
	lm.DrawMap();

	std::list <Entity*> entities;
	std::list <Entity*>::iterator it;
	std::list <Entity*>::iterator it2;
	
	PlayerTank player(sprite, &entities, 320, 540, 0, 0, 16, 16);

	entities.push_back(new EnemyTank(sprite, &entities, 0, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 144, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, &entities, 192, 0, 0, 0, 16, 16));
	/*
	entities.push_back(new EnemyTank(sprite, entities, 240, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 288, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 336, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 384, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 432, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 480, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 528, 0, 0, 0, 16, 16));
	entities.push_back(new EnemyTank(sprite, entities, 576, 0, 0, 0, 16, 16));
	*/


	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.setDirection('l');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.setDirection('r');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.setDirection('u');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.setDirection('d');
			player.update(dt);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			std::cout << entities.size() << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player.getReload()) {
			player.shoot(sprite);
		}

		for (it = entities.begin(); it != entities.end();) {
			Entity *p = *it;
			p->update(dt);
			if (!p->isAlive()) {
				it = entities.erase(it);
				delete p;
			}else {
				it++;
			}
		}

		IntRect lol;

		for (it = entities.begin(); it != entities.end(); it++)
		{
			for (it2 = entities.begin(); it2 != entities.end(); it2++) {
				if ((*it) == (*it2))continue;

				if ((*it)->getRect().intersects((*it2)->getRect(), lol) && (*it)->getName()=="Enemy" && (*it2)->getName()=="Enemy") {

				}
			}
		}

		collisions(&player,lm);

		window.clear();

		for (auto i : lm.tiles) {
			if (i->getLayout() != 1)
				window.draw(*(i->getSprite()));
		}
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw(*(*it)->getSprite());
		}
		window.draw(*player.getSprite());
		for (auto i : lm.tiles) {
			if (i->getLayout() == 1)
				window.draw(*(i->getSprite()));
		}
		window.display();
		
	}

	return 0;
}