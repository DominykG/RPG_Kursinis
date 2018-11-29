#include "Character.h"

//Private funkcijos
void Character::updateStats()
{
	this->hpMax = this->vitality * 10 + this->vitality;
	this->hp = this->hpMax;
	this->staminaMax = this->vitality * 2;
	this->stamina = this->staminaMax;
	this->manaMax = this->vitality * 10 + this->vitality;
	this->mana = this->manaMax;

	this->damageMin = this->strength * 2;
	this->damageMax = this->strength + this->strength * 2;
	this->defence = this->agility * 2;
	this->hitRating = this->dexterity * 2 + this->dexterity;
	this->critChance = static_cast<float>(this->dexterity) / 60;
	this->magicFind = static_cast<float>(this->intelligence) / 70;
}

const std::string Character::Save_stats()
{
	std::stringstream ss;

	ss << this->name
		<< " " << this->level
		<< " " << this->exp
		<< " " << this->statpoints
		<< std::endl//attributes
		<< " " << this->strength
		<< " " << this->vitality
		<< " " << this->agility
		<< " " << this->dexterity
		<< " " << this->intelligence
		<< std::endl//money
		<< " " << this->gold;

	return ss.str();
}

//Konstruktoriai ir dekonstruktoriai
Character::Character(std::string name)
{
	this->x = 0;
	this->y = 0;

	this->name = name;
	
	this->level = 1;
	this->exp = 0;
	this->expNext = 46;
	this->statpoints = 5;

	this->strength = 1;
	this->vitality = 1;
	this->agility = 1;
	this->dexterity = 1;
	this->intelligence = 1;

	this->gold = 100;

	this->updateStats();

	this->inventory.add(Item("test", 0, 1, 200)); // testinis daiktas inventoriuje

}

Character::~Character()
{

}

//Funkcjos gavimui private reiksmiu
const int Character::getAttribute(const unsigned attribute)
{
	switch (attribute)
	{
	case STRENGTH:
		return this->strength;
		break;
	case VITALITY:
		return this->vitality;
		break;
	case AGILITY:
		return this->agility;
		break;
	case DEXTERITY:
		return this->dexterity;
		break;
	case INTELLIGENCE:
		return this->intelligence;
		break;
	default:
		return -1;
		break;
	}
}

//Funkcijos modifikuoti private reiksmes
void Character::setPosition(const unsigned x, const unsigned y)
{
	this->x = x;
	this->y = y;
}

void Character::move(const int x, const int y)
{
	if (static_cast<int>(this->x) + x < 0)
		this->x = 0;
	else
		this->x += x;

	if (static_cast<int>(this->y) + y < 0)
		this->y = 0;
	else
		this->y += y;
}

//Funkcijos
const std::string Character::flee()
{
	std::stringstream ss;
	int lostExp = rand() % (this->level * 5) + 1;
	int lostGold = rand() % (this->level * 5) + 1;
	ss << " Exp lost: " << lostExp << " | " << " Gold lost: " << lostGold;

	this->exp -= lostExp;;

	if (this->exp < 0)
		this->exp = 0;

	this->gold -= lostGold;

	if (this->gold < 0)
		this->gold = 0;

	return ss.str();
}

void Character::reset()
{
	this->hp = this->hpMax;
	this->stamina = this->staminaMax;
	this->mana = this->manaMax;
}

void Character::takeDamage(const int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
		this->setDead();
		
	
}

void Character::setDead()
{
	this->hp = 0;

	//Pagalvoti gal dar kokiu veiksmu pvz prikelti zaideja 
	this->exp -= rand() % (this->level * 10) + 1;

	if (this->exp < 0)
		this->exp = 0;

	this->gold -= rand() % (this->level * 10) + 1;

	if (this->gold < 0)
		this->gold = 0;
}

bool Character::addExp(const int exp)
{
	bool levelup = false;

	this->exp += exp;

	while (this->exp >= this->expNext)
	{
		this->level++;
		this->exp -= this->expNext;
		this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12);
		this->statpoints++;

		this->strength += this->level % 2;
		this->vitality += this->level % 2;
		this->agility += this->level % 2;
		this->dexterity += this->level % 2;
		this->intelligence += this->level % 2;

		levelup = true;
	}

	this->updateStats();

	return levelup;
}

bool Character::addGold(const int gold)
{
	this->gold += gold;
	return true;
	
}

