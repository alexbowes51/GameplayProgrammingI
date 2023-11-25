#include <./include/Player.h>

// Implementation of Character Methods

void Player::flip() { std::cout << "CHARACTER : I know how to flip and I will flipping do it" << std::endl; }
void Player::walk() { std::cout << "CHARACTER : Just in case they are too young to walk yet" << std::endl; }

void Player::Sheild(){
		std::cout << "Sheild!" << std::endl;
	}

void Player::Sword(){
		std::cout << "Sword!" << std::endl;
		int swordDamage = 5;
	}

 void Player::Bat(){
		std::cout << "BAT!" << std::endl;
		int BatDamage = 10;
	}