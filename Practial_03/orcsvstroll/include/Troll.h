#ifndef TROLL_H
#define TROLL_H

#include <./include/Player.h>


//Troll class but Troll = Player 
class Troll : public Player{
public:
//attack Player/enemy 
	void attack(Player* enemy){
		std::cout << "TROLL IS ATTACKING!!!!" << std::endl;
		int enemyHealth = enemy->getHealth();
	    int damage = m_weapon->damage();
	    enemy->setHealth(enemyHealth - damage);
	}
//arming function 
	void arming(Weapons* weapon){
		m_weapon = weapon;
	}
};


#endif

