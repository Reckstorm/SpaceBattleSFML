#pragma once
#include "Ship.h"
#include "commandShip.h"
#include "attackShip.h"
#include "defenceShip.h"
#include "supportShip.h"
#include "Weapon.h"
#include "Laser.h"
#include "Missile.h"
#include "Turret.h"
#include "attackLieutenant.h"
#include "commandLieutenant.h"
#include "defenceLieutenant.h"
#include "supportLieutenant.h"
#include <fstream>

using namespace ProtoShip;
using namespace ProtoShip::Ships;
using namespace ProtoWeapon;
using namespace ProtoWeapon::Weapons;
using namespace ProtoCrew;
using namespace ProtoCrew::Lieutenants;
using std::ofstream;
using std::ifstream;

class Fleet final: public vector<Ship>
{
	int money{0};
	int resources{0};
public:
	Fleet() = default;
	Fleet(int i);
	Fleet(RenderWindow& window);
	void setMoney(int i);
	void setResources(int i);
	void makeCommandShip(RenderWindow& window);
	void makeShip(RenderWindow& window);
	void makeWeapon(Ship& ship, RenderWindow& window);
	void makeCrew(Ship& ship, RenderWindow& window);
	void battle(Fleet& fleet);
	void printFleet(RenderWindow& window);
	void printEnemyFleet(RenderWindow& window);
	int getMoney();
	int getResources();
	void printCurrency(RenderWindow& window);
	void insufficientMoney(RenderWindow& window);
	void replaceShip(RenderWindow& window);
	void refillAmmo();
	void repairShips();
	void sellResources();
	void resetPos();
	void save();
};

int* table();
int menuDelay();
bool findDef(Ship& ship);
bool findDead(Ship& ship);
bool findLowAmmo(Ship& ship);
bool findLowHP(Ship& ship);
void load(Fleet& fleet);