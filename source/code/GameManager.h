#pragma once
#ifndef GAME_H
#define GAME_H
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "leveling.h"
#include <fstream>
#include <string>
#include "entity.h"
#include "collision.h"


using namespace sf;

class Game {
private:
	int health = 0;
public:
	int getHealth() { return health; };
	void setHealth(int hp) { health = hp; };
	void StartGame(RenderWindow &window,int level);
	void Constructor(RenderWindow &window);
	void Quit();
};

#endif