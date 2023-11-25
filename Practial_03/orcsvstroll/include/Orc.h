#ifndef ORC_H
#define ORC_H

#include <./include/Player.h>

//orc class but Orc = player 
class Orc : public Player{

public:

//attacks the enemy/ player
void attack(Player* enemy){
	std::cout << "ORC IS ATTACKING!!!" << std::endl;
	int enemyHealth = enemy->getHealth();
	int damage = m_weapon->damage();
	enemy->setHealth(enemyHealth - damage);
}

//Arms the enemy with the weapon 
void arming(Weapons* weapon)
{
	m_weapon = weapon;
}

};

#endif