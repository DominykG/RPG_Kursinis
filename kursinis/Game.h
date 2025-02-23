#pragma once
#include "MenuStates.h"
#include <fstream>


class Game
{
private:
	//Kintamieji
	bool quit;

	unsigned activeCharacter;
	std::vector<Character*> characterList;
	std::stack<State*> states;

public:
	//Konstruktoriai ir dekonstruktoriai
	Game();
	virtual ~Game();

	//Funkcjos gavimui private reiksmiu
	const bool& getQuit() const;

	//Funkcijos
	void update();
};
