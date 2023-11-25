#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
//weapon class
class Weapons{
		public:
	enum WT{BAT,SWORD,SHIELD};

	//default constructor
	Weapons(){

	}

    // public variable
	int weapon_select;
	int enemyselector;

		int damage(){
			switch(type)
			{
				case Weapons::WT::BAT:
				return 10;
				case Weapons::WT::SWORD:
				return 20;
				case Weapons::WT::SHIELD:
				return 0;
			}
		
	}

	WT type;
private:

};


//player class
class Player {
public:
//constructor for player 

      Player(){
		m_health = 100;
		m_weapon = new Weapons();
	  }
	//get health
	int getHealth(){
		return m_health;
	}

	//sets the health 
	void setHealth(int health)
	{
		m_health = health;
	}
	
	//virtual functions that orc and troll have to have 
	virtual void attack(Player*) = 0;
	virtual void arming(Weapons* weapon) =0;

//get weapon function
	Weapons* getWeapon()
	{
       return m_weapon;
	}

//private variables
	private:
	int m_health;

//protected variables
	protected:
	Weapons* m_weapon;
};


#endif