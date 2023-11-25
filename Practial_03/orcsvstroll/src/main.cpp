//include strandard libary
#include <iostream>

//include header files
#include <./include/Orc.h>
#include <./include/Troll.h>
#include <./include/Player.h>

using namespace std;

// main function 
int main() {

//random seed 
srand((unsigned)time(0));

//creates instances of player object
Player* player = new Orc();
Player* enemy = new Troll();

//deletes instances
delete player;
delete enemy;

//loads battle field
std::cout << "Loading battle field" << std::endl;


//choose the race 
std::cout << "WHO ARE YOU!!!" << std::endl;
std::cout << "1 | ORC | OR  2 | TROLL |" << std::endl;

int selector;
std::cin >> selector;

//sets the player & enemy either troll or orc 
if(selector == 1)
{
	std::cout << "HMM!! YOUR AN ORC HAHAHAHAH!!" << std::endl;
	Player* player = new Orc();
	Player* enemy = new Troll();
}
else
{
	std::cout << "AAAAA YOUR A TROLL!!" << std::endl;
	Player* player = new Troll();
	Player* enemy = new Orc();
}

//loops while player/enemy health is greater than 0
while (player->getHealth() > 0 || enemy->getHealth() > 0) {

std::cout << "Your Health = " << player->getHealth() << std::endl;
std::cout << "Enemy Health = " << enemy->getHealth() << std::endl;

//weapon select
std::cout << "Select your weapon of choice" << std::endl;
std::cout << "1:|BAT| 2:|SWORD| 3:|SHEILD| " << std::endl;

int weapon_select;
std::cin >> weapon_select;



//weapons select
if(weapon_select == 1)
{
	Weapons* bat = new Weapons();
	player->arming(bat);
	player->attack(enemy);
	
}
if(weapon_select == 2)
{
	Weapons* sword = new Weapons();
	player->arming(sword);
	player->attack(enemy);

}
if(weapon_select == 3)
{
	Weapons* shield = new Weapons();
	player->arming(shield);
	player->attack(enemy);
	
}

//displays enemy health
std::cout << "Enemys Health = " << enemy->getHealth() << std::endl;

//enemy selector randomizer
int enemyselector = (rand() % 4) + 1;

if(enemyselector == 1 )
{
	Weapons* bat = new Weapons();
	enemy->arming(bat);
	enemy->attack(player);
	
}
else if(enemyselector == 2)
{
	Weapons* sword = new Weapons();
	enemy->arming(sword);
	enemy->attack(player);
	
}
else if(enemyselector == 3)
{
	Weapons* shield = new Weapons();
	enemy->arming(shield);
	enemy->attack(player);
	
}
else if (enemyselector == 4 )
{
	std::cout << "The enemy swung and missed HAHAHAHA!!!" << std::endl;
}


//displays players health
std::cout << "Players health = " << enemy->getHealth() << std::endl;


//ending depending on result of battle
if(player->getHealth() <= 0)
{
	std::cout << "GAME OVER YOU LOSE BOZO" << std::endl;
	break;
	
}
if(enemy->getHealth() <= 0)
{
	std::cout << "GAME OVER YOU WON THE BATTLE BUT NOT THE WAR" << std::endl;
	break;
}

}


}