bool Character::addStatpoint(const int attribute)
{
	if (this->statpoints > 0)
	{
		this->statpoints--;

		switch (attribute)
		{
		case STRENGTH:
			this->strength++;
			break;
		case VITALITY:
			this->vitality++;
			break;
		case AGILITY:
			this->agility++;
			break;
		case DEXTERITY:
			this->dexterity++;
			break;
		case INTELLIGENCE:
			this->intelligence++;
			break;
		default:
			this->statpoints++;
			return false;
			break;
		}

		this->updateStats();

		return true;
	}

	return false;
}

const std::string Character::getMenuBar(const bool show_attributes)
{
	std::stringstream ss;

	int expDone = 10 * (static_cast<float>(this->exp) / this->expNext);
	int expRemain = 10 - expDone;

	ss
		<< std::string(4, ' ') << " | Name: " << this->name << "\n"
		<< std::string(4, ' ') << " | Level: " << this->level << " [" << std::string(expDone, '=') << std::string(expRemain, '-') << "]" << "\n"
		<< std::string(4, ' ') << " | HP: " << this->hp << " / " << this->hpMax << "\n"
		<< std::string(4, ' ') << " | Stamina: " << this->stamina << " / " << this->staminaMax << "\n"
		<< std::string(4, ' ') << " | Stat points available: " << this->statpoints << "\n";

	if (show_attributes)
	{
		ss
			<< "\n"
			<< std::string(4, ' ') << " | Strength: " << this->strength << "\n"
			<< std::string(4, ' ') << " | Vitality: " << this->vitality << "\n"
			<< std::string(4, ' ') << " | Agility: " << this->agility << "\n"
			<< std::string(4, ' ') << " | Dexterity: " << this->dexterity << "\n"
			<< std::string(4, ' ') << " | Intelligence: " << this->intelligence << "\n";
	}

	ss << "\n";

	return ss.str();
}

const std::string Character::toString()
{
	/* Function will format all member variables and
	send them out as a string to be printed.
	*/

	std::stringstream ss;

	ss << " Name: " << this->name << "\n" << "\n"
		<< " Level: " << this->level << "\n"
		<< " Exp: " << this->exp << " / " << this->expNext << "\n"
		<< "\n"

		<< " Strenght: " << this->strength << "\n"
		<< " Vitality: " << this->vitality << "\n"
		<< " Agility: " << this->agility << "\n"
		<< " Dexterity: " << this->dexterity << "\n"
		<< " Intelligence: " << this->intelligence << "\n"
		<< "\n"

		<< " HP: " << this->hp << " / " << this->hpMax << "\n"
		<< " Stamina: " << this->stamina << " / " << this->staminaMax << "\n"
		<< " Mana: " << this->mana << " / " << this->manaMax << "\n"
		<< "\n"

		<< " Damage: " << this->damageMin << " - " << this->damageMax << "\n"
		<< " Defence: " << this->defence << "\n"
		<< " Hit rating: " << this->hitRating << "\n"
		<< " Crit chance: " << this->critChance << "\n"
		<< " Magic find: " << this->magicFind << "\n"
		<< "\n"

		<< " Gold: " << this->gold << "\n"
		<< "\n";

	return ss.str();
}

const std::string Character::toStringPosition()
{
	std::stringstream ss;

	ss << " x: " << this->x << " y: " << this->y << "\n";

	return ss.str();
}

const std::string Character::toStringStats()
{
	std::stringstream ss;

	ss << " Level: " << this->level << "\n"
		<< " Exp: " << this->exp << " / " << this->expNext << "\n"
		<< "\n"

		<< " Strenght: " << this->strength << "\n"
		<< " Vitality: " << this->vitality << "\n"
		<< " Agility: " << this->agility << "\n"
		<< " Dexterity: " << this->dexterity << "\n"
		<< " Intelligence: " << this->intelligence << "\n"
		<< "\n"

		<< " HP: " << this->hp << " / " << this->hpMax << "\n"
		<< " Stamina: " << this->stamina << " / " << this->staminaMax << "\n"
		<< " Mana: " << this->mana << " / " << this->manaMax << "\n"
		<< "\n"

		<< " Damage: " << this->damageMin << " - " << this->damageMax << "\n"
		<< " Defence: " << this->defence << "\n"
		<< " Hit rating: " << this->hitRating << "\n"
		<< " Crit chance: " << this->critChance << "\n"
		<< " Magic find: " << this->magicFind << "\n"
		<< "\n"

		<< " Gold: " << this->gold << "\n"
		<< "\n";

	return ss.str();
}
