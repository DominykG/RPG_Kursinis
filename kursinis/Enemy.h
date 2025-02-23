#pragma once

#include<string>
#include<sstream>

class Enemy
{
private:
	int level;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int defence;
	float hitRating;
	float critChance;

public:
	Enemy(int level);
	virtual ~Enemy();

	//Funkcjos gavimui private reiksmiu
	inline const int getLevel() const { return this->level; }
	inline const bool isDead() const { return this->hp <= 0; }
	inline const int getHP() const { return this->hp; }
	inline const int getHPMax() const { return this->hpMax; }
	inline const int getDamageMin() const { return this->damageMin; }
	inline const int getDamageMax() const { return this->damageMax; }
	inline const int getDefence() const { return this->defence; }
	inline const int getHitRating() const { return this->hitRating; }

	//Funkcijos
	void takeDamage(const int damage);
	void setDead();
	const std::string toStringStats();
};


